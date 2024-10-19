#include "mem2reg.h"
#include <memory>
#include <queue>
#include "IR/IR_basic.h"
#include "cfg.h"

void BuildDomForFunction(const std::shared_ptr<FunctionDefItem> &func, const CFGType &cfg) {
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
          tmp = GetCollectionsIntersection(tmp, cur->predecessors[i]->dom);
        }
        new_dom = GetCollectionsUnion(new_dom, tmp);
      }
      if (!GetCollectionsIsSame(new_dom, cur->dom)) {
        all_dom_unchanged = false;
        cur->dom = new_dom;
      }
    }
  } while (!all_dom_unchanged);
  for (auto node : cfg.nodes) {
    if (node.get() == cfg.entry) continue;
    for (auto potential_predecessor : node->dom) {
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
    tmp1 = GetCollectionsDifference(node->dom, tmp1);
    for (auto pred : node->predecessors) {
      CFGNodeCollection tmp2 = GetCollectionsDifference(pred->dom, tmp1);
      is_frontier_of = GetCollectionsUnion(is_frontier_of, tmp2);
    }
    for (auto frontier_node : is_frontier_of) {
      frontier_node->dom_frontier.push_back(node.get());
    }
  }
  // debug
  for (auto &node : cfg.nodes) {
    std::cerr << node->corresponding_block->label_full << ":\n";
    std::cerr << "\tdom:";
    for (auto &dom_node : node->dom) {
      std::cerr << ' ' << dom_node->corresponding_block->label_full;
    }
    if (node->idom) std::cerr << "\n\tidom: " << node->idom->corresponding_block->label_full;
    std::cerr << "\n\tdom_frontier:";
    for (auto &frontier_node : node->dom_frontier) {
      std::cerr << ' ' << frontier_node->corresponding_block->label_full;
    }
    std::cerr << "\n\tcfg pred:";
    for (auto &pred : node->predecessors) {
      std::cerr << ' ' << pred->corresponding_block->label_full;
    }
    std::cerr << "\n\tsuccessors_in_dom_tree:";
    for (auto &succ : node->successors_in_dom_tree) {
      std::cerr << ' ' << succ->corresponding_block->label_full;
    }
    std::cerr << std::endl;
  }
}

std::unordered_map<std::string, size_t> InNodeReplace(
    CFGNodeType *cur_node, std::unordered_map<std::string, size_t> &var_to_version,
    std::unordered_map<std::string, std::stack<std::string>> &var_to_name_stk) {
  std::unordered_map<std::string, size_t> var_to_versions_pushed;
  BlockItem *cur_block = cur_node->corresponding_block;
  std::vector<std::shared_ptr<ActionItem>> new_actions;
  std::unordered_map<std::string, std::string> is_an_alias_generated_by_load;
  for (auto [origin_var_name, _] : var_to_version) {
    if (cur_block->phi_map.find(origin_var_name) != cur_block->phi_map.end()) {
      var_to_name_stk[origin_var_name].push(cur_block->phi_map[origin_var_name]->result_full);
      var_to_versions_pushed[origin_var_name]++;
    }
  }
  for (auto act : cur_block->actions) {
    if (std::dynamic_pointer_cast<JMPActionItem>(act))
      throw std::runtime_error("JMPActionItem should not appear in actions");
    if (auto alloca_act = std::dynamic_pointer_cast<AllocaAction>(act)) {
      if (var_to_version.find(alloca_act->name_full) != var_to_version.end()) {
        // do nothing, just erase it
      } else {
        new_actions.push_back(alloca_act);
      }
    } else if (auto bin_act = std::dynamic_pointer_cast<BinaryOperationAction>(act)) {
      if (is_an_alias_generated_by_load.find(bin_act->operand1_full) != is_an_alias_generated_by_load.end()) {
        bin_act->operand1_full = is_an_alias_generated_by_load[bin_act->operand1_full];
      }
      if (is_an_alias_generated_by_load.find(bin_act->operand2_full) != is_an_alias_generated_by_load.end()) {
        bin_act->operand2_full = is_an_alias_generated_by_load[bin_act->operand2_full];
      }
      new_actions.push_back(bin_act);
    } else if (auto load_act = std::dynamic_pointer_cast<LoadAction>(act)) {
      if (var_to_version.find(load_act->ptr_full) != var_to_version.end()) {
        // remove it
        is_an_alias_generated_by_load[load_act->result_full] = var_to_name_stk[load_act->ptr_full].top();
      } else {
        new_actions.push_back(load_act);
      }
    } else if (auto store_act = std::dynamic_pointer_cast<StoreAction>(act)) {
      if (is_an_alias_generated_by_load.find(store_act->value_full) != is_an_alias_generated_by_load.end()) {
        store_act->value_full = is_an_alias_generated_by_load[store_act->value_full];
      }
      if (var_to_version.find(store_act->ptr_full) != var_to_version.end()) {
        // remove it
        var_to_name_stk[store_act->ptr_full].push(store_act->value_full);
        var_to_versions_pushed[store_act->ptr_full]++;
      } else {
        new_actions.push_back(store_act);
      }
    } else if (auto get_act = std::dynamic_pointer_cast<GetElementPtrAction>(act)) {
      new_actions.push_back(get_act);
      if (is_an_alias_generated_by_load.find(get_act->ptr_full) != is_an_alias_generated_by_load.end()) {
        get_act->ptr_full = is_an_alias_generated_by_load[get_act->ptr_full];
      }
      for (auto &idx : get_act->indices) {
        if (is_an_alias_generated_by_load.find(idx) != is_an_alias_generated_by_load.end()) {
          idx = is_an_alias_generated_by_load[idx];
        }
      }
    } else if (auto icmp_act = std::dynamic_pointer_cast<ICMPAction>(act)) {
      if (is_an_alias_generated_by_load.find(icmp_act->operand1_full) != is_an_alias_generated_by_load.end()) {
        icmp_act->operand1_full = is_an_alias_generated_by_load[icmp_act->operand1_full];
      }
      if (is_an_alias_generated_by_load.find(icmp_act->operand2_full) != is_an_alias_generated_by_load.end()) {
        icmp_act->operand2_full = is_an_alias_generated_by_load[icmp_act->operand2_full];
      }
      new_actions.push_back(icmp_act);
    } else if (auto phi_act = std::dynamic_pointer_cast<PhiItem>(act)) {
      new_actions.push_back(phi_act);
      for (auto &val : phi_act->values) {
        if (is_an_alias_generated_by_load.find(val.first) != is_an_alias_generated_by_load.end()) {
          val.first = is_an_alias_generated_by_load[val.first];
        }
      }
    } else if (auto call_act = std::dynamic_pointer_cast<CallItem>(act)) {
      for (size_t i = 0; i < call_act->args_val_full.size(); i++) {
        if (is_an_alias_generated_by_load.find(call_act->args_val_full[i]) != is_an_alias_generated_by_load.end()) {
          call_act->args_val_full[i] = is_an_alias_generated_by_load[call_act->args_val_full[i]];
        }
      }
      new_actions.push_back(call_act);
    } else if (auto select_act = std::dynamic_pointer_cast<SelectItem>(act)) {
      if (is_an_alias_generated_by_load.find(select_act->cond_full) != is_an_alias_generated_by_load.end()) {
        select_act->cond_full = is_an_alias_generated_by_load[select_act->cond_full];
      }
      if (is_an_alias_generated_by_load.find(select_act->true_val_full) != is_an_alias_generated_by_load.end()) {
        select_act->true_val_full = is_an_alias_generated_by_load[select_act->true_val_full];
      }
      if (is_an_alias_generated_by_load.find(select_act->false_val_full) != is_an_alias_generated_by_load.end()) {
        select_act->false_val_full = is_an_alias_generated_by_load[select_act->false_val_full];
      }
      new_actions.push_back(select_act);
    } else {
      throw std::runtime_error("Unknown action type");
    }
  }
  if (auto br_act = std::dynamic_pointer_cast<BRAction>(cur_block->exit_action)) {
    if (is_an_alias_generated_by_load.find(br_act->cond) != is_an_alias_generated_by_load.end()) {
      br_act->cond = is_an_alias_generated_by_load[br_act->cond];
    }
  } else if (auto ret_act = std::dynamic_pointer_cast<RETAction>(cur_block->exit_action)) {
    if (is_an_alias_generated_by_load.find(ret_act->value) != is_an_alias_generated_by_load.end()) {
      ret_act->value = is_an_alias_generated_by_load[ret_act->value];
    }
  }
  cur_block->actions = new_actions;
  return var_to_versions_pushed;
}
void DFSReplace(CFGNodeType *cur_node, std::unordered_map<std::string, size_t> &var_to_version,
                std::unordered_map<std::string, std::stack<std::string>> &var_to_name_stk) {
  // std::cerr << "DFSReplace: " << cur_node->corresponding_block->label_full << std::endl;
  std::unordered_map<std::string, size_t> var_to_version_pushed;
  // step 1: process current node
  var_to_version_pushed = InNodeReplace(cur_node, var_to_version, var_to_name_stk);
  // step 2: process the phi commands in the successors in cfg
  for (auto [origin_var_name, _] : var_to_version) {
    for (auto succ : cur_node->successors) {
      if (succ->corresponding_block->phi_map.find(origin_var_name) != succ->corresponding_block->phi_map.end()) {
        auto phi = succ->corresponding_block->phi_map[origin_var_name];
        phi->values.push_back(
            std::make_pair(var_to_name_stk[origin_var_name].top(), cur_node->corresponding_block->label_full));
      }
    }
  }
  // step 3: process the successors in dom tree
  for (auto succ : cur_node->successors_in_dom_tree) {
    DFSReplace(succ, var_to_version, var_to_name_stk);
  }
  // step 4: restore the stack
  for (auto [var, version_pushed] : var_to_version_pushed) {
    for (size_t i = 0; i < version_pushed; i++) {
      var_to_name_stk[var].pop();
    }
  }
}
void ConductMem2RegForFunction(const std::shared_ptr<FunctionDefItem> &func, const CFGType &cfg) {
  BuildDomForFunction(func, cfg);
  std::vector<std::string> all_local_vars;
  std::unordered_map<std::string, size_t> var_to_version;
  std::unordered_map<std::string, LLVMType> var_to_type;
  for (auto act : cfg.entry->corresponding_block->actions) {
    if (auto alloca_act = std::dynamic_pointer_cast<AllocaAction>(act)) {
      if (alloca_act->num == 1 && alloca_act->name_full.substr(0, 12) == "%.var.local.") {
        all_local_vars.push_back(alloca_act->name_full);
        var_to_version[alloca_act->name_full] = 0;
        var_to_type[alloca_act->name_full] = alloca_act->type;
      }
    }
  }
  std::unordered_map<std::string, std::unordered_set<CFGNodeType *>> var_to_def_sites;
  for (auto node : cfg.nodes) {
    for (auto act : node->corresponding_block->actions) {
      if (auto store_act = std::dynamic_pointer_cast<StoreAction>(act)) {
        if (var_to_version.find(store_act->ptr_full) != var_to_version.end()) {
          var_to_def_sites[store_act->ptr_full].insert(node.get());
          // break;
        }
      }
    }
  }
  for (const auto &var : all_local_vars) {
    // std::cerr << "now consider var: " << var << std::endl;
    size_t &cur_version = var_to_version[var];
    std::queue<CFGNodeType *> Q;
    // std::cerr << "\tdef sites:";
    for (auto def_site : var_to_def_sites[var]) {
      Q.push(def_site);
      // std::cerr << ' ' << def_site->corresponding_block->label_full;
    }
    // std::cerr << std::endl;
    while (Q.size() > 0) {
      CFGNodeType *cur_node = Q.front();
      Q.pop();
      for (auto frontier : cur_node->dom_frontier) {
        if (frontier->corresponding_block->phi_map.find(var) != frontier->corresponding_block->phi_map.end()) continue;
        auto new_phi = std::make_shared<PhiItem>();
        frontier->corresponding_block->phi_map[var] = new_phi;
        new_phi->result_full = var + ".v" + std::to_string(++cur_version);
        new_phi->ty = var_to_type[var];
        Q.push(frontier);
      }
    }
  }
  std::unordered_map<std::string, std::stack<std::string>> var_to_name_stk;
  for (const auto &var : all_local_vars) {
    var_to_name_stk[var] = std::stack<std::string>();
    if (std::holds_alternative<LLVMIRPTRType>(var_to_type[var])) {
      var_to_name_stk[var].push("null");
    } else {
      var_to_name_stk[var].push("0");
    }
  }
  DFSReplace(cfg.entry, var_to_version, var_to_name_stk);
}
std::shared_ptr<ModuleItem> Mem2Reg(std::shared_ptr<ModuleItem> src) {
  // auto res = std::make_shared<ModuleItem>(*src);
  auto res = src;
  for (auto &func : res->function_defs) {
    // func = std::make_shared<FunctionDefItem>(*func);
    auto cfg = BuildCFGForFunction(func);
    ConductMem2RegForFunction(func, cfg);
  }
  return res;
}