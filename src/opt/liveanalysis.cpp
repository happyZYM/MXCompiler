#include "liveanalysis.h"
#include <queue>
#include <stdexcept>
#include "IR/IR_basic.h"
#include "cfg.h"
#include "tools.h"

void VarCollect(CFGType &cfg, std::vector<std::string> &id_to_var, std::unordered_map<std::string, size_t> &var_to_id) {
  for (auto node : cfg.nodes) {
    auto block = node->corresponding_block;
    for (auto act : block->actions) {
      if (auto bin_act = std::dynamic_pointer_cast<BinaryOperationAction>(act)) {
        id_to_var.push_back(bin_act->result_full);
        var_to_id[bin_act->result_full] = id_to_var.size() - 1;
      } else if (auto load_act = std::dynamic_pointer_cast<LoadAction>(act)) {
        id_to_var.push_back(load_act->result_full);
        var_to_id[load_act->result_full] = id_to_var.size() - 1;
      } else if (auto get_act = std::dynamic_pointer_cast<GetElementPtrAction>(act)) {
        id_to_var.push_back(get_act->result_full);
        var_to_id[get_act->result_full] = id_to_var.size() - 1;
      } else if (auto icmp_act = std::dynamic_pointer_cast<ICMPAction>(act)) {
        id_to_var.push_back(icmp_act->result_full);
        var_to_id[icmp_act->result_full] = id_to_var.size() - 1;
      } else if (auto call_act = std::dynamic_pointer_cast<CallItem>(act)) {
        if (!std::holds_alternative<LLVMVOIDType>(call_act->return_type)) {
          id_to_var.push_back(call_act->result_full);
          var_to_id[call_act->result_full] = id_to_var.size() - 1;
        }
      } else if (auto select_act = std::dynamic_pointer_cast<SelectItem>(act)) {
        id_to_var.push_back(select_act->result_full);
        var_to_id[select_act->result_full] = id_to_var.size() - 1;
      }
    }
  }
}

void UseDefCollect(CFGType &cfg, [[maybe_unused]] std::vector<std::string> &id_to_var,
                   std::unordered_map<std::string, size_t> &var_to_id) {
  for (auto node : cfg.nodes) {
    auto block = node->corresponding_block;
    std::vector<size_t> cur_node_use;
    std::vector<size_t> cur_node_def;
    bool use_def_init = false;
    for (auto act : block->actions) {
      std::vector<size_t> cur_act_use;
      std::vector<size_t> cur_act_def;
      if (auto br_act = std::dynamic_pointer_cast<BRAction>(act)) {
        if (var_to_id.find(br_act->cond) != var_to_id.end()) {
          cur_act_use.push_back(var_to_id[br_act->cond]);
        }
      } else if (auto ret_act = std::dynamic_pointer_cast<RETAction>(act)) {
        if (!std::holds_alternative<LLVMVOIDType>(ret_act->type) && var_to_id.find(ret_act->value) != var_to_id.end()) {
          cur_act_use.push_back(var_to_id[ret_act->value]);
        }
      } else if (auto bin_act = std::dynamic_pointer_cast<BinaryOperationAction>(act)) {
        if (var_to_id.find(bin_act->operand1_full) != var_to_id.end()) {
          cur_act_use.push_back(var_to_id[bin_act->operand1_full]);
        }
        if (bin_act->operand2_full != bin_act->operand1_full &&
            var_to_id.find(bin_act->operand2_full) != var_to_id.end()) {
          cur_act_use.push_back(var_to_id[bin_act->operand2_full]);
        }
        if (var_to_id.find(bin_act->result_full) != var_to_id.end()) {
          cur_act_def.push_back(var_to_id[bin_act->result_full]);
        }
      } else if (auto load_act = std::dynamic_pointer_cast<LoadAction>(act)) {
        if (var_to_id.find(load_act->ptr_full) != var_to_id.end()) {
          cur_act_use.push_back(var_to_id[load_act->ptr_full]);
        }
        if (var_to_id.find(load_act->result_full) != var_to_id.end()) {
          cur_act_def.push_back(var_to_id[load_act->result_full]);
        }
      } else if (auto store_act = std::dynamic_pointer_cast<StoreAction>(act)) {
        if (var_to_id.find(store_act->value_full) != var_to_id.end()) {
          cur_act_use.push_back(var_to_id[store_act->value_full]);
        }
        if (store_act->ptr_full == store_act->value_full)
          throw std::runtime_error("store action should not have the same ptr and value");
        if (var_to_id.find(store_act->ptr_full) != var_to_id.end()) {
          cur_act_use.push_back(var_to_id[store_act->ptr_full]);
        }
      } else if (auto get_act = std::dynamic_pointer_cast<GetElementPtrAction>(act)) {
        std::unordered_set<std::string> used_vars;
        if (var_to_id.find(get_act->ptr_full) != var_to_id.end()) {
          cur_act_use.push_back(var_to_id[get_act->ptr_full]);
          used_vars.insert(get_act->ptr_full);
        }
        for (auto idx : get_act->indices) {
          if (used_vars.find(idx) != used_vars.end()) continue;
          if (var_to_id.find(idx) != var_to_id.end()) {
            cur_act_use.push_back(var_to_id[idx]);
            used_vars.insert(idx);
          }
        }
        if (var_to_id.find(get_act->result_full) != var_to_id.end()) {
          cur_act_def.push_back(var_to_id[get_act->result_full]);
        }
      } else if (auto icmp_act = std::dynamic_pointer_cast<ICMPAction>(act)) {
        if (var_to_id.find(icmp_act->operand1_full) != var_to_id.end()) {
          cur_act_use.push_back(var_to_id[icmp_act->operand1_full]);
        }
        if (icmp_act->operand2_full != icmp_act->operand1_full &&
            var_to_id.find(icmp_act->operand2_full) != var_to_id.end()) {
          cur_act_use.push_back(var_to_id[icmp_act->operand2_full]);
        }
        if (var_to_id.find(icmp_act->result_full) != var_to_id.end()) {
          cur_act_def.push_back(var_to_id[icmp_act->result_full]);
        }
      } else if (auto call_act = std::dynamic_pointer_cast<CallItem>(act)) {
        std::unordered_set<std::string> used_vars;
        for (auto arg : call_act->args_val_full) {
          if (used_vars.find(arg) != used_vars.end()) continue;
          if (var_to_id.find(arg) != var_to_id.end()) {
            cur_act_use.push_back(var_to_id[arg]);
            used_vars.insert(arg);
          }
        }
        if (!std::holds_alternative<LLVMVOIDType>(call_act->return_type) &&
            var_to_id.find(call_act->result_full) != var_to_id.end()) {
          cur_act_def.push_back(var_to_id[call_act->result_full]);
        }
      } else if (auto select_act = std::dynamic_pointer_cast<SelectItem>(act)) {
        if (var_to_id.find(select_act->cond_full) != var_to_id.end()) {
          cur_act_use.push_back(var_to_id[select_act->cond_full]);
        }
        if (select_act->true_val_full != select_act->cond_full &&
            var_to_id.find(select_act->true_val_full) != var_to_id.end()) {
          cur_act_use.push_back(var_to_id[select_act->true_val_full]);
        }
        if (select_act->false_val_full != select_act->cond_full &&
            select_act->false_val_full != select_act->cond_full &&
            var_to_id.find(select_act->false_val_full) != var_to_id.end()) {
          cur_act_use.push_back(var_to_id[select_act->false_val_full]);
        }
        if (var_to_id.find(select_act->result_full) != var_to_id.end()) {
          cur_act_def.push_back(var_to_id[select_act->result_full]);
        }
      }
      std::sort(cur_act_use.begin(), cur_act_use.end());
      std::sort(cur_act_def.begin(), cur_act_def.end());
      for (size_t i = 1; i < cur_act_use.size(); i++) {
        if (cur_act_use[i] == cur_act_use[i - 1]) {
          throw std::runtime_error("use variable appears twice in one action");
        }
      }
      for (size_t i = 1; i < cur_act_def.size(); i++) {
        if (cur_act_def[i] == cur_act_def[i - 1]) {
          throw std::runtime_error("def variable appears twice in one action");
        }
      }
      if (!use_def_init) {
        use_def_init = true;
        cur_node_use = cur_act_use;
        cur_node_def = cur_act_def;
      } else {
        auto use_p = std::move(cur_node_use);
        auto def_p = std::move(cur_node_def);
        auto use_n = std::move(cur_act_use);
        auto def_n = std::move(cur_act_def);
        cur_node_use = GetCollectionsUnion(use_p, GetCollectionsDifference(use_n, def_p));
        cur_node_def = GetCollectionsUnion(def_p, use_n);
      }
    }
    node->use_vars = cur_node_use;
    node->def_vars = cur_node_def;
  }
}

void LiveAnalysis(CFGType &cfg) {
  std::vector<std::string> id_to_var;
  std::unordered_map<std::string, size_t> var_to_id;
  VarCollect(cfg, id_to_var, var_to_id);
  UseDefCollect(cfg, id_to_var, var_to_id);
  std::vector<CFGNodeType *> exists;
  for (auto node : cfg.nodes) {
    node->in_active_vars = node->use_vars;
    if (node->successors.size() == 0) {
      exists.push_back(node.get());
    }
  }
  bool all_data_unchanged;
  do {
    all_data_unchanged = true;
    for (auto node : cfg.nodes) {
      node->visited = false;
    }
    std::queue<CFGNodeType *> Q;
    for (auto e : exists) {
      Q.push(e);
      e->visited = true;
    }
    while (Q.size() > 0) {
      auto cur_node = Q.front();
      Q.pop();
      for (auto pred : cur_node->predecessors) {
        if (!pred->visited) {
          pred->visited = true;
          Q.push(pred);
        }
      }
      std::vector<size_t> out_active_vars;
      for (auto succ : cur_node->successors) {
        out_active_vars = GetCollectionsUnion(out_active_vars, succ->in_active_vars);
      }
      if (!GetCollectionsIsSame(cur_node->out_active_vars, out_active_vars)) {
        all_data_unchanged = false;
        cur_node->out_active_vars = std::move(out_active_vars);
      }
      std::vector<size_t> in_active_vars = GetCollectionsUnion(
          cur_node->use_vars, GetCollectionsDifference(cur_node->out_active_vars, cur_node->def_vars));
      if (!GetCollectionsIsSame(cur_node->in_active_vars, in_active_vars)) {
        all_data_unchanged = false;
        cur_node->in_active_vars = std::move(in_active_vars);
      }
    }
  } while (!all_data_unchanged);
}