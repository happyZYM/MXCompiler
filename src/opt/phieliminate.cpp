#include "phieliminate.h"
#include <cstdarg>
#include <stdexcept>
#include "IR/IR_basic.h"
#include "cfg.h"

using namespace opt;
void ConductPhiEliminateForFunction(std::shared_ptr<FunctionDefItem> func, CFGType &cfg);
void ConductPhiEliminateForFunction(std::shared_ptr<FunctionDefItem> func, CFGType &cfg) {
  size_t new_block_cnt = 0;
  for (auto cur_node : cfg.nodes) {
    auto cur_block = cur_node->corresponding_block;
    if (cur_block->actions.size() > 0) {
      if (auto phi_act = std::dynamic_pointer_cast<PhiItem>(cur_block->actions.front())) {
        // simple phi action caused by and, or and ternary operator, no need to insert extra blocks, just remove it and
        // add phi values to the corresponding blocks
        cur_block->actions.erase(cur_block->actions.begin());
        for (auto [src_val, src_label] : phi_act->values) {
          auto src_block = cfg.label_to_block[src_label];
          auto new_move = std::make_shared<MoveInstruct>();
          new_move->src_full = src_val;
          new_move->dest_full = phi_act->result_full;
          new_move->ty = phi_act->ty;
          src_block->actions.push_back(new_move);
        }
      }
    }
    std::unordered_map<std::string, BlockItem *> src_changed;
    for (auto [_, phi_act] : cur_block->phi_map) {
      for (auto [src_val, src_label] : phi_act->values) {
        auto src_block = cfg.label_to_block[src_label];
        auto src_node = cfg.block_to_node[src_block];
        if (src_changed.find(src_label) != src_changed.end()) {
          src_block = src_changed[src_label];
          auto new_move = std::make_shared<MoveInstruct>();
          new_move->src_full = src_val;
          new_move->dest_full = phi_act->result_full;
          new_move->ty = phi_act->ty;
          src_block->actions.push_back(new_move);
        } else if (src_node->successors.size() > 1 && cur_node->predecessors.size() > 1) {
          // it is a critical edge, need to insert a new block
          auto new_block = std::make_shared<BlockItem>();
          func->basic_blocks.push_back(new_block);
          new_block->label_full = cur_block->label_full + ".phieliminate." + std::to_string(new_block_cnt++);
          src_changed[src_label] = new_block.get();
          new_block->exit_action = std::make_shared<UNConditionJMPAction>();
          std::dynamic_pointer_cast<UNConditionJMPAction>(new_block->exit_action)->label_full = cur_block->label_full;
          auto src_block_exit_action = std::dynamic_pointer_cast<BRAction>(src_block->exit_action);
          if (!src_block_exit_action) {
            throw std::runtime_error(
                "something strange happened: src block of a critical edge does not have a BRAction");
          }
          if (src_block_exit_action->true_label_full == cur_block->label_full) {
            src_block_exit_action->true_label_full = new_block->label_full;
          } else if (src_block_exit_action->false_label_full == cur_block->label_full) {
            src_block_exit_action->false_label_full = new_block->label_full;
          } else {
            throw std::runtime_error(
                "something strange happened: src block of a critical edge cannot find the corresponding label, src "
                "block label=" +
                src_block->label_full);
          }
          auto new_move = std::make_shared<MoveInstruct>();
          new_move->src_full = src_val;
          new_move->dest_full = phi_act->result_full;
          new_move->ty = phi_act->ty;
          new_block->actions.push_back(new_move);
        } else {
          auto new_move = std::make_shared<MoveInstruct>();
          new_move->src_full = src_val;
          new_move->dest_full = phi_act->result_full;
          new_move->ty = phi_act->ty;
          src_block->actions.push_back(new_move);
        }
      }
    }
    cur_block->phi_map.clear();
  }
  size_t move_tmp_counter = 0;
  for (auto cur_node : cfg.nodes) {
    auto cur_block = cur_node->corresponding_block;
    if (cur_block->actions.size() == 0) continue;
    std::list<MoveInstruct *> suffix_moves;
    auto it = cur_block->actions.end();
    while (it != cur_block->actions.begin()) {
      --it;
      if (std::dynamic_pointer_cast<MoveInstruct>(*it)) {
        suffix_moves.push_front(dynamic_cast<MoveInstruct *>(it->get()));
      } else {
        break;
      }
    }
    std::unordered_map<std::string, MoveInstruct *> value_decided_by;
    for (auto move : suffix_moves) {
      if (value_decided_by.find(move->src_full) != value_decided_by.end()) {
        auto new_move = std::make_shared<MoveInstruct>();
        new_move->dest_full = value_decided_by[move->src_full]->dest_full;
        new_move->ty = value_decided_by[move->src_full]->ty;
        std::string tmp_var_name = "%movetmp." + std::to_string(move_tmp_counter++);
        new_move->src_full = tmp_var_name;
        value_decided_by[move->src_full]->dest_full = tmp_var_name;
        cur_block->actions.push_back(new_move);
      }
      value_decided_by[move->dest_full] = move;
    }
  }
}

std::shared_ptr<ModuleItem> PhiEliminate(std::shared_ptr<ModuleItem> src) {
  auto res = src;
  for (auto &func : res->function_defs) {
    // func = std::make_shared<FunctionDefItem>(*func);
    auto cfg = BuildCFGForFunction(func);
    ConductPhiEliminateForFunction(func, cfg);
  }
  return res;
}