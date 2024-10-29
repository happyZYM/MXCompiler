#include "regalloc.h"
#include "IR/IR_basic.h"
#include "cfg.h"
#include "confgraph.h"
#include "liveanalysis.h"
#include "phieliminate.h"
#include "tools.h"
void EnforcePhysicalRegs(CFGType &cfg);
void TranslateColorResult(std::shared_ptr<FunctionDefItem> func, CFGType &cfg, ConfGraph &confgraph);
void PairMoveEliminate(std::shared_ptr<FunctionDefItem> func, CFGType &cfg, ConfGraph &confgraph);
void RemoveCallingConventionKeeper(std::shared_ptr<FunctionDefItem> func, CFGType &cfg, ConfGraph &confgraph);
void ConductRegAllocForFunction(std::shared_ptr<FunctionDefItem> func);
void EnforcePhysicalRegs(CFGType &cfg) {
  using namespace opt;
  // process callee side
  auto entry_node = cfg.entry;
  auto func = cfg.corresponding_func;
  std::unordered_set<std::string> missing_caller_saved_regs;
  for (auto reg : caller_saved_regs) {
    missing_caller_saved_regs.insert(reg);
  }
  for (size_t i = 0; i < 8 && i < func->args_full_name.size(); i++) {
    auto new_def = std::make_shared<ForceDef>();
    new_def->var_full = "%reg." + arg_regs[i];
    new_def->ty = func->args[i];
    auto new_move = std::make_shared<MoveInstruct>();
    new_move->src_full = "%reg." + arg_regs[i];
    new_move->dest_full = func->args_full_name[i];
    new_move->ty = func->args[i];
    entry_node->corresponding_block->actions.push_front(new_move);
    entry_node->corresponding_block->actions.push_front(new_def);
    missing_caller_saved_regs.erase(arg_regs[i]);
  }
  for (size_t i = 8; i < func->args_full_name.size(); i++) {
    auto arg_load = std::make_shared<LoadSpilledArgs>();
    arg_load->arg_id = i;
    arg_load->var_full = func->args_full_name[i];
    arg_load->ty = func->args[i];
    entry_node->corresponding_block->actions.push_front(arg_load);
  }
  for (auto callee_saved_reg : callee_saved_regs) {
    auto new_def = std::make_shared<ForceDef>();
    new_def->var_full = "%reg." + callee_saved_reg;
    new_def->ty = LLVMIRIntType(32);
    auto new_move = std::make_shared<MoveInstruct>();
    new_move->src_full = new_def->var_full;
    new_move->dest_full = "%calleesave." + callee_saved_reg;
    new_move->ty = LLVMIRIntType(32);
    entry_node->corresponding_block->actions.push_front(new_move);
    entry_node->corresponding_block->actions.push_front(new_def);
  }
  for (auto node : cfg.nodes) {
    auto block = node->corresponding_block;
    if (std::dynamic_pointer_cast<RETAction>(block->exit_action)) {
      for (auto callee_saved_reg : callee_saved_regs) {
        auto new_move = std::make_shared<MoveInstruct>();
        new_move->src_full = "%calleesave." + callee_saved_reg;
        new_move->dest_full = "%reg." + callee_saved_reg;
        new_move->ty = LLVMIRIntType(32);
        auto new_use = std::make_shared<ForceUse>();
        new_use->var_full = "%reg." + callee_saved_reg;
        block->actions.push_back(new_move);
        block->actions.push_back(new_use);
      }
      if (!std::holds_alternative<LLVMVOIDType>(std::dynamic_pointer_cast<RETAction>(block->exit_action)->type)) {
        auto new_move = std::make_shared<MoveInstruct>();
        new_move->src_full = std::dynamic_pointer_cast<RETAction>(block->exit_action)->value;
        new_move->dest_full = "%reg.x10";
        new_move->ty = std::dynamic_pointer_cast<RETAction>(block->exit_action)->type;
        if (new_move->src_full == "%reg.x10" && new_move->dest_full == "%reg.x10") throw std::runtime_error("error");
        block->actions.push_back(new_move);
        std::dynamic_pointer_cast<RETAction>(block->exit_action)->value = "%reg.x10";
      }
    }
  }
  // TODO: process caller side
  for (auto node : cfg.nodes) {
    auto block = node->corresponding_block;
    for (auto it_act = block->actions.begin(); it_act != block->actions.end(); ++it_act) {
      if (!std::dynamic_pointer_cast<CallItem>(*it_act)) continue;
      auto it_next = it_act;
      ++it_next;
      auto call_act = std::dynamic_pointer_cast<CallItem>(*it_act);
      if (!std::holds_alternative<LLVMVOIDType>(call_act->return_type)) {
        auto return_value_collect = std::make_shared<MoveInstruct>();
        return_value_collect->ty = call_act->return_type;
        return_value_collect->src_full = "%reg.x10";
        return_value_collect->dest_full = call_act->result_full;
        block->actions.insert(it_next, return_value_collect);
        call_act->result_full = "%reg.x10";
      }
      std::unordered_set<std::string> caller_saved_regs_to_process;
      for (auto reg : caller_saved_regs) {
        caller_saved_regs_to_process.insert(reg);
        missing_caller_saved_regs.erase(reg);
      }
      for (size_t i = 0; i < call_act->args_val_full.size() & i < 8; i++) {
        auto new_move = std::make_shared<MoveInstruct>();
        new_move->ty = call_act->args_ty[i];
        new_move->src_full = call_act->args_val_full[i];
        new_move->dest_full = "%reg." + arg_regs[i];
        block->actions.insert(it_act, new_move);
        call_act->args_val_full[i] = "%reg." + arg_regs[i];
        caller_saved_regs_to_process.erase(arg_regs[i]);
      }
      if (call_act->args_val_full.size() > 8) {
        for (size_t i = call_act->args_val_full.size() - 1; i >= 8; i--) {
          auto new_store = std::make_shared<StoreSpilledArgs>();
          new_store->arg_id = i;
          new_store->var_full = call_act->args_val_full[i];
          new_store->ty = call_act->args_ty[i];
          block->actions.insert(it_act, new_store);
          if (i == call_act->args_val_full.size() - 1) {
            new_store->move_sp_down = call_act->args_val_full.size() - 8;
          } else {
            new_store->move_sp_down = 0;
          }
        }
        call_act->move_sp_up = call_act->args_val_full.size() - 8;
        call_act->args_val_full.resize(8);
        call_act->args_ty.resize(8);
      } else {
        call_act->move_sp_up = 0;
      }
      for (auto reg : caller_saved_regs_to_process) {
        auto new_def = std::make_shared<ForceDef>();
        new_def->var_full = "%reg." + reg;
        new_def->ty = LLVMIRIntType(32);
        block->actions.insert(it_act, new_def);
      }
      for (auto reg : caller_saved_regs) {
        auto new_use = std::make_shared<ForceUse>();
        new_use->var_full = "%reg." + reg;
        block->actions.insert(it_next, new_use);
      }
      it_act = it_next;
      --it_act;
    }
  }
  // avoid missing some caller saved regs
  for (auto reg : missing_caller_saved_regs) {
    auto new_def = std::make_shared<ForceDef>();
    new_def->var_full = "%reg." + reg;
    new_def->ty = LLVMIRIntType(32);
    auto new_use = std::make_shared<ForceUse>();
    new_use->var_full = "%reg." + reg;
    entry_node->corresponding_block->actions.push_front(new_use);
    entry_node->corresponding_block->actions.push_front(new_def);
  }
}
void TranslateColorResult(std::shared_ptr<FunctionDefItem> func, CFGType &cfg, ConfGraph &confgraph) {
  using namespace opt;
  std::unordered_map<std::string, size_t> spilled_var_to_id;
  auto &var_to_id = cfg.var_to_id;
  auto ApplyColoringResult = [&](std::string &var) {
    auto confnode = confgraph.id_to_node[var_to_id[var]];
    confnode = ConfGraphNode::FindFather(confnode);
    if (!confnode->is_binded_with_physical_reg) {
      if (spilled_var_to_id.find(var) != spilled_var_to_id.end()) {
        var = "#" + std::to_string(spilled_var_to_id[var]);
      } else {
        spilled_var_to_id[var] = func->spilled_vars++;
        var = "#" + std::to_string(spilled_var_to_id[var]);
      }
    } else {
      var = "$reg." + std::to_string(confnode->color);
    }
  };
  func->spilled_vars = 0;
  for (auto node : cfg.nodes) {
    auto block = node->corresponding_block;
    std::vector<size_t> cur_node_use;
    std::vector<size_t> cur_node_def;
    bool use_def_init = false;
    for (auto act : block->actions) {
      if (auto br_act = std::dynamic_pointer_cast<BRAction>(act)) {
        throw std::runtime_error("BRAction should not exist in the middle of a block");
      } else if (auto ret_act = std::dynamic_pointer_cast<RETAction>(act)) {
        throw std::runtime_error("RETAction should not exist in the middle of a block");
      } else if (auto bin_act = std::dynamic_pointer_cast<BinaryOperationAction>(act)) {
        if (var_to_id.find(bin_act->operand1_full) != var_to_id.end()) {
          ApplyColoringResult(bin_act->operand1_full);
        }
        if (var_to_id.find(bin_act->operand2_full) != var_to_id.end()) {
          ApplyColoringResult(bin_act->operand2_full);
        }
        if (var_to_id.find(bin_act->result_full) != var_to_id.end()) {
          ApplyColoringResult(bin_act->result_full);
        }
      } else if (auto load_act = std::dynamic_pointer_cast<LoadAction>(act)) {
        if (var_to_id.find(load_act->ptr_full) != var_to_id.end()) {
          ApplyColoringResult(load_act->ptr_full);
        }
        if (var_to_id.find(load_act->result_full) != var_to_id.end()) {
          ApplyColoringResult(load_act->result_full);
        }
      } else if (auto store_act = std::dynamic_pointer_cast<StoreAction>(act)) {
        if (var_to_id.find(store_act->value_full) != var_to_id.end()) {
          ApplyColoringResult(store_act->value_full);
        }
        if (var_to_id.find(store_act->ptr_full) != var_to_id.end()) {
          ApplyColoringResult(store_act->ptr_full);
        }
      } else if (auto get_act = std::dynamic_pointer_cast<GetElementPtrAction>(act)) {
        std::unordered_set<std::string> used_vars;
        if (var_to_id.find(get_act->ptr_full) != var_to_id.end()) {
          ApplyColoringResult(get_act->ptr_full);
        }
        for (auto &idx : get_act->indices) {
          if (var_to_id.find(idx) != var_to_id.end()) {
            ApplyColoringResult(idx);
          }
        }
        if (var_to_id.find(get_act->result_full) != var_to_id.end()) {
          ApplyColoringResult(get_act->result_full);
        }
      } else if (auto icmp_act = std::dynamic_pointer_cast<ICMPAction>(act)) {
        if (var_to_id.find(icmp_act->operand1_full) != var_to_id.end()) {
          ApplyColoringResult(icmp_act->operand1_full);
        }
        if (var_to_id.find(icmp_act->operand2_full) != var_to_id.end()) {
          ApplyColoringResult(icmp_act->operand2_full);
        }
        if (var_to_id.find(icmp_act->result_full) != var_to_id.end()) {
          ApplyColoringResult(icmp_act->result_full);
        }
      } else if (auto call_act = std::dynamic_pointer_cast<CallItem>(act)) {
        for (auto &arg : call_act->args_val_full) {
          if (var_to_id.find(arg) != var_to_id.end()) {
            ApplyColoringResult(arg);
          }
        }
        if (!std::holds_alternative<LLVMVOIDType>(call_act->return_type) &&
            var_to_id.find(call_act->result_full) != var_to_id.end()) {
          ApplyColoringResult(call_act->result_full);
        }
      } else if (auto select_act = std::dynamic_pointer_cast<SelectItem>(act)) {
        if (var_to_id.find(select_act->cond_full) != var_to_id.end()) {
          ApplyColoringResult(select_act->cond_full);
        }
        if (var_to_id.find(select_act->true_val_full) != var_to_id.end()) {
          ApplyColoringResult(select_act->true_val_full);
        }
        if (var_to_id.find(select_act->false_val_full) != var_to_id.end()) {
          ApplyColoringResult(select_act->false_val_full);
        }
        if (var_to_id.find(select_act->result_full) != var_to_id.end()) {
          ApplyColoringResult(select_act->result_full);
        }
      } else if (auto move_act = std::dynamic_pointer_cast<MoveInstruct>(act)) {
        if (VRegCheck(move_act->src_full) && var_to_id.find(move_act->src_full) != var_to_id.end()) {
          ApplyColoringResult(move_act->src_full);
        }
        if (var_to_id.find(move_act->dest_full) != var_to_id.end()) {
          ApplyColoringResult(move_act->dest_full);
        }
      } else if (auto force_def_act = std::dynamic_pointer_cast<ForceDef>(act)) {
        if (var_to_id.find(force_def_act->var_full) != var_to_id.end()) {
          ApplyColoringResult(force_def_act->var_full);
        }
      } else if (auto force_use_act = std::dynamic_pointer_cast<ForceUse>(act)) {
        if (var_to_id.find(force_use_act->var_full) != var_to_id.end()) {
          ApplyColoringResult(force_use_act->var_full);
        }
      } else if (auto load_spilled_args_act = std::dynamic_pointer_cast<LoadSpilledArgs>(act)) {
        if (var_to_id.find(load_spilled_args_act->var_full) != var_to_id.end()) {
          ApplyColoringResult(load_spilled_args_act->var_full);
        }
      } else if (auto store_spilled_args_act = std::dynamic_pointer_cast<StoreSpilledArgs>(act)) {
        if (var_to_id.find(store_spilled_args_act->var_full) != var_to_id.end()) {
          ApplyColoringResult(store_spilled_args_act->var_full);
        }
      } else if (auto alloca_act = std::dynamic_pointer_cast<AllocaAction>(act)) {
        ApplyColoringResult(alloca_act->name_full);
      }
    }
    {
      auto act = block->exit_action;
      if (auto br_act = std::dynamic_pointer_cast<BRAction>(act)) {
        if (auto beq_act = std::dynamic_pointer_cast<BEQAction>(br_act)) {
          if (var_to_id.find(beq_act->rs1) != var_to_id.end()) {
            ApplyColoringResult(beq_act->rs1);
          }
          if (var_to_id.find(beq_act->rs2) != var_to_id.end()) {
            ApplyColoringResult(beq_act->rs2);
          }
        } else if (auto bne_act = std::dynamic_pointer_cast<BNEAction>(br_act)) {
          if (var_to_id.find(bne_act->rs1) != var_to_id.end()) {
            ApplyColoringResult(bne_act->rs1);
          }
          if (var_to_id.find(bne_act->rs2) != var_to_id.end()) {
            ApplyColoringResult(bne_act->rs2);
          }
        } else if (auto blt_act = std::dynamic_pointer_cast<BLTAction>(br_act)) {
          if (var_to_id.find(blt_act->rs1) != var_to_id.end()) {
            ApplyColoringResult(blt_act->rs1);
          }
          if (var_to_id.find(blt_act->rs2) != var_to_id.end()) {
            ApplyColoringResult(blt_act->rs2);
          }
        } else if (auto bge_act = std::dynamic_pointer_cast<BGEAction>(br_act)) {
          if (var_to_id.find(bge_act->rs1) != var_to_id.end()) {
            ApplyColoringResult(bge_act->rs1);
          }
          if (var_to_id.find(bge_act->rs2) != var_to_id.end()) {
            ApplyColoringResult(bge_act->rs2);
          }
        } else {
          if (var_to_id.find(br_act->cond) != var_to_id.end()) {
            ApplyColoringResult(br_act->cond);
          }
        }
      } else if (auto ret_act = std::dynamic_pointer_cast<RETAction>(act)) {
        if (!std::holds_alternative<LLVMVOIDType>(ret_act->type) && var_to_id.find(ret_act->value) != var_to_id.end()) {
          ApplyColoringResult(ret_act->value);
        }
      }
    }
    for (auto act_it = block->actions.begin(); act_it != block->actions.end(); ++act_it) {
      bool need_remove = false;
      if (auto move_act = std::dynamic_pointer_cast<MoveInstruct>(*act_it)) {
        if (move_act->src_full == move_act->dest_full) {
          need_remove = true;
        }
      }
      // else if (auto force_def_act = std::dynamic_pointer_cast<ForceDef>(*act_it)) {
      //   need_remove = true;
      // } else if (auto force_use_act = std::dynamic_pointer_cast<ForceUse>(*act_it)) {
      //   need_remove = true;
      // }
      if (need_remove) {
        auto it_next = act_it;
        ++it_next;
        block->actions.erase(act_it);
        act_it = it_next;
        --act_it;
      }
    }
  }
}

void PairMoveEliminate(std::shared_ptr<FunctionDefItem> func, CFGType &cfg, ConfGraph &confgraph) {
  for (auto node : cfg.nodes) {
    auto block = node->corresponding_block;
    auto it = block->actions.begin();
    while (it != block->actions.end()) {
      while (it != block->actions.end() && !std::dynamic_pointer_cast<opt::MoveInstruct>(*it)) {
        ++it;
      }
      if (it == block->actions.end()) break;
      std::unordered_map<std::string, std::list<std::shared_ptr<ActionItem>>::iterator> defined_by;
      do {
        auto cur_move = std::dynamic_pointer_cast<opt::MoveInstruct>(*it);
        if (defined_by.find(cur_move->src_full) != defined_by.end() &&
            std::dynamic_pointer_cast<opt::MoveInstruct>(*defined_by[cur_move->src_full])->src_full ==
                cur_move->dest_full) {
          auto it_next = it;
          ++it_next;
          block->actions.erase(it);
          it = it_next;
        } else {
          defined_by[cur_move->dest_full] = it;
          ++it;
        }
      } while (it != block->actions.end() && std::dynamic_pointer_cast<opt::MoveInstruct>(*it));
    }
  }
}

void RemoveCallingConventionKeeper(std::shared_ptr<FunctionDefItem> func, CFGType &cfg, ConfGraph &confgraph) {
  for (auto node : cfg.nodes) {
    auto block = node->corresponding_block;
    std::vector<std::list<std::shared_ptr<ActionItem>>::iterator> act_to_move;
    for (auto it = block->actions.begin(); it != block->actions.end(); ++it) {
      if (std::dynamic_pointer_cast<opt::ForceDef>(*it) || std::dynamic_pointer_cast<opt::ForceUse>(*it)) {
        act_to_move.push_back(it);
      }
    }
    for (auto it : act_to_move) {
      block->actions.erase(it);
    }
  }
}

void ConductRegAllocForFunction(std::shared_ptr<FunctionDefItem> func) {
  std::cerr << "processing function " << func->func_name_raw << std::endl;
  CFGType cfg;
  ConfGraph confgraph;
  cfg = BuildCFGForFunction(func);
  EnforcePhysicalRegs(cfg);
  // func->RecursivePrint(std::cerr);
  do {
    cfg.init();
    cfg = BuildCFGForFunction(func);
    LiveAnalysis(cfg);
    confgraph.init();
    confgraph = BuildConfGraph(cfg);
  } while (ConductColoring(func, cfg, confgraph));
  TranslateColorResult(func, cfg, confgraph);
  RemoveCallingConventionKeeper(func, cfg, confgraph);
  PairMoveEliminate(func, cfg, confgraph);
  // func->RecursivePrint(std::cerr);
}

std::shared_ptr<ModuleItem> RegAlloc(std::shared_ptr<ModuleItem> src) {
  auto res = src;
  for (auto &func : res->function_defs) {
    // func = std::make_shared<FunctionDefItem>(*func);
    ConductRegAllocForFunction(func);
  }
  return res;
}