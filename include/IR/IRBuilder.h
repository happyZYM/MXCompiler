#pragma once
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include "IR_basic.h"
#include "ast/astnode_visitor.h"
#include "ast/scope.hpp"
#include "tools.h"
class IRBuilder : public ASTNodeVirturalVisitor {
  friend std::shared_ptr<ModuleItem> BuildIR(std::shared_ptr<Program_ASTNode> src);
  std::shared_ptr<ModuleItem> prog;
  std::shared_ptr<TypeDefItem> cur_class;
  std::shared_ptr<FunctionDefItem> cur_func;
  std::shared_ptr<BlockItem> cur_block;
  std::shared_ptr<BlockItem> main_init_block;
  std::string cur_class_name;
  bool is_in_class_def;
  bool is_in_func_def;
  size_t tmp_var_counter;
  size_t block_counter;
  std::string cur_break_target;
  std::string cur_continue_target;
  bool just_encountered_jmp;
  std::shared_ptr<GlobalScope> global_scope;
  std::shared_ptr<FunctionScope> cur_func_scope;
  size_t const_str_counter;
  std::unordered_map<std::string, size_t> const_str_dict;
  size_t const_arr_counter;
  std::unordered_set<std::string> already_set_constructor;
  std::unordered_map<std::string, std::shared_ptr<BlockItem>> inline_builders;

 public:
  IRBuilder() {
    tmp_var_counter = 0;
    block_counter = 0;
    is_in_class_def = false;
    is_in_func_def = false;
    just_encountered_jmp = false;
    const_str_counter = 0;
    const_arr_counter = 0;
    main_init_block = std::make_shared<BlockItem>();
    main_init_block->label_full = "main_init";
  }
  // Structural AST Nodes
  void ActuralVisit(FuncDef_ASTNode *node) override;
  void ActuralVisit(ClassDef_ASTNode *node) override;
  void ActuralVisit(Program_ASTNode *node) override;

  // Statement AST Nodes
  void ActuralVisit(EmptyStatement_ASTNode *node) override;
  void ActuralVisit(DefinitionStatement_ASTNode *node) override;
  void ActuralVisit(ExprStatement_ASTNode *node) override;
  void ActuralVisit(IfStatement_ASTNode *node) override;
  void ActuralVisit(WhileStatement_ASTNode *node) override;
  void ActuralVisit(ForStatement_ASTNode *node) override;
  void ActuralVisit(JmpStatement_ASTNode *node) override;
  void ActuralVisit(SuiteStatement_ASTNode *node) override;

  // Expression AST Nodes
  void ActuralVisit(NewArrayExpr_ASTNode *node) override;
  void ActuralVisit(NewConstructExpr_ASTNode *node) override;
  void ActuralVisit(NewExpr_ASTNode *node) override;
  void ActuralVisit(AccessExpr_ASTNode *node) override;
  void ActuralVisit(IndexExpr_ASTNode *node) override;
  void ActuralVisit(SuffixExpr_ASTNode *node) override;
  void ActuralVisit(PrefixExpr_ASTNode *node) override;
  void ActuralVisit(OppositeExpr_ASTNode *node) override;
  void ActuralVisit(LNotExpr_ASTNode *node) override;
  void ActuralVisit(BNotExpr_ASTNode *node) override;
  void ActuralVisit(MDMExpr_ASTNode *node) override;
  void ActuralVisit(PMExpr_ASTNode *node) override;
  void ActuralVisit(RLExpr_ASTNode *node) override;
  void ActuralVisit(GGLLExpr_ASTNode *node) override;
  void ActuralVisit(NEExpr_ASTNode *node) override;
  void ActuralVisit(BAndExpr_ASTNode *node) override;
  void ActuralVisit(BXorExpr_ASTNode *node) override;
  void ActuralVisit(BOrExpr_ASTNode *node) override;
  void ActuralVisit(LAndExpr_ASTNode *node) override;
  void ActuralVisit(LOrExpr_ASTNode *node) override;
  void ActuralVisit(TernaryExpr_ASTNode *node) override;
  void ActuralVisit(AssignExpr_ASTNode *node) override;
  void ActuralVisit(ThisExpr_ASTNode *node) override;
  void ActuralVisit(ParenExpr_ASTNode *node) override;
  void ActuralVisit(IDExpr_ASTNode *node) override;
  void ActuralVisit(FunctionCallExpr_ASTNode *node) override;
  void ActuralVisit(FormattedStringExpr_ASTNode *node) override;
  void ActuralVisit(ConstantExpr_ASTNode *node) override;
  std::string ArrangeConstArrDfs(BlockItem &blk, ConstantExpr_ASTNode *node, size_t depth, size_t total_level,
                                 LLVMType basetype) {
    if (std::holds_alternative<AtomicConstantType>(node->value)) {
      node->accept(this);
      return node->IR_result_full;
    }
    LLVMType ty;
    size_t elem_size;
    if (depth + 1 == total_level) {
      ty = basetype;
      if (std::holds_alternative<LLVMIRIntType>(ty)) {
        elem_size = (std::get<LLVMIRIntType>(ty).bits + 7) / 8;
      } else if (std::holds_alternative<LLVMIRPTRType>(ty)) {
        elem_size = 4;
      } else {
        throw std::runtime_error("Unexpected type in const array");
      }
    } else {
      ty = LLVMIRPTRType();
      elem_size = 4;
    }
    auto &sub_nodes = std::get<std::vector<std::shared_ptr<ConstantExpr_ASTNode>>>(node->value);
    std::string array_head = "%.var.tmp." + std::to_string(tmp_var_counter++);
    auto allocate_action = std::make_shared<CallItem>();
    blk.actions.push_back(allocate_action);
    allocate_action->func_name_raw = ".builtin.AllocateArray";
    allocate_action->result_full = array_head;
    allocate_action->return_type = LLVMIRPTRType();
    allocate_action->args_ty.push_back(LLVMIRIntType(32));
    allocate_action->args_val_full.push_back(std::to_string(elem_size));
    allocate_action->args_ty.push_back(LLVMIRIntType(32));
    allocate_action->args_val_full.push_back(std::to_string(sub_nodes.size()));
    for (size_t i = 0; i < sub_nodes.size(); i++) {
      std::string ret = ArrangeConstArrDfs(blk, sub_nodes[i].get(), depth + 1, total_level, basetype);
      std::string addr = "%.var.tmp." + std::to_string(tmp_var_counter++);
      auto ptr_cal = std::make_shared<GetElementPtrAction>();
      blk.actions.push_back(ptr_cal);
      ptr_cal->result_full = addr;
      ptr_cal->ty = ty;
      ptr_cal->ptr_full = array_head;
      ptr_cal->indices.push_back(std::to_string(i));
      auto store_action = std::make_shared<StoreAction>();
      blk.actions.push_back(store_action);
      store_action->ty = ty;
      store_action->ptr_full = addr;
      store_action->value_full = ret;
    }

    return allocate_action->result_full;
  }
  void ArrangeConstArr(BlockItem &blk, ConstantExpr_ASTNode *node) {
    ArrayType tp = std::get<ArrayType>(node->expr_type_info);
    std::dynamic_pointer_cast<RETAction>(blk.exit_action)->value =
        ArrangeConstArrDfs(blk, node, 0, tp.level, Type_AST2LLVM(tp.basetype));
  }
};

std::shared_ptr<ModuleItem> BuildIR(std::shared_ptr<Program_ASTNode> src);