#pragma once
#include "IR/IR_basic.h"
#include "cfg.h"
#include "tools.h"

void LiveAnalysis(CFGType &cfg);

namespace opt {
class ForceDef : public ActionItem {
 public:
  std::string var_full;
  LLVMType ty;
  ForceDef() = default;
  void RecursivePrint(std::ostream &os) const {
    throw std::runtime_error("ForceDef instruction is not an actual LLVM IR instruction");
  }
};
class ForceUse : public ActionItem {
 public:
  std::string var_full;
  ForceUse() = default;
  void RecursivePrint(std::ostream &os) const {
    throw std::runtime_error("ForceUse instruction is not an actual LLVM IR instruction");
  }
};
class LoadSpilledArgs : public ActionItem {
 public:
  size_t arg_id;  // [8,+inf)
  std::string var_full;
  LLVMType ty;
  LoadSpilledArgs() = default;
  void RecursivePrint(std::ostream &os) const {
    throw std::runtime_error("LoadSpilledArgs instruction is not an actual LLVM IR instruction");
  }
};
}  // namespace opt