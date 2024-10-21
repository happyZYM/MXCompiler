#pragma once
#include <cstddef>
#include "IR/IR_basic.h"
#include "cfg.h"
class ConfGraphNode {
 public:
  const static size_t kInf = (std::numeric_limits<size_t>::max()) >> 2;
  std::list<size_t> var_ids;
  size_t color;
  size_t degree;
  bool is_binded_with_physical_reg;
  std::list<ConfGraphNode *> neighbors;

  // the following are for graph maintenance
  ConfGraphNode *is_merged_into;
  static ConfGraphNode *FindFather(ConfGraphNode *x) {
    if (x->is_merged_into == x) return x;
    return x->is_merged_into = FindFather(x->is_merged_into);
  }
  bool is_temporarily_removed;
  std::list<ConfGraphNode *> neighbors_half_available;
  std::list<ConfGraphNode *> neighbors_not_available;
  std::list<std::pair<ConfGraphNode *, opt::MoveInstruct *>> original_move_neighbors;
};
class ConfGraph {
 public:
  // available after construction
  std::unordered_map<size_t, ConfGraphNode *> id_to_node;
  std::vector<std::shared_ptr<ConfGraphNode>> nodes;
  std::unordered_map<ConfGraphNode *, std::unordered_map<ConfGraphNode *, std::list<ConfGraphNode *>::iterator>>
      adj_table;

  // available during coloring
  std::vector<ConfGraphNode *> stack;
  std::vector<ConfGraphNode *> actual_spills;
  std::unordered_set<ConfGraphNode *> low_degree_and_not_move_related;
  std::unordered_set<ConfGraphNode *> low_degree_and_move_related;
  std::unordered_set<ConfGraphNode *> high_degree_nodes;
  std::unordered_set<opt::MoveInstruct *> pending_moves;

  std::unordered_set<opt::MoveInstruct *> potential_moves;
  std::unordered_map<ConfGraphNode *, std::unordered_map<ConfGraphNode *, std::list<ConfGraphNode *>::iterator>>
      adj_table_half_available;
  std::unordered_map<ConfGraphNode *, std::unordered_map<ConfGraphNode *, std::list<ConfGraphNode *>::iterator>>
      adj_table_not_available;
  void init() {
    id_to_node.clear();
    nodes.clear();
    adj_table.clear();
    stack.clear();
    actual_spills.clear();
    low_degree_and_not_move_related.clear();
    low_degree_and_move_related.clear();
    high_degree_nodes.clear();
    pending_moves.clear();
    potential_moves.clear();
    adj_table_half_available.clear();
    adj_table_not_available.clear();
  }
};

ConfGraph BuildConfGraph(CFGType &cfg);
bool ConductColoring(std::shared_ptr<FunctionDefItem> src, CFGType &cfg, ConfGraph &confgraph);