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
  void RecursivePrint(std::ostream &os) const { os << "[Persudo] def " << var_full << "\n"; }
};
class ForceUse : public ActionItem {
 public:
  std::string var_full;
  ForceUse() = default;
  void RecursivePrint(std::ostream &os) const { os << "[Persudo] use " << var_full << "\n"; }
};
class LoadSpilledArgs : public ActionItem {
 public:
  size_t arg_id;  // [8,+inf)
  std::string var_full;
  LLVMType ty;
  LoadSpilledArgs() = default;
  void RecursivePrint(std::ostream &os) const {
    os << "[Persudo] load spilled args " << var_full << "with id=" << arg_id << "\n";
  }
};

class StoreSpilledArgs : public ActionItem {
 public:
  size_t arg_id;  // [8,+inf)
  std::string var_full;
  LLVMType ty;
  StoreSpilledArgs() = default;
  void RecursivePrint(std::ostream &os) const {
    os << "[Persudo] store spilled args " << var_full << "with id=" << arg_id << "\n";
  }
};
}  // namespace opt