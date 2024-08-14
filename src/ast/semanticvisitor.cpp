#include <functional>
#include "astnode_visitor.h"
#include "scope.hpp"
#include "tools.h"

// Structural AST Nodes
void ASTSemanticCheckVisitor::ActuralVisit(FuncDef_ASTNode *node) {
  is_in_func = true;
  cur_func_schema = std::dynamic_pointer_cast<FunctionScope>(node->current_scope)->schema;
  std::cerr << "enter function " << node->func_name << std::endl;
  node->func_body->accept(this);
  std::cerr << "leave function " << node->func_name << std::endl;
  is_in_func = false;
}

void ASTSemanticCheckVisitor::ActuralVisit(ClassDef_ASTNode *node) {
  for (auto var : node->member_variables) {
    var->accept(this);
  }
  for (auto ch : node->sorted_children) {
    if (std::dynamic_pointer_cast<DefinitionStatement_ASTNode>(ch) == nullptr) {
      ch->accept(this);
    }
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
    std::string base_type;
    if (std::holds_alternative<IdentifierType>(node->var_type)) {
      base_type = std::get<IdentifierType>(node->var_type);
    } else {
      base_type = std::get<ArrayType>(node->var_type).basetype;
    }
    if (!ClassExists(base_type)) {
      throw SemanticError("Undefined class " + base_type, 1);
    }
    if (!cur_scope->add_variable(var.first, node->var_type)) {
      throw SemanticError("Variable redefinition for " + var.first, 1);
    }
    if (var.second) {
      var.second->accept(this);
      // TODO type check
    }
  }
}

void ASTSemanticCheckVisitor::ActuralVisit(ExprStatement_ASTNode *node) { node->expr->accept(this); }

void ASTSemanticCheckVisitor::ActuralVisit(IfStatement_ASTNode *node) {
  node->condition->accept(this);
  // TODO type check
  node->if_clause->accept(this);
  if (node->has_else_clause) {
    node->else_clause->accept(this);
  }
}

void ASTSemanticCheckVisitor::ActuralVisit(WhileStatement_ASTNode *node) {
  node->condition->accept(this);
  // TODO type check
  loop_level++;
  node->loop_body->accept(this);
  loop_level--;
}

void ASTSemanticCheckVisitor::ActuralVisit(ForStatement_ASTNode *node) {
  if (node->initial) {
    node->initial->accept(this);
  }
  if (node->condition) {
    node->condition->accept(this);
    // TODO type check
  }
  if (node->update) {
    node->update->accept(this);
  }
  loop_level++;
  node->loop_body->accept(this);
  loop_level--;
}

void ASTSemanticCheckVisitor::ActuralVisit(JmpStatement_ASTNode *node) {
  if (loop_level == 0 && node->jmp_type > 0) throw SemanticError("Jump statement outside loop", 1);
  if (node->jmp_type == 0) {
    // TODO : return type check
  }
}

void ASTSemanticCheckVisitor::ActuralVisit(SuiteStatement_ASTNode *node) {
  for (auto ch : node->statements) {
    ch->accept(this);
  }
}

// Expression AST Nodes
void ASTSemanticCheckVisitor::ActuralVisit(NewArrayExpr_ASTNode *node) {
  // TODO: Implement this method
  for (size_t i = 0; i < node->dim_size.size(); i++) {
    if (node->dim_size[i]) {
      node->dim_size[i]->accept(this);
      // TODO type check
    }
  }
  if (node->has_initial_value) {
    node->initial_value->accept(this);
    // TODO type check
  }
}

void ASTSemanticCheckVisitor::ActuralVisit(NewConstructExpr_ASTNode *node) {}

void ASTSemanticCheckVisitor::ActuralVisit(NewExpr_ASTNode *node) {}

void ASTSemanticCheckVisitor::ActuralVisit(AccessExpr_ASTNode *node) {
  // TODO: Implement this method
  node->base->accept(this);
  // TODO: member check
  if (node->is_function) {
    // TODO arg number check
    for (auto arg : node->arguments) {
      arg->accept(this);
      // TODO type check
    }
  }
}

void ASTSemanticCheckVisitor::ActuralVisit(IndexExpr_ASTNode *node) {
  // TODO: Implement this method
  node->base->accept(this);
  // TODO: dimension check
  for (auto idx : node->indices) {
    idx->accept(this);
    // TODO type check
  }
}

void ASTSemanticCheckVisitor::ActuralVisit(SuffixExpr_ASTNode *node) {
  // TODO: Implement this method
  node->base->accept(this);
  // TODO: type check
}

void ASTSemanticCheckVisitor::ActuralVisit(PrefixExpr_ASTNode *node) {
  // TODO: Implement this method
  node->base->accept(this);
  // TODO: type check
}

void ASTSemanticCheckVisitor::ActuralVisit(OppositeExpr_ASTNode *node) {
  // TODO: Implement this method
  node->base->accept(this);
  // TODO: type check
}

void ASTSemanticCheckVisitor::ActuralVisit(LNotExpr_ASTNode *node) {
  // TODO: Implement this method
  node->base->accept(this);
  // TODO: type check
}

void ASTSemanticCheckVisitor::ActuralVisit(BNotExpr_ASTNode *node) {
  // TODO: Implement this method
  node->base->accept(this);
  // TODO: type check
}

void ASTSemanticCheckVisitor::ActuralVisit(MDMExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  // TODO: type check
}

void ASTSemanticCheckVisitor::ActuralVisit(PMExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  // TODO: type check
}

void ASTSemanticCheckVisitor::ActuralVisit(RLExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  // TODO: type check
}

void ASTSemanticCheckVisitor::ActuralVisit(GGLLExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  // TODO: type check
}

void ASTSemanticCheckVisitor::ActuralVisit(NEExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  // TODO: type check
}

void ASTSemanticCheckVisitor::ActuralVisit(BAndExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  // TODO: type check
}

void ASTSemanticCheckVisitor::ActuralVisit(BXorExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  // TODO: type check
}

void ASTSemanticCheckVisitor::ActuralVisit(BOrExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  // TODO: type check
}

void ASTSemanticCheckVisitor::ActuralVisit(LAndExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  // TODO: type check
}

void ASTSemanticCheckVisitor::ActuralVisit(LOrExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  // TODO: type check
}

void ASTSemanticCheckVisitor::ActuralVisit(TernaryExpr_ASTNode *node) {
  // TODO: Implement this method
  node->condition->accept(this);
  // TODO: type check
  node->src1->accept(this);
  node->src2->accept(this);
  // TODO: type check
}

void ASTSemanticCheckVisitor::ActuralVisit(AssignExpr_ASTNode *node) {
  // TODO: Implement this method
  node->dest->accept(this);
  node->src->accept(this);
  // TODO: check type and assignability
}

void ASTSemanticCheckVisitor::ActuralVisit(ThisExpr_ASTNode *node) {}

void ASTSemanticCheckVisitor::ActuralVisit(ParenExpr_ASTNode *node) {
  // TODO: Implement this method
  node->expr->accept(this);
  node->expr_type_info = node->expr->expr_type_info;
}

void ASTSemanticCheckVisitor::ActuralVisit(IDExpr_ASTNode *node) {
  // TODO: Implement this method
  // TODO: process type
  node->expr_type_info = node->current_scope->fetch_varaible(node->id);
}

void ASTSemanticCheckVisitor::ActuralVisit(FunctionCallExpr_ASTNode *node) {
  // TODO: Implement this method
  // TODO: check function existence and arg number
  for (auto arg : node->arguments) {
    arg->accept(this);
    // TODO: type check
  }
}

void ASTSemanticCheckVisitor::ActuralVisit(FormattedStringExpr_ASTNode *node) {
  // TODO: Implement this method
  for (auto arg : node->exprs) {
    arg->accept(this);
    // TODO: type check
  }
}

void ASTSemanticCheckVisitor::ActuralVisit(ConstantExpr_ASTNode *node) {
  // TODO: Implement this method
  // type process
  if (std::holds_alternative<IdentifierType>(node->expr_type_info)) {
    return;
  } else {
    ;
  }
}
