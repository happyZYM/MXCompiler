#include "naivebackend.h"
#include <unordered_map>
#include "IR/IR_basic.h"
#include "build_layout.hpp"
using namespace NaiveBackend;
void GenerateNaiveASM(std::ostream &os, std::shared_ptr<ModuleItem> prog) {
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
    if (func_def->init_block) {
      for (auto act : func_def->init_block->actions) {
        ScanForVar(func_layouts[func_def->func_name_raw], act);
      }
    }
    for (auto block : func_def->basic_blocks) {
      for (auto act : block->actions) {
        ScanForVar(func_layouts[func_def->func_name_raw], act);
      }
    }
    FuncLayout &layout = func_layouts[func_def->func_name_raw];
    for (size_t i = 0; i < func_def->args_full_name.size(); i++) {
      layout.arg_offset[func_def->args_full_name[i]] = i;
    }
    // debug:

    std::cerr << "layout info of function " << func_def->func_name_raw << std::endl;
    std::cerr << "\tcur_pos=" << layout.cur_pos << std::endl;
    std::cerr << "\ttotal_frame_size=" << layout.total_frame_size << std::endl;
    for (const auto &item : layout.local_items) {
      std::cerr << "\t" << item.first << " " << item.second << std::endl;
    }
  }

  for (auto func_def : prog->function_defs) {
    auto func_asm = std::make_shared<RISCVFuncItem>();
    riscv->funcs.push_back(func_asm);
    func_asm->full_label = func_def->func_name_raw;
    if (func_def->init_block) {
      func_asm->code_lines.push_back(".entrylabel." + func_def->init_block->label_full + ":");
    }
    for (auto block : func_def->basic_blocks) {
      func_asm->code_lines.push_back(".entrylabel." + block->label_full + ":");
    }
  }

  riscv->RecursivePrint(os);
}