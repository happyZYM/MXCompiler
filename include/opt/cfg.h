#pragma once
#include <deque>
#include <list>
#include <memory>
#include <unordered_map>
#include <vector>
#include "IR/IR_basic.h"
using CFGNodeCollection = std::list<class CFGNodeType *>;
class CFGNodeType {
 public:
  std::vector<CFGNodeType *> successors, predecessors;
  BlockItem *corresponding_block;
  CFGNodeCollection dom;
  CFGNodeType *idom;
  std::vector<CFGNodeType *> successors_in_dom_tree;
  CFGNodeCollection dom_frontier;
};

class CFGType {
 public:
  std::vector<std::shared_ptr<CFGNodeType>> nodes;
  CFGNodeType *entry;
  std::unordered_map<BlockItem *, CFGNodeType *> block_to_node;
  std::unordered_map<std::string, BlockItem *> label_to_block;
};

CFGNodeCollection GetCFGNodeCollectionsIntersection(const CFGNodeCollection &a, const CFGNodeCollection &b);
CFGNodeCollection GetCFGNodeCollectionsUnion(const CFGNodeCollection &a, const CFGNodeCollection &b);
CFGNodeCollection GetCFGNodeCollectionsDifference(const CFGNodeCollection &a, const CFGNodeCollection &b);

CFGType BuildCFGForFunction(const std::shared_ptr<FunctionDefItem> &func);