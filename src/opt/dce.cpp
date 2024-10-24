#include "dce.h"
#include "IR/IR_basic.h"
#include "cfg.h"
#include "liveanalysis.h"
void ConductDCEForFunction(std::shared_ptr<FunctionDefItem> func);

void ConductDCEForFunction(std::shared_ptr<FunctionDefItem> func) {
  CFGType cfg;
  cfg = BuildCFGForFunction(func);
  LiveAnalysis(cfg);
  std::unordered_set<std::string> all_vars;
  std::unordered_map<std::string, std::unordered_set<ActionItem *>> use_map, def_map;
  std::unordered_map<ActionItem *, std::vector<size_t>> actions_use_vars;
  for (size_t i = 0; i < cfg.id_to_var.size(); i++) {
    all_vars.insert(cfg.id_to_var[i]);
  }
  for (auto node : cfg.nodes) {
    for (const auto &[action, use_vars] : node->action_use_vars) {
      for (auto var_id : use_vars) {
        use_map[cfg.id_to_var[var_id]].insert(action);
      }
      actions_use_vars[action] = use_vars;
    }
    for (const auto &[action, def_vars] : node->action_def_vars) {
      for (auto var_id : def_vars) {
        def_map[cfg.id_to_var[var_id]].insert(action);
      }
    }
  }
  while (all_vars.size() > 0) {
    auto v = *(all_vars.begin());
    all_vars.erase(v);
    if (use_map[v].size() == 0) {
      if (def_map[v].size() != 1) throw std::runtime_error("def_map[v].size()!=1");
      auto def_inst = *(def_map[v].begin());
      if (!dynamic_cast<CallItem *>(def_inst)) {
        // no side effect
        def_inst->marked_as_useless = true;
        const auto &use_vars = actions_use_vars[def_inst];
        for (auto var_id : use_vars) {
          use_map[cfg.id_to_var[var_id]].erase(def_inst);
          all_vars.insert(cfg.id_to_var[var_id]);
        }
      }
    }
  }
  for (auto node : cfg.nodes) {
    auto block = node->corresponding_block;
    auto tmp = block->actions;
    block->actions.clear();
    for (auto act : tmp) {
      if (!act->marked_as_useless) {
        block->actions.push_back(act);
      }
    }
    std::vector<std::string> phi_to_remove;
    for (auto [key, phi_act] : block->phi_map) {
      if (phi_act->marked_as_useless) {
        phi_to_remove.push_back(key);
      }
    }
    for (auto key : phi_to_remove) {
      block->phi_map.erase(key);
    }
  }
}
std::shared_ptr<ModuleItem> DCE(std::shared_ptr<ModuleItem> src) {
  for (auto func : src->function_defs) {
    ConductDCEForFunction(func);
  }
  return src;
}