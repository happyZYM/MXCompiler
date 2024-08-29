#pragma once
#include <bit>
#include <stdexcept>
#include "naivebackend.h"
#include "tools.h"
namespace NaiveBackend {
extern std::string cur_block_label_for_phi;
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
    if (layout.total_frame_size < 2048) {
      code_lines.push_back("addi sp, sp, " + std::to_string(layout.total_frame_size));
    } else {
      code_lines.push_back("li t0, " + std::to_string(layout.total_frame_size));
      code_lines.push_back("add sp, sp, t0");
    }
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
    if (get_element_act->indices.size() == 1) {
      // array access
      IRVar2RISCVReg(get_element_act->ptr_full, 4, "t0", layout, code_lines);
      IRVar2RISCVReg(get_element_act->indices[0], 4, "t1", layout, code_lines);
      size_t element_sz = CalcSize(get_element_act->ty);
      code_lines.push_back("slli t1, t1, " + std::to_string(std::countr_zero(element_sz)));
      code_lines.push_back("add t2, t0, t1");
      GenerateWriteAccess(get_element_act->result_full, 4, "t2", layout, code_lines);
    } else if (get_element_act->indices.size() == 2) {
      // struct access
      if (get_element_act->indices[0] != "0") {
        throw std::runtime_error("struct access with non-zero offset is not supported");
      }
      size_t element_idx = std::stoull(get_element_act->indices[1]);
      auto class_ty = std::get<LLVMIRCLASSTYPE>(get_element_act->ty);
      const IRClassInfo &class_info = low_level_class_info.at(class_ty.class_name_full);
      size_t offset = class_info.member_var_pos_after_align[element_idx];
      IRVar2RISCVReg(get_element_act->ptr_full, 4, "t0", layout, code_lines);
      if (offset < 2048) {
        code_lines.push_back("addi t2, t0, " + std::to_string(offset));
      } else {
        code_lines.push_back("li t1, " + std::to_string(offset));
        code_lines.push_back("add t2, t0, t1");
      }
      GenerateWriteAccess(get_element_act->result_full, 4, "t2", layout, code_lines);
    } else {
      throw std::runtime_error("Unknown getelementptr indices size");
    }
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
    code_lines.push_back("addi sp, sp, -16");
    code_lines.push_back("sw a0, 0(sp)");
    for (size_t i = 0; i < num_of_args && i < 8; i++) {
      IRVar2RISCVReg(call_act->args_val_full[i], CalcSize(call_act->args_ty[i]), "a" + std::to_string(i), layout,
                     code_lines);
    }
    if (num_of_args >= 8) {
      size_t ps_delta = (num_of_args * 4 + 15) / 16 * 16;
      if (ps_delta < 2048) {
        code_lines.push_back("addi sp, sp, -" + std::to_string(ps_delta));
      } else {
        code_lines.push_back("li t0, -" + std::to_string(ps_delta));
        code_lines.push_back("add sp, sp, t0");
      }
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
    code_lines.push_back("lw a0, 0(sp)");
    code_lines.push_back("addi sp, sp, 16");
  } else if (auto phi_act = std::dynamic_pointer_cast<PhiItem>(act)) {
    if (!process_phi) {
      return;  // for efficiency, phi actions are implemented as store action in the previous block
    }
    std::string self_label = NaiveBackend::cur_block_label_for_phi;
    for (const auto &[val, label] : phi_act->values) {
      if (label == self_label) {
        size_t sz = CalcSize(phi_act->ty);
        IRVar2RISCVReg(val, sz, "t0", layout, code_lines);
        GenerateWriteAccess(phi_act->result_full, sz, "t0", layout, code_lines);
        return;
      }
    }
    throw std::runtime_error("cannot found label for phi action");
  } else if (auto select_act = std::dynamic_pointer_cast<SelectItem>(act)) {
    LLVMType ty_int32 = LLVMIRIntType(32);
    LLVMType ty_ptr = LLVMIRPTRType();
    if (select_act->ty != ty_int32 && select_act->ty != ty_ptr) {
      throw std::runtime_error("select action only support int32 or ptr");
    }
    IRVar2RISCVReg(select_act->cond_full, 1, "t0", layout, code_lines);
    IRVar2RISCVReg(select_act->true_val_full, 4, "t1", layout, code_lines);
    IRVar2RISCVReg(select_act->false_val_full, 4, "t2", layout, code_lines);
    // use binary operation to implement select for efficiency
    code_lines.push_back("slli t0, t0, 31");
    code_lines.push_back("srai t0, t0, 31");
    code_lines.push_back("and t1, t0, t1");
    code_lines.push_back("not t0, t0");
    code_lines.push_back("and t2, t0, t2");
    code_lines.push_back("or t0, t1, t2");
    GenerateWriteAccess(select_act->result_full, 4, "t0", layout, code_lines);
  } else {
    throw std::runtime_error("Unknown action type");
  }
}
}  // namespace NaiveBackend