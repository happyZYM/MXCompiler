#include "mem2reg.h"
#include "cfg.h"

void ConductMem2RegForFunction(const std::shared_ptr<FunctionDefItem> &func, const CFGType &cfg) {}
std::shared_ptr<ModuleItem> Mem2Reg(std::shared_ptr<ModuleItem> src) {
  auto res = std::make_shared<ModuleItem>(*src);
  for (auto &func : res->function_defs) {
    func = std::make_shared<FunctionDefItem>(*func);
    auto cfg = BuildCFGForFunction(func);
    ConductMem2RegForFunction(func, cfg);
  }
  return res;
}