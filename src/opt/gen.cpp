#include "gen.h"

namespace OptBackend {
void FetchValueToReg(std::string original_val, std::string &out_reg, FuncLayout &layout,
                     std::vector<std::string> &code_lines, std::vector<std::string> &available_tmp_regs) {
  if (original_val[0] == '$') {
    // already assigned to a register, such as `$reg.10`
    out_reg = ExtractRegName(original_val);
  } else if (original_val[0] == '#') {
    // spilled variable, we need find it in the layout
    size_t offset = layout.QueryOffeset(original_val);
    out_reg = AllocateTmpReg(available_tmp_regs);
    if (offset < 2048) {
      code_lines.push_back("lw " + out_reg + ", -" + std::to_string(offset) + "(s0)");
    } else {
      code_lines.push_back("li " + out_reg + ", -" + std::to_string(offset));
      code_lines.push_back("add " + out_reg + ", s0, " + out_reg);
      code_lines.push_back("lw " + out_reg + ", 0(" + out_reg + ")");
    }
  } else if (original_val[0] == '@') {
    // global variable address keeper
    out_reg = AllocateTmpReg(available_tmp_regs);
    std::string label_in_asm = original_val.substr(1, original_val.size() - 1);
    code_lines.push_back("la " + out_reg + ", " + label_in_asm);
  } else if (original_val[0] == '-' || std::isdigit(original_val[0])) {
    // immediate value
    out_reg = AllocateTmpReg(available_tmp_regs);
    StoreImmToReg(std::stoi(original_val), out_reg, code_lines);
  } else if (original_val == "null") {
    out_reg = "x0";
  } else {
    throw std::runtime_error("Unknown value type");
  }
}

void WriteToSpilledVar(std::string val, std::string reg, FuncLayout &layout, std::vector<std::string> &code_lines,
                       std::vector<std::string> &available_tmp_regs) {
  if (val[0] != '#') throw std::runtime_error("Not a spilled variable");
  size_t offset = layout.QueryOffeset(val);
  if (offset < 2048) {
    code_lines.push_back("sw " + reg + ", -" + std::to_string(offset) + "(s0)");
  } else {
    std::string tmp_reg = AllocateTmpReg(available_tmp_regs);
    code_lines.push_back("li " + tmp_reg + ", -" + std::to_string(offset));
    code_lines.push_back("add " + tmp_reg + ", s0, " + tmp_reg);
    code_lines.push_back("sw " + reg + ", 0(" + tmp_reg + ")");
  }
}
size_t CalcSize(const LLVMType &tp) {
  if (std::holds_alternative<LLVMIRIntType>(tp)) {
    auto &int_tp = std::get<LLVMIRIntType>(tp);
    return (int_tp.bits + 7) / 8;
  } else if (std::holds_alternative<LLVMIRPTRType>(tp)) {
    return 4;
  } else if (std::holds_alternative<LLVMVOIDType>(tp)) {
    throw std::runtime_error("Cannot calculate size of void type");
    return 0;
  } else if (std::holds_alternative<LLVMIRCLASSTYPE>(tp)) {
    throw std::runtime_error("Cannot calculate size of class type");
  } else
    throw std::runtime_error("Unknown type");
}


void GenerateASM(std::shared_ptr<ActionItem> act, std::vector<std::string> &code_lines, FuncLayout &layout,
                        const std::unordered_map<std::string, IRClassInfo> &low_level_class_info) {
  std::vector<std::string> available_tmp_regs = held_tmp_regs;
  if (auto br_act = std::dynamic_pointer_cast<BRAction>(act)) {
    std::string cond_reg;
    FetchValueToReg(br_act->cond, cond_reg, layout, code_lines, available_tmp_regs);
    code_lines.push_back("bnez " + cond_reg + ", .entrylabel." + br_act->true_label_full);
    code_lines.push_back("j .entrylabel." + br_act->false_label_full);
  } else if (auto jmp_act = std::dynamic_pointer_cast<UNConditionJMPAction>(act)) {
    code_lines.push_back("j .entrylabel." + jmp_act->label_full);
  } else if (auto ret_act = std::dynamic_pointer_cast<RETAction>(act)) {
    code_lines.push_back("lw ra, -4(s0)");
    code_lines.push_back("lw sp, -12(s0)");
    code_lines.push_back("lw s0, -8(s0)");
    code_lines.push_back("ret");
  } else if (auto binary_act = std::dynamic_pointer_cast<BinaryOperationAction>(act)) {
    // size_t sz = CalcSize(binary_act->type);
    // IRVar2RISCVReg(binary_act->operand1_full, sz, "t0", layout, code_lines);
    // IRVar2RISCVReg(binary_act->operand2_full, sz, "t1", layout, code_lines);
    std::string operand1_reg, operand2_reg;
    FetchValueToReg(binary_act->operand1_full, operand1_reg, layout, code_lines, available_tmp_regs);
    FetchValueToReg(binary_act->operand2_full, operand2_reg, layout, code_lines, available_tmp_regs);
    std::string res_reg;
    bool need_extra_store = false;
    if (binary_act->result_full[0] == '$') {
      res_reg = ExtractRegName(binary_act->result_full);
    } else if (binary_act->result_full[0] == '#') {
      need_extra_store = true;
      res_reg = AllocateTmpReg(available_tmp_regs);
    } else {
      throw std::runtime_error("Unknown result type");
    }
    if (binary_act->op == "add") {
      code_lines.push_back("add " + res_reg + ", " + operand1_reg + ", " + operand2_reg);
    } else if (binary_act->op == "sub") {
      code_lines.push_back("sub " + res_reg + ", " + operand1_reg + ", " + operand2_reg);
    } else if (binary_act->op == "mul") {
      code_lines.push_back("mul " + res_reg + ", " + operand1_reg + ", " + operand2_reg);
    } else if (binary_act->op == "sdiv") {
      code_lines.push_back("div " + res_reg + ", " + operand1_reg + ", " + operand2_reg);
    } else if (binary_act->op == "srem") {
      code_lines.push_back("rem " + res_reg + ", " + operand1_reg + ", " + operand2_reg);
    } else if (binary_act->op == "and") {
      code_lines.push_back("and " + res_reg + ", " + operand1_reg + ", " + operand2_reg);
    } else if (binary_act->op == "or") {
      code_lines.push_back("or " + res_reg + ", " + operand1_reg + ", " + operand2_reg);
    } else if (binary_act->op == "xor") {
      code_lines.push_back("xor " + res_reg + ", " + operand1_reg + ", " + operand2_reg);
    } else if (binary_act->op == "shl") {
      code_lines.push_back("sll " + res_reg + ", " + operand1_reg + ", " + operand2_reg);
    } else if (binary_act->op == "ashr") {
      code_lines.push_back("sra " + res_reg + ", " + operand1_reg + ", " + operand2_reg);
    } else {
      throw std::runtime_error("Unknown binary operation");
    }
    if (need_extra_store) {
      WriteToSpilledVar(binary_act->result_full, res_reg, layout, code_lines, available_tmp_regs);
    }
  } else if (auto alloca_act = std::dynamic_pointer_cast<AllocaAction>(act)) {
    std::string res_reg;
    bool need_extra_store = false;
    if (alloca_act->name_full[0] == '#') {
      need_extra_store = true;
      res_reg = AllocateTmpReg(available_tmp_regs);
    } else if (alloca_act->name_full[0] == '$') {
      res_reg = ExtractRegName(alloca_act->name_full);
    } else {
      throw std::runtime_error("Unknown result type");
    }
    size_t sz = CalcSize(alloca_act->type) * alloca_act->num;
    sz = (sz + 15) / 16 * 16;
    code_lines.push_back("addi sp, sp, -" + std::to_string(sz));
    if (!need_extra_store) {
      code_lines.push_back("mv " + res_reg + ", sp");
    } else {
      WriteToSpilledVar(alloca_act->name_full, "sp", layout, code_lines, available_tmp_regs);
    }
  } else if (auto load_act = std::dynamic_pointer_cast<LoadAction>(act)) {
    std::string res_reg;
    bool need_extra_store = false;
    if (load_act->result_full[0] == '#') {
      need_extra_store = true;
      res_reg = AllocateTmpReg(available_tmp_regs);
    } else if (load_act->result_full[0] == '$') {
      res_reg = ExtractRegName(load_act->result_full);
    } else {
      throw std::runtime_error("Unknown result type");
    }
    std::string ptr_reg;
    FetchValueToReg(load_act->ptr_full, ptr_reg, layout, code_lines, available_tmp_regs);
    if (CalcSize(load_act->ty) == 4) {
      code_lines.push_back("lw " + res_reg + ", 0(" + ptr_reg + ")");
    } else if (CalcSize(load_act->ty) == 1) {
      code_lines.push_back("lb " + res_reg + ", 0(" + ptr_reg + ")");
    } else {
      throw std::runtime_error("Unknown bytes");
    }
    if (need_extra_store) {
      WriteToSpilledVar(load_act->result_full, res_reg, layout, code_lines, available_tmp_regs);
    }
  } else if (auto store_act = std::dynamic_pointer_cast<StoreAction>(act)) {
    std::string val_reg;
    std::string ptr_reg;
    FetchValueToReg(store_act->value_full, val_reg, layout, code_lines, available_tmp_regs);
    FetchValueToReg(store_act->ptr_full, ptr_reg, layout, code_lines, available_tmp_regs);
    if (CalcSize(store_act->ty) == 4) {
      code_lines.push_back("sw " + val_reg + ", 0(" + ptr_reg + ")");
    } else if (CalcSize(store_act->ty) == 1) {
      code_lines.push_back("sb " + val_reg + ", 0(" + ptr_reg + ")");
    } else {
      throw std::runtime_error("Unknown bytes");
    }
  } else if (auto get_element_act = std::dynamic_pointer_cast<GetElementPtrAction>(act)) {
    if (get_element_act->indices.size() == 1) {
      // array access
      std::string res_reg;
      bool need_extra_store = false;
      if (get_element_act->result_full[0] == '#') {
        need_extra_store = true;
        res_reg = AllocateTmpReg(available_tmp_regs);
      } else if (get_element_act->result_full[0] == '$') {
        res_reg = ExtractRegName(get_element_act->result_full);
      } else {
        throw std::runtime_error("Unknown result type");
      }
      std::string ptr_reg;
      std::string idx_reg;
      FetchValueToReg(get_element_act->ptr_full, ptr_reg, layout, code_lines, available_tmp_regs);
      FetchValueToReg(get_element_act->indices[0], idx_reg, layout, code_lines, available_tmp_regs);
      std::string tmp_reg = AllocateTmpReg(available_tmp_regs);
      size_t element_sz = CalcSize(get_element_act->ty);
      code_lines.push_back("slli " + tmp_reg + ", " + idx_reg + ", " + std::to_string(std::countr_zero(element_sz)));
      code_lines.push_back("add " + res_reg + ", " + ptr_reg + ", " + tmp_reg);
      if (need_extra_store) {
        WriteToSpilledVar(get_element_act->result_full, res_reg, layout, code_lines, available_tmp_regs);
      }
    } else if (get_element_act->indices.size() == 2) {
      // // struct access
      if (get_element_act->indices[0] != "0") {
        throw std::runtime_error("struct access with non-zero offset is not supported");
      }
      size_t element_idx = std::stoull(get_element_act->indices[1]);
      auto class_ty = std::get<LLVMIRCLASSTYPE>(get_element_act->ty);
      const IRClassInfo &class_info = low_level_class_info.at(class_ty.class_name_full);
      size_t offset = class_info.member_var_pos_after_align[element_idx];
      std::string res_reg;
      bool need_extra_store = false;
      if (get_element_act->result_full[0] == '#') {
        need_extra_store = true;
        res_reg = AllocateTmpReg(available_tmp_regs);
      } else if (get_element_act->result_full[0] == '$') {
        res_reg = ExtractRegName(get_element_act->result_full);
      } else {
        throw std::runtime_error("Unknown result type");
      }
      std::string base_ptr_reg;
      FetchValueToReg(get_element_act->ptr_full, base_ptr_reg, layout, code_lines, available_tmp_regs);
      if (offset < 2048) {
        code_lines.push_back("addi " + res_reg + ", " + base_ptr_reg + ", " + std::to_string(offset));
      } else {
        std::string tmp_reg = AllocateTmpReg(available_tmp_regs);
        code_lines.push_back("li " + tmp_reg + ", " + std::to_string(offset));
        code_lines.push_back("add " + res_reg + ", " + base_ptr_reg + ", " + tmp_reg);
      }
      if (need_extra_store) {
        WriteToSpilledVar(get_element_act->result_full, res_reg, layout, code_lines, available_tmp_regs);
      }
    } else {
      throw std::runtime_error("Unknown getelementptr indices size");
    }
  } else if (auto icmp_act = std::dynamic_pointer_cast<ICMPAction>(act)) {
    std::string operand1_reg, operand2_reg;
    FetchValueToReg(icmp_act->operand1_full, operand1_reg, layout, code_lines, available_tmp_regs);
    FetchValueToReg(icmp_act->operand2_full, operand2_reg, layout, code_lines, available_tmp_regs);
    std::string res_reg;
    bool need_extra_store = false;
    if (icmp_act->result_full[0] == '#') {
      need_extra_store = true;
      res_reg = AllocateTmpReg(available_tmp_regs);
    } else if (icmp_act->result_full[0] == '$') {
      res_reg = ExtractRegName(icmp_act->result_full);
    } else {
      throw std::runtime_error("Unknown result type");
    }
    std::string tmp_reg = AllocateTmpReg(available_tmp_regs);
    if (icmp_act->op == "eq") {
      // code_lines.push_back("xor t2, t0, t1");
      // code_lines.push_back("seqz t2, t2");
      code_lines.push_back("xor " + tmp_reg + ", " + operand1_reg + ", " + operand2_reg);
      code_lines.push_back("seqz " + res_reg + ", " + tmp_reg);
    } else if (icmp_act->op == "ne") {
      // code_lines.push_back("xor t2, t0, t1");
      // code_lines.push_back("snez t2, t2");
      code_lines.push_back("xor " + tmp_reg + ", " + operand1_reg + ", " + operand2_reg);
      code_lines.push_back("snez " + res_reg + ", " + tmp_reg);
    } else if (icmp_act->op == "slt") {
      // code_lines.push_back("slt t2, t0, t1");
      code_lines.push_back("slt " + res_reg + ", " + operand1_reg + ", " + operand2_reg);
    } else if (icmp_act->op == "sle") {
      // code_lines.push_back("slt t2, t1, t0");
      // code_lines.push_back("xori t2, t2, 1");
      code_lines.push_back("slt " + res_reg + ", " + operand2_reg + ", " + operand1_reg);
      code_lines.push_back("xori " + res_reg + ", " + res_reg + ", 1");
    } else if (icmp_act->op == "sgt") {
      // code_lines.push_back("slt t2, t1, t0");
      code_lines.push_back("slt " + res_reg + ", " + operand2_reg + ", " + operand1_reg);
    } else if (icmp_act->op == "sge") {
      // code_lines.push_back("slt t2, t0, t1");
      // code_lines.push_back("xori t2, t2, 1");
      code_lines.push_back("slt " + res_reg + ", " + operand1_reg + ", " + operand2_reg);
      code_lines.push_back("xori " + res_reg + ", " + res_reg + ", 1");
    } else {
      throw std::runtime_error("Unknown icmp operation");
    }
    if (need_extra_store) {
      WriteToSpilledVar(icmp_act->result_full, res_reg, layout, code_lines, available_tmp_regs);
    }
  } else if (auto call_act = std::dynamic_pointer_cast<CallItem>(act)) {
    // no need to to further process, as callling convention is handled in reg alloc
    code_lines.push_back("call " + call_act->func_name_raw);
    if (call_act->move_sp_up) {
      size_t delta = 4 * call_act->move_sp_up;
      code_lines.push_back("addi sp, sp, " + std::to_string(delta));
    }
  } else if (auto phi_act = std::dynamic_pointer_cast<PhiItem>(act)) {
    throw std::runtime_error("Phi should not be in the layout");
  } else if (auto select_act = std::dynamic_pointer_cast<SelectItem>(act)) {
    std::string res_reg;
    bool need_extra_store = false;
    if (select_act->result_full[0] == '#') {
      need_extra_store = true;
      res_reg = AllocateTmpReg(available_tmp_regs);
    } else if (select_act->result_full[0] == '$') {
      res_reg = ExtractRegName(select_act->result_full);
    } else {
      throw std::runtime_error("Unknown result type");
    }
    std::string operand1_reg, operand2_reg, cond_reg;
    FetchValueToReg(select_act->cond_full, cond_reg, layout, code_lines, available_tmp_regs);
    FetchValueToReg(select_act->true_val_full, operand1_reg, layout, code_lines, available_tmp_regs);
    FetchValueToReg(select_act->false_val_full, operand2_reg, layout, code_lines, available_tmp_regs);
    std::string tmp1_reg = AllocateTmpReg(available_tmp_regs);
    std::string tmp2_reg = AllocateTmpReg(available_tmp_regs);
    code_lines.push_back("slli " + tmp1_reg + ", " + cond_reg + ", 31");
    code_lines.push_back("srai " + tmp1_reg + ", " + tmp1_reg + ", 31");
    code_lines.push_back("xor " + tmp2_reg + ", " + operand1_reg + ", " + operand2_reg);
    code_lines.push_back("and " + tmp2_reg + ", " + tmp2_reg + ", " + tmp1_reg);
    code_lines.push_back("xor " + res_reg + ", " + tmp2_reg + ", " + operand2_reg);
    if (need_extra_store) {
      WriteToSpilledVar(select_act->result_full, res_reg, layout, code_lines, available_tmp_regs);
    }
  } else if (auto load_spilled_args_act = std::dynamic_pointer_cast<opt::LoadSpilledArgs>(act)) {
    std::string res_reg;
    bool need_extra_store = false;
    if (load_spilled_args_act->var_full[0] == '$') {
      res_reg = ExtractRegName(load_spilled_args_act->var_full);
    } else if (load_spilled_args_act->var_full[0] == '#') {
      need_extra_store = true;
      res_reg = AllocateTmpReg(available_tmp_regs);
    } else {
      throw std::runtime_error("Unknown result type");
    }
    size_t offset = 4 * (load_spilled_args_act->arg_id - 8);
    code_lines.push_back("lw " + res_reg + ", " + std::to_string(offset) + "(s0)");
    if (need_extra_store) {
      WriteToSpilledVar(load_spilled_args_act->var_full, res_reg, layout, code_lines, available_tmp_regs);
    }
  } else if (auto store_spilled_args_act = std::dynamic_pointer_cast<opt::StoreSpilledArgs>(act)) {
    if (store_spilled_args_act->move_sp_down) {
      size_t delta = 4 * store_spilled_args_act->move_sp_down;
      code_lines.push_back("addi sp, sp, -" + std::to_string(delta));
    }
    std::string val_reg;
    FetchValueToReg(store_spilled_args_act->var_full, val_reg, layout, code_lines, available_tmp_regs);
    size_t offset = 4 * (store_spilled_args_act->arg_id - 8);
    code_lines.push_back("sw " + val_reg + ", " + std::to_string(offset) + "(sp)");
  } else if (auto move_act = std::dynamic_pointer_cast<opt::MoveInstruct>(act)) {
    std::string src_reg;
    FetchValueToReg(move_act->src_full, src_reg, layout, code_lines, available_tmp_regs);
    if (move_act->dest_full[0] == '$') {
      std::string dest_reg = ExtractRegName(move_act->dest_full);
      code_lines.push_back("mv " + dest_reg + ", " + src_reg);
    } else if (move_act->dest_full[0] == '#') {
      WriteToSpilledVar(move_act->dest_full, src_reg, layout, code_lines, available_tmp_regs);
    } else {
      throw std::runtime_error("Unknown dest type");
    }
  } else {
    throw std::runtime_error("Unknown action type");
  }
}

std::string AllocateTmpReg(std::vector<std::string> &available_tmp_regs) {
  if (available_tmp_regs.size() == 0) throw std::runtime_error("No available tmp register");
  std::string res;
  res = available_tmp_regs.back();
  available_tmp_regs.pop_back();
  return res;
}

std::string ExtractRegName(const std::string &raw) {
  if (raw[0] != '$') throw std::runtime_error("Not a register");
  size_t reg_id = std::stoull(raw.substr(5));
  return "x" + std::to_string(reg_id);
}

}  // namespace OptBackend