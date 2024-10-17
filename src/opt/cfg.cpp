#include "cfg.h"
#include <string>
CFGNodeCollection GetCFGNodeCollectionsIntersection(const CFGNodeCollection &a, const CFGNodeCollection &b) {
  // assume that thety are both sorted
  CFGNodeCollection res;
  auto ita = a.begin();
  auto itb = b.begin();
  while (ita != a.end() && itb != b.end()) {
    if (*ita == *itb) {
      res.push_back(*ita);
      ita++;
      itb++;
    } else if (*ita < *itb) {
      ita++;
    } else {
      itb++;
    }
  }
  return res;
}

CFGNodeCollection GetCFGNodeCollectionsUnion(const CFGNodeCollection &a, const CFGNodeCollection &b) {
  // assume that thety are both sorted
  CFGNodeCollection res;
  auto ita = a.begin();
  auto itb = b.begin();
  while (ita != a.end() && itb != b.end()) {
    if (*ita == *itb) {
      res.push_back(*ita);
      ita++;
      itb++;
    } else if (*ita < *itb) {
      res.push_back(*ita);
      ita++;
    } else {
      res.push_back(*itb);
      itb++;
    }
  }
  while (ita != a.end()) {
    res.push_back(*ita);
    ita++;
  }
  while (itb != b.end()) {
    res.push_back(*itb);
    itb++;
  }
  return res;
}

CFGNodeCollection GetCFGNodeCollectionsDifference(const CFGNodeCollection &a, const CFGNodeCollection &b) {
  // assume that thety are both sorted
  CFGNodeCollection res;
  auto ita = a.begin();
  auto itb = b.begin();
  while (ita != a.end() && itb != b.end()) {
    if (*ita == *itb) {
      ita++;
      itb++;
    } else if (*ita < *itb) {
      res.push_back(*ita);
      ita++;
    } else {
      itb++;
    }
  }
  while (ita != a.end()) {
    res.push_back(*ita);
    ita++;
  }
  return res;
}

bool CFGNodeCollectionIsSame(const CFGNodeCollection &a, const CFGNodeCollection &b) {
  auto ita = a.begin();
  auto itb = b.begin();
  while (ita != a.end() && itb != b.end()) {
    if (*ita != *itb) {
      return false;
    }
    ita++;
    itb++;
  }
  return ita == a.end() && itb == b.end();
}

CFGType BuildCFGForFunction(const std::shared_ptr<FunctionDefItem> &func) {
  CFGType res;
  if (!func->init_block) {
    throw std::runtime_error("Function does not have an init block");
  }
  res.label_to_block[func->init_block->label_full] = func->init_block.get();
  res.nodes.push_back(std::make_shared<CFGNodeType>());
  res.entry = res.nodes.back().get();
  res.entry->corresponding_block = func->init_block.get();
  res.block_to_node[func->init_block.get()] = res.entry;
  for (auto block_ptr : func->basic_blocks) {
    res.label_to_block[block_ptr->label_full] = block_ptr.get();
    res.nodes.push_back(std::make_shared<CFGNodeType>());
    res.nodes.back()->corresponding_block = block_ptr.get();
    res.block_to_node[block_ptr.get()] = res.nodes.back().get();
  }
  // now add information for successors and predecessors
  for (auto node : res.nodes) {
    auto block = node->corresponding_block;
    if (block->exit_action) {
      if (auto br = std::dynamic_pointer_cast<BRAction>(block->exit_action)) {
        node->successors.push_back(res.block_to_node[res.label_to_block[br->true_label_full]]);
        node->successors.push_back(res.block_to_node[res.label_to_block[br->false_label_full]]);
        res.block_to_node[res.label_to_block[br->true_label_full]]->predecessors.push_back(node.get());
        res.block_to_node[res.label_to_block[br->false_label_full]]->predecessors.push_back(node.get());
      } else if (auto uncond = std::dynamic_pointer_cast<UNConditionJMPAction>(block->exit_action)) {
        node->successors.push_back(res.block_to_node[res.label_to_block[uncond->label_full]]);
        res.block_to_node[res.label_to_block[uncond->label_full]]->predecessors.push_back(node.get());
      } else if (auto ret = std::dynamic_pointer_cast<RETAction>(block->exit_action)) {
        // do nothing
      } else {
        throw std::runtime_error("Unknown exit action");
      }
    } else {
      throw std::runtime_error("Block does not have an exit action");
    }
  }
  return res;
}