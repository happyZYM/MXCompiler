#include "regalloc.h"

void ConductRegAllocForFunction([[maybe_unused]] std::shared_ptr<FunctionDefItem> func, CFGType &cfg) {
  LiveAnalysis(cfg);
}

std::shared_ptr<ModuleItem> RegAlloc(std::shared_ptr<ModuleItem> src) {
  auto res = src;
  for (auto &func : res->function_defs) {
    // func = std::make_shared<FunctionDefItem>(*func);
    auto cfg = BuildCFGForFunction(func);
    ConductRegAllocForFunction(func, cfg);
  }
  return res;
}