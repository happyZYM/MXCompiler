#pragma once
#include "liveanalysis.h"
#include "phieliminate.h"
#include "confgraph.h"

std::shared_ptr<ModuleItem> RegAlloc(std::shared_ptr<ModuleItem> src);