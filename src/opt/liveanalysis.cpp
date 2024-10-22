#include "liveanalysis.h"
#include <queue>
#include <stdexcept>
#include "IR/IR_basic.h"
#include "cfg.h"
#include "tools.h"

using namespace opt;
void VarCollect(CFGType &cfg, std::vector<std::string> &id_to_var, std::unordered_map<std::string, size_t> &var_to_id);
void UseDefCollect(CFGType &cfg, [[maybe_unused]] std::vector<std::string> &id_to_var,
                   std::unordered_map<std::string, size_t> &var_to_id);
void BlockLevelTracking(CFGType &cfg, [[maybe_unused]] std::vector<std::string> &id_to_var,
                        [[maybe_unused]] std::unordered_map<std::string, size_t> &var_to_id);
void ActionLevelTracking(CFGType &cfg, CFGNodeType *node);
void LiveAnalysis(CFGType &cfg);
void VarCollect(CFGType &cfg, std::vector<std::string> &id_to_var, std::unordered_map<std::string, size_t> &var_to_id) {
  auto TryAddVar = [&](const std::string &var) {
    if (var_to_id.find(var) == var_to_id.end()) {
      id_to_var.push_back(var);
      var_to_id[var] = id_to_var.size() - 1;
    }
  };
  for (auto node : cfg.nodes) {
    auto block = node->corresponding_block;
    for (auto act : block->actions) {
      if (auto bin_act = std::dynamic_pointer_cast<BinaryOperationAction>(act)) {
        TryAddVar(bin_act->result_full);
      } else if (auto load_act = std::dynamic_pointer_cast<LoadAction>(act)) {
        TryAddVar(load_act->result_full);
      } else if (auto get_act = std::dynamic_pointer_cast<GetElementPtrAction>(act)) {
        TryAddVar(get_act->result_full);
      } else if (auto icmp_act = std::dynamic_pointer_cast<ICMPAction>(act)) {
        TryAddVar(icmp_act->result_full);
        ;
      } else if (auto call_act = std::dynamic_pointer_cast<CallItem>(act)) {
        if (!std::holds_alternative<LLVMVOIDType>(call_act->return_type)) {
          TryAddVar(call_act->result_full);
        }
      } else if (auto select_act = std::dynamic_pointer_cast<SelectItem>(act)) {
        TryAddVar(select_act->result_full);
      } else if (auto move_act = std::dynamic_pointer_cast<MoveInstruct>(act)) {
        TryAddVar(move_act->dest_full);
      } else if (auto force_def_act = std::dynamic_pointer_cast<ForceDef>(act)) {
        TryAddVar(force_def_act->var_full);
      } else if (auto load_spilled_args_act = std::dynamic_pointer_cast<LoadSpilledArgs>(act)) {
        TryAddVar(load_spilled_args_act->var_full);
      } else if (auto alloca_act = std::dynamic_pointer_cast<AllocaAction>(act)) {
        TryAddVar(alloca_act->name_full);
      }
    }
  }
  for (size_t i = 0; i < id_to_var.size(); i++) {
    if (var_to_id.find(id_to_var[i]) == var_to_id.end())
      throw std::runtime_error("var_to_id.find(id_to_var[i])==var_to_id.end()");
    if (i != var_to_id[id_to_var[i]]) throw std::runtime_error("i!=var_to_id[id_to_var[i]]");
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
      std::vector<size_t> &cur_act_use = node->action_use_vars[act.get()];
      std::vector<size_t> &cur_act_def = node->action_def_vars[act.get()];
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
      } else if (auto move_act = std::dynamic_pointer_cast<MoveInstruct>(act)) {
        if (VRegCheck(move_act->src_full) && var_to_id.find(move_act->src_full) != var_to_id.end()) {
          cur_act_use.push_back(var_to_id[move_act->src_full]);
        }
        if (var_to_id.find(move_act->dest_full) != var_to_id.end()) {
          cur_act_def.push_back(var_to_id[move_act->dest_full]);
        }
      } else if (auto force_def_act = std::dynamic_pointer_cast<ForceDef>(act)) {
        if (var_to_id.find(force_def_act->var_full) != var_to_id.end()) {
          cur_act_def.push_back(var_to_id[force_def_act->var_full]);
        }
      } else if (auto force_use_act = std::dynamic_pointer_cast<ForceUse>(act)) {
        if (var_to_id.find(force_use_act->var_full) != var_to_id.end()) {
          cur_act_use.push_back(var_to_id[force_use_act->var_full]);
        }
      } else if (auto load_spilled_args_act = std::dynamic_pointer_cast<LoadSpilledArgs>(act)) {
        if (var_to_id.find(load_spilled_args_act->var_full) != var_to_id.end()) {
          cur_act_def.push_back(var_to_id[load_spilled_args_act->var_full]);
        }
      } else if (auto store_spilled_args_act = std::dynamic_pointer_cast<StoreSpilledArgs>(act)) {
        if (var_to_id.find(store_spilled_args_act->var_full) != var_to_id.end()) {
          cur_act_use.push_back(var_to_id[store_spilled_args_act->var_full]);
        }
      } else if (auto alloca_act = std::dynamic_pointer_cast<AllocaAction>(act)) {
        cur_act_def.push_back(var_to_id[alloca_act->name_full]);
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
        const auto &use_p = cur_node_use;
        const auto &def_p = cur_node_def;
        const auto &use_n = cur_act_use;
        const auto &def_n = cur_act_def;
        cur_node_use = GetCollectionsUnion(use_p, GetCollectionsDifference(use_n, def_p));
        cur_node_def = GetCollectionsUnion(def_p, def_n);
      }
    }
    {
      auto act = block->exit_action;
      std::vector<size_t> &cur_act_use = node->action_use_vars[act.get()];
      std::vector<size_t> &cur_act_def = node->action_def_vars[act.get()];
      if (auto br_act = std::dynamic_pointer_cast<BRAction>(act)) {
        if (var_to_id.find(br_act->cond) != var_to_id.end()) {
          cur_act_use.push_back(var_to_id[br_act->cond]);
        }
      } else if (auto ret_act = std::dynamic_pointer_cast<RETAction>(act)) {
        if (!std::holds_alternative<LLVMVOIDType>(ret_act->type) && var_to_id.find(ret_act->value) != var_to_id.end()) {
          cur_act_use.push_back(var_to_id[ret_act->value]);
        }
      }
      if (!use_def_init) {
        use_def_init = true;
        cur_node_use = cur_act_use;
        cur_node_def = cur_act_def;
      } else {
        const auto &use_p = cur_node_use;
        const auto &def_p = cur_node_def;
        const auto &use_n = cur_act_use;
        const auto &def_n = cur_act_def;
        cur_node_use = GetCollectionsUnion(use_p, GetCollectionsDifference(use_n, def_p));
        cur_node_def = GetCollectionsUnion(def_p, def_n);
      }
    }
    node->block_use_vars = cur_node_use;
    node->block_def_vars = cur_node_def;
  }
}

void BlockLevelTracking(CFGType &cfg, [[maybe_unused]] std::vector<std::string> &id_to_var,
                        [[maybe_unused]] std::unordered_map<std::string, size_t> &var_to_id) {
  std::vector<CFGNodeType *> exists;
  for (auto node : cfg.nodes) {
    node->block_in_active_vars = node->block_use_vars;
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
        out_active_vars = GetCollectionsUnion(out_active_vars, succ->block_in_active_vars);
      }
      if (!GetCollectionsIsSame(cur_node->block_out_active_vars, out_active_vars)) {
        all_data_unchanged = false;
        cur_node->block_out_active_vars = std::move(out_active_vars);
      }
      std::vector<size_t> in_active_vars =
          GetCollectionsUnion(cur_node->block_use_vars,
                              GetCollectionsDifference(cur_node->block_out_active_vars, cur_node->block_def_vars));
      if (!GetCollectionsIsSame(cur_node->block_in_active_vars, in_active_vars)) {
        all_data_unchanged = false;
        cur_node->block_in_active_vars = std::move(in_active_vars);
      }
    }
  } while (!all_data_unchanged);
}

void ActionLevelTracking(CFGType &cfg, CFGNodeType *node) {
  if (node->corresponding_block->actions.size() == 0) {
    node->action_in_active_vars[node->corresponding_block->exit_action.get()] = node->block_in_active_vars;
    node->action_out_active_vars[node->corresponding_block->exit_action.get()] = node->block_out_active_vars;
    return;
  }
  node->action_in_active_vars[node->corresponding_block->actions.front().get()] = node->block_in_active_vars;
  node->action_out_active_vars[node->corresponding_block->exit_action.get()] = node->block_out_active_vars;
  node->action_in_active_vars[node->corresponding_block->exit_action.get()] = GetCollectionsUnion(
      node->action_use_vars[node->corresponding_block->exit_action.get()],
      GetCollectionsDifference(node->action_out_active_vars[node->corresponding_block->exit_action.get()],
                               node->action_def_vars[node->corresponding_block->exit_action.get()]));
  node->action_out_active_vars[node->corresponding_block->actions.back().get()] =
      node->action_in_active_vars[node->corresponding_block->exit_action.get()];
  if (node->corresponding_block->actions.size() == 1) return;
  auto it = node->corresponding_block->actions.end();
  --it;
  while (true) {
    node->action_in_active_vars[it->get()] = GetCollectionsUnion(
        node->action_use_vars[it->get()],
        GetCollectionsDifference(node->action_out_active_vars[it->get()], node->action_def_vars[it->get()]));
    auto tmp = node->action_in_active_vars[it->get()];
    --it;
    node->action_out_active_vars[it->get()] = tmp;
    if (it == node->corresponding_block->actions.begin()) break;
  }
}

void LiveAnalysis(CFGType &cfg) {
  VarCollect(cfg, cfg.id_to_var, cfg.var_to_id);
  UseDefCollect(cfg, cfg.id_to_var, cfg.var_to_id);
  BlockLevelTracking(cfg, cfg.id_to_var, cfg.var_to_id);
  for (auto node : cfg.nodes) {
    ActionLevelTracking(cfg, node.get());
  }
}