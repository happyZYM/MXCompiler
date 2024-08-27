#pragma once
#include <ios>
#include <memory>
#include <ostream>
#include <string>
#include "IR/IR_basic.h"
class RISCVAsmItemBase {
 public:
  RISCVAsmItemBase() = default;
  virtual ~RISCVAsmItemBase() = default;
  virtual void RecursivePrint(std::ostream &os) const = 0;
};
namespace NaiveBackend {
  class RISCVConstStrItem : public RISCVAsmItemBase {
   public:
    RISCVConstStrItem() = default;
    ~RISCVConstStrItem() = default;
    void RecursivePrint(std::ostream &os) const override;
  };
  class RISCVGlobalVarItem : public RISCVAsmItemBase {
   public:
    RISCVGlobalVarItem() = default;
    ~RISCVGlobalVarItem() = default;
    void RecursivePrint(std::ostream &os) const override;
  };
  class RISCVFuncItem : public RISCVAsmItemBase {
   public:
    RISCVFuncItem() = default;
    ~RISCVFuncItem() = default;
    void RecursivePrint(std::ostream &os) const override;
  };
  class RISCVProgItem : public RISCVAsmItemBase {
   public:
    RISCVProgItem() = default;
    ~RISCVProgItem() = default;
    void RecursivePrint(std::ostream &os) const override;
  };
}
void GenerateNaiveASM(std::ostream &os, std::shared_ptr<ModuleItem> prog);