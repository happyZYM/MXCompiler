#pragma once
#include <memory>
#include <stdexcept>
#include "IR/IR_basic.h"
#include "naivebackend.h"
#include "tools.h"

namespace NaiveBackend {
inline size_t CalcSize(const LLVMType &tp) {
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
inline void ScanForVar(FuncLayout &layout, std::shared_ptr<ActionItem> action) {
  if (std::dynamic_pointer_cast<JMPActionItem>(action)) {
    throw std::runtime_error("JMPActionItem should not be in the layout");
  } else if (auto binary_act = std::dynamic_pointer_cast<BinaryOperationAction>(action)) {
    if (binary_act->result_full == "") {
      throw std::runtime_error("BinaryOperationAction should have a result_full");
    }
    layout.AllocateItem(binary_act->result_full, CalcSize(binary_act->type));
  } else if (auto alloca_act = std::dynamic_pointer_cast<AllocaAction>(action)) {
    if (alloca_act->name_full == "") {
      throw std::runtime_error("AllocaAction should have a name_full");
    }
    layout.AllocateItem(alloca_act->name_full, CalcSize(alloca_act->type), alloca_act->num);
  } else if (auto load_act = std::dynamic_pointer_cast<LoadAction>(action)) {
    if (load_act->result_full == "") {
      throw std::runtime_error("LoadAction should have a result_full");
    }
    layout.AllocateItem(load_act->result_full, CalcSize(load_act->ty));
  } else if (auto store_act = std::dynamic_pointer_cast<StoreAction>(action)) {
    // just do nothing
  } else if (auto get_element_act = std::dynamic_pointer_cast<GetElementPtrAction>(action)) {
    if (get_element_act->result_full == "") {
      throw std::runtime_error("GetElementPtrAction should have a result_full");
    }
    layout.AllocateItem(get_element_act->result_full, CalcSize(get_element_act->ty));
  } else if (auto icmp_act = std::dynamic_pointer_cast<ICMPAction>(action)) {
    if (icmp_act->result_full == "") {
      throw std::runtime_error("ICMPAction should have a result_full");
    }
    layout.AllocateItem(icmp_act->result_full, 1);
  } else if (auto call_act = std::dynamic_pointer_cast<CallItem>(action)) {
    if (call_act->result_full == "") {
      if (!std::holds_alternative<LLVMVOIDType>(call_act->return_type)) {
        throw std::runtime_error("CallItem should have a result_full");
      }
      return;
    }
    layout.AllocateItem(call_act->result_full, CalcSize(call_act->return_type));
  } else if (auto phi_act = std::dynamic_pointer_cast<PhiItem>(action)) {
    if (phi_act->result_full == "") {
      throw std::runtime_error("PhiItem should have a result_full");
    }
    layout.AllocateItem(phi_act->result_full, CalcSize(phi_act->ty));
  } else if (auto select_act = std::dynamic_pointer_cast<SelectItem>(action)) {
    if (select_act->result_full == "") {
      throw std::runtime_error("SelectItem should have a result_full");
    }
    layout.AllocateItem(select_act->result_full, CalcSize(select_act->ty));
  } else {
    throw std::runtime_error("Unknown action type");
  }
}
}  // namespace NaiveBackend