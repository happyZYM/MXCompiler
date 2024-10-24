#pragma once
#include "mem2reg.h"
#include <memory>
#include <queue>
#include "IR/IR_basic.h"
#include "cfg.h"

std::shared_ptr<ModuleItem> GloabalVarCache(std::shared_ptr<ModuleItem> src);