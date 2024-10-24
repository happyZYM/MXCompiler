#include "IR/IR_basic.h"
#include "opt/gen.h"
namespace OptBackend {
void RemoveJumpOnlyBlock(FunctionDefItem *func);

std::string FindFinalDestination(std::string cur, std::unordered_map<std::string, std::string> &rerouted_to,
                                 std::unordered_set<std::string> &visited) {
  if (visited.find(cur) != visited.end()) return cur;
  if (rerouted_to.find(cur) == rerouted_to.end()) throw std::runtime_error("reroute not found");
  std::string next = rerouted_to[cur];
  if (rerouted_to.find(next) == rerouted_to.end()) return next;
  visited.insert(cur);
  return rerouted_to[cur] = FindFinalDestination(next, rerouted_to, visited);
}
void RemoveJumpOnlyBlock(FunctionDefItem *func) {
  std::unordered_map<std::string, std::vector<std::string *>> reverse_lookup;
  if (auto block = func->init_block) {
    if (auto br_act = std::dynamic_pointer_cast<BRAction>(block->exit_action)) {
      reverse_lookup[br_act->true_label_full].push_back(&br_act->true_label_full);
      reverse_lookup[br_act->false_label_full].push_back(&br_act->false_label_full);
    } else if (auto uncond = std::dynamic_pointer_cast<UNConditionJMPAction>(block->exit_action)) {
      reverse_lookup[uncond->label_full].push_back(&uncond->label_full);
    }
  }
  for (auto block : func->basic_blocks) {
    if (auto br_act = std::dynamic_pointer_cast<BRAction>(block->exit_action)) {
      reverse_lookup[br_act->true_label_full].push_back(&br_act->true_label_full);
      reverse_lookup[br_act->false_label_full].push_back(&br_act->false_label_full);
    } else if (auto uncond = std::dynamic_pointer_cast<UNConditionJMPAction>(block->exit_action)) {
      reverse_lookup[uncond->label_full].push_back(&uncond->label_full);
    }
  }
  std::unordered_set<std::string> block_need_remove;
  std::unordered_map<std::string, std::string> rerouted_to;
  for (auto block : func->basic_blocks) {
    if (block->actions.size() == 0 && std::dynamic_pointer_cast<UNConditionJMPAction>(block->exit_action)) {
      auto uncond = std::dynamic_pointer_cast<UNConditionJMPAction>(block->exit_action);
      // for (auto label : reverse_lookup[uncond->label_full]) {
      // *label = uncond->label_full;
      // }
      rerouted_to[block->label_full] = uncond->label_full;
      block_need_remove.insert(block->label_full);
    }
  }
  for (auto [src, _] : rerouted_to) {
    for (auto label : reverse_lookup[src]) {
      std::unordered_set<std::string> tmp;
      *label = FindFinalDestination(*label, rerouted_to, tmp);
    }
  }
  auto tmp = func->basic_blocks;
  func->basic_blocks.clear();
  for (auto block : tmp) {
    if (block_need_remove.find(block->label_full) == block_need_remove.end()) {
      func->basic_blocks.push_back(block);
    }
  }
}
void GenerateOptASM(std::ostream &os, std::shared_ptr<ModuleItem> prog) {
  auto riscv = std::make_shared<RISCVProgItem>();

  for (auto conststr : prog->const_strs) {
    auto asm_item = std::make_shared<RISCVConstStrItem>();
    riscv->const_strs.push_back(asm_item);
    asm_item->content = conststr->string_raw;
    asm_item->full_label = ".str." + std::to_string(conststr->const_str_id);
  }
  for (auto global_var : prog->global_var_defs) {
    auto asm_item = std::make_shared<RISCVGlobalVarItem>();
    riscv->global_vars.push_back(asm_item);
    asm_item->full_label = ".var.global." + global_var->name_raw + ".addrkp";
  }
  std::unordered_map<std::string, FuncLayout> func_layouts;
  for (auto func_def : prog->function_defs) {
    // if (func_def->init_block) {
    //   for (auto act : func_def->init_block->actions) {
    //     ScanForVar(func_layouts[func_def->func_name_raw], act, prog->low_level_class_info);
    //   }
    // }
    // for (auto block : func_def->basic_blocks) {
    //   for (auto act : block->actions) {
    //     ScanForVar(func_layouts[func_def->func_name_raw], act, prog->low_level_class_info);
    //   }
    // }
    FuncLayout &layout = func_layouts[func_def->func_name_raw];
    // for (size_t i = 0; i < func_def->args_full_name.size(); i++) {
    //   layout.arg_offset[func_def->args_full_name[i]] = i;
    // }
    for (size_t i = 0; i < func_def->spilled_vars; i++) {
      layout.AllocateItem("#" + std::to_string(i), 4, 1);
    }
    // debug:

    // std::cerr << "layout info of function " << func_def->func_name_raw << std::endl;
    // std::cerr << "\tcur_pos=" << layout.cur_pos << std::endl;
    // std::cerr << "\ttotal_frame_size=" << layout.total_frame_size << std::endl;
    // for (const auto &item : layout.local_items) {
    //   std::cerr << "\t" << item.first << " " << item.second << std::endl;
    // }
  }

  for (auto func_def : prog->function_defs) {
    std::cerr << "generating asm for function " << func_def->func_name_raw << std::endl;
    RemoveJumpOnlyBlock(func_def.get());
    auto func_asm = std::make_shared<RISCVFuncItem>();
    riscv->funcs.push_back(func_asm);
    func_asm->full_label = func_def->func_name_raw;
    FuncLayout &layout = func_layouts[func_def->func_name_raw];
    if (layout.total_frame_size < 2048) {
      func_asm->code_lines.push_back("addi sp, sp, -" + std::to_string(layout.total_frame_size));
      func_asm->code_lines.push_back("sw ra, " + std::to_string(layout.total_frame_size - 4) + "(sp)");
      func_asm->code_lines.push_back("sw s0, " + std::to_string(layout.total_frame_size - 8) + "(sp)");
      func_asm->code_lines.push_back("addi s0, sp, " + std::to_string(layout.total_frame_size));
      func_asm->code_lines.push_back("sw s0, " + std::to_string(layout.total_frame_size - 12) + "(sp)");
    } else {
      func_asm->code_lines.push_back("li x31, " + std::to_string(layout.total_frame_size));
      func_asm->code_lines.push_back("sub sp, sp, x31");
      func_asm->code_lines.push_back("add x31, x31, sp");
      func_asm->code_lines.push_back("sw ra, -4(x31)");
      func_asm->code_lines.push_back("sw s0, -8(x31)");
      func_asm->code_lines.push_back("sw x31, -12(x31)");
      func_asm->code_lines.push_back("mv s0, t0");
    }
    if (func_def->init_block) {
      func_asm->code_lines.push_back(".entrylabel." + func_def->init_block->label_full + ":");
      for (auto act : func_def->init_block->actions) {
        OptBackend::GenerateASM(act, func_asm->code_lines, func_layouts[func_def->func_name_raw],
                                prog->low_level_class_info);
      }
      OptBackend::GenerateASM(func_def->init_block->exit_action, func_asm->code_lines,
                              func_layouts[func_def->func_name_raw], prog->low_level_class_info);
    }
    for (auto block : func_def->basic_blocks) {
      if (func_asm->code_lines.size() > 0 && func_asm->code_lines.back() == "j .entrylabel." + block->label_full) {
        func_asm->code_lines.pop_back();  // remove redundant jump
      }
      func_asm->code_lines.push_back(".entrylabel." + block->label_full + ":");
      for (auto act : block->actions) {
        OptBackend::GenerateASM(act, func_asm->code_lines, func_layouts[func_def->func_name_raw],
                                prog->low_level_class_info);
      }
      OptBackend::GenerateASM(block->exit_action, func_asm->code_lines, func_layouts[func_def->func_name_raw],
                              prog->low_level_class_info);
    }
  }

  riscv->RecursivePrint(os);
}
}  // namespace OptBackend