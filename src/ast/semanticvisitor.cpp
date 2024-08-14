#include <cstddef>
#include <functional>
#include "astnode_visitor.h"
#include "scope.hpp"
#include "tools.h"

// Structural AST Nodes
void ASTSemanticCheckVisitor::ActuralVisit(FuncDef_ASTNode *node) {
  is_in_func_def = true;
  cur_func_schema = std::dynamic_pointer_cast<FunctionScope>(node->current_scope)->schema;
  std::cerr << "enter function " << node->func_name << std::endl;
  has_return = false;
  node->func_body->accept(this);
  if (!has_return && std::holds_alternative<IdentifierType>(cur_func_schema.return_type) &&
      std::get<IdentifierType>(cur_func_schema.return_type) != "void" && node->func_name != "main") {
    throw SemanticError("Non-void function must have a return value", 1);
  }
  std::cerr << "leave function " << node->func_name << std::endl;
  is_in_func_def = false;
}

void ASTSemanticCheckVisitor::ActuralVisit(ClassDef_ASTNode *node) {
  // for (auto var : node->member_variables) {
  //   var->accept(this);
  // }
  cur_class_name = node->class_name;
  is_in_class_def = true;
  if (node->constructor) {
    if (node->constructor->func_name != node->class_name) {
      throw SemanticError("Constructor name mismatch", 1);
    }
  }
  for (auto func : node->member_functions) {
    if (func->func_name == node->class_name) {
      throw SemanticError("Constructor Type Error", 1);
    }
  }
  for (auto ch : node->sorted_children) {
    if (std::dynamic_pointer_cast<DefinitionStatement_ASTNode>(ch) == nullptr) {
      ch->accept(this);
    }
  }
  is_in_class_def = false;
}

void ASTSemanticCheckVisitor::ActuralVisit(Program_ASTNode *node) {
  for (auto ch : node->sorted_children) {
    ch->accept(this);
  }
}

// Statement AST Nodes
void ASTSemanticCheckVisitor::ActuralVisit(EmptyStatement_ASTNode *node) {}

void ASTSemanticCheckVisitor::ActuralVisit(DefinitionStatement_ASTNode *node) {
  std::cerr << "visit definition statement" << std::endl;
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
    if (var.second) {
      var.second->accept(this);
    }
    if (!cur_scope->add_variable(var.first, node->var_type)) {
      throw SemanticError("Variable redefinition for " + var.first, 1);
    }
    if (var.second) {
      if (node->var_type != var.second->expr_type_info) {
        throw SemanticError("Variable type mismatch", 1);
      }
    }
  }
}

void ASTSemanticCheckVisitor::ActuralVisit(ExprStatement_ASTNode *node) { node->expr->accept(this); }

void ASTSemanticCheckVisitor::ActuralVisit(IfStatement_ASTNode *node) {
  node->condition->accept(this);
  const static ExprTypeInfo standard = "bool";
  if (node->condition->expr_type_info != standard) {
    throw SemanticError("If condition must be bool", 1);
  }
  node->if_clause->accept(this);
  if (node->has_else_clause) {
    node->else_clause->accept(this);
  }
}

void ASTSemanticCheckVisitor::ActuralVisit(WhileStatement_ASTNode *node) {
  node->condition->accept(this);
  const static ExprTypeInfo standard = "bool";
  if (node->condition->expr_type_info != standard) {
    throw SemanticError("While condition must be bool", 1);
  }
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
    const static ExprTypeInfo standard = "bool";
    if (node->condition->expr_type_info != standard) {
      throw SemanticError("For condition must be bool", 1);
    }
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
    if (node->return_value) {
      has_return = true;
      node->return_value->accept(this);
      if (cur_func_schema.return_type != node->return_value->expr_type_info) {
        throw SemanticError("Return type mismatch", 1);
      }
    } else {
      if (cur_func_schema.return_type != "void") {
        throw SemanticError("Return type mismatch", 1);
      }
    }
  }
}

void ASTSemanticCheckVisitor::ActuralVisit(SuiteStatement_ASTNode *node) {
  for (auto ch : node->statements) {
    ch->accept(this);
  }
}

// Expression AST Nodes
void ASTSemanticCheckVisitor::ActuralVisit(NewArrayExpr_ASTNode *node) {
  if (std::get<ArrayType>(node->expr_type_info).basetype == "void") {
    throw SemanticError("Array base type cannot be void", 1);
  }
  for (size_t i = 0; i < node->dim_size.size(); i++) {
    if (node->dim_size[i]) {
      node->dim_size[i]->accept(this);
      const static ExprTypeInfo standard = "int";
      if (node->dim_size[i]->expr_type_info != standard) {
        throw SemanticError("Array dimension must be int", 1);
      }
    }
  }
  if (node->has_initial_value) {
    node->initial_value->accept(this);
    if (node->expr_type_info != node->initial_value->expr_type_info) {
      throw SemanticError("Array type mismatch", 1);
    }
  }
}

void ASTSemanticCheckVisitor::ActuralVisit(NewConstructExpr_ASTNode *node) {
  if (std::get<IdentifierType>(node->expr_type_info) == "void") {
    throw SemanticError("Cannot construct void", 1);
  }
}

void ASTSemanticCheckVisitor::ActuralVisit(NewExpr_ASTNode *node) {
  if (std::get<IdentifierType>(node->expr_type_info) == "void") {
    throw SemanticError("Cannot construct void", 1);
  }
}

void ASTSemanticCheckVisitor::ActuralVisit(AccessExpr_ASTNode *node) {
  // TODO: Implement this method
  node->base->accept(this);
  if (std::holds_alternative<ArrayType>(node->base->expr_type_info)) {
    if (node->is_function && node->member == "size" && node->arguments.size() == 0) {
      node->expr_type_info = "int";
      return;
    }
    throw SemanticError("Access on non-class", 1);
  }
  std::string base_type;
  try {
    base_type = std::get<IdentifierType>(node->base->expr_type_info);
  } catch (...) {
    throw SemanticError("Access on non-class", 1);
  }
  if (node->is_function) {
    auto schema = global_scope->FetchClassMemberFunction(base_type, node->member);
    if (schema.arguments.size() != node->arguments.size()) {
      throw SemanticError("Argument number mismatch", 1);
    }
    for (auto &arg : node->arguments) {
      arg->accept(this);
      if (arg->expr_type_info != schema.arguments[&arg - &node->arguments[0]].first) {
        throw SemanticError("Argument type mismatch", 1);
      }
    }
    node->expr_type_info = schema.return_type;
    // node->assignable = true;
    // if (std::holds_alternative<IdentifierType>(node->expr_type_info)) {
    //   std::string type = std::get<IdentifierType>(node->expr_type_info);
    //   if (type == "int" || type == "bool" || type == "void") node->assignable = false;
    // }
  } else {
    node->expr_type_info = global_scope->FetchClassMemberVariable(base_type, node->member);
    node->assignable = true;
  }
}

void ASTSemanticCheckVisitor::ActuralVisit(IndexExpr_ASTNode *node) {
  // TODO: Implement this method
  node->base->accept(this);
  if (std::holds_alternative<IdentifierType>(node->base->expr_type_info)) {
    throw SemanticError("Indexing on non-array", 1);
  }
  const auto &tp = std::get<ArrayType>(node->base->expr_type_info);
  if (tp.level < node->indices.size()) {
    throw SemanticError("Indexing on non-array", 1);
  }
  for (auto idx : node->indices) {
    idx->accept(this);
    const static ExprTypeInfo standard = "int";
    if (idx->expr_type_info != standard) {
      throw SemanticError("Index must be int", 1);
    }
  }
  if (tp.level == node->indices.size()) {
    node->expr_type_info = tp.basetype;
  } else {
    node->expr_type_info = ArrayType{true, tp.basetype, tp.level - node->indices.size()};
  }
  node->assignable = true;
}

void ASTSemanticCheckVisitor::ActuralVisit(SuffixExpr_ASTNode *node) {
  // TODO: Implement this method
  node->base->accept(this);
  if (!node->base->assignable) {
    throw SemanticError("Suffix operation on non-assignable", 1);
  }
  const static ExprTypeInfo standard = "int";
  if (node->base->expr_type_info != standard) {
    throw SemanticError("Suffix operation on non-int", 1);
  }
  node->expr_type_info = standard;
}

void ASTSemanticCheckVisitor::ActuralVisit(PrefixExpr_ASTNode *node) {
  // TODO: Implement this method
  node->base->accept(this);
  if (!node->base->assignable) {
    throw SemanticError("Prefix operation on non-assignable", 1);
  }
  const static ExprTypeInfo standard = "int";
  if (node->base->expr_type_info != standard) {
    throw SemanticError("Prefix operation on non-int", 1);
  }
  node->expr_type_info = standard;
  node->assignable = true;
}

void ASTSemanticCheckVisitor::ActuralVisit(OppositeExpr_ASTNode *node) {
  // TODO: Implement this method
  node->base->accept(this);
  const static ExprTypeInfo standard = "int";
  if (node->base->expr_type_info != standard) {
    throw SemanticError("Opposite operation on non-int", 1);
  }
  node->expr_type_info = standard;
}

void ASTSemanticCheckVisitor::ActuralVisit(LNotExpr_ASTNode *node) {
  // TODO: Implement this method
  node->base->accept(this);
  const static ExprTypeInfo standard = "bool";
  if (node->base->expr_type_info != standard) {
    throw SemanticError("Logical not operation on non-bool", 1);
  }
  node->expr_type_info = standard;
}

void ASTSemanticCheckVisitor::ActuralVisit(BNotExpr_ASTNode *node) {
  // TODO: Implement this method
  node->base->accept(this);
  const static ExprTypeInfo standard = "int";
  if (node->base->expr_type_info != standard) {
    throw SemanticError("Bitwise not operation on non-int", 1);
  }
  node->expr_type_info = standard;
}

void ASTSemanticCheckVisitor::ActuralVisit(MDMExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  const static ExprTypeInfo standard = "int";
  if (node->left->expr_type_info != standard || node->right->expr_type_info != standard) {
    throw SemanticError("MDM operation on non-int", 1);
  }
  node->expr_type_info = standard;
}

void ASTSemanticCheckVisitor::ActuralVisit(PMExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  const static ExprTypeInfo STRING = "string";
  if (node->left->expr_type_info == STRING && node->right->expr_type_info == STRING) {
    node->expr_type_info = STRING;
    return;
  }
  const static ExprTypeInfo standard = "int";
  if (node->left->expr_type_info != standard || node->right->expr_type_info != standard) {
    throw SemanticError("PM operation on non-int", 1);
  }
  node->expr_type_info = standard;
}

void ASTSemanticCheckVisitor::ActuralVisit(RLExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  const static ExprTypeInfo standard = "int";
  if (node->left->expr_type_info != standard || node->right->expr_type_info != standard) {
    throw SemanticError("RL operation on non-int", 1);
  }
  node->expr_type_info = standard;
}

void ASTSemanticCheckVisitor::ActuralVisit(GGLLExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  const static ExprTypeInfo STRING = "string";
  if (node->left->expr_type_info == STRING && node->right->expr_type_info == STRING) {
    node->expr_type_info = "bool";
    return;
  }
  const static ExprTypeInfo standard = "int";
  if (node->left->expr_type_info != standard || node->right->expr_type_info != standard) {
    throw SemanticError("GGLL operation on non-int", 1);
  }
  node->expr_type_info = "bool";
}

void ASTSemanticCheckVisitor::ActuralVisit(NEExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  // TODO: type check
  node->expr_type_info = "bool";
}

void ASTSemanticCheckVisitor::ActuralVisit(BAndExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  const static ExprTypeInfo standard = "int";
  if (node->left->expr_type_info != standard || node->right->expr_type_info != standard) {
    throw SemanticError("BAnd operation on non-int", 1);
  }
  node->expr_type_info = standard;
}

void ASTSemanticCheckVisitor::ActuralVisit(BXorExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  const static ExprTypeInfo standard = "int";
  if (node->left->expr_type_info != standard || node->right->expr_type_info != standard) {
    throw SemanticError("BXor operation on non-int", 1);
  }
  node->expr_type_info = standard;
}

void ASTSemanticCheckVisitor::ActuralVisit(BOrExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  const static ExprTypeInfo standard = "int";
  if (node->left->expr_type_info != standard || node->right->expr_type_info != standard) {
    throw SemanticError("BOr operation on non-int", 1);
  }
  node->expr_type_info = standard;
}

void ASTSemanticCheckVisitor::ActuralVisit(LAndExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  const static ExprTypeInfo standard = "bool";
  if (node->left->expr_type_info != standard || node->right->expr_type_info != standard) {
    throw SemanticError("LAnd operation on non-bool", 1);
  }
  node->expr_type_info = standard;
}

void ASTSemanticCheckVisitor::ActuralVisit(LOrExpr_ASTNode *node) {
  // TODO: Implement this method
  node->left->accept(this);
  node->right->accept(this);
  const static ExprTypeInfo standard = "bool";
  if (node->left->expr_type_info != standard || node->right->expr_type_info != standard) {
    throw SemanticError("LOr operation on non-bool", 1);
  }
  node->expr_type_info = standard;
}

void ASTSemanticCheckVisitor::ActuralVisit(TernaryExpr_ASTNode *node) {
  // TODO: Implement this method
  node->condition->accept(this);
  const static ExprTypeInfo standard = "bool";
  node->src1->accept(this);
  node->src2->accept(this);
  if (node->src1->expr_type_info != node->src2->expr_type_info &&
      node->src2->expr_type_info != node->src1->expr_type_info) {
    throw SemanticError("Ternary operation on different type", 1);
  }
  node->expr_type_info = node->src1->expr_type_info;
}

void ASTSemanticCheckVisitor::ActuralVisit(AssignExpr_ASTNode *node) {
  // TODO: Implement this method
  node->dest->accept(this);
  if (!node->dest->assignable) {
    throw SemanticError("Assign operation on non-assignable", 1);
  }
  node->src->accept(this);
  if (node->dest->expr_type_info != node->src->expr_type_info) {
    throw SemanticError("Assign operation on different type", 1);
  }
}

void ASTSemanticCheckVisitor::ActuralVisit(ThisExpr_ASTNode *node) {
  // TODO
  node->expr_type_info = cur_class_name;
}

void ASTSemanticCheckVisitor::ActuralVisit(ParenExpr_ASTNode *node) {
  node->expr->accept(this);
  node->expr_type_info = node->expr->expr_type_info;
  node->assignable = node->expr->assignable;
}

void ASTSemanticCheckVisitor::ActuralVisit(IDExpr_ASTNode *node) {
  // TODO: Implement this method
  // TODO: process type
  node->expr_type_info = node->current_scope->fetch_varaible(node->id);
  node->assignable = true;
}

void ASTSemanticCheckVisitor::ActuralVisit(FunctionCallExpr_ASTNode *node) {
  // TODO: Implement this method
  // TODO: check function existence and arg number
  FunctionSchema schema;
  bool schema_ready = false;
  if (is_in_class_def) {
    try {
      schema = global_scope->FetchClassMemberFunction(cur_class_name, node->func_name);
      schema_ready = true;
    } catch (...) {
    }
  }
  if (!schema_ready) {
    schema = global_scope->FetchFunction(node->func_name);
  }
  std::cerr << "function to call is " << node->func_name << std::endl;
  if (schema.arguments.size() != node->arguments.size()) {
    throw SemanticError("Argument number mismatch", 1);
  }
  for (auto &arg : node->arguments) {
    arg->accept(this);
    int idx = &arg - &node->arguments[0];  // for debug;
    if (schema.arguments[&arg - &node->arguments[0]].first != arg->expr_type_info) {
      throw SemanticError("Argument type mismatch", 1);
    }
  }
  node->expr_type_info = schema.return_type;
  // node->assignable = true;
  // if (std::holds_alternative<IdentifierType>(node->expr_type_info)) {
  //   std::string type = std::get<IdentifierType>(node->expr_type_info);
  //   if (type == "int" || type == "bool" || type == "void") node->assignable = false;
  // }
}

void ASTSemanticCheckVisitor::ActuralVisit(FormattedStringExpr_ASTNode *node) {
  // TODO: Implement this method
  for (auto arg : node->exprs) {
    arg->accept(this);
    const static ExprTypeInfo valid_types[] = {"int", "bool", "string"};
    if (arg->expr_type_info != valid_types[0] && arg->expr_type_info != valid_types[1] &&
        arg->expr_type_info != valid_types[2]) {
      throw SemanticError("Invalid type in formatted string", 1);
    }
  }
  node->expr_type_info = "string";
}

void ASTSemanticCheckVisitor::ActuralVisit(ConstantExpr_ASTNode *node) {
  // TODO: Implement this method
  // type process
  if (std::holds_alternative<IdentifierType>(node->expr_type_info)) {
    return;
  } else {
    std::string base_type;
    bool found_base_type = false;
    size_t found_level = 0;
    std::function<void(ConstantExpr_ASTNode *, int)> search = [&](ConstantExpr_ASTNode *node, int depth) {
      if (std::holds_alternative<IdentifierType>(node->expr_type_info)) {
        if (!found_base_type) {
          found_base_type = true;
          base_type = std::get<IdentifierType>(node->expr_type_info);
          found_level = depth;
        } else {
          if (base_type != std::get<IdentifierType>(node->expr_type_info) || found_level != depth) {
            throw SemanticError("Invalid const array type", 1);
          }
        }
      } else {
        const auto &sub_nodes = std::get<std::vector<std::shared_ptr<ConstantExpr_ASTNode>>>(node->value);
        for (auto sub_node : sub_nodes) {
          search(sub_node.get(), depth + 1);
        }
      }
    };
    search(node, 0);
    node->expr_type_info = ArrayType{found_base_type, base_type, found_level};
  }
}
