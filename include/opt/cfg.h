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

  std::vector<size_t> in_active_vars;
  std::vector<size_t> out_active_vars;
  std::vector<size_t> use_vars;
  std::vector<size_t> def_vars;
};

class CFGType {
 public:
  std::vector<std::shared_ptr<CFGNodeType>> nodes;
  CFGNodeType *entry;
  std::unordered_map<BlockItem *, CFGNodeType *> block_to_node;
  std::unordered_map<std::string, BlockItem *> label_to_block;
};

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