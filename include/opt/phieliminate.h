#pragma once
#include "IR/IR_basic.h"
#include "cfg.h"

namespace opt {
class MoveInstruct : public ActionItem {
 public:
  std::string src_full;
  std::string dest_full;
  MoveInstruct() = default;
  void RecursivePrint([[maybe_unused]] std::ostream &os) const {
    throw std::runtime_error("Move instruction is not an actual LLVM IR instruction");
  }
};
}  // namespace opt

std::shared_ptr<ModuleItem> PhiEliminate(std::shared_ptr<ModuleItem> src);