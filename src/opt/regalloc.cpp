#include "regalloc.h"
#include "IR/IR_basic.h"
#include "cfg.h"
#include "confgraph.h"
#include "liveanalysis.h"
#include "phieliminate.h"
#include "tools.h"

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
        for (size_t i = 8; i < call_act->args_val_full.size(); i++) {
          auto new_store = std::make_shared<StoreSpilledArgs>();
          new_store->arg_id = i;
          new_store->var_full = call_act->args_val_full[i];
          new_store->ty = call_act->args_ty[i];
          block->actions.insert(it_act, new_store);
        }
        call_act->args_val_full.resize(8);
        call_act->args_ty.resize(8);
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
void ConductRegAllocForFunction(std::shared_ptr<FunctionDefItem> func) {
  std::cerr << "processing function " << func->func_name_raw << std::endl;
  CFGType cfg;
  ConfGraph confgraph;
  cfg = BuildCFGForFunction(func);
  EnforcePhysicalRegs(cfg);
  func->RecursivePrint(std::cerr);
  do {
    cfg.init();
    cfg = BuildCFGForFunction(func);
    LiveAnalysis(cfg);
    confgraph.init();
    confgraph = BuildConfGraph(cfg);
  } while (ConductColoring(func, cfg, confgraph));
}

std::shared_ptr<ModuleItem> RegAlloc(std::shared_ptr<ModuleItem> src) {
  auto res = src;
  for (auto &func : res->function_defs) {
    // func = std::make_shared<FunctionDefItem>(*func);
    ConductRegAllocForFunction(func);
  }
  return res;
}