#include "betterbr.h"
#include "IR/IR_basic.h"
#include "cfg.h"

void GenerateBetterBRForFunction(std::shared_ptr<FunctionDefItem> func);

void GenerateBetterBRForBlock(std::shared_ptr<BlockItem> block);

void GenerateBetterBRForBlock(std::shared_ptr<BlockItem> block) {
  std::unordered_map<std::string, std::shared_ptr<ICMPAction>> icmp_map;
  for (auto act : block->actions) {
    if (auto icmp_act = std::dynamic_pointer_cast<ICMPAction>(act)) {
      icmp_map[icmp_act->result_full] = icmp_act;
    }
  }
  if (auto br_act = std::dynamic_pointer_cast<BRAction>(block->exit_action)) {
    if (icmp_map.find(br_act->cond) != icmp_map.end()) {
      auto icmp_act = icmp_map[br_act->cond];
      if (icmp_act->op == "eq") {
        auto new_br = std::make_shared<BEQAction>();
        new_br->true_label_full = br_act->true_label_full;
        new_br->false_label_full = br_act->false_label_full;
        new_br->rs1 = icmp_act->operand1_full;
        new_br->rs2 = icmp_act->operand2_full;
        block->exit_action = new_br;
      } else if (icmp_act->op == "ne") {
        auto new_br = std::make_shared<BNEAction>();
        new_br->true_label_full = br_act->true_label_full;
        new_br->false_label_full = br_act->false_label_full;
        new_br->rs1 = icmp_act->operand1_full;
        new_br->rs2 = icmp_act->operand2_full;
        block->exit_action = new_br;
      } else if (icmp_act->op == "slt") {
        auto new_br = std::make_shared<BLTAction>();
        new_br->true_label_full = br_act->true_label_full;
        new_br->false_label_full = br_act->false_label_full;
        new_br->rs1 = icmp_act->operand1_full;
        new_br->rs2 = icmp_act->operand2_full;
        block->exit_action = new_br;
      } else if (icmp_act->op == "sle") {
        auto new_br = std::make_shared<BGEAction>();
        new_br->true_label_full = br_act->true_label_full;
        new_br->false_label_full = br_act->false_label_full;
        new_br->rs1 = icmp_act->operand2_full;
        new_br->rs2 = icmp_act->operand1_full;
        block->exit_action = new_br;
      } else if (icmp_act->op == "sgt") {
        auto new_br = std::make_shared<BLTAction>();
        new_br->true_label_full = br_act->true_label_full;
        new_br->false_label_full = br_act->false_label_full;
        new_br->rs1 = icmp_act->operand2_full;
        new_br->rs2 = icmp_act->operand1_full;
        block->exit_action = new_br;
      } else if (icmp_act->op == "sge") {
        auto new_br = std::make_shared<BGEAction>();
        new_br->true_label_full = br_act->true_label_full;
        new_br->false_label_full = br_act->false_label_full;
        new_br->rs1 = icmp_act->operand1_full;
        new_br->rs2 = icmp_act->operand2_full;
        block->exit_action = new_br;
      } else {
        throw std::runtime_error("Unknown icmp op");
      }
    }
  }
}
void GenerateBetterBRForFunction(std::shared_ptr<FunctionDefItem> func) {
  if (func->init_block) {
    GenerateBetterBRForBlock(func->init_block);
  }
  for (auto block : func->basic_blocks) {
    GenerateBetterBRForBlock(block);
  }
}

std::shared_ptr<ModuleItem> GenerateBetterBR(std::shared_ptr<ModuleItem> src) {
  for (auto func : src->function_defs) {
    GenerateBetterBRForFunction(func);
  }
  return src;
}