#pragma once
#include "astnode.h"
#include "expr_astnode.h"
#include "statement_astnode.h"
#include "structural_astnode.h"
#include "astnode_visitor.h"

class ASTSemanticCheckVisitor : public ASTNodeVirturalVisitor {
  bool is_in_func_def;
  bool has_return;
  FunctionSchema cur_func_schema;
  std::string cur_class_name;
  bool is_in_class_def;
  size_t loop_level;
  std::shared_ptr<GlobalScope> global_scope;
  friend std::shared_ptr<Program_ASTNode> CheckAndDecorate(std::shared_ptr<Program_ASTNode> src);

  bool ClassExists(const std::string &name) {
    if (name == "int" || name == "bool") return true;
    return global_scope->classes.find(name) != global_scope->classes.end();
  }

 public:
  ASTSemanticCheckVisitor() : is_in_func_def(false), loop_level(0) {}
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