#include "astnode_visitor.h"
#include "tools.h"

// Structural AST Nodes
void ASTSemanticCheckVisitor::ActuralVisit(FuncDef_ASTNode *node) { node->func_body->accept(this); }

void ASTSemanticCheckVisitor::ActuralVisit(ClassDef_ASTNode *node) {
  for (auto ch : node->sorted_children) {
    ch->accept(this);
  }
}

void ASTSemanticCheckVisitor::ActuralVisit(Program_ASTNode *node) {
  for (auto ch : node->sorted_children) {
    ch->accept(this);
  }
}

// Statement AST Nodes
void ASTSemanticCheckVisitor::ActuralVisit(EmptyStatement_ASTNode *node) {}

void ASTSemanticCheckVisitor::ActuralVisit(DefinitionStatement_ASTNode *node) {
  auto cur_scope = node->current_scope;
  for (const auto &var : node->vars) {
    if (!cur_scope->add_variable(var.first, node->var_type)) {
      throw SemanticError("Variable redefinition for " + var.first, 1);
    }
  }
}

void ASTSemanticCheckVisitor::ActuralVisit(ExprStatement_ASTNode *node) { node->expr->accept(this); }

void ASTSemanticCheckVisitor::ActuralVisit(IfStatement_ASTNode *node) {
  node->condition->accept(this);
  node->if_clause->accept(this);
  if (node->has_else_clause) {
    node->else_clause->accept(this);
  }
}

void ASTSemanticCheckVisitor::ActuralVisit(WhileStatement_ASTNode *node) {
  node->condition->accept(this);
  node->loop_body->accept(this);
}

void ASTSemanticCheckVisitor::ActuralVisit(ForStatement_ASTNode *node) {
  if (node->initial) {
    node->initial->accept(this);
  }
  if (node->condition) {
    node->condition->accept(this);
  }
  if (node->update) {
    node->update->accept(this);
  }
  node->loop_body->accept(this);
}

void ASTSemanticCheckVisitor::ActuralVisit(JmpStatement_ASTNode *node) {}

void ASTSemanticCheckVisitor::ActuralVisit(SuiteStatement_ASTNode *node) {
  for (auto ch : node->statements) {
    ch->accept(this);
  }
}

// Expression AST Nodes
void ASTSemanticCheckVisitor::ActuralVisit(NewArrayExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(NewConstructExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(NewExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(AccessExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(IndexExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(SuffixExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(PrefixExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(OppositeExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(LNotExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(BNotExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(MDMExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(PMExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(RLExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(GGLLExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(NEExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(BAndExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(BXorExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(BOrExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(LAndExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(LOrExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(TernaryExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(AssignExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(ThisExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(ParenExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(IDExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(FunctionCallExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(FormattedStringExpr_ASTNode *node) {
  // TODO: Implement this method
}

void ASTSemanticCheckVisitor::ActuralVisit(ConstantExpr_ASTNode *node) {
  // TODO: Implement this method
}
