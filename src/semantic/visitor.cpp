#include "visitor.h"
#include <stdexcept>
#include <type_traits>
#include "MXParser.h"
#include "MXParserVisitor.h"
#include "ast/ast.h"

std::any Visitor::visitMxprog(MXParser::MxprogContext *context) {
  auto program = std::make_shared<Program_ASTNode>();
  program->type = ASTNodeType::Program;
  program->start_line = context->getStart()->getLine();
  program->start_char_pos = context->getStart()->getCharPositionInLine();
  program->end_line = context->getStop()->getLine();
  program->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::Program);

  for (auto def : context->children) {
    if (auto classDefContext = dynamic_cast<MXParser::Class_defContext *>(def)) {
      auto classNode = std::any_cast<std::shared_ptr<ClassDef_ASTNode>>(visit(classDefContext));
      program->classes.push_back(classNode);
    } else if (auto defineStmtContext = dynamic_cast<MXParser::Define_statementContext *>(def)) {
      auto defineNode = std::any_cast<std::shared_ptr<DefinitionStatement_ASTNode>>(visit(defineStmtContext));
      program->global_variables.push_back(defineNode);
    } else if (auto funcDefContext = dynamic_cast<MXParser::Function_defContext *>(def)) {
      auto funcNode = std::any_cast<std::shared_ptr<FuncDef_ASTNode>>(visit(funcDefContext));
      program->functions.push_back(funcNode);
    } else if (auto EOFToken = dynamic_cast<antlr4::tree::TerminalNode *>(def)) {
      if (EOFToken == context->EOF()) break;
      throw std::runtime_error("unknown subnode occurred in visitMxprog");
    } else {
      throw std::runtime_error("unknown subnode occurred in visitMxprog");
    }
  }
  nodetype_stk.pop_back();

  return program;
}

std::any Visitor::visitFunction_def(MXParser::Function_defContext *context) {
  auto func = std::make_shared<FuncDef_ASTNode>();
  func->type = ASTNodeType::FuncDef;
  func->is_constructor = false;
  func->start_line = context->getStart()->getLine();
  func->start_char_pos = context->getStart()->getCharPositionInLine();
  func->end_line = context->getStop()->getLine();
  func->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::FuncDef);
  std::string return_type_str;

  if (auto type_context = dynamic_cast<MXParser::TypeContext *>(context->children[0])) {
    // return type
    return_type_str = type_context->getText();
    std::cerr << std::string(nodetype_stk.size() * 2, ' ') << "return_type_str=" << return_type_str << std::endl;
  } else
    throw std::runtime_error("unknown subnode occurred in visitFunction_def");
  int return_dimensions = 0;
  for (size_t i = 1; i < context->children.size(); i++) {
    if (dynamic_cast<antlr4::tree::TerminalNode *>(context->children[i]) != nullptr &&
        dynamic_cast<antlr4::tree::TerminalNode *>(context->children[i])->getSymbol()->getType() == MXParser::ID) {
      break;
    }
    return_dimensions++;
  }
  return_dimensions >>= 1;
  if (return_dimensions == 0) {
    func->return_type = return_type_str;
    std::cerr << std::string(nodetype_stk.size() * 2, ' ') << "recorded return type is [none-array]" << return_type_str
              << std::endl;
  } else {
    func->return_type = ArrayType{true, return_type_str, static_cast<size_t>(return_dimensions)};
    std::cerr << std::string(nodetype_stk.size() * 2, ' ') << "recorded return type is [array]" << return_type_str
              << " with dimensions=" << return_dimensions << std::endl;
  }
  func->func_name = context->children[1 + 2 * return_dimensions]->getText();
  std::cerr << std::string(nodetype_stk.size() * 2, ' ') << "func_name=" << func->func_name << std::endl;
  size_t cur = 3 + 2 * return_dimensions;
  bool is_first_para = true;
  while (true) {
    if (cur >= context->children.size()) throw std::runtime_error("something strange happened in visitFunction_def");
    auto ptr = dynamic_cast<antlr4::tree::TerminalNode *>(context->children[cur]);
    if (ptr != nullptr && ptr->getSymbol()->getType() == MXParser::RPAREN) break;
    if (is_first_para) goto cancel_first;
    if (ptr->getSymbol()->getType() != MXParser::COMMA)
      throw std::runtime_error("something strange happened in visitFunction_def");
    cur++;
  cancel_first:
    is_first_para = false;
    std::string cur_para_type_base_str = context->children[cur]->getText();
    int cur_para_dimensions = 0;
    while (dynamic_cast<antlr4::tree::TerminalNode *>(context->children[cur + 1]) != nullptr &&
           (dynamic_cast<antlr4::tree::TerminalNode *>(context->children[cur + 1])->getSymbol()->getType() ==
                MXParser::LBRACKET ||
            dynamic_cast<antlr4::tree::TerminalNode *>(context->children[cur + 1])->getSymbol()->getType() ==
                MXParser::RBRACKET)) {
      cur_para_dimensions++;
      cur++;
    }
    cur++;
    cur_para_dimensions >>= 1;
    std::string cur_para_name = context->children[cur]->getText();
    ExprTypeInfo cur_para_type;
    if (cur_para_dimensions == 0) {
      cur_para_type = cur_para_type_base_str;
      std::cerr << std::string(nodetype_stk.size() * 2, ' ') << "recorded parameter type is [none-array]"
                << cur_para_type_base_str << std::endl;
      std::cerr << std::string(nodetype_stk.size() * 2, ' ') << "recorded parameter name is " << cur_para_name
                << std::endl;
    } else {
      cur_para_type = ArrayType{true, cur_para_type_base_str, static_cast<size_t>(cur_para_dimensions)};
      std::cerr << std::string(nodetype_stk.size() * 2, ' ') << "recorded parameter type is [array]"
                << cur_para_type_base_str << " with dimensions=" << cur_para_dimensions << std::endl;
      std::cerr << std::string(nodetype_stk.size() * 2, ' ') << "recorded parameter name is " << cur_para_name
                << std::endl;
    }
    func->params.push_back(std::make_pair(cur_para_name, cur_para_type));
    cur++;
  }
  func->func_body = std::any_cast<std::shared_ptr<SuiteStatement_ASTNode>>(visit(context->suite()));
  nodetype_stk.pop_back();
  return func;
}
std::any Visitor::visitClass_def(MXParser::Class_defContext *context) {
  auto class_def = std::make_shared<ClassDef_ASTNode>();
  class_def->type = ASTNodeType::ClassDef;
  class_def->start_line = context->getStart()->getLine();
  class_def->start_char_pos = context->getStart()->getCharPositionInLine();
  class_def->end_line = context->getStop()->getLine();
  class_def->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::ClassDef);

  class_def->class_name = context->ID()->getText();
  std::cerr << std::string(nodetype_stk.size() * 2, ' ') << "building a class named " << class_def->class_name
            << std::endl;
  std::vector<MXParser::Class_constructorContext *> constructors = context->class_constructor();
  if (constructors.size() > 1) throw SemanticError("Multiple constructor found for class " + class_def->class_name, 2);
  if (constructors.size() > 0)
    class_def->constructor = std::any_cast<std::shared_ptr<FuncDef_ASTNode>>(visit(constructors[0]));
  std::vector<MXParser::Function_defContext *> functions = context->function_def();
  for (auto func : functions) {
    auto func_node = std::any_cast<std::shared_ptr<FuncDef_ASTNode>>(visit(func));
    class_def->member_functions.push_back(func_node);
  }

  nodetype_stk.pop_back();
  return class_def;
}
std::any Visitor::visitClass_var_def(MXParser::Class_var_defContext *context) {
  auto member_var_def = std::make_shared<DefinitionStatement_ASTNode>();
  member_var_def->type = ASTNodeType::ClassVariable;
  member_var_def->start_line = context->getStart()->getLine();
  member_var_def->start_char_pos = context->getStart()->getCharPositionInLine();
  member_var_def->end_line = context->getStop()->getLine();
  member_var_def->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::ClassVariable);

  std::string define_type_base;
  if (auto type_context = dynamic_cast<MXParser::TypeContext *>(context->children[0])) {
    define_type_base = type_context->getText();
  } else
    throw std::runtime_error("unknown subnode occurred in visitClass_var_def");
  int define_dimensions = 0;
  for (size_t i = 1; i < context->children.size(); i++) {
    if (dynamic_cast<antlr4::tree::TerminalNode *>(context->children[i]) != nullptr &&
        dynamic_cast<antlr4::tree::TerminalNode *>(context->children[i])->getSymbol()->getType() == MXParser::ID) {
      break;
    }
    define_dimensions++;
  }
  define_dimensions >>= 1;
  if (define_dimensions == 0) {
    member_var_def->var_type = define_type_base;
    std::cerr << std::string(nodetype_stk.size() * 2, ' ') << "recorded member variable type is [none-array]"
              << define_type_base << std::endl;
  } else {
    member_var_def->var_type = ArrayType{true, define_type_base, static_cast<size_t>(define_dimensions)};
    std::cerr << std::string(nodetype_stk.size() * 2, ' ') << "recorded member variable type is [array]"
              << define_type_base << " with dimensions=" << define_dimensions << std::endl;
  }
  auto identifiers = context->ID();
  for (auto id : identifiers) {
    member_var_def->vars.push_back(std::make_pair(id->getText(), nullptr));
    std::cerr << std::string(nodetype_stk.size() * 2, ' ') << "recorded member variable name is " << id->getText()
              << std::endl;
  }

  nodetype_stk.pop_back();
  return member_var_def;
}
std::any Visitor::visitClass_constructor(MXParser::Class_constructorContext *context) {
  auto construct_func = std::make_shared<FuncDef_ASTNode>();
  construct_func->type = ASTNodeType::Constructor;
  construct_func->is_constructor = false;
  construct_func->start_line = context->getStart()->getLine();
  construct_func->start_char_pos = context->getStart()->getCharPositionInLine();
  construct_func->end_line = context->getStop()->getLine();
  construct_func->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::Constructor);

  construct_func->func_body = std::any_cast<std::shared_ptr<SuiteStatement_ASTNode>>(visit(context->suite()));

  nodetype_stk.pop_back();
  return construct_func;
}
std::any Visitor::visitSuite(MXParser::SuiteContext *context) { throw std::runtime_error("Not implemented"); }
std::any Visitor::visitEmpty_statement(MXParser::Empty_statementContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitDefinition_statement(MXParser::Definition_statementContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitExpr_statement(MXParser::Expr_statementContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitIf_statement(MXParser::If_statementContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitWhile_statement(MXParser::While_statementContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitFor_statement(MXParser::For_statementContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitJmp_statement(MXParser::Jmp_statementContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitSuite_statement(MXParser::Suite_statementContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitDefine_statement(MXParser::Define_statementContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitGgll_expression(MXParser::Ggll_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitBxor_expression(MXParser::Bxor_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitSuffix_expression(MXParser::Suffix_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitLand_expression(MXParser::Land_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitPm_expression(MXParser::Pm_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitIndex_expression(MXParser::Index_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitOpposite_expression(MXParser::Opposite_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitNew_array_expression(MXParser::New_array_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitBasic_expression(MXParser::Basic_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitAccess_expression(MXParser::Access_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitBand_expression(MXParser::Band_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitNew_construct_expression(MXParser::New_construct_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitTernary_expression(MXParser::Ternary_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitBnot_expression(MXParser::Bnot_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitLnot_expression(MXParser::Lnot_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitPrefix_expression(MXParser::Prefix_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitRl_expression(MXParser::Rl_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitAssign_expression(MXParser::Assign_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitMdm_expression(MXParser::Mdm_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitNew_expression(MXParser::New_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitNe_expression(MXParser::Ne_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitBor_expression(MXParser::Bor_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitLor_expression(MXParser::Lor_expressionContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitThis_expr(MXParser::This_exprContext *context) { throw std::runtime_error("Not implemented"); }
std::any Visitor::visitParen_expr(MXParser::Paren_exprContext *context) { throw std::runtime_error("Not implemented"); }
std::any Visitor::visitId_expr(MXParser::Id_exprContext *context) { throw std::runtime_error("Not implemented"); }
std::any Visitor::visitFunction_call_expr(MXParser::Function_call_exprContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitFormatted_string_expr(MXParser::Formatted_string_exprContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitConstant_expr(MXParser::Constant_exprContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitFormatted_string(MXParser::Formatted_stringContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitConstant(MXParser::ConstantContext *context) { throw std::runtime_error("Not implemented"); }
std::any Visitor::visitType(MXParser::TypeContext *context) { throw std::runtime_error("Not implemented"); }
