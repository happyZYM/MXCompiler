#pragma once
#include "IR/IR_basic.h"
#include "cfg.h"
class ConfGraphNode {
 public:
  const static size_t kInf = (std::numeric_limits<size_t>::max()) >> 2;
  std::vector<size_t> var_ids;
  size_t color;
  size_t degree;
  bool is_binded_with_physical_reg;
  std::list<ConfGraphNode *> neighbors;
  std::list<opt::MoveInstruct *> move_neighbors;
  ConfGraphNode() = default;
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
};

ConfGraph BuildConfGraph(CFGType &cfg);
bool ConductColoring(std::shared_ptr<FunctionDefItem> src, CFGType &cfg, ConfGraph &confgraph);