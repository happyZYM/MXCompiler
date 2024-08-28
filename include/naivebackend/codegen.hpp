#pragma once
#include <stdexcept>
#include "naivebackend.h"
namespace NaiveBackend {
inline void GenerateASM(std::shared_ptr<ActionItem> act, std::vector<std::string> &code_lines, FuncLayout &layout,
                        const std::unordered_map<std::string, IRClassInfo> &low_level_class_info,
                        bool process_phi = false) {
  if (auto br_act = std::dynamic_pointer_cast<BRAction>(act)) {
    IRVar2RISCVReg(br_act->cond, 1, "t0", layout, code_lines);
    code_lines.push_back("bnez t0, .entrylabel." + br_act->true_label_full);
    code_lines.push_back("j .entrylabel." + br_act->false_label_full);
  } else if (auto jmp_act = std::dynamic_pointer_cast<UNConditionJMPAction>(act)) {
    code_lines.push_back("j .entrylabel." + jmp_act->label_full);
  } else if (auto ret_act = std::dynamic_pointer_cast<RETAction>(act)) {
    if (!std::holds_alternative<LLVMVOIDType>(ret_act->type)) {
      size_t sz = CalcSize(ret_act->type);
      IRVar2RISCVReg(ret_act->value, sz, "a0", layout, code_lines);
    }
    code_lines.push_back("lw ra, -4(s0)");
    code_lines.push_back("lw s0, -8(s0)");
    code_lines.push_back("addi sp, sp, " + std::to_string(layout.total_frame_size));
    code_lines.push_back("ret");
  } else if (auto binary_act = std::dynamic_pointer_cast<BinaryOperationAction>(act)) {
    size_t sz = CalcSize(binary_act->type);
    IRVar2RISCVReg(binary_act->operand1_full, sz, "t0", layout, code_lines);
    IRVar2RISCVReg(binary_act->operand2_full, sz, "t1", layout, code_lines);
    if (binary_act->op == "add") {
      code_lines.push_back("add t2, t0, t1");
    } else if (binary_act->op == "sub") {
      code_lines.push_back("sub t2, t0, t1");
    } else if (binary_act->op == "mul") {
      code_lines.push_back("mul t2, t0, t1");
    } else if (binary_act->op == "sdiv") {
      code_lines.push_back("div t2, t0, t1");
    } else if (binary_act->op == "srem") {
      code_lines.push_back("rem t2, t0, t1");
    } else if (binary_act->op == "and") {
      code_lines.push_back("and t2, t0, t1");
    } else if (binary_act->op == "or") {
      code_lines.push_back("or t2, t0, t1");
    } else if (binary_act->op == "xor") {
      code_lines.push_back("xor t2, t0, t1");
    } else if (binary_act->op == "shl") {
      code_lines.push_back("sll t2, t0, t1");
    } else if (binary_act->op == "ashr") {
      code_lines.push_back("sra t2, t0, t1");
    } else {
      throw std::runtime_error("Unknown binary operation");
    }
    GenerateWriteAccess(binary_act->result_full, sz, "t2", layout, code_lines);
  } else if (auto alloca_act = std::dynamic_pointer_cast<AllocaAction>(act)) {
    // just do nothing
  } else if (auto load_act = std::dynamic_pointer_cast<LoadAction>(act)) {
    size_t sz = CalcSize(load_act->ty);
    IRVar2RISCVReg(load_act->ptr_full, 4, "t0", layout, code_lines);
    if (sz == 1) {
      code_lines.push_back("lb t1, 0(t0)");
    } else if (sz == 4) {
      code_lines.push_back("lw t1, 0(t0)");
    } else {
      throw std::runtime_error("Unknown bytes");
    }
    GenerateWriteAccess(load_act->result_full, sz, "t1", layout, code_lines);
  } else if (auto store_act = std::dynamic_pointer_cast<StoreAction>(act)) {
    size_t sz = CalcSize(store_act->ty);
    IRVar2RISCVReg(store_act->ptr_full, 4, "t0", layout, code_lines);
    IRVar2RISCVReg(store_act->value_full, sz, "t1", layout, code_lines);
    if (sz == 1) {
      code_lines.push_back("sb t1, 0(t0)");
    } else if (sz == 4) {
      code_lines.push_back("sw t1, 0(t0)");
    } else {
      throw std::runtime_error("Unknown bytes");
    }
  } else if (auto get_element_act = std::dynamic_pointer_cast<GetElementPtrAction>(act)) {
    // TODO: implement this
  } else if (auto icmp_act = std::dynamic_pointer_cast<ICMPAction>(act)) {
    size_t sz = CalcSize(icmp_act->type);
    IRVar2RISCVReg(icmp_act->operand1_full, sz, "t0", layout, code_lines);
    IRVar2RISCVReg(icmp_act->operand2_full, sz, "t1", layout, code_lines);
    if (icmp_act->op == "eq") {
      code_lines.push_back("xor t2, t0, t1");
      code_lines.push_back("seqz t2, t2");
    } else if (icmp_act->op == "ne") {
      code_lines.push_back("xor t2, t0, t1");
      code_lines.push_back("snez t2, t2");
    } else if (icmp_act->op == "slt") {
      code_lines.push_back("slt t2, t0, t1");
    } else if (icmp_act->op == "sle") {
      code_lines.push_back("slt t2, t1, t0");
      code_lines.push_back("xori t2, t2, 1");
    } else if (icmp_act->op == "sgt") {
      code_lines.push_back("slt t2, t1, t0");
    } else if (icmp_act->op == "sge") {
      code_lines.push_back("slt t2, t0, t1");
      code_lines.push_back("xori t2, t2, 1");
    } else {
      throw std::runtime_error("Unknown icmp operation");
    }
    GenerateWriteAccess(icmp_act->result_full, 1, "t2", layout, code_lines);
  } else if (auto call_act = std::dynamic_pointer_cast<CallItem>(act)) {
    size_t num_of_args = call_act->args_ty.size();
    if (call_act->args_ty.size() != call_act->args_val_full.size()) {
      throw std::runtime_error("args_ty and args_full_name should have the same size");
    }
    for (size_t i = 0; i < num_of_args && i < 8; i++) {
      IRVar2RISCVReg(call_act->args_val_full[i], CalcSize(call_act->args_ty[i]), "a" + std::to_string(i), layout,
                     code_lines);
    }
    if (num_of_args >= 8) {
      size_t ps_delta = (num_of_args * 4 + 15) / 16 * 16;
      code_lines.push_back("addi sp, sp, -" + std::to_string(ps_delta));
      for (size_t i = 8; i < num_of_args; i++) {
        IRVar2RISCVReg(call_act->args_val_full[i], CalcSize(call_act->args_ty[i]), "t0", layout, code_lines);
        code_lines.push_back("sw t0, " + std::to_string((i - 8) * 4) + "(sp)");
      }
    }
    code_lines.push_back("call " + call_act->func_name_raw);
    if (call_act->result_full != "") {
      size_t ret_sz = CalcSize(call_act->return_type);
      GenerateWriteAccess(call_act->result_full, ret_sz, "a0", layout, code_lines);
    }
  } else if (auto phi_act = std::dynamic_pointer_cast<PhiItem>(act)) {
    if (!process_phi) {
      return;  // for efficiency, phi actions are implemented as store action in the previous block
    }
    // TODO: implement this
    // throw std::runtime_error("not implemented");
  } else if (auto select_act = std::dynamic_pointer_cast<SelectItem>(act)) {
    // TODO: implement this
    // throw std::runtime_error("not implemented");
  } else {
    throw std::runtime_error("Unknown action type");
  }
}
}  // namespace NaiveBackend