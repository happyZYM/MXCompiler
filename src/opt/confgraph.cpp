#include "confgraph.h"
#include <cstdint>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "cfg.h"
ConfGraph BuildConfGraph(CFGType &cfg) {
  std::unordered_map<ConfGraphNode *, std::unordered_set<ConfGraphNode *>> edges;
  ConfGraph res;
  for (size_t id = 0; id < cfg.id_to_var.size(); id++) {
    auto node = std::make_shared<ConfGraphNode>();
    node->var_ids.push_back(id);
    res.id_to_node[id] = node.get();
    res.nodes.push_back(node);
    node->is_binded_with_physical_reg = false;
    node->is_merged_into = node.get();  // the same as `fa` in DSU
    node->is_temporarily_removed = false;
  }
  for (auto cfg_node : cfg.nodes) {
    for (const auto &[act, out_active] : cfg_node->action_out_active_vars) {
      const auto &def_vars = cfg_node->action_def_vars[act];
      for (auto def_var : def_vars) {
        for (auto out_var : out_active) {
          edges[res.id_to_node[def_var]].insert(res.id_to_node[out_var]);
          edges[res.id_to_node[out_var]].insert(res.id_to_node[def_var]);
        }
      }
    }
  }
  for (const auto &[u, neighbors] : edges) {
    for (auto v : neighbors) {
      if (u == v) continue;
      u->neighbors.push_back(v);
      res.adj_table[u][v] = std::prev(u->neighbors.end());
    }
    u->neighbors.sort();
  }
  for (auto node : res.nodes) {
    node->degree = node->neighbors.size();
  }
  for (auto reg : allocating_regs) {
    size_t reg_id = cfg.var_to_id["%reg." + reg];
    res.id_to_node[reg_id]->is_binded_with_physical_reg = true;
    res.id_to_node[reg_id]->color = std::stoi(reg.substr(1));
    std::cerr << "coloring node whith id=" << reg_id << " with color=" << res.id_to_node[reg_id]->color << std::endl;
    res.id_to_node[reg_id]->degree = ConfGraphNode::kInf;
  }
  for (auto cfg_node : cfg.nodes) {
    auto block = cfg_node->corresponding_block;
    for (auto act : block->actions) {
      if (auto move_act = std::dynamic_pointer_cast<opt::MoveInstruct>(act)) {
        if (!VRegCheck(move_act->src_full)) continue;
        if (cfg.var_to_id.find(move_act->src_full) == cfg.var_to_id.end()) {
          move_act->RecursivePrint(std::cerr);
          std::cerr << std::endl;
          throw std::runtime_error("move_act->src_full not found in var_to_id");
        }
        if (cfg.var_to_id.find(move_act->dest_full) == cfg.var_to_id.end()) {
          throw std::runtime_error("move_act->dest_full not found in var_to_id");
        }
        size_t src_id = cfg.var_to_id[move_act->src_full];
        size_t dest_id = cfg.var_to_id[move_act->dest_full];
        res.id_to_node[src_id]->original_move_neighbors.push_back({res.id_to_node[dest_id], move_act.get()});
        res.id_to_node[dest_id]->original_move_neighbors.push_back({res.id_to_node[src_id], move_act.get()});
      }
    }
  }
  return res;
}
const static size_t kMaxRegs = allocating_regs.size();
void InitializeBeforeColoring([[maybe_unused]] std::shared_ptr<FunctionDefItem> src, [[maybe_unused]] CFGType &cfg,
                              ConfGraph &confgraph) {
  confgraph.stack.clear();
  confgraph.actual_spills.clear();

  confgraph.low_degree_and_not_move_related.clear();
  confgraph.low_degree_and_move_related.clear();
  confgraph.high_degree_nodes.clear();  // note that physical registers are not included in this set

  confgraph.pending_moves.clear();
  confgraph.potential_moves.clear();
  for (auto confg_node : confgraph.nodes) {
    for (auto [move_neighbor, move] : confg_node->original_move_neighbors) {
      if (confgraph.adj_table[confg_node.get()].find(move_neighbor) == confgraph.adj_table[confg_node.get()].end()) {
        if (confg_node->degree < kMaxRegs && move_neighbor->degree < kMaxRegs) {
          confgraph.pending_moves.insert(move);
        } else if (confg_node->is_binded_with_physical_reg || move_neighbor->is_binded_with_physical_reg) {
          if (confg_node->is_binded_with_physical_reg && move_neighbor->is_binded_with_physical_reg) {
            std::cerr << confg_node->var_ids.front() << " " << move_neighbor->var_ids.front() << std::endl;
            std::cerr << confg_node->color << " " << move_neighbor->color << std::endl;
            move->RecursivePrint(std::cerr);
            std::cerr << std::endl;
            throw std::runtime_error(
                "something strange happened: at the beginning two physical registers are directly move related");
          }
          confgraph.pending_moves.insert(move);
        } else {
          confgraph.potential_moves.insert(move);
        }
      } else {
        // do nothing
      }
    }
    if (confg_node->degree < kMaxRegs) {
      if (confg_node->original_move_neighbors.size() == 0) {
        confgraph.low_degree_and_not_move_related.insert(confg_node.get());
      } else {
        confgraph.low_degree_and_move_related.insert(confg_node.get());
      }
    } else if (!confg_node->is_binded_with_physical_reg) {
      confgraph.high_degree_nodes.insert(confg_node.get());
    }
  }
}

void DetachNode(ConfGraphNode *node, ConfGraph &confgraph) {
  // this function operates on the conflict graph, temporarily remove the node from the graph, it do nothing on the move
  // link graph although they share the same node set
  // It is also responsible for maintaining all the changes caused by the removal of the node
  if (node->is_temporarily_removed)
    throw std::runtime_error("something strange happened: a temporarily removed node is removed");
  node->is_temporarily_removed = true;
  if (node->is_binded_with_physical_reg)
    throw std::runtime_error("something strange happened: a physical register is removed");
  std::cerr << "detaching node containing var ids:";
  for (auto id : node->var_ids) {
    std::cerr << id << " ";
  }
  std::cerr << std::endl;
  for (auto neighbor : node->neighbors_half_available) {
    neighbor->neighbors_half_available.erase(confgraph.adj_table_half_available[neighbor][node]);
    confgraph.adj_table_half_available[neighbor].erase(node);
    // node->neighbors_half_available.erase(confgraph.adj_table_half_available[node][neighbor]);
    confgraph.adj_table_half_available[node].erase(neighbor);
    neighbor->neighbors_not_available.push_back(node);
    confgraph.adj_table_not_available[neighbor][node] = std::prev(neighbor->neighbors_not_available.end());
    node->neighbors_not_available.push_back(neighbor);
    confgraph.adj_table_not_available[node][neighbor] = std::prev(node->neighbors_not_available.end());
  }
  node->neighbors_half_available.clear();
  for (auto neighbor : node->neighbors) {
    if (neighbor == node) throw std::runtime_error("something strange happened: a node is its own neighbor");
    neighbor->neighbors.erase(confgraph.adj_table[neighbor][node]);
    confgraph.adj_table[neighbor].erase(node);
    neighbor->degree = neighbor->neighbors.size();

    confgraph.low_degree_and_not_move_related.erase(neighbor);
    confgraph.low_degree_and_move_related.erase(neighbor);
    confgraph.high_degree_nodes.erase(neighbor);
    if (!neighbor->is_binded_with_physical_reg) {
      if (neighbor->degree >= kMaxRegs) {
        confgraph.high_degree_nodes.insert(neighbor);
      } else {
        confgraph.low_degree_and_move_related.insert(neighbor);  // it may be wrong, but it is safe
      }
    }

    // node->neighbors.erase(confgraph.adj_table[node][neighbor]);
    confgraph.adj_table[node].erase(neighbor);
    neighbor->neighbors_half_available.push_back(node);
    confgraph.adj_table_half_available[neighbor][node] = std::prev(neighbor->neighbors_half_available.end());
    node->neighbors_half_available.push_back(neighbor);
    confgraph.adj_table_half_available[node][neighbor] = std::prev(node->neighbors_half_available.end());
  }
  node->neighbors.clear();
}

void JoinNode(ConfGraphNode *node, ConfGraph &confgraph) {
  // this function operates on the conflict graph, temporarily remove the node from the graph, it do nothing on the move
  // link graph although they share the same node set
  // It is also responsible for maintaining all the changes caused by the removal of the node
}

void MergeNodeInto(ConfGraphNode *node, ConfGraphNode *target, ConfGraph &confgraph) {
  // this function operates on both the conflict graph and the move link graph, and the effect is permanent
  // It is also responsible for maintaining all the changes caused by the merge of the node
  if (node->is_temporarily_removed)
    throw std::runtime_error("something strange happened: a temporarily removed node is merged");
  std::cerr << "node ids:";
  for (auto id : node->var_ids) {
    std::cerr << id << " ";
  }
  std::cerr << std::endl;
  std::cerr << "target ids:";
  for (auto id : target->var_ids) {
    std::cerr << id << " ";
  }
  std::cerr << std::endl;
  confgraph.low_degree_and_move_related.erase(node);
  confgraph.low_degree_and_not_move_related.erase(node);
  confgraph.high_degree_nodes.erase(node);
  node->is_merged_into = target;
  target->var_ids.splice(target->var_ids.end(), node->var_ids);
  for (auto neighbor : node->neighbors) {
    if (neighbor == target) continue;
    if (confgraph.adj_table[target].find(neighbor) == confgraph.adj_table[target].end()) {
      target->neighbors.push_back(neighbor);
      confgraph.adj_table[target][neighbor] = std::prev(target->neighbors.end());
      neighbor->neighbors.push_back(target);
      confgraph.adj_table[neighbor][target] = std::prev(neighbor->neighbors.end());
    }
    neighbor->neighbors.erase(confgraph.adj_table[neighbor][node]);
    // node->neighbors.erase(confgraph.adj_table[node][neighbor]);
    confgraph.adj_table[neighbor].erase(node);
    confgraph.adj_table[node].erase(neighbor);
    neighbor->degree = neighbor->neighbors.size();
    confgraph.low_degree_and_not_move_related.erase(neighbor);
    confgraph.low_degree_and_move_related.erase(neighbor);
    confgraph.high_degree_nodes.erase(neighbor);
    if (!neighbor->is_binded_with_physical_reg) {
      if (neighbor->degree >= kMaxRegs) {
        confgraph.high_degree_nodes.insert(neighbor);
      } else {
        confgraph.low_degree_and_move_related.insert(neighbor);  // it may be wrong, but it is safe
      }
    }
  }
  node->neighbors.clear();
  for (auto neighbor : node->neighbors_half_available) {
    if (neighbor == target) continue;
    if (confgraph.adj_table_half_available[target].find(neighbor) == confgraph.adj_table_half_available[target].end()) {
      target->neighbors_half_available.push_back(neighbor);
      confgraph.adj_table_half_available[target][neighbor] = std::prev(target->neighbors_half_available.end());
      neighbor->neighbors_half_available.push_back(target);
      confgraph.adj_table_half_available[neighbor][target] = std::prev(neighbor->neighbors_half_available.end());
    }
    neighbor->neighbors_half_available.erase(confgraph.adj_table_half_available[neighbor][node]);
    // node->neighbors_half_available.erase(confgraph.adj_table_half_available[node][neighbor]);
    confgraph.adj_table_half_available[neighbor].erase(node);
    confgraph.adj_table_half_available[node].erase(neighbor);
  }
  node->neighbors_half_available.clear();
  if (node->neighbors_not_available.size() > 0) {
    throw std::runtime_error(
        "something strange happened: neighbors_not_available is not empty in function MergeNodeInto");
  }
  target->degree = target->neighbors.size();
  if (!target->is_binded_with_physical_reg) {
    if (target->degree >= kMaxRegs) {
      confgraph.high_degree_nodes.insert(target);
    } else {
      confgraph.low_degree_and_move_related.insert(target);  // it may be wrong, but it is safe
    }
  }
}

void Simplify(std::shared_ptr<FunctionDefItem> src, CFGType &cfg, ConfGraph &confgraph) {
  auto u = *(confgraph.low_degree_and_not_move_related.begin());
  confgraph.low_degree_and_not_move_related.erase(u);
  DetachNode(u, confgraph);
  confgraph.stack.push_back(u);
}

void Coalesce(std::shared_ptr<FunctionDefItem> src, CFGType &cfg, ConfGraph &confgraph) {
  auto move = *(confgraph.pending_moves.begin());
  confgraph.pending_moves.erase(move);
  size_t src_id = cfg.var_to_id[move->src_full];
  size_t dest_id = cfg.var_to_id[move->dest_full];
  auto src_node = confgraph.id_to_node[src_id];
  src_node = ConfGraphNode::FindFather(src_node);
  auto dest_node = confgraph.id_to_node[dest_id];
  dest_node = ConfGraphNode::FindFather(dest_node);
  if (src_node == dest_node) {
    return;
  }
  if (confgraph.adj_table[src_node].find(dest_node) != confgraph.adj_table[src_node].end()) {
    // no need to update low_degree_and_move_related, when confgraph.pending_moves.size()==0, nodes in
    // low_degree_and_move_related will automatically be moved to low_degree_and_not_move_related
    return;
  }
  if (src_node->is_binded_with_physical_reg && dest_node->is_binded_with_physical_reg)
    throw std::runtime_error("something strange happened: two physical registers do not conflict");
  if (src_node->is_binded_with_physical_reg || dest_node->is_binded_with_physical_reg) {
    // George condition
    if (src_node->is_binded_with_physical_reg) {
      std::swap(src_node, dest_node);
    }
    bool condition_satisfied = true;
    for (auto t : src_node->neighbors) {
      if (t->degree >= kMaxRegs && confgraph.adj_table[t].find(dest_node) == confgraph.adj_table[t].end()) {
        condition_satisfied = false;
        break;
      }
    }
    if (condition_satisfied) {
      MergeNodeInto(src_node, dest_node, confgraph);
    } else {
      confgraph.potential_moves.insert(move);
    }
  } else {
    // Briggs condition
    std::unordered_set<ConfGraphNode *> dangerous_neighbors;
    for (auto t : src_node->neighbors) {
      if (t != dest_node && t->degree >= kMaxRegs) {
        dangerous_neighbors.insert(t);
      }
    }
    for (auto t : dest_node->neighbors) {
      if (t != src_node && t->degree >= kMaxRegs) {
        dangerous_neighbors.insert(t);
      }
    }
    if (dangerous_neighbors.size() < kMaxRegs) {
      MergeNodeInto(src_node, dest_node, confgraph);
    } else {
      confgraph.potential_moves.insert(move);
    }
  }
}

void Freeze(std::shared_ptr<FunctionDefItem> src, CFGType &cfg, ConfGraph &confgraph) {
  auto u = *confgraph.low_degree_and_move_related.begin();
  confgraph.low_degree_and_move_related.erase(u);
  confgraph.low_degree_and_not_move_related.insert(u);
  for (auto [_, ins] : u->original_move_neighbors) {
    confgraph.potential_moves.erase(ins);
  }
}

void PotentailSpill(std::shared_ptr<FunctionDefItem> src, CFGType &cfg, ConfGraph &confgraph) {
  auto u = *confgraph.high_degree_nodes.begin();
  confgraph.high_degree_nodes.erase(u);
  DetachNode(u, confgraph);
  confgraph.stack.push_back(u);
}
bool ConductColoring(std::shared_ptr<FunctionDefItem> src, CFGType &cfg, ConfGraph &confgraph) {
  if (cfg.id_to_var.size() != cfg.var_to_id.size()) {
    throw std::runtime_error("something strange happened: id_to_var and var_to_id do not match");
  }
  for (size_t i = 0; i < cfg.id_to_var.size(); i++) {
    std::cerr << "id=" << i << " var=" << cfg.id_to_var[i] << std::endl;
    if (i != cfg.var_to_id[cfg.id_to_var[i]]) {
      throw std::runtime_error("something strange happened: id_to_var and var_to_id do not match");
    }
  }
  if (cfg.id_to_var.size() != confgraph.nodes.size()) {
    throw std::runtime_error("something strange happened: id_to_var and confgraph.nodes do not match");
  }
  if (cfg.id_to_var.size() != confgraph.id_to_node.size()) {
    throw std::runtime_error("something strange happened: id_to_var and confgraph.nodes do not match");
  }
  for (size_t i = 0; i < cfg.id_to_var.size(); i++) {
    if (confgraph.id_to_node[i]->var_ids.size() != 1)
      throw std::runtime_error("something strange happened: id_to_node.size()!=1");
    if (confgraph.id_to_node[i]->var_ids.front() != i)
      throw std::runtime_error("something strange happened: id_to_node[0]!=i");
  }
  InitializeBeforeColoring(src, cfg, confgraph);
  do {
    // std::cerr << std::endl;
    // std::cerr << "confgraph.low_degree_and_not_move_related.size()=" <<
    // confgraph.low_degree_and_not_move_related.size()
    //           << std::endl;
    // std::cerr << "confgraph.pending_moves.size()=" << confgraph.pending_moves.size() << std::endl;
    // std::cerr << "confgraph.low_degree_and_move_related.size()=" << confgraph.low_degree_and_move_related.size()
    //           << std::endl;
    // std::cerr << "confgraph.high_degree_nodes.size()=" << confgraph.high_degree_nodes.size() << std::endl;
    for (auto node : confgraph.low_degree_and_not_move_related) {
      if (node->is_binded_with_physical_reg) {
        throw std::runtime_error("something strange happened: node is binded with physical reg");
      }
    }
    for (auto node : confgraph.low_degree_and_move_related) {
      if (node->is_binded_with_physical_reg) {
        throw std::runtime_error("something strange happened: node is binded with physical reg");
      }
    }
    for (auto node : confgraph.high_degree_nodes) {
      if (node->is_binded_with_physical_reg) {
        throw std::runtime_error("something strange happened: node is binded with physical reg");
      }
    }
    if (confgraph.low_degree_and_not_move_related.size() > 0) {
      Simplify(src, cfg, confgraph);
    } else if (confgraph.pending_moves.size() > 0) {
      Coalesce(src, cfg, confgraph);
    } else if (confgraph.low_degree_and_move_related.size() > 0) {
      Freeze(src, cfg, confgraph);
    } else if (confgraph.high_degree_nodes.size() > 0) {
      PotentailSpill(src, cfg, confgraph);
    }
  } while (confgraph.low_degree_and_not_move_related.size() > 0 || confgraph.pending_moves.size() > 0 ||
           confgraph.low_degree_and_move_related.size() > 0 || confgraph.high_degree_nodes.size() > 0);
  // select and spill
  return false;
  if (confgraph.actual_spills.size() > 0) {
    std::cerr << "spilled " << confgraph.actual_spills.size() << " nodes" << std::endl;
    // allocate memory for spilled nodes
    // rewrite the spilled nodes
    return true;
  }
  return false;
}