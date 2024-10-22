#include "opt/gen.h"
namespace OptBackend {
std::string cur_block_label_for_phi;
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
      if (func_def->init_block->exit_action->corresponding_phi) {
        OptBackend::cur_block_label_for_phi = func_def->init_block->label_full;
        OptBackend::GenerateASM(func_def->init_block->exit_action->corresponding_phi, func_asm->code_lines,
                                func_layouts[func_def->func_name_raw], prog->low_level_class_info);
      }
      OptBackend::GenerateASM(func_def->init_block->exit_action, func_asm->code_lines,
                              func_layouts[func_def->func_name_raw], prog->low_level_class_info);
    }
    for (auto block : func_def->basic_blocks) {
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