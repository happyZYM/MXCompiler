#include "regalloc.h"
#include "IR/IR_basic.h"
#include "liveanalysis.h"
#include "tools.h"

// RISC-V calling convention compatible
static std::vector<std::string> held_tmp_regs = {"x28", "x29", "x30", "x31"};
static std::vector<std::string> callee_saved_regs = {"x3",  "x4",  "x9",  "x18", "x19", "x20", "x21",
                                                     "x22", "x23", "x24", "x25", "x26", "x27"};
static std::vector<std::string> caller_saved_regs = {"x5",  "x6",  "x7",  "x10", "x11", "x12",
                                                     "x13", "x14", "x15", "x16", "x17"};
static std::vector<std::string> arg_regs = {"x10", "x11", "x12", "x13", "x14", "x15", "x16", "x17"};
static std::string zero = "x0", sp = "x2", ra = "x1", fp = "x8";
void EnforcePhysicalRegs(CFGType &cfg) {
  using namespace opt;
  // process callee side
  auto entry_node = cfg.entry;
  auto func = cfg.corresponding_func;
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
        block->actions.push_back(new_move);
        std::dynamic_pointer_cast<RETAction>(block->exit_action)->value = "%reg.x10";
      }
    }
  }
  // TODO: process caller side
}
void ConductRegAllocForFunction([[maybe_unused]] std::shared_ptr<FunctionDefItem> func, CFGType &cfg) {
  EnforcePhysicalRegs(cfg);
  LiveAnalysis(cfg);
}

std::shared_ptr<ModuleItem> RegAlloc(std::shared_ptr<ModuleItem> src) {
  auto res = src;
  for (auto &func : res->function_defs) {
    // func = std::make_shared<FunctionDefItem>(*func);
    auto cfg = BuildCFGForFunction(func);
    ConductRegAllocForFunction(func, cfg);
  }
  return res;
}