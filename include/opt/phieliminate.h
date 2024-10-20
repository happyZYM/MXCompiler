#pragma once
#include "IR/IR_basic.h"
#include "cfg.h"

std::shared_ptr<ModuleItem> PhiEliminate(std::shared_ptr<ModuleItem> src);