#pragma once
#include <memory>
#include "IR_basic.h"
#include "ast/astnode_visitor.h"
class IRBuilder : public ASTNodeVirturalVisitor {
  friend std::shared_ptr<ModuleItem> BuildIR(std::shared_ptr<Program_ASTNode> src);
  std::shared_ptr<ModuleItem> prog;
  std::shared_ptr<TypeDefItem> cur_class;
  std::shared_ptr<FunctionDefItem> cur_func;
  std::shared_ptr<BlockItem> cur_block;
  std::string cur_class_name;
  bool is_in_class_def;
  bool is_in_func_def;
  size_t tmp_var_counter;
  size_t block_counter;
  std::string cur_break_target;
  std::string cur_continue_target;
  bool just_encountered_jmp;
  std::shared_ptr<GlobalScope> global_scope;

 public:
  IRBuilder() {
    tmp_var_counter = 0;
    block_counter = 0;
    is_in_class_def = false;
    is_in_func_def = false;
    just_encountered_jmp = false;
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
};

std::shared_ptr<ModuleItem> BuildIR(std::shared_ptr<Program_ASTNode> src);