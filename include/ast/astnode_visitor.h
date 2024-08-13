#ifndef ASTNODE_ActuralVisitOR_H
#define ASTNODE_ActuralVisitOR_H

#include "astnode.h"
#include "expr_astnode.h"
#include "statement_astnode.h"
#include "structural_astnode.h"

class ASTNodeVirturalVisitor : public ASTNodeVisitorBase {
 public:
  // Structural AST Nodes
  virtual void ActuralVisit(FuncDef_ASTNode *node) = 0;
  virtual void ActuralVisit(ClassDef_ASTNode *node) = 0;
  virtual void ActuralVisit(Program_ASTNode *node) = 0;

  // Statement AST Nodes
  virtual void ActuralVisit(EmptyStatement_ASTNode *node) = 0;
  virtual void ActuralVisit(DefinitionStatement_ASTNode *node) = 0;
  virtual void ActuralVisit(ExprStatement_ASTNode *node) = 0;
  virtual void ActuralVisit(IfStatement_ASTNode *node) = 0;
  virtual void ActuralVisit(WhileStatement_ASTNode *node) = 0;
  virtual void ActuralVisit(ForStatement_ASTNode *node) = 0;
  virtual void ActuralVisit(JmpStatement_ASTNode *node) = 0;
  virtual void ActuralVisit(SuiteStatement_ASTNode *node) = 0;

  // Expression AST Nodes
  virtual void ActuralVisit(NewArrayExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(NewConstructExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(NewExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(AccessExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(IndexExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(SuffixExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(PrefixExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(OppositeExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(LNotExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(BNotExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(MDMExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(PMExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(RLExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(GGLLExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(NEExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(BAndExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(BXorExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(BOrExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(LAndExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(LOrExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(TernaryExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(AssignExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(ThisExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(ParenExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(IDExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(FunctionCallExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(FormattedStringExpr_ASTNode *node) = 0;
  virtual void ActuralVisit(ConstantExpr_ASTNode *node) = 0;
};

class ASTSemanticCheckVisitor : public ASTNodeVirturalVisitor {
 public:
  ASTSemanticCheckVisitor() = default;
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

#endif  // ASTNODE_ActuralVisitOR_H