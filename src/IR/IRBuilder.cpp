#include "IRBuilder.h"
#include <stdexcept>
#include "IR.h"
#include "IR_basic.h"
#include "tools.h"

// Structural AST Nodes
void IRBuilder::ActuralVisit(FuncDef_ASTNode *node) {
  auto declare = std::make_shared<FunctionDeclareItem>();
  auto func_def = std::make_shared<FunctionDefItem>();
  // prog->function_declares.push_back(declare);
  prog->function_defs.push_back(func_def);
  if (is_in_class_def) {
    declare->func_name_raw = cur_class_name + "." + node->func_name;
    declare->args.push_back(LLVMIRPTRType());  // The `self` pointer
  } else {
    declare->func_name_raw = node->func_name;
  }
  declare->return_type = Type_AST2LLVM(node->return_type);
  for (auto &arg : node->params) {
    declare->args.push_back(Type_AST2LLVM(arg.second));
  }
  func_def->func_name_raw = declare->func_name_raw;
  func_def->return_type = declare->return_type;
  func_def->args = declare->args;
  size_t scope_id = node->current_scope->scope_id;
  if (is_in_class_def) {
    std::string arg_name_raw = "this";
    std::string full_name = "%.var.local." + std::to_string(scope_id) + "." + arg_name_raw + ".val";
    func_def->args_full_name.push_back(full_name);
  }
  for (auto &arg : node->params) {
    std::string &arg_name_raw = arg.first;
    std::string full_name = "%.var.local." + std::to_string(scope_id) + "." + arg_name_raw + ".val";
    func_def->args_full_name.push_back(full_name);
  }
  if (func_def->args.size() != func_def->args_full_name.size()) throw std::runtime_error("args size not match");

  cur_func = func_def;
  auto current_block = std::make_shared<BlockItem>();
  cur_block = current_block;
  cur_func->basic_blocks.push_back(current_block);
  size_t block_id = block_counter++;
  current_block->label_full = "label_" + std::to_string(block_id);

  is_in_func_def = true;
  node->func_body->accept(this);
  is_in_func_def = false;

  if (!(cur_block->exit_action)) {
    auto default_ret = std::make_shared<RETAction>();
    cur_block->exit_action = default_ret;
    default_ret->type = cur_func->return_type;
    if (std::holds_alternative<LLVMIRIntType>(default_ret->type)) {
      default_ret->value = "0";
    } else {
      default_ret->value = "null";
    }
  }
}

void IRBuilder::ActuralVisit(ClassDef_ASTNode *node) {
  is_in_class_def = true;
  cur_class_name = node->class_name;
  auto tpdf = std::make_shared<TypeDefItem>();
  tpdf->class_name_raw = node->class_name;
  cur_class = tpdf;
  prog->type_defs.push_back(tpdf);
  for (auto ch : node->sorted_children) {
    ch->accept(this);
  }
  is_in_class_def = false;
}

void IRBuilder::ActuralVisit(Program_ASTNode *node) {
  for (auto ch : node->sorted_children) {
    ch->accept(this);
  }
}

// Statement AST Nodes
void IRBuilder::ActuralVisit(EmptyStatement_ASTNode *node) {
  // do nothing
}

void IRBuilder::ActuralVisit(DefinitionStatement_ASTNode *node) {
  if (is_in_class_def) {
    cur_class->elements.push_back(Type_AST2LLVM(node->var_type));
  } else if (!is_in_func_def) {
    for (const auto &var : node->vars) {
      auto var_def = std::make_shared<GlobalVarDefItem>();
      prog->global_var_defs.push_back(var_def);
      var_def->type = Type_AST2LLVM(node->var_type);
      var_def->name_raw = var.first;
      // TODO: initial value
    }
  } else {
    for (const auto &var : node->vars) {
      auto var_def = std::make_shared<AllocaAction>();
      cur_block->actions.push_back(var_def);
      var_def->num = 1;
      var_def->type = Type_AST2LLVM(node->var_type);
      var_def->name_full = "%.var.local." + std::to_string(node->current_scope->scope_id) + "." + var.first + ".addrkp";
      if (var.second) {
        var.second->accept(this);
        auto act = std::make_shared<StoreAction>();
        cur_block->actions.push_back(act);
        act->ty = var_def->type;
        act->ptr_full = var_def->name_full;
        act->value_full = var.second->IR_result_full;
      }
    }
  }
  just_encountered_jmp = false;
}

void IRBuilder::ActuralVisit(ExprStatement_ASTNode *node) {
  // just visit it
  node->expr->accept(this);
  just_encountered_jmp = false;
}

void IRBuilder::ActuralVisit(IfStatement_ASTNode *node) {
  node->condition->accept(this);
  cur_block->exit_action = std::make_shared<BRAction>();
  if (node->else_clause) {
    size_t if_block_start_id = block_counter++;
    size_t else_block_start_id = block_counter++;
    size_t following_block_id = block_counter++;
    auto first_if_block = std::make_shared<BlockItem>();
    first_if_block->label_full = "label_" + std::to_string(if_block_start_id);
    auto first_else_block = std::make_shared<BlockItem>();
    first_else_block->label_full = "label_" + std::to_string(else_block_start_id);
    auto following_block = std::make_shared<BlockItem>();
    following_block->label_full = "label_" + std::to_string(following_block_id);
    std::dynamic_pointer_cast<BRAction>(cur_block->exit_action)->cond = node->condition->IR_result_full;
    std::dynamic_pointer_cast<BRAction>(cur_block->exit_action)->true_label_full = first_if_block->label_full;
    std::dynamic_pointer_cast<BRAction>(cur_block->exit_action)->false_label_full = first_else_block->label_full;
    cur_block = first_if_block;
    cur_func->basic_blocks.push_back(first_if_block);
    node->if_clause->accept(this);
    if (!(cur_block->exit_action)) {
      cur_block->exit_action = std::make_shared<UNConditionJMPAction>();
      std::dynamic_pointer_cast<UNConditionJMPAction>(cur_block->exit_action)->label_full = following_block->label_full;
    }
    cur_block = first_else_block;
    cur_func->basic_blocks.push_back(first_else_block);
    node->else_clause->accept(this);
    if (!(cur_block->exit_action)) {
      cur_block->exit_action = std::make_shared<UNConditionJMPAction>();
      std::dynamic_pointer_cast<UNConditionJMPAction>(cur_block->exit_action)->label_full = following_block->label_full;
    }
    cur_block = following_block;
    cur_func->basic_blocks.push_back(following_block);
  } else {
    size_t if_block_start_id = block_counter++;
    size_t following_block_id = block_counter++;
    auto first_if_block = std::make_shared<BlockItem>();
    first_if_block->label_full = "label_" + std::to_string(if_block_start_id);
    auto following_block = std::make_shared<BlockItem>();
    following_block->label_full = "label_" + std::to_string(following_block_id);
    std::dynamic_pointer_cast<BRAction>(cur_block->exit_action)->cond = node->condition->IR_result_full;
    std::dynamic_pointer_cast<BRAction>(cur_block->exit_action)->true_label_full = first_if_block->label_full;
    std::dynamic_pointer_cast<BRAction>(cur_block->exit_action)->false_label_full = following_block->label_full;
    cur_block = first_if_block;
    cur_func->basic_blocks.push_back(first_if_block);
    node->if_clause->accept(this);
    if (!(cur_block->exit_action)) {
      cur_block->exit_action = std::make_shared<UNConditionJMPAction>();
      std::dynamic_pointer_cast<UNConditionJMPAction>(cur_block->exit_action)->label_full = following_block->label_full;
    }
    cur_block = following_block;
    cur_func->basic_blocks.push_back(following_block);
  }
  just_encountered_jmp = false;
}

void IRBuilder::ActuralVisit(WhileStatement_ASTNode *node) {
  std::string break_target_backup = cur_break_target;
  std::string continue_target_backup = cur_continue_target;

  size_t checker_block_id = block_counter++;
  size_t first_loop_body_block_id = block_counter++;
  size_t following_block_id = block_counter++;
  auto checker_block = std::make_shared<BlockItem>();
  auto first_loop_body_block = std::make_shared<BlockItem>();
  auto following_block = std::make_shared<BlockItem>();
  checker_block->label_full = "label_" + std::to_string(checker_block_id);
  first_loop_body_block->label_full = "label_" + std::to_string(first_loop_body_block_id);
  following_block->label_full = "label_" + std::to_string(following_block_id);
  cur_block->exit_action = std::make_shared<UNConditionJMPAction>();
  std::dynamic_pointer_cast<UNConditionJMPAction>(cur_block->exit_action)->label_full = checker_block->label_full;
  cur_block = checker_block;
  cur_func->basic_blocks.push_back(checker_block);
  node->condition->accept(this);
  cur_block->exit_action = std::make_shared<BRAction>();
  std::dynamic_pointer_cast<BRAction>(cur_block->exit_action)->cond = node->condition->IR_result_full;
  std::dynamic_pointer_cast<BRAction>(cur_block->exit_action)->true_label_full = first_loop_body_block->label_full;
  std::dynamic_pointer_cast<BRAction>(cur_block->exit_action)->false_label_full = following_block->label_full;

  cur_block = first_loop_body_block;
  cur_func->basic_blocks.push_back(first_loop_body_block);
  cur_break_target = following_block->label_full;
  cur_continue_target = checker_block->label_full;
  node->loop_body->accept(this);
  if (!(cur_block->exit_action)) {
    cur_block->exit_action = std::make_shared<UNConditionJMPAction>();
    std::dynamic_pointer_cast<UNConditionJMPAction>(cur_block->exit_action)->label_full = checker_block->label_full;
  }

  cur_block = following_block;
  cur_func->basic_blocks.push_back(following_block);

  cur_break_target = break_target_backup;
  cur_continue_target = continue_target_backup;
  just_encountered_jmp = false;
}

void IRBuilder::ActuralVisit(ForStatement_ASTNode *node) {
  std::string break_target_backup = cur_break_target;
  std::string continue_target_backup = cur_continue_target;
  size_t checker_block_id = block_counter++;
  size_t first_loop_body_block_id = block_counter++;
  size_t step_block_id = block_counter++;
  size_t following_block_id = block_counter++;
  auto checker_block = std::make_shared<BlockItem>();
  auto first_loop_body_block = std::make_shared<BlockItem>();
  auto step_block = std::make_shared<BlockItem>();
  auto following_block = std::make_shared<BlockItem>();
  checker_block->label_full = "label_" + std::to_string(checker_block_id);
  first_loop_body_block->label_full = "label_" + std::to_string(first_loop_body_block_id);
  step_block->label_full = "label_" + std::to_string(step_block_id);
  following_block->label_full = "label_" + std::to_string(following_block_id);
  if (node->initial) {
    node->initial->accept(this);  // just finish initialization worker in current block
  }
  cur_block->exit_action = std::make_shared<UNConditionJMPAction>();
  std::dynamic_pointer_cast<UNConditionJMPAction>(cur_block->exit_action)->label_full = checker_block->label_full;
  cur_block = checker_block;
  cur_func->basic_blocks.push_back(checker_block);
  if (node->condition) {
    node->condition->accept(this);
    cur_block->exit_action = std::make_shared<BRAction>();
    std::dynamic_pointer_cast<BRAction>(cur_block->exit_action)->cond = node->condition->IR_result_full;
    std::dynamic_pointer_cast<BRAction>(cur_block->exit_action)->true_label_full = first_loop_body_block->label_full;
    std::dynamic_pointer_cast<BRAction>(cur_block->exit_action)->false_label_full = following_block->label_full;
  } else {
    cur_block->exit_action = std::make_shared<UNConditionJMPAction>();
    std::dynamic_pointer_cast<UNConditionJMPAction>(cur_block->exit_action)->label_full =
        first_loop_body_block->label_full;
  }
  cur_block = first_loop_body_block;
  cur_func->basic_blocks.push_back(first_loop_body_block);
  cur_break_target = following_block->label_full;
  cur_continue_target = step_block->label_full;
  node->loop_body->accept(this);
  if (!(cur_block->exit_action)) {
    cur_block->exit_action = std::make_shared<UNConditionJMPAction>();
    std::dynamic_pointer_cast<UNConditionJMPAction>(cur_block->exit_action)->label_full = step_block->label_full;
  }
  cur_block = step_block;
  cur_func->basic_blocks.push_back(step_block);
  if (node->update) {
    node->update->accept(this);
  }
  cur_block->exit_action = std::make_shared<UNConditionJMPAction>();
  std::dynamic_pointer_cast<UNConditionJMPAction>(cur_block->exit_action)->label_full = checker_block->label_full;
  cur_block = following_block;
  cur_func->basic_blocks.push_back(following_block);
  cur_break_target = break_target_backup;
  cur_continue_target = continue_target_backup;
  just_encountered_jmp = false;
}

void IRBuilder::ActuralVisit(JmpStatement_ASTNode *node) {
  if (node->jmp_type == 1) {
    // break
    cur_block->exit_action = std::make_shared<UNConditionJMPAction>();
    std::dynamic_pointer_cast<UNConditionJMPAction>(cur_block->exit_action)->label_full = cur_break_target;
    just_encountered_jmp = true;
  } else if (node->jmp_type == 2) {
    // continue
    cur_block->exit_action = std::make_shared<UNConditionJMPAction>();
    std::dynamic_pointer_cast<UNConditionJMPAction>(cur_block->exit_action)->label_full = cur_continue_target;
    just_encountered_jmp = true;
  } else if (node->jmp_type == 0) {
    // return
    cur_block->exit_action = std::make_shared<RETAction>();
    if (node->return_value) {
      node->return_value->accept(this);
      std::dynamic_pointer_cast<RETAction>(cur_block->exit_action)->value = node->return_value->IR_result_full;
    }
    std::dynamic_pointer_cast<RETAction>(cur_block->exit_action)->type = cur_func->return_type;
    just_encountered_jmp = true;
  } else {
    throw std::runtime_error("unknown jmp type");
  }
}

void IRBuilder::ActuralVisit(SuiteStatement_ASTNode *node) {
  for (auto &stmt : node->statements) {
    stmt->accept(this);
    if (just_encountered_jmp) {
      just_encountered_jmp = false;
      break;  // no need to continue
    }
  }
}

// Expression AST Nodes
void IRBuilder::ActuralVisit(NewArrayExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(NewConstructExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(NewExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(AccessExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(IndexExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(SuffixExpr_ASTNode *node) {
  node->base->is_requiring_lvalue = true;
  node->base->accept(this);
  std::string val_backup = "%.var.tmp." + std::to_string(tmp_var_counter++);
  auto backup_act = std::make_shared<LoadAction>();
  cur_block->actions.push_back(backup_act);
  backup_act->ty = Type_AST2LLVM(node->base->expr_type_info);
  backup_act->ptr_full = node->base->IR_result_full;
  backup_act->result_full = val_backup;
  auto op_act = std::make_shared<BinaryOperationAction>();
  cur_block->actions.push_back(op_act);
  if (node->op == "++") {
    op_act->op = "add";
  } else {
    op_act->op = "sub";
  }
  op_act->type = LLVMIRIntType(32);
  op_act->operand1_full = val_backup;
  op_act->operand2_full = "1";
  op_act->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
  auto store_act = std::make_shared<StoreAction>();
  cur_block->actions.push_back(store_act);
  store_act->ty = Type_AST2LLVM(node->base->expr_type_info);
  store_act->ptr_full = node->base->IR_result_full;
  store_act->value_full = op_act->result_full;
  node->IR_result_full = val_backup;
}

void IRBuilder::ActuralVisit(PrefixExpr_ASTNode *node) {
  node->base->is_requiring_lvalue = true;
  node->base->accept(this);
  std::string val_backup = "%.var.tmp." + std::to_string(tmp_var_counter++);
  auto backup_act = std::make_shared<LoadAction>();
  cur_block->actions.push_back(backup_act);
  backup_act->ty = Type_AST2LLVM(node->base->expr_type_info);
  backup_act->ptr_full = node->base->IR_result_full;
  backup_act->result_full = val_backup;
  auto op_act = std::make_shared<BinaryOperationAction>();
  cur_block->actions.push_back(op_act);
  if (node->op == "++") {
    op_act->op = "add";
  } else {
    op_act->op = "sub";
  }
  op_act->type = LLVMIRIntType(32);
  op_act->operand1_full = val_backup;
  op_act->operand2_full = "1";
  op_act->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
  auto store_act = std::make_shared<StoreAction>();
  cur_block->actions.push_back(store_act);
  store_act->ty = Type_AST2LLVM(node->base->expr_type_info);
  store_act->ptr_full = node->base->IR_result_full;
  store_act->value_full = op_act->result_full;
  if (node->is_requiring_lvalue) {
    node->IR_result_full = node->base->IR_result_full;
  } else {
    node->IR_result_full = op_act->result_full;
  }
}

void IRBuilder::ActuralVisit(OppositeExpr_ASTNode *node) {
  node->base->accept(this);
  auto act = std::make_shared<BinaryOperationAction>();
  cur_block->actions.push_back(act);
  act->op = "sub";
  act->operand1_full = "0";
  act->operand2_full = node->base->IR_result_full;
  act->type = LLVMIRIntType(32);
  act->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
  node->IR_result_full = act->result_full;
}

void IRBuilder::ActuralVisit(LNotExpr_ASTNode *node) {
  node->base->accept(this);
  auto act = std::make_shared<BinaryOperationAction>();
  cur_block->actions.push_back(act);
  act->op = "xor";
  act->operand1_full = node->base->IR_result_full;
  act->operand2_full = "1";
  act->type = LLVMIRIntType(1);
  act->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
  node->IR_result_full = act->result_full;
}

void IRBuilder::ActuralVisit(BNotExpr_ASTNode *node) {
  node->base->accept(this);
  auto act = std::make_shared<BinaryOperationAction>();
  cur_block->actions.push_back(act);
  act->op = "xor";
  act->operand1_full = node->base->IR_result_full;
  act->operand2_full = "-1";
  act->type = LLVMIRIntType(32);
  act->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
  node->IR_result_full = act->result_full;
}

void IRBuilder::ActuralVisit(MDMExpr_ASTNode *node) {
  node->left->accept(this);
  node->right->accept(this);
  auto act = std::make_shared<BinaryOperationAction>();
  cur_block->actions.push_back(act);
  if (node->op == "*") {
    act->op = "mul";
  } else if (node->op == "/") {
    act->op = "sdiv";
  } else if (node->op == "%") {
    act->op = "srem";
  } else {
    throw std::runtime_error("unknown MDM operator");
  }
  act->operand1_full = node->left->IR_result_full;
  act->operand2_full = node->right->IR_result_full;
  act->type = LLVMIRIntType(32);
  act->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
  node->IR_result_full = act->result_full;
}

void IRBuilder::ActuralVisit(PMExpr_ASTNode *node) {
  node->left->accept(this);
  node->right->accept(this);
  auto act = std::make_shared<BinaryOperationAction>();
  cur_block->actions.push_back(act);
  if (node->op == "+") {
    act->op = "add";
  } else if (node->op == "-") {
    act->op = "sub";
  } else {
    throw std::runtime_error("unknown PM operator");
  }
  act->operand1_full = node->left->IR_result_full;
  act->operand2_full = node->right->IR_result_full;
  act->type = LLVMIRIntType(32);
  act->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
  node->IR_result_full = act->result_full;
  // TODO: support for string concatenation
}

void IRBuilder::ActuralVisit(RLExpr_ASTNode *node) {
  node->left->accept(this);
  node->right->accept(this);
  auto act = std::make_shared<BinaryOperationAction>();
  cur_block->actions.push_back(act);
  if (node->op == ">>") {
    act->op = "ashr";
  } else if (node->op == "<<") {
    act->op = "shl";
  } else {
    throw std::runtime_error("unknown RL operator");
  }
  act->operand1_full = node->left->IR_result_full;
  act->operand2_full = node->right->IR_result_full;
  act->type = LLVMIRIntType(32);
  act->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
  node->IR_result_full = act->result_full;
}

void IRBuilder::ActuralVisit(GGLLExpr_ASTNode *node) {
  node->left->accept(this);
  node->right->accept(this);
  auto act = std::make_shared<ICMPAction>();
  cur_block->actions.push_back(act);
  if (node->op == ">=") {
    act->op = "sge";
  } else if (node->op == ">") {
    act->op = "sgt";
  } else if (node->op == "<=") {
    act->op = "sle";
  } else if (node->op == "<") {
    act->op = "slt";
  } else {
    throw std::runtime_error("unknown GGLL operator");
  }
  act->operand1_full = node->left->IR_result_full;
  act->operand2_full = node->right->IR_result_full;
  act->type = Type_AST2LLVM(node->left->expr_type_info);
  act->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
  node->IR_result_full = act->result_full;
  // TODO: string comparison
}

void IRBuilder::ActuralVisit(NEExpr_ASTNode *node) {
  node->left->accept(this);
  node->right->accept(this);
  auto act = std::make_shared<ICMPAction>();
  cur_block->actions.push_back(act);
  if (node->op == "!=") {
    act->op = "ne";
  } else if (node->op == "==") {
    act->op = "eq";
  } else {
    throw std::runtime_error("unknown NE operator");
  }
  act->operand1_full = node->left->IR_result_full;
  act->operand2_full = node->right->IR_result_full;
  act->type = Type_AST2LLVM(node->left->expr_type_info);
  act->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
  node->IR_result_full = act->result_full;
  // TODO: string comparison
}

void IRBuilder::ActuralVisit(BAndExpr_ASTNode *node) {
  node->left->accept(this);
  node->right->accept(this);
  auto act = std::make_shared<BinaryOperationAction>();
  cur_block->actions.push_back(act);
  act->op = "and";
  act->operand1_full = node->left->IR_result_full;
  act->operand2_full = node->right->IR_result_full;
  act->type = LLVMIRIntType(32);
  act->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
  node->IR_result_full = act->result_full;
}

void IRBuilder::ActuralVisit(BXorExpr_ASTNode *node) {
  node->left->accept(this);
  node->right->accept(this);
  auto act = std::make_shared<BinaryOperationAction>();
  cur_block->actions.push_back(act);
  act->op = "xor";
  act->operand1_full = node->left->IR_result_full;
  act->operand2_full = node->right->IR_result_full;
  act->type = LLVMIRIntType(32);
  act->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
  node->IR_result_full = act->result_full;
}

void IRBuilder::ActuralVisit(BOrExpr_ASTNode *node) {
  node->left->accept(this);
  node->right->accept(this);
  auto act = std::make_shared<BinaryOperationAction>();
  cur_block->actions.push_back(act);
  act->op = "or";
  act->operand1_full = node->left->IR_result_full;
  act->operand2_full = node->right->IR_result_full;
  act->type = LLVMIRIntType(32);
  act->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
  node->IR_result_full = act->result_full;
}

void IRBuilder::ActuralVisit(LAndExpr_ASTNode *node) {
  node->left->accept(this);
  node->right->accept(this);
  auto act = std::make_shared<BinaryOperationAction>();
  cur_block->actions.push_back(act);
  act->op = "and";
  act->operand1_full = node->left->IR_result_full;
  act->operand2_full = node->right->IR_result_full;
  act->type = LLVMIRIntType(1);
  act->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
  node->IR_result_full = act->result_full;
  // TODO: short-circuit
}

void IRBuilder::ActuralVisit(LOrExpr_ASTNode *node) {
  node->left->accept(this);
  node->right->accept(this);
  auto act = std::make_shared<BinaryOperationAction>();
  cur_block->actions.push_back(act);
  act->op = "or";
  act->operand1_full = node->left->IR_result_full;
  act->operand2_full = node->right->IR_result_full;
  act->type = LLVMIRIntType(1);
  act->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
  node->IR_result_full = act->result_full;
  // TODO: short-circuit
}

void IRBuilder::ActuralVisit(TernaryExpr_ASTNode *node) {
  // TODO: Implement function body
  throw std::runtime_error("ternary operator not supported");
}

void IRBuilder::ActuralVisit(AssignExpr_ASTNode *node) {
  node->dest->is_requiring_lvalue = true;
  node->dest->accept(this);
  node->src->accept(this);
  auto act = std::make_shared<StoreAction>();
  cur_block->actions.push_back(act);
  act->ptr_full = node->dest->IR_result_full;
  act->value_full = node->src->IR_result_full;
  act->ty = Type_AST2LLVM(node->src->expr_type_info);
}

void IRBuilder::ActuralVisit(ThisExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(ParenExpr_ASTNode *node) {
  node->expr->accept(this);  // just visit it
}

void IRBuilder::ActuralVisit(IDExpr_ASTNode *node) {
  IRVariableInfo var_info = node->current_scope->fetch_variable_for_IR(node->id);
  if (var_info.variable_type == 0 || var_info.variable_type == 1) {
    if (node->is_requiring_lvalue) {
      node->IR_result_full = var_info.GenerateFullName();
      return;
    }
    auto act = std::make_shared<LoadAction>();
    cur_block->actions.push_back(act);
    act->ptr_full = var_info.GenerateFullName();
    act->ty = var_info.ty;
    act->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
    node->IR_result_full = act->result_full;
  } else if (var_info.variable_type == 2) {
    throw std::runtime_error("not support for class member access");
  } else if (var_info.variable_type == 3) {
    if (node->is_requiring_lvalue) {
      throw std::runtime_error("for argument, lvalue support need additional work");
    }
    node->IR_result_full = var_info.GenerateFullName();
    return;
  } else {
    throw std::runtime_error("unknown variable type");
  }
}

void IRBuilder::ActuralVisit(FunctionCallExpr_ASTNode *node) {
  bool is_member_func = false;
  if (is_in_class_def) {
    try {
      auto schema = global_scope->FetchClassMemberFunction(cur_class_name, node->func_name);
      is_member_func = true;
    } catch (...) {
    }
  }
  if (is_member_func) {
    // TODO: member function call
    throw std::runtime_error("not support for class member function call");
  } else {
    auto call = std::make_shared<CallItem>();
    call->return_type = Type_AST2LLVM(node->expr_type_info);
    call->func_name_raw = node->func_name;
    for (auto &arg : node->arguments) {
      arg->accept(this);
      call->args_val_full.push_back(arg->IR_result_full);
      call->args_ty.push_back(Type_AST2LLVM(arg->expr_type_info));
    }
    cur_block->actions.push_back(call);
    if (!std::holds_alternative<LLVMVOIDType>(call->return_type)) {
      call->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
      node->IR_result_full = call->result_full;
    }
  }
}

void IRBuilder::ActuralVisit(FormattedStringExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(ConstantExpr_ASTNode *node) {
  if ((node->level == 0) != std::holds_alternative<AtomicConstantType>(node->value)) {
    throw std::runtime_error("ConstantExpr_ASTNode level not match");
  }
  if (std::holds_alternative<AtomicConstantType>(node->value)) {
    auto &val = std::get<AtomicConstantType>(node->value);
    if (std::holds_alternative<uint32_t>(val)) {
      node->IR_result_full = std::to_string(std::get<uint32_t>(val));
    } else if (std::holds_alternative<bool>(val)) {
      node->IR_result_full = std::to_string(int(std::get<bool>(val)));
    } else if (std::holds_alternative<std::string>(val)) {
      // TODO: string constant
      throw std::runtime_error("String constant not supported");
    } else if (std::holds_alternative<NullType>(val)) {
      node->IR_result_full = "null";
    } else {
      throw std::runtime_error("unknown constant type");
    }
  } else {
    // TODO: array constant
    throw std::runtime_error("Array constant not supported");
  }
}

std::shared_ptr<ModuleItem> BuildIR(std::shared_ptr<Program_ASTNode> src) {
  IRBuilder visitor;
  visitor.prog = std::make_shared<ModuleItem>();
  auto tmp = std::make_shared<FunctionDeclareItem>();
  tmp->func_name_raw = "malloc";
  tmp->return_type = LLVMIRPTRType();
  tmp->args.push_back(LLVMIRIntType(32));
  visitor.prog->function_declares.push_back(tmp);
  tmp = std::make_shared<FunctionDeclareItem>();
  tmp->func_name_raw = "printInt";
  tmp->return_type = LLVMVOIDType();
  tmp->args.push_back(LLVMIRIntType(32));
  visitor.prog->function_declares.push_back(tmp);
  tmp = std::make_shared<FunctionDeclareItem>();
  tmp->func_name_raw = "print";
  tmp->return_type = LLVMVOIDType();
  tmp->args.push_back(LLVMIRPTRType());
  visitor.prog->function_declares.push_back(tmp);
  visitor.global_scope = std::dynamic_pointer_cast<GlobalScope>(src->current_scope);
  if (!(visitor.global_scope)) throw std::runtime_error("global scope not found");
  visitor.visit(src.get());
  return visitor.prog;
}