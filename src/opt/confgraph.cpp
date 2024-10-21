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
  return res;
}
const static size_t kMaxRegs = allocating_regs.size();
void InitializeBeforeColoring(std::shared_ptr<FunctionDefItem> src, CFGType &cfg, ConfGraph &confgraph) {
  confgraph.stack.clear();
  confgraph.actual_spills.clear();

  confgraph.low_degree_and_not_move_related.clear();
  confgraph.low_degree_and_move_related.clear();
  confgraph.high_degree_nodes.clear();  // note that physical registers are not included in this set

  confgraph.pending_moves.clear();
  confgraph.potential_moves.clear();
}
bool ConductColoring(std::shared_ptr<FunctionDefItem> src, CFGType &cfg, ConfGraph &confgraph) {
  InitializeBeforeColoring(src, cfg, confgraph);
  do {
    if (confgraph.low_degree_and_not_move_related.size() > 0) {
      // simplify
    } else if (confgraph.pending_moves.size() > 0) {
      // coalesce
    } else if (confgraph.low_degree_and_move_related.size() > 0) {
      // freeze
    } else if (confgraph.high_degree_nodes.size() > 0) {
      // potential spill
    }
  } while (confgraph.low_degree_and_not_move_related.size() > 0 || confgraph.pending_moves.size() > 0 ||
           confgraph.low_degree_and_move_related.size() > 0 || confgraph.high_degree_nodes.size() > 0);
  // select and spill
  if (confgraph.actual_spills.size() > 0) {
    std::cerr << "spilled " << confgraph.actual_spills.size() << " nodes" << std::endl;
    // allocate memory for spilled nodes
    return true;
  }
  return false;
}