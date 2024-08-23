#include "IRBuilder.h"
#include <stdexcept>
#include <string>
#include "IR.h"
#include "IR_basic.h"
#include "ast/scope.hpp"
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
  cur_func_scope = std::dynamic_pointer_cast<FunctionScope>(node->current_scope);
  if (!(cur_func_scope)) throw std::runtime_error("Function scope not found");
  auto current_block = std::make_shared<BlockItem>();
  cur_block = current_block;
  cur_func->basic_blocks.push_back(current_block);
  size_t block_id = block_counter++;
  current_block->label_full = "label_" + std::to_string(block_id);

  if (node->func_name == "main") {
    func_def->init_block = main_init_block;
  } else {
    func_def->init_block = std::make_shared<BlockItem>();
    func_def->init_block->label_full = "label_init_" + node->func_name;
    for (auto &arg : node->params) {
      std::string &arg_name_raw = arg.first;
      std::string rvalue_full_name = "%.var.local." + std::to_string(scope_id) + "." + arg_name_raw + ".val";
      std::string lvalue_full_name = "%.var.local." + std::to_string(scope_id) + "." + arg_name_raw + ".addrkp";
      auto allocact = std::make_shared<AllocaAction>();
      func_def->init_block->actions.push_back(allocact);
      allocact->num = 1;
      allocact->type = Type_AST2LLVM(arg.second);
      allocact->name_full = lvalue_full_name;
      auto storeact = std::make_shared<StoreAction>();
      func_def->init_block->actions.push_back(storeact);
      storeact->ty = Type_AST2LLVM(arg.second);
      storeact->ptr_full = lvalue_full_name;
      storeact->value_full = rvalue_full_name;
    }
  }
  cur_func->init_block->exit_action = std::make_shared<UNConditionJMPAction>();
  std::dynamic_pointer_cast<UNConditionJMPAction>(cur_func->init_block->exit_action)->label_full =
      current_block->label_full;
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
  if (is_in_class_def && !is_in_func_def) {
    for (size_t i = 0; i < node->vars.size(); i++) cur_class->elements.push_back(Type_AST2LLVM(node->var_type));
  } else if (!is_in_func_def) {
    for (const auto &var : node->vars) {
      auto var_def = std::make_shared<GlobalVarDefItem>();
      prog->global_var_defs.push_back(var_def);
      var_def->type = Type_AST2LLVM(node->var_type);
      var_def->name_raw = var.first;
      if (var.second) {
        var.second->accept(this);
        std::string init_var = var.second->IR_result_full;
        if (init_var[0] == '#') {
          init_var = "%.var.tmp." + std::to_string(tmp_var_counter++);
          auto const_array_construct_call = std::make_shared<CallItem>();
          main_init_block->actions.push_back(const_array_construct_call);
          const_array_construct_call->result_full = init_var;
          const_array_construct_call->return_type = LLVMIRPTRType();
          const_array_construct_call->func_name_raw = var.second->IR_result_full.substr(1);
        } else if (init_var[0] == '!') {
          // inline builder
          auto inline_builder = inline_builders[init_var.substr(1)];
          init_var = std::dynamic_pointer_cast<RETAction>(inline_builder->exit_action)->value;
          for (auto &act : inline_builder->actions) {
            main_init_block->actions.push_back(act);
          }
        }
        auto act = std::make_shared<StoreAction>();
        main_init_block->actions.push_back(act);
        act->ty = var_def->type;
        act->ptr_full = "@.var.global." + var_def->name_raw + ".addrkp";
        act->value_full = init_var;
      }
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
        std::string init_var = var.second->IR_result_full;
        if (init_var[0] == '#') {
          init_var = "%.var.tmp." + std::to_string(tmp_var_counter++);
          auto const_array_construct_call = std::make_shared<CallItem>();
          cur_block->actions.push_back(const_array_construct_call);
          const_array_construct_call->result_full = init_var;
          const_array_construct_call->return_type = LLVMIRPTRType();
          const_array_construct_call->func_name_raw = var.second->IR_result_full.substr(1);
        } else if (init_var[0] == '!') {
          // inline builder
          auto inline_builder = inline_builders[init_var.substr(1)];
          init_var = std::dynamic_pointer_cast<RETAction>(inline_builder->exit_action)->value;
          for (auto &act : inline_builder->actions) {
            cur_block->actions.push_back(act);
          }
        }
        auto act = std::make_shared<StoreAction>();
        cur_block->actions.push_back(act);
        act->ty = var_def->type;
        act->ptr_full = var_def->name_full;
        act->value_full = init_var;
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
  if (node->initial_value) {
    node->initial_value->accept(this);  // Just visit it
    node->IR_result_full = node->initial_value->IR_result_full;
    return;
  }
  std::string constructing_func_name = ".constarr." + std::to_string(const_arr_counter++);
  // auto cons_func = std::make_shared<FunctionDefItem>();
  // prog->function_defs.push_back(cons_func);
  // cons_func->func_name_raw = constructing_func_name;
  // cons_func->return_type = LLVMIRPTRType();
  auto block = std::make_shared<BlockItem>();
  inline_builders[constructing_func_name] = block;
  block->label_full = "label_constarr_" + std::to_string(const_arr_counter - 1);
  block->exit_action = std::make_shared<RETAction>();
  std::dynamic_pointer_cast<RETAction>(block->exit_action)->type = LLVMIRPTRType();

  std::vector<std::string> dim_size_info;
  for (size_t i = 0; i < node->dim_size.size(); i++) {
    if (!(node->dim_size[i])) break;
    node->dim_size[i]->accept(this);
    dim_size_info.push_back(node->dim_size[i]->IR_result_full);
  }
  int dims_with_size = dim_size_info.size();
  int element_size = 4;
  if (dims_with_size == node->dim_size.size()) {
    ArrayType tp = std::get<ArrayType>(node->expr_type_info);
    std::string base_type = tp.basetype;
    if (base_type == "bool") element_size = 1;
  }

  auto dim_info = std::make_shared<AllocaAction>();
  std::string dim_info_var = "%.var.tmp." + std::to_string(tmp_var_counter++);
  block->actions.push_back(dim_info);
  dim_info->num = dims_with_size;
  dim_info->name_full = dim_info_var;
  dim_info->type = LLVMIRIntType(32);
  for (size_t i = 0; i < dim_size_info.size(); i++) {
    std::string cur_ptr = "%.var.tmp." + std::to_string(tmp_var_counter++);
    auto get_addr = std::make_shared<GetElementPtrAction>();
    block->actions.push_back(get_addr);
    get_addr->result_full = cur_ptr;
    get_addr->ty = LLVMIRIntType(32);
    get_addr->ptr_full = dim_info_var;
    get_addr->indices.push_back(std::to_string(i));
    auto store_act = std::make_shared<StoreAction>();
    block->actions.push_back(store_act);
    store_act->ty = LLVMIRIntType(32);
    store_act->ptr_full = cur_ptr;
    store_act->value_full = dim_size_info[i];
  }
  auto allocate_call = std::make_shared<CallItem>();
  block->actions.push_back(allocate_call);
  allocate_call->func_name_raw = ".builtin.RecursiveAllocateArray";
  allocate_call->return_type = LLVMIRPTRType();
  std::string res = "%.var.tmp." + std::to_string(tmp_var_counter++);
  allocate_call->result_full = res;
  allocate_call->args_ty.push_back(LLVMIRIntType(32));
  allocate_call->args_val_full.push_back(std::to_string(dims_with_size));
  allocate_call->args_ty.push_back(LLVMIRIntType(32));
  allocate_call->args_val_full.push_back(std::to_string(element_size));
  allocate_call->args_ty.push_back(LLVMIRPTRType());
  allocate_call->args_val_full.push_back(dim_info_var);
  auto ret = std::make_shared<RETAction>();
  block->exit_action = ret;
  ret->type = LLVMIRPTRType();
  ret->value = res;

  node->IR_result_full = "!" + constructing_func_name;  // inline builder
}

void IRBuilder::ActuralVisit(NewConstructExpr_ASTNode *node) {
  std::string class_name = std::get<IdentifierType>(node->expr_type_info);
  if (already_set_constructor.find(class_name) != already_set_constructor.end()) {
    node->IR_result_full = "#.classconstruct." + class_name;
    return;
  }
  already_set_constructor.insert(class_name);
  std::string construct_func_name = ".classconstruct." + class_name;
  auto construct_func = std::make_shared<FunctionDefItem>();
  prog->function_defs.push_back(construct_func);
  construct_func->return_type = LLVMIRPTRType();
  construct_func->func_name_raw = construct_func_name;
  auto block = std::make_shared<BlockItem>();
  construct_func->basic_blocks.push_back(block);
  block->label_full = "label_construct_" + class_name;
  IRClassInfo class_info = global_scope->fetch_class_info(class_name);
  std::string allocated_addr = "%.var.tmp." + std::to_string(tmp_var_counter++);
  auto malloc_call = std::make_shared<CallItem>();
  block->actions.push_back(malloc_call);
  malloc_call->result_full = allocated_addr;
  malloc_call->return_type = LLVMIRPTRType();
  malloc_call->func_name_raw = "malloc";  // just use libc malloc
  malloc_call->args_ty.push_back(LLVMIRIntType(32));
  malloc_call->args_val_full.push_back(std::to_string(class_info.class_size_after_align));
  if (class_info.has_user_specified_constructor) {
    auto call_act = std::make_shared<CallItem>();
    block->actions.push_back(call_act);
    call_act->return_type = LLVMVOIDType();
    call_act->func_name_raw = class_name + "." + class_name;
    call_act->args_ty.push_back(LLVMIRPTRType());
    call_act->args_val_full.push_back(allocated_addr);
  }
  auto ret_act = std::make_shared<RETAction>();
  block->exit_action = ret_act;
  ret_act->type = LLVMIRPTRType();
  ret_act->value = allocated_addr;
  node->IR_result_full = "#" + construct_func_name;
}

void IRBuilder::ActuralVisit(NewExpr_ASTNode *node) {
  std::string class_name = std::get<IdentifierType>(node->expr_type_info);
  if (already_set_constructor.find(class_name) != already_set_constructor.end()) {
    node->IR_result_full = "#.classconstruct." + class_name;
    return;
  }
  already_set_constructor.insert(class_name);
  std::string construct_func_name = ".classconstruct." + class_name;
  auto construct_func = std::make_shared<FunctionDefItem>();
  prog->function_defs.push_back(construct_func);
  construct_func->return_type = LLVMIRPTRType();
  construct_func->func_name_raw = construct_func_name;
  auto block = std::make_shared<BlockItem>();
  construct_func->basic_blocks.push_back(block);
  block->label_full = "label_construct_" + class_name;
  IRClassInfo class_info = global_scope->fetch_class_info(class_name);
  std::string allocated_addr = "%.var.tmp." + std::to_string(tmp_var_counter++);
  auto malloc_call = std::make_shared<CallItem>();
  block->actions.push_back(malloc_call);
  malloc_call->result_full = allocated_addr;
  malloc_call->return_type = LLVMIRPTRType();
  malloc_call->func_name_raw = "malloc";  // just use libc malloc
  malloc_call->args_ty.push_back(LLVMIRIntType(32));
  malloc_call->args_val_full.push_back(std::to_string(class_info.class_size_after_align));
  if (class_info.has_user_specified_constructor) {
    auto call_act = std::make_shared<CallItem>();
    block->actions.push_back(call_act);
    call_act->return_type = LLVMVOIDType();
    call_act->func_name_raw = class_name + "." + class_name;
    call_act->args_ty.push_back(LLVMIRPTRType());
    call_act->args_val_full.push_back(allocated_addr);
  }
  auto ret_act = std::make_shared<RETAction>();
  block->exit_action = ret_act;
  ret_act->type = LLVMIRPTRType();
  ret_act->value = allocated_addr;
  node->IR_result_full = "#" + construct_func_name;
}

void IRBuilder::ActuralVisit(AccessExpr_ASTNode *node) {
  if (!node->is_function) {
    node->base->accept(this);
    std::string type_of_base = std::get<IdentifierType>(node->base->expr_type_info);
    IRClassInfo class_info = global_scope->fetch_class_info(type_of_base);
    std::string base_ptr = node->base->IR_result_full;
    size_t idx = class_info.member_var_offset[node->member];
    auto member_addr_cal = std::make_shared<GetElementPtrAction>();
    cur_block->actions.push_back(member_addr_cal);
    member_addr_cal->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
    member_addr_cal->ty = LLVMIRCLASSTYPE{"%.class." + type_of_base};
    member_addr_cal->ptr_full = base_ptr;
    member_addr_cal->indices.push_back("0");
    member_addr_cal->indices.push_back(std::to_string(idx));
    if (node->is_requiring_lvalue) {
      node->IR_result_full = member_addr_cal->result_full;
    } else {
      auto member_val_load = std::make_shared<LoadAction>();
      cur_block->actions.push_back(member_val_load);
      member_val_load->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
      member_val_load->ty = class_info.member_var_type[idx];
      member_val_load->ptr_full = member_addr_cal->result_full;
      node->IR_result_full = member_val_load->result_full;
    }
  } else {
    node->base->accept(this);
    std::string type_of_base;
    if (std::holds_alternative<IdentifierType>(node->base->expr_type_info))
      type_of_base = std::get<IdentifierType>(node->base->expr_type_info);
    std::string base_ptr = node->base->IR_result_full;
    std::string func_name = type_of_base + "." + node->member;
    if (std::holds_alternative<ArrayType>(node->base->expr_type_info)) func_name = ".builtin.GetArrayLength";
    std::vector<std::string> arg_val;
    for (size_t i = 0; i < node->arguments.size(); i++) {
      node->arguments[i]->accept(this);
      arg_val.push_back(node->arguments[i]->IR_result_full);
    }
    auto call_act = std::make_shared<CallItem>();
    cur_block->actions.push_back(call_act);
    call_act->return_type = Type_AST2LLVM(node->expr_type_info);
    if (!std::holds_alternative<LLVMVOIDType>(call_act->return_type)) {
      call_act->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
    }
    call_act->func_name_raw = func_name;
    call_act->args_ty.push_back(LLVMIRPTRType());
    call_act->args_val_full.push_back(base_ptr);
    for (size_t i = 0; i < arg_val.size(); i++) {
      call_act->args_ty.push_back(Type_AST2LLVM(node->arguments[i]->expr_type_info));
      call_act->args_val_full.push_back(arg_val[i]);
    }
    if (!std::holds_alternative<LLVMVOIDType>(call_act->return_type)) {
      node->IR_result_full = call_act->result_full;
    }
  }
}

void IRBuilder::ActuralVisit(IndexExpr_ASTNode *node) {
  node->base->accept(this);
  std::string cur_val = node->base->IR_result_full;
  std::string cur_addr;
  for (size_t i = 0; i < node->indices.size(); i++) {
    LLVMType cur_ty;
    if (i + 1 < node->indices.size())
      cur_ty = LLVMIRPTRType();
    else {
      ArrayType tp = std::get<ArrayType>(node->base->expr_type_info);
      if (tp.basetype == "bool")
        cur_ty = LLVMIRIntType(1);
      else if (tp.basetype == "int")
        cur_ty = LLVMIRIntType(32);
      else
        cur_ty = LLVMIRPTRType();
    }
    node->indices[i]->accept(this);
    std::string idx = node->indices[i]->IR_result_full;
    cur_addr = "%.var.tmp." + std::to_string(tmp_var_counter++);
    auto addr_cal = std::make_shared<GetElementPtrAction>();
    cur_block->actions.push_back(addr_cal);
    addr_cal->result_full = cur_addr;
    addr_cal->ty = cur_ty;
    addr_cal->ptr_full = cur_val;
    addr_cal->indices.push_back(idx);
    if (i + 1 == node->indices.size() && node->is_requiring_lvalue) break;
    auto val_load = std::make_shared<LoadAction>();
    cur_val = "%.var.tmp." + std::to_string(tmp_var_counter++);
    cur_block->actions.push_back(val_load);
    val_load->result_full = cur_val;
    val_load->ty = cur_ty;
    val_load->ptr_full = cur_addr;
  }
  if (node->is_requiring_lvalue) {
    node->IR_result_full = cur_addr;
  } else {
    node->IR_result_full = cur_val;
  }
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
  act->ptr_full = node->dest->IR_result_full;
  std::string src = node->src->IR_result_full;
  if (src[0] == '#') {
    src = "%.var.tmp." + std::to_string(tmp_var_counter++);
    auto const_array_construct_call = std::make_shared<CallItem>();
    cur_block->actions.push_back(const_array_construct_call);
    const_array_construct_call->result_full = src;
    const_array_construct_call->return_type = LLVMIRPTRType();
    const_array_construct_call->func_name_raw = node->src->IR_result_full.substr(1);
  } else if (src[0] == '!') {
    // inline builder
    auto inline_builder = inline_builders[src.substr(1)];
    src = std::dynamic_pointer_cast<RETAction>(inline_builder->exit_action)->value;
    for (auto &act : inline_builder->actions) {
      cur_block->actions.push_back(act);
    }
  }
  cur_block->actions.push_back(act);
  act->value_full = src;
  act->ty = Type_AST2LLVM(node->src->expr_type_info);
}

void IRBuilder::ActuralVisit(ThisExpr_ASTNode *node) {
  size_t scope_id = cur_func_scope->scope_id;
  node->IR_result_full = "%.var.local." + std::to_string(scope_id) + ".this.val";
}

void IRBuilder::ActuralVisit(ParenExpr_ASTNode *node) {
  node->expr->accept(this);  // just visit it
  node->IR_result_full = node->expr->IR_result_full;
}

void IRBuilder::ActuralVisit(IDExpr_ASTNode *node) {
  IRVariableInfo var_info = node->current_scope->fetch_variable_for_IR(node->id);
  if (var_info.variable_type == 0 || var_info.variable_type == 1 || var_info.variable_type == 3) {
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
    size_t scope_id = cur_func_scope->scope_id;
    std::string this_ptr = "%.var.local." + std::to_string(scope_id) + ".this.val";
    std::string class_name = cur_class_name;
    std::string member_var_name = var_info.variable_name_raw;
    IRClassInfo class_info = global_scope->fetch_class_info(class_name);
    size_t idx = class_info.member_var_offset[member_var_name];
    auto member_addr_cal = std::make_shared<GetElementPtrAction>();
    cur_block->actions.push_back(member_addr_cal);
    member_addr_cal->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
    member_addr_cal->ty = LLVMIRCLASSTYPE{"%.class." + class_name};
    member_addr_cal->ptr_full = this_ptr;
    member_addr_cal->indices.push_back("0");
    member_addr_cal->indices.push_back(std::to_string(idx));
    if (node->is_requiring_lvalue) {
      node->IR_result_full = member_addr_cal->result_full;
    } else {
      auto member_val_load = std::make_shared<LoadAction>();
      cur_block->actions.push_back(member_val_load);
      member_val_load->result_full = "%.var.tmp." + std::to_string(tmp_var_counter++);
      member_val_load->ty = class_info.member_var_type[idx];
      member_val_load->ptr_full = member_addr_cal->result_full;
      node->IR_result_full = member_val_load->result_full;
    }
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
    size_t scope_id = cur_func_scope->scope_id;
    std::string this_ptr = "%.var.local." + std::to_string(scope_id) + ".this.val";
    std::string class_name = cur_class_name;
    std::string full_func_name = class_name + "." + node->func_name;
    auto call = std::make_shared<CallItem>();
    call->return_type = Type_AST2LLVM(node->expr_type_info);
    call->func_name_raw = full_func_name;
    call->args_val_full.push_back(this_ptr);
    call->args_ty.push_back(LLVMIRPTRType());
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
  throw std::runtime_error("formatted string not supported");
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
      std::string str = StringLiteralDeEscape(std::get<std::string>(val));
      if (const_str_dict.find(str) == const_str_dict.end()) {
        const_str_dict[str] = const_str_counter++;
        auto const_str_item = std::make_shared<ConstStrItem>();
        prog->const_strs.push_back(const_str_item);
        const_str_item->string_raw = str;
        const_str_item->const_str_id = const_str_dict[str];
      }
      node->IR_result_full = "@.str." + std::to_string(const_str_dict[str]);
    } else if (std::holds_alternative<NullType>(val)) {
      node->IR_result_full = "null";
    } else {
      throw std::runtime_error("unknown constant type");
    }
  } else {
    std::string constructing_func_name = ".constarr." + std::to_string(const_arr_counter++);
    auto cons_func = std::make_shared<FunctionDefItem>();
    prog->function_defs.push_back(cons_func);
    cons_func->func_name_raw = constructing_func_name;
    cons_func->return_type = LLVMIRPTRType();
    auto block = std::make_shared<BlockItem>();
    cons_func->basic_blocks.push_back(block);
    block->label_full = "label_constarr_" + std::to_string(const_arr_counter - 1);
    block->exit_action = std::make_shared<RETAction>();
    std::dynamic_pointer_cast<RETAction>(block->exit_action)->type = LLVMIRPTRType();
    ArrangeConstArr(*block, node);
    node->IR_result_full = "#" + constructing_func_name;
  }
}

std::shared_ptr<ModuleItem> BuildIR(std::shared_ptr<Program_ASTNode> src) {
  IRBuilder visitor;
  visitor.prog = std::make_shared<ModuleItem>();
  auto tmp = std::make_shared<FunctionDeclareItem>();  // void* malloc(unsigned int size)
  tmp->func_name_raw = "malloc";
  tmp->return_type = LLVMIRPTRType();
  tmp->args.push_back(LLVMIRIntType(32));
  visitor.prog->function_declares.push_back(tmp);

  tmp = std::make_shared<FunctionDeclareItem>();  // void printInt(int n)
  tmp->func_name_raw = "printInt";
  tmp->return_type = LLVMVOIDType();
  tmp->args.push_back(LLVMIRIntType(32));
  visitor.prog->function_declares.push_back(tmp);

  tmp = std::make_shared<FunctionDeclareItem>();  // void print(char *str)
  tmp->func_name_raw = "print";
  tmp->return_type = LLVMVOIDType();
  tmp->args.push_back(LLVMIRPTRType());
  visitor.prog->function_declares.push_back(tmp);

  tmp = std::make_shared<FunctionDeclareItem>();  // void* _builtin_AllocateArray(int element_size, int element_num)
  tmp->func_name_raw = ".builtin.AllocateArray";
  tmp->return_type = LLVMIRPTRType();
  tmp->args.push_back(LLVMIRIntType(32));
  tmp->args.push_back(LLVMIRIntType(32));
  visitor.prog->function_declares.push_back(tmp);

  tmp = std::make_shared<FunctionDeclareItem>();  // void* _builtin_RecursiveAllocateArray(int dims_with_size,
                                                  // int element_size, int* dim_size)
  tmp->func_name_raw = ".builtin.RecursiveAllocateArray";
  tmp->return_type = LLVMIRPTRType();
  tmp->args.push_back(LLVMIRIntType(32));
  tmp->args.push_back(LLVMIRIntType(32));
  tmp->args.push_back(LLVMIRPTRType());
  visitor.prog->function_declares.push_back(tmp);

  tmp = std::make_shared<FunctionDeclareItem>();  // int _builtin_GetArrayLength(void* array)
  tmp->func_name_raw = ".builtin.GetArrayLength";
  tmp->return_type = LLVMIRIntType(32);
  tmp->args.push_back(LLVMIRPTRType());
  visitor.prog->function_declares.push_back(tmp);

  tmp = std::make_shared<FunctionDeclareItem>();  // int getInt()
  tmp->func_name_raw = "getInt";
  tmp->return_type = LLVMIRIntType(32);
  visitor.prog->function_declares.push_back(tmp);

  tmp = std::make_shared<FunctionDeclareItem>();  // char* getString()
  tmp->func_name_raw = "getString";
  tmp->return_type = LLVMIRPTRType();
  visitor.prog->function_declares.push_back(tmp);

  tmp = std::make_shared<FunctionDeclareItem>();  // char* toString(int n)
  tmp->func_name_raw = "toString";
  tmp->return_type = LLVMIRPTRType();
  tmp->args.push_back(LLVMIRIntType(32));
  visitor.prog->function_declares.push_back(tmp);

  tmp = std::make_shared<FunctionDeclareItem>();  // void printlnInt(int n)
  tmp->func_name_raw = "printlnInt";
  tmp->return_type = LLVMVOIDType();
  tmp->args.push_back(LLVMIRIntType(32));
  visitor.prog->function_declares.push_back(tmp);

  tmp = std::make_shared<FunctionDeclareItem>();  // void println(char *str)
  tmp->func_name_raw = "println";
  tmp->return_type = LLVMVOIDType();
  tmp->args.push_back(LLVMIRPTRType());
  visitor.prog->function_declares.push_back(tmp);

  tmp = std::make_shared<FunctionDeclareItem>();  // int string_length(char *self)
  tmp->func_name_raw = "string.length";
  tmp->return_type = LLVMIRIntType(32);
  tmp->args.push_back(LLVMIRPTRType());
  visitor.prog->function_declares.push_back(tmp);

  tmp = std::make_shared<FunctionDeclareItem>();  // char* string_substring(char *self,int left, int right)
  tmp->func_name_raw = "string.substring";
  tmp->return_type = LLVMIRPTRType();
  tmp->args.push_back(LLVMIRPTRType());
  tmp->args.push_back(LLVMIRIntType(32));
  tmp->args.push_back(LLVMIRIntType(32));
  visitor.prog->function_declares.push_back(tmp);

  tmp = std::make_shared<FunctionDeclareItem>();  // int string_parseInt(char *self)
  tmp->func_name_raw = "string.parseInt";
  tmp->return_type = LLVMIRIntType(32);
  tmp->args.push_back(LLVMIRPTRType());
  visitor.prog->function_declares.push_back(tmp);

  tmp = std::make_shared<FunctionDeclareItem>();  // int string_ord(char *self, int index)
  tmp->func_name_raw = "string.ord";
  tmp->return_type = LLVMIRIntType(32);
  tmp->args.push_back(LLVMIRPTRType());
  tmp->args.push_back(LLVMIRIntType(32));
  visitor.prog->function_declares.push_back(tmp);

  visitor.global_scope = std::dynamic_pointer_cast<GlobalScope>(src->current_scope);
  if (!(visitor.global_scope)) throw std::runtime_error("global scope not found");
  visitor.visit(src.get());
  return visitor.prog;
}