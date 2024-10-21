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
  // successors, predecessors, corresponding_block is provided by BuildCFGForFunction
  std::vector<CFGNodeType *> successors, predecessors;
  BlockItem *corresponding_block;
  // the following fields are provided by user
  CFGNodeCollection dom;
  bool visited;
  CFGNodeType *idom;
  std::vector<CFGNodeType *> successors_in_dom_tree;
  CFGNodeCollection dom_frontier;

  std::vector<size_t> block_in_active_vars;
  std::vector<size_t> block_out_active_vars;
  std::vector<size_t> block_use_vars;
  std::vector<size_t> block_def_vars;

  std::unordered_map<ActionItem *, std::vector<size_t>> action_use_vars;
  std::unordered_map<ActionItem *, std::vector<size_t>> action_def_vars;
  std::unordered_map<ActionItem *, std::vector<size_t>> action_in_active_vars;
  std::unordered_map<ActionItem *, std::vector<size_t>> action_out_active_vars;
};

class CFGType {
 public:
  std::vector<std::shared_ptr<CFGNodeType>> nodes;
  CFGNodeType *entry;
  std::unordered_map<BlockItem *, CFGNodeType *> block_to_node;
  std::unordered_map<std::string, BlockItem *> label_to_block;
  std::vector<std::string> id_to_var;
  std::unordered_map<std::string, size_t> var_to_id;
  FunctionDefItem *corresponding_func;
};

namespace opt {
class MoveInstruct : public ActionItem {
 public:
  std::string src_full;
  std::string dest_full;
  LLVMType ty;
  MoveInstruct() = default;
  void RecursivePrint([[maybe_unused]] std::ostream &os) const {
    throw std::runtime_error("Move instruction is not an actual LLVM IR instruction");
  }
};
}  // namespace opt

template <typename Container, typename Compare = std::less<typename Container::value_type>>
Container GetCollectionsIntersection(const Container &a, const Container &b, Compare comp = Compare()) {
  Container result;
  auto ita = a.begin();
  auto itb = b.begin();

  while (ita != a.end() && itb != b.end()) {
    if (comp(*ita, *itb)) {
      ++ita;
    } else if (comp(*itb, *ita)) {
      ++itb;
    } else {
      result.push_back(*ita);
      ++ita;
      ++itb;
    }
  }

  return result;
}

template <typename Container, typename Compare = std::less<typename Container::value_type>>
Container GetCollectionsUnion(const Container &a, const Container &b, Compare comp = Compare()) {
  Container result;
  auto ita = a.begin();
  auto itb = b.begin();

  while (ita != a.end() && itb != b.end()) {
    if (comp(*ita, *itb)) {
      result.push_back(*ita);
      ++ita;
    } else if (comp(*itb, *ita)) {
      result.push_back(*itb);
      ++itb;
    } else {
      result.push_back(*ita);
      ++ita;
      ++itb;
    }
  }

  while (ita != a.end()) {
    result.push_back(*ita);
    ++ita;
  }

  while (itb != b.end()) {
    result.push_back(*itb);
    ++itb;
  }

  return result;
}

template <typename Container, typename Compare = std::less<typename Container::value_type>>
Container GetCollectionsDifference(const Container &a, const Container &b, Compare comp = Compare()) {
  Container result;
  auto ita = a.begin();
  auto itb = b.begin();

  while (ita != a.end() && itb != b.end()) {
    if (comp(*ita, *itb)) {
      result.push_back(*ita);
      ++ita;
    } else if (comp(*itb, *ita)) {
      ++itb;
    } else {
      ++ita;
      ++itb;
    }
  }

  while (ita != a.end()) {
    result.push_back(*ita);
    ++ita;
  }

  return result;
}

template <typename Container, typename Compare = std::less<typename Container::value_type>>
bool GetCollectionsIsSame(const Container &a, const Container &b, Compare comp = Compare()) {
  auto ita = a.begin();
  auto itb = b.begin();

  while (ita != a.end() && itb != b.end()) {
    if (comp(*ita, *itb) || comp(*itb, *ita)) {
      return false;
    }
    ++ita;
    ++itb;
  }

  return ita == a.end() && itb == b.end();
}

CFGType BuildCFGForFunction(const std::shared_ptr<FunctionDefItem> &func);

// RISC-V calling convention compatible
const static std::vector<std::string> held_tmp_regs = {"x28", "x29", "x30", "x31"};
const static std::string zero = "x0", sp = "x2", ra = "x1", fp = "x8";
const static std::vector<std::string> callee_saved_regs = {"x3",  "x4",  "x9",  "x18", "x19", "x20", "x21",
                                                           "x22", "x23", "x24", "x25", "x26", "x27"};
const static std::vector<std::string> caller_saved_regs = {"x5",  "x6",  "x7",  "x10", "x11", "x12",
                                                           "x13", "x14", "x15", "x16", "x17"};
const static std::vector<std::string> arg_regs = {"x10", "x11", "x12", "x13", "x14", "x15", "x16", "x17"};
const static std::vector<std::string> allocating_regs = {"x3",  "x4",  "x9",  "x18", "x19", "x20", "x21", "x22",
                                                         "x23", "x24", "x25", "x26", "x27", "x5",  "x6",  "x7",
                                                         "x10", "x11", "x12", "x13", "x14", "x15", "x16", "x17"};