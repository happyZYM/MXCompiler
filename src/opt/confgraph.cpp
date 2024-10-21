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
    res.id_to_node[reg_id]->degree = ConfGraphNode::kInf;
  }
  for (auto cfg_node : cfg.nodes) {
    auto block = cfg_node->corresponding_block;
    for (auto act : block->actions) {
      if (auto move_act = std::dynamic_pointer_cast<opt::MoveInstruct>(act)) {
        size_t src_id = cfg.var_to_id[move_act->src_full];
        size_t dest_id = cfg.var_to_id[move_act->dest_full];
        res.id_to_node[src_id]->move_neighbors.push_back({res.id_to_node[dest_id], move_act.get()});
        res.id_to_node[dest_id]->move_neighbors.push_back({res.id_to_node[src_id], move_act.get()});
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
    for (auto [move_neighbor, move] : confg_node->move_neighbors) {
      if (confgraph.adj_table[confg_node.get()].find(move_neighbor) == confgraph.adj_table[confg_node.get()].end()) {
        if (confg_node->degree < kMaxRegs && move_neighbor->degree < kMaxRegs) {
          confgraph.pending_moves.insert(move);
        } else if (confg_node->is_binded_with_physical_reg || move_neighbor->is_binded_with_physical_reg) {
          if (confg_node->is_binded_with_physical_reg && move_neighbor->is_binded_with_physical_reg)
            throw std::runtime_error(
                "something strange happened: at the beginning two physical registers are directly move related");
          confgraph.pending_moves.insert(move);
        } else {
          confgraph.potential_moves.insert(move);
        }
      } else {
        // do nothing
      }
    }
    if (confg_node->degree < kMaxRegs) {
      if (confg_node->move_neighbors.size() == 0) {
        confgraph.low_degree_and_not_move_related.insert(confg_node.get());
      } else {
        confgraph.low_degree_and_move_related.insert(confg_node.get());
      }
    } else if (!confg_node->is_binded_with_physical_reg) {
      confgraph.high_degree_nodes.insert(confg_node.get());
    }
  }
}

void DetachNode(ConfGraphNode *node, ConfGraph &confgraph, bool during_selecting = false) {
  // this function operates on the conflict graph, temporarily remove the node from the graph, it do nothing on the move
  // link graph although they share the same node set
  // It is also responsible for maintaining all the changes caused by the removal of the node
}

void JoinNode(ConfGraphNode *node, ConfGraph &confgraph, bool during_selecting = false) {
  // this function operates on the conflict graph, temporarily remove the node from the graph, it do nothing on the move
  // link graph although they share the same node set
  // It is also responsible for maintaining all the changes caused by the removal of the node
}

void MergeNodeInto(ConfGraphNode *node, ConfGraphNode *target, ConfGraph &confgraph) {
  // this function operates on both the conflict graph and the move link graph, and the effect is permanent
  // It is also responsible for maintaining all the changes caused by the merge of the node
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
  auto dest_node = confgraph.id_to_node[dest_id];
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
      confgraph.pending_moves.insert(move);
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
      confgraph.pending_moves.insert(move);
    }
  }
}

void Freeze(std::shared_ptr<FunctionDefItem> src, CFGType &cfg, ConfGraph &confgraph) {
  auto u = *confgraph.low_degree_and_move_related.begin();
  confgraph.low_degree_and_move_related.erase(u);
  confgraph.low_degree_and_not_move_related.insert(u);
  for (auto [_, ins] : u->move_neighbors) {
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
  InitializeBeforeColoring(src, cfg, confgraph);
  do {
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
  if (confgraph.actual_spills.size() > 0) {
    std::cerr << "spilled " << confgraph.actual_spills.size() << " nodes" << std::endl;
    // allocate memory for spilled nodes
    // rewrite the spilled nodes
    return true;
  }
  return false;
}