#include "global_var_cache.h"
#include "IR/IR_basic.h"
#include "tools.h"
void GlobalBuildDomForFunction(const std::shared_ptr<FunctionDefItem> &func, const CFGType &cfg);
void GlobalDFSReplace(CFGNodeType *cur_node, std::unordered_map<std::string, size_t> &var_to_version,
                      std::unordered_map<std::string, std::stack<std::string>> &var_to_name_stk);
void ConductGloabalVarCacheForFunction(const std::shared_ptr<FunctionDefItem> &func, const CFGType &cfg);
void GlobalBuildDomForFunction(const std::shared_ptr<FunctionDefItem> &func, const CFGType &cfg) {
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
    CFGNodeType *cur_node, std::unordered_map<std::string, std::stack<std::string>> &var_to_name_stk) {
  std::unordered_map<std::string, size_t> var_to_versions_pushed;
  BlockItem *cur_block = cur_node->corresponding_block;
  std::list<std::shared_ptr<ActionItem>> new_actions;
  std::unordered_map<std::string, std::string> is_an_alias_generated_by_load;
  for (auto [origin_var_name, _] : var_to_name_stk) {
    if (cur_block->phi_map.find(origin_var_name) != cur_block->phi_map.end()) {
      var_to_name_stk[origin_var_name].push(cur_block->phi_map[origin_var_name]->result_full);
      var_to_versions_pushed[origin_var_name]++;
    }
  }
  for (auto act : cur_block->actions) {
    if (std::dynamic_pointer_cast<JMPActionItem>(act))
      throw std::runtime_error("JMPActionItem should not appear in actions");
    if (auto bin_act = std::dynamic_pointer_cast<BinaryOperationAction>(act)) {
      if (is_an_alias_generated_by_load.find(bin_act->operand1_full) != is_an_alias_generated_by_load.end()) {
        bin_act->operand1_full = is_an_alias_generated_by_load[bin_act->operand1_full];
      }
      if (is_an_alias_generated_by_load.find(bin_act->operand2_full) != is_an_alias_generated_by_load.end()) {
        bin_act->operand2_full = is_an_alias_generated_by_load[bin_act->operand2_full];
      }
      new_actions.push_back(bin_act);
    } else if (auto load_act = std::dynamic_pointer_cast<LoadAction>(act)) {
      if (var_to_name_stk.find(load_act->ptr_full) != var_to_name_stk.end()) {
        if (var_to_name_stk[load_act->ptr_full].top()[0] != '~') {
          // remove it
          is_an_alias_generated_by_load[load_act->result_full] = var_to_name_stk[load_act->ptr_full].top();
        } else {
          new_actions.push_back(load_act);
          var_to_name_stk[load_act->ptr_full].push(load_act->result_full);
          var_to_versions_pushed[load_act->ptr_full]++;
        }
      } else {
        new_actions.push_back(load_act);
      }
    } else if (auto store_act = std::dynamic_pointer_cast<StoreAction>(act)) {
      if (is_an_alias_generated_by_load.find(store_act->value_full) != is_an_alias_generated_by_load.end()) {
        store_act->value_full = is_an_alias_generated_by_load[store_act->value_full];
      }
      if (var_to_name_stk.find(store_act->ptr_full) != var_to_name_stk.end()) {
        var_to_name_stk[store_act->ptr_full].push(store_act->value_full);
        var_to_versions_pushed[store_act->ptr_full]++;
        new_actions.push_back(store_act);
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
      for (auto [var, _] : var_to_name_stk) {
        var_to_name_stk[var].push("~");
        var_to_versions_pushed[var]++;
      }
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
    } else if (std::dynamic_pointer_cast<AllocaAction>(act)) {
      // do nothing
      new_actions.push_back(act);
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
void GlobalDFSReplace(CFGNodeType *cur_node,
                      std::unordered_map<std::string, std::stack<std::string>> &var_to_name_stk) {
  // std::cerr << "GlobalDFSReplace: " << cur_node->corresponding_block->label_full << std::endl;
  std::unordered_map<std::string, size_t> var_to_version_pushed;
  // step 1: process current node
  var_to_version_pushed = InNodeReplace(cur_node, var_to_name_stk);
  // step 2: process the phi commands in the successors in cfg
  for (auto [origin_var_name, _] : var_to_name_stk) {
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
    GlobalDFSReplace(succ, var_to_name_stk);
  }
  // step 4: restore the stack
  for (auto [var, version_pushed] : var_to_version_pushed) {
    for (size_t i = 0; i < version_pushed; i++) {
      var_to_name_stk[var].pop();
    }
  }
}
void ConductGloabalVarCacheForFunction(const std::shared_ptr<FunctionDefItem> &func, const CFGType &cfg,
                                       std::unordered_map<std::string, LLVMType> &global_var_to_type) {
  GlobalBuildDomForFunction(func, cfg);
  std::unordered_set<std::string> all_global_vars;
  for (auto node : cfg.nodes) {
    for (auto act : node->corresponding_block->actions) {
      if (auto load_act = std::dynamic_pointer_cast<LoadAction>(act)) {
        if (load_act->ptr_full[0] == '@') {
          all_global_vars.insert(load_act->ptr_full);
        }
      } else if (auto store_act = std::dynamic_pointer_cast<StoreAction>(act)) {
        if (store_act->ptr_full[0] == '@') {
          all_global_vars.insert(store_act->ptr_full);
        }
      }
    }
  }
  std::unordered_map<std::string, std::unordered_set<CFGNodeType *>> var_to_def_sites;
  for (auto var : all_global_vars) {
    var_to_def_sites[var].insert(cfg.entry);
    // std::cerr << "found global var: " << var << std::endl;
  }
  for (auto node : cfg.nodes) {
    for (auto act : node->corresponding_block->actions) {
      if (auto store_act = std::dynamic_pointer_cast<StoreAction>(act)) {
        if (all_global_vars.find(store_act->ptr_full) != all_global_vars.end()) {
          var_to_def_sites[store_act->ptr_full].insert(node.get());
        }
      } else if (std::dynamic_pointer_cast<CallItem>(act)) {
        for (auto var : all_global_vars) {
          var_to_def_sites[var].insert(node.get());
        }
      }
    }
  }
  size_t global_cache_cnt = 0;
  for (const auto &var : all_global_vars) {
    // std::cerr << "now consider var: " << var << std::endl;
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
        new_phi->result_full = "%globalvarcache." + std::to_string(global_cache_cnt++);
        new_phi->ty = global_var_to_type[var];
        frontier->corresponding_block->phi_map[var] = new_phi;
        Q.push(frontier);
      }
    }
  }
  std::unordered_map<std::string, std::stack<std::string>> var_to_name_stk;
  for (const auto &var : all_global_vars) {
    var_to_name_stk[var] = std::stack<std::string>();
    var_to_name_stk[var].push("~");
  }
  GlobalDFSReplace(cfg.entry, var_to_name_stk);
  for (auto node : cfg.nodes) {
    auto block = node->corresponding_block;
    for (auto &[var, _] : var_to_name_stk) {
      if (block->phi_map.find(var) != block->phi_map.end()) {
        bool phi_has_unkown_value = false;
        auto phi_act = block->phi_map[var];
        for (auto &[value, _] : phi_act->values) {
          if (value[0] == '~') {
            phi_has_unkown_value = true;
            break;
          }
        }
        if (phi_has_unkown_value) {
          std::string virtual_reg_name = phi_act->result_full;
          block->phi_map.erase(var);
          auto new_load_act = std::make_shared<LoadAction>();
          new_load_act->ptr_full = var;
          new_load_act->result_full = virtual_reg_name;
          new_load_act->ty = global_var_to_type[var];
          if (block->actions.size() > 0 && std::dynamic_pointer_cast<PhiItem>(block->actions.front())) {
            auto it_act = block->actions.begin();
            while (it_act != block->actions.end() && std::dynamic_pointer_cast<PhiItem>(*it_act)) {
              ++it_act;
            }
            block->actions.insert(it_act, new_load_act);
          } else {
            block->actions.push_front(new_load_act);
          }
        }
      }
    }
  }
}

std::shared_ptr<ModuleItem> GloabalVarCache(std::shared_ptr<ModuleItem> src) {
  // auto res = std::make_shared<ModuleItem>(*src);
  auto res = src;
  std::unordered_map<std::string, LLVMType> global_var_to_type;
  for (auto var_def : src->global_var_defs) {
    auto full_name = "@.var.global." + var_def->name_raw + ".addrkp";
    global_var_to_type[full_name] = var_def->type;
  }
  for (auto &func : res->function_defs) {
    // func = std::make_shared<FunctionDefItem>(*func);
    auto cfg = BuildCFGForFunction(func);
    ConductGloabalVarCacheForFunction(func, cfg, global_var_to_type);
  }
  return res;
}