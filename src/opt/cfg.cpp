#include "cfg.h"
#include <queue>
#include <string>

CFGType BuildCFGForFunction(const std::shared_ptr<FunctionDefItem> &func, bool remove_poison_entry) {
  CFGType res;
  if (func->init_block) {
    res.label_to_block[func->init_block->label_full] = func->init_block.get();
    res.nodes.push_back(std::make_shared<CFGNodeType>());
    res.entry = res.nodes.back().get();
    res.entry->corresponding_block = func->init_block.get();
    res.block_to_node[func->init_block.get()] = res.entry;
  }
  for (auto block_ptr : func->basic_blocks) {
    res.label_to_block[block_ptr->label_full] = block_ptr.get();
    res.nodes.push_back(std::make_shared<CFGNodeType>());
    res.nodes.back()->corresponding_block = block_ptr.get();
    res.block_to_node[block_ptr.get()] = res.nodes.back().get();
  }
  res.entry = res.nodes.front().get();
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
  res.corresponding_func = func.get();
  bool need_rebuild = false;
  if (remove_poison_entry) {
    auto tmp = func->basic_blocks;
    func->basic_blocks.clear();
    std::queue<CFGNodeType *> Q;
    std::unordered_set<CFGNodeType *> visited;
    Q.push(res.entry);
    visited.insert(res.entry);
    while (Q.size() > 0) {
      auto cur = Q.front();
      Q.pop();
      for (auto succ : cur->successors) {
        if (visited.find(succ) == visited.end()) {
          visited.insert(succ);
          Q.push(succ);
        }
      }
    }
    for (auto block : tmp) {
      auto node = res.block_to_node[block.get()];
      if (visited.find(node) == visited.end()) {
        need_rebuild = true;
        continue;
      }
      func->basic_blocks.push_back(block);
    }
  }
  if (need_rebuild) {
    res = BuildCFGForFunction(func, false);
  }
  return res;
}