#include "IRBuilder.h"
#include <stdexcept>

// Structural AST Nodes
void IRBuilder::ActuralVisit(FuncDef_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(ClassDef_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(Program_ASTNode *node) {
  // TODO: Implement function body
  throw std::runtime_error("IRBuilder not implemented");
}

// Statement AST Nodes
void IRBuilder::ActuralVisit(EmptyStatement_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(DefinitionStatement_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(ExprStatement_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(IfStatement_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(WhileStatement_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(ForStatement_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(JmpStatement_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(SuiteStatement_ASTNode *node) {
  // TODO: Implement function body
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
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(PrefixExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(OppositeExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(LNotExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(BNotExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(MDMExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(PMExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(RLExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(GGLLExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(NEExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(BAndExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(BXorExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(BOrExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(LAndExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(LOrExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(TernaryExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(AssignExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(ThisExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(ParenExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(IDExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(FunctionCallExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(FormattedStringExpr_ASTNode *node) {
  // TODO: Implement function body
}

void IRBuilder::ActuralVisit(ConstantExpr_ASTNode *node) {
  // TODO: Implement function body
}

std::shared_ptr<ModuleItem> BuildIR(std::shared_ptr<Program_ASTNode> src) {
  IRBuilder visitor;
  visitor.visit(src.get());
}