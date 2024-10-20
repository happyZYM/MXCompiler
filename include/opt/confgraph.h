#pragma once
#include "IR/IR_basic.h"
#include "cfg.h"
class ConfGraphNode {
 public:
  std::string var_name;
  size_t color;
  bool is_move_related;
  bool move_related_but_frozen;
  bool is_binded_with_physical_reg;
  std::vector<ConfGraphNode *> neighbors;
  ConfGraphNode(std::string var_name) : var_name(var_name) {}
};
class ConfGraph {
 public:
  std::unordered_map<std::string, ConfGraphNode *> name_to_node;
  std::vector<std::shared_ptr<ConfGraphNode>> nodes;
};

ConfGraph BuildConfGraph(CFGType &cfg);
bool TryColoring(std::shared_ptr<FunctionDefItem> src, CFGType &cfg, ConfGraph& confgraph);