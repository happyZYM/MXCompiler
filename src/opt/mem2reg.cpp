#include "mem2reg.h"
#include <queue>
#include "cfg.h"

void ConductMem2RegForFunction(const std::shared_ptr<FunctionDefItem> &func, const CFGType &cfg) {
  bool all_dom_unchanged;
  CFGNodeCollection all_nodes;
  for (auto &node : cfg.nodes) {
    all_nodes.push_back(node.get());
  }
  all_nodes.sort();
  for (auto cfg_node : all_nodes) {
    cfg_node->dom = all_nodes;
  }
  cfg.entry->dom = {cfg.entry};
  do {
    all_dom_unchanged = true;
    for (auto cfg_node : all_nodes) {
      cfg_node->visited = false;
    }
    std::queue<CFGNodeType *> Q;
    Q.push(cfg.entry);
    cfg.entry->visited = true;
    while (Q.size() > 0) {
      auto cur = Q.front();
      Q.pop();
      for (auto succ : cur->successors) {
        if (!succ->visited) {
          succ->visited = true;
          Q.push(succ);
        }
      }
      CFGNodeCollection new_dom = {cur};
      if (cur->predecessors.size() > 0) {
        CFGNodeCollection tmp = cur->predecessors[0]->dom;
        for (size_t i = 1; i < cur->predecessors.size(); i++) {
          tmp = GetCFGNodeCollectionsIntersection(tmp, cur->predecessors[i]->dom);
        }
        new_dom = GetCFGNodeCollectionsUnion(new_dom, tmp);
      }
      if (!CFGNodeCollectionIsSame(new_dom, cur->dom)) {
        all_dom_unchanged = false;
        cur->dom = new_dom;
      }
    }
  } while (all_dom_unchanged);
  for (auto node : cfg.nodes) {
    if (node.get() == cfg.entry) continue;
    for (auto potential_predecessor : node->predecessors) {
      if (potential_predecessor->dom.size() + 1 == node->dom.size()) {
        node->idom = potential_predecessor;
        node->idom->successors_in_dom_tree.push_back(node.get());
        break;
      }
    }
  }
  for (auto node : cfg.nodes) {
    CFGNodeCollection is_frontier_of;
    CFGNodeCollection tmp1 = {node.get()};
    tmp1 = GetCFGNodeCollectionsDifference(node->dom, tmp1);
    for (auto pred : node->predecessors) {
      CFGNodeCollection tmp2 = GetCFGNodeCollectionsDifference(pred->dom, tmp1);
      is_frontier_of = GetCFGNodeCollectionsUnion(is_frontier_of, tmp2);
    }
    for (auto frontier_node : is_frontier_of) {
      frontier_node->dom_frontier.push_back(node.get());
    }
  }
}
std::shared_ptr<ModuleItem> Mem2Reg(std::shared_ptr<ModuleItem> src) {
  auto res = std::make_shared<ModuleItem>(*src);
  for (auto &func : res->function_defs) {
    func = std::make_shared<FunctionDefItem>(*func);
    auto cfg = BuildCFGForFunction(func);
    ConductMem2RegForFunction(func, cfg);
  }
  return res;
}