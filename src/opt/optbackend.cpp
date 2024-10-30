#include <cstdint>
#include <sstream>
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

  size_t tmp_label_counter = 0;
  for (auto func_def : prog->function_defs) {
    std::cerr << "generating asm for function " << func_def->func_name_raw << std::endl;
    RemoveJumpOnlyBlock(func_def.get());
    auto func_asm = std::make_shared<RISCVFuncItem>();
    riscv->funcs.push_back(func_asm);
    func_asm->full_label = func_def->func_name_raw;
    FuncLayout &layout = func_layouts[func_def->func_name_raw];
    std::vector<std::string> code_line_tmp;
    if (layout.total_frame_size < 2048) {
      code_line_tmp.push_back("addi sp, sp, -" + std::to_string(layout.total_frame_size));
      code_line_tmp.push_back("sw ra, " + std::to_string(layout.total_frame_size - 4) + "(sp)");
      code_line_tmp.push_back("sw s0, " + std::to_string(layout.total_frame_size - 8) + "(sp)");
      code_line_tmp.push_back("addi s0, sp, " + std::to_string(layout.total_frame_size));
      code_line_tmp.push_back("sw s0, " + std::to_string(layout.total_frame_size - 12) + "(sp)");
    } else {
      code_line_tmp.push_back("li x31, " + std::to_string(layout.total_frame_size));
      code_line_tmp.push_back("sub sp, sp, x31");
      code_line_tmp.push_back("add x31, x31, sp");
      code_line_tmp.push_back("sw ra, -4(x31)");
      code_line_tmp.push_back("sw s0, -8(x31)");
      code_line_tmp.push_back("sw x31, -12(x31)");
      code_line_tmp.push_back("mv s0, x31");
    }
    if (func_def->init_block) {
      code_line_tmp.push_back(".entrylabel." + func_def->init_block->label_full + ":");
      for (auto act : func_def->init_block->actions) {
        OptBackend::GenerateASM(act, code_line_tmp, func_layouts[func_def->func_name_raw], prog->low_level_class_info);
      }
      OptBackend::GenerateASM(func_def->init_block->exit_action, code_line_tmp, func_layouts[func_def->func_name_raw],
                              prog->low_level_class_info);
    }
    for (auto block : func_def->basic_blocks) {
      if (code_line_tmp.size() > 0 && code_line_tmp.back() == "j .entrylabel." + block->label_full) {
        code_line_tmp.pop_back();  // remove redundant jump
      }
      code_line_tmp.push_back(".entrylabel." + block->label_full + ":");
      for (auto act : block->actions) {
        OptBackend::GenerateASM(act, code_line_tmp, func_layouts[func_def->func_name_raw], prog->low_level_class_info);
      }
      OptBackend::GenerateASM(block->exit_action, code_line_tmp, func_layouts[func_def->func_name_raw],
                              prog->low_level_class_info);
    }
    std::unordered_map<std::string, int64_t> label_to_line;
    std::vector<std::string> code_line_tmp2;
    bool branch_replaced = false;
    std::unordered_set<std::string> is_branch;
    is_branch.insert("beq");
    is_branch.insert("bne");
    is_branch.insert("blt");
    is_branch.insert("bge");
    is_branch.insert("bnez");
    is_branch.insert("beqz");
    do {
      branch_replaced = false;
      code_line_tmp2.clear();
      label_to_line.clear();
      for (size_t i = 0; i < code_line_tmp.size(); i++) {
        if (code_line_tmp[i].substr(0, 12) == ".entrylabel.") {
          label_to_line[code_line_tmp[i].substr(0, code_line_tmp[i].size() - 1)] = i;
        }
      }
      for (size_t i = 0; i < code_line_tmp.size(); i++) {
        std::stringstream ss(code_line_tmp[i]);
        std::string tmp;
        std::string label;
        std::vector<std::string> tokens;
        while (ss >> tmp) {
          label = tmp;
          tokens.push_back(tmp);
        }
        if (is_branch.find(tokens[0]) != is_branch.end()) {
          if (label_to_line.find(label) == label_to_line.end()) {
            goto write;
            throw std::runtime_error("label " + label + " not found");
          }
          int64_t delta = label_to_line[label] - static_cast<int64_t>(i);
          if (delta < -2000 || delta > 2000) {
            std::string tmp_label_name = ".entrylabel.tmp_label." + std::to_string(tmp_label_counter++);
            ss.clear();
            if (tokens[0] == "beq") {
              tokens[0] = "bne";
            } else if (tokens[0] == "bne") {
              tokens[0] = "beq";
            } else if (tokens[0] == "blt") {
              tokens[0] = "bge";
            } else if (tokens[0] == "bge") {
              tokens[0] = "blt";
            } else if (tokens[0] == "bnez") {
              tokens[0] = "beqz";
            } else if (tokens[0] == "beqz") {
              tokens[0] = "bnez";
            } else {
              throw std::runtime_error("unknown branch type");
            }
            for (size_t j = 0; j < tokens.size() - 1; j++) {
              ss << tokens[j] << " ";
            }
            ss << tmp_label_name;
            code_line_tmp2.push_back(ss.str());
            code_line_tmp2.push_back("j " + label);
            code_line_tmp2.push_back(tmp_label_name + ":");
            branch_replaced = true;
          } else {
            code_line_tmp2.push_back(code_line_tmp[i]);
          }
        } else {
          code_line_tmp2.push_back(code_line_tmp[i]);
        }
      }
      code_line_tmp = code_line_tmp2;
    } while (branch_replaced);
    write:
    for (const auto &code : code_line_tmp) {
      func_asm->code_lines.push_back(code);
    }
  }

  riscv->RecursivePrint(os);
}
}  // namespace OptBackend