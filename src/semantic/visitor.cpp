#include "visitor.h"
#include <stdexcept>
#include <type_traits>
#include "MXParser.h"
#include "MXParserVisitor.h"
#include "ast/ast.h"
#include "tools.h"

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
      auto defineNode = std::dynamic_pointer_cast<DefinitionStatement_ASTNode>(
          std::any_cast<std::shared_ptr<Statement_ASTNode>>(visit(defineStmtContext)));
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
  func->func_body = std::dynamic_pointer_cast<SuiteStatement_ASTNode>(
      std::any_cast<std::shared_ptr<Statement_ASTNode>>(visit(context->suite())));
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
  std::vector<MXParser::Class_var_defContext *> vars = context->class_var_def();
  for (auto var : vars) {
    auto var_node = std::dynamic_pointer_cast<DefinitionStatement_ASTNode>(
        std::any_cast<std::shared_ptr<Statement_ASTNode>>(visit(var)));
    class_def->member_variables.push_back(var_node);
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
  return std::static_pointer_cast<Statement_ASTNode>(member_var_def);
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

  construct_func->func_body = std::dynamic_pointer_cast<SuiteStatement_ASTNode>(
      std::any_cast<std::shared_ptr<Statement_ASTNode>>(visit(context->suite())));

  nodetype_stk.pop_back();
  return construct_func;
}
std::any Visitor::visitSuite(MXParser::SuiteContext *context) {
  auto suite_node = std::make_shared<SuiteStatement_ASTNode>();
  suite_node->type = ASTNodeType::SuiteStatement;
  suite_node->start_line = context->getStart()->getLine();
  suite_node->start_char_pos = context->getStart()->getCharPositionInLine();
  suite_node->end_line = context->getStop()->getLine();
  suite_node->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::SuiteStatement);

  std::vector<MXParser::StatementContext *> stmts = context->statement();
  for (auto stmt : stmts) {
    auto stmt_node = std::any_cast<std::shared_ptr<Statement_ASTNode>>(visit(stmt));
    suite_node->statements.push_back(stmt_node);
  }

  nodetype_stk.pop_back();
  return std::static_pointer_cast<Statement_ASTNode>(suite_node);
}
std::any Visitor::visitEmpty_statement(MXParser::Empty_statementContext *context) {
  auto stmt = std::make_shared<EmptyStatement_ASTNode>();
  stmt->type = ASTNodeType::EmptyStatement;
  stmt->start_line = context->getStart()->getLine();
  stmt->start_char_pos = context->getStart()->getCharPositionInLine();
  stmt->end_line = context->getStop()->getLine();
  stmt->end_char_pos = context->getStop()->getCharPositionInLine();
  return std::static_pointer_cast<Statement_ASTNode>(stmt);
}
std::any Visitor::visitDefinition_statement(MXParser::Definition_statementContext *context) {
  return visit(context->define_statement());
}
std::any Visitor::visitExpr_statement(MXParser::Expr_statementContext *context) {
  auto expr_stmt = std::make_shared<ExprStatement_ASTNode>();
  expr_stmt->type = ASTNodeType::ExprStatement;
  expr_stmt->start_line = context->getStart()->getLine();
  expr_stmt->start_char_pos = context->getStart()->getCharPositionInLine();
  expr_stmt->end_line = context->getStop()->getLine();
  expr_stmt->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::ExprStatement);
  expr_stmt->expr = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->expr()));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Statement_ASTNode>(expr_stmt);
}
std::any Visitor::visitIf_statement(MXParser::If_statementContext *context) {
  auto if_stmt = std::make_shared<IfStatement_ASTNode>();
  if_stmt->type = ASTNodeType::IfStatement;
  if_stmt->start_line = context->getStart()->getLine();
  if_stmt->start_char_pos = context->getStart()->getCharPositionInLine();
  if_stmt->end_line = context->getStop()->getLine();
  if_stmt->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::IfStatement);
  if_stmt->condition = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->expr()));
  std::vector<MXParser::StatementContext *> sub_stmts = context->statement();
  if_stmt->if_clause = std::any_cast<std::shared_ptr<Statement_ASTNode>>(visit(sub_stmts[0]));
  if (sub_stmts.size() > 1) {
    if_stmt->has_else_clause = true;
    if_stmt->else_clause = std::any_cast<std::shared_ptr<Statement_ASTNode>>(visit(sub_stmts[1]));
  } else {
    if_stmt->has_else_clause = false;
    if_stmt->else_clause = nullptr;
  }
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Statement_ASTNode>(if_stmt);
}
std::any Visitor::visitWhile_statement(MXParser::While_statementContext *context) {
  auto while_stmt = std::make_shared<WhileStatement_ASTNode>();
  while_stmt->type = ASTNodeType::WhileStatement;
  while_stmt->start_line = context->getStart()->getLine();
  while_stmt->start_char_pos = context->getStart()->getCharPositionInLine();
  while_stmt->end_line = context->getStop()->getLine();
  while_stmt->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::WhileStatement);
  while_stmt->condition = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->expr()));
  while_stmt->loop_body = std::any_cast<std::shared_ptr<Statement_ASTNode>>(visit(context->statement()));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Statement_ASTNode>(while_stmt);
}
std::any Visitor::visitFor_statement(MXParser::For_statementContext *context) {
  auto for_stmt = std::make_shared<ForStatement_ASTNode>();
  for_stmt->type = ASTNodeType::ForStatement;
  for_stmt->start_line = context->getStart()->getLine();
  for_stmt->start_char_pos = context->getStart()->getCharPositionInLine();
  for_stmt->end_line = context->getStop()->getLine();
  for_stmt->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::ForStatement);
  size_t cur = 2;
  if (dynamic_cast<antlr4::tree::TerminalNode *>(context->children[cur]) != nullptr &&
      dynamic_cast<antlr4::tree::TerminalNode *>(context->children[cur])->getSymbol()->getType() ==
          MXParser::SEMICOLON) {
    for_stmt->initial = nullptr;
    cur += 1;
  } else if (dynamic_cast<MXParser::Define_statementContext *>(context->children[cur]) != nullptr) {
    for_stmt->initial = std::dynamic_pointer_cast<Statement_ASTNode>(
        std::any_cast<std::shared_ptr<Statement_ASTNode>>(visit(context->children[cur])));
    cur += 1;
  } else if (dynamic_cast<MXParser::ExprContext *>(context->children[cur]) != nullptr) {
    auto expr = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[cur]));
    auto expr_stmt = std::make_shared<ExprStatement_ASTNode>();
    expr_stmt->type = ASTNodeType::ExprStatement;
    expr_stmt->start_line = expr->start_line;
    expr_stmt->start_char_pos = expr->start_char_pos;
    expr_stmt->end_line = expr->end_line;
    expr_stmt->end_char_pos = expr->end_char_pos;
    expr_stmt->expr = expr;
    for_stmt->initial = std::static_pointer_cast<Statement_ASTNode>(expr_stmt);
    cur += 2;
  } else {
    throw std::runtime_error("unknown subnode occurred in visitFor_statement");
  }
  if (dynamic_cast<antlr4::tree::TerminalNode *>(context->children[cur]) != nullptr &&
      dynamic_cast<antlr4::tree::TerminalNode *>(context->children[cur])->getSymbol()->getType() ==
          MXParser::SEMICOLON) {
    for_stmt->condition = nullptr;
    cur += 1;
  } else {
    for_stmt->condition = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[cur]));
    cur += 2;
  }
  if (dynamic_cast<MXParser::Define_statementContext *>(context->children[cur]) != nullptr) {
    for_stmt->update = std::dynamic_pointer_cast<Statement_ASTNode>(
        std::any_cast<std::shared_ptr<Statement_ASTNode>>(visit(context->children[cur])));
    cur += 1;
  } else if (dynamic_cast<MXParser::ExprContext *>(context->children[cur]) != nullptr) {
    auto expr = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[cur]));
    auto expr_stmt = std::make_shared<ExprStatement_ASTNode>();
    expr_stmt->type = ASTNodeType::ExprStatement;
    expr_stmt->start_line = expr->start_line;
    expr_stmt->start_char_pos = expr->start_char_pos;
    expr_stmt->end_line = expr->end_line;
    expr_stmt->end_char_pos = expr->end_char_pos;
    expr_stmt->expr = expr;
    for_stmt->update = std::static_pointer_cast<Statement_ASTNode>(expr_stmt);
    cur += 2;
  } else {
    throw std::runtime_error("unknown subnode occurred in visitFor_statement");
  }
  for_stmt->loop_body = std::any_cast<std::shared_ptr<Statement_ASTNode>>(visit(context->children[cur]));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Statement_ASTNode>(for_stmt);
}
std::any Visitor::visitJmp_statement(MXParser::Jmp_statementContext *context) {
  auto jmp_stmt = std::make_shared<JmpStatement_ASTNode>();
  jmp_stmt->type = ASTNodeType::JmpStatement;
  jmp_stmt->start_line = context->getStart()->getLine();
  jmp_stmt->start_char_pos = context->getStart()->getCharPositionInLine();
  jmp_stmt->end_line = context->getStop()->getLine();
  jmp_stmt->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::JmpStatement);
  if (context->RETURN() != nullptr) {
    jmp_stmt->jmp_type = 0;
    if (context->expr() != nullptr) {
      jmp_stmt->return_value = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->expr()));
    } else {
      jmp_stmt->return_value = nullptr;
    }
  } else if (context->BREAK() != nullptr) {
    jmp_stmt->jmp_type = 1;
    jmp_stmt->return_value = nullptr;
  } else if (context->CONTINUE() != nullptr) {
    jmp_stmt->jmp_type = 2;
    jmp_stmt->return_value = nullptr;
  } else {
    throw std::runtime_error("unknown jmp statement type");
  }
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Statement_ASTNode>(jmp_stmt);
}
std::any Visitor::visitSuite_statement(MXParser::Suite_statementContext *context) { return visit(context->suite()); }
std::any Visitor::visitDefine_statement(MXParser::Define_statementContext *context) {
  // define_statement : type (LBRACKET RBRACKET)* ID (ASSIGN expr)? (COMMA ID (ASSIGN expr)?)* SEMICOLON;
  auto def_stmt = std::make_shared<DefinitionStatement_ASTNode>();
  def_stmt->type = ASTNodeType::DefinitionStatement;
  def_stmt->start_line = context->getStart()->getLine();
  def_stmt->start_char_pos = context->getStart()->getCharPositionInLine();
  def_stmt->end_line = context->getStop()->getLine();
  def_stmt->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::DefinitionStatement);
  std::string define_type_base;
  if (auto type_context = dynamic_cast<MXParser::TypeContext *>(context->children[0])) {
    define_type_base = type_context->getText();
  } else
    throw std::runtime_error("unknown subnode occurred in visitDefine_statement");
  size_t define_dimensions = 0;
  for (size_t i = 1; i < context->children.size(); i++) {
    if (dynamic_cast<antlr4::tree::TerminalNode *>(context->children[i]) != nullptr &&
        dynamic_cast<antlr4::tree::TerminalNode *>(context->children[i])->getSymbol()->getType() == MXParser::ID) {
      break;
    }
    define_dimensions++;
  }
  define_dimensions >>= 1;
  if (define_dimensions == 0) {
    def_stmt->var_type = define_type_base;
    std::cerr << std::string(nodetype_stk.size() * 2, ' ') << "recorded member variable type is [none-array]"
              << define_type_base << std::endl;
  } else {
    def_stmt->var_type = ArrayType{true, define_type_base, static_cast<size_t>(define_dimensions)};
    std::cerr << std::string(nodetype_stk.size() * 2, ' ') << "recorded member variable type is [array]"
              << define_type_base << " with dimensions=" << define_dimensions << std::endl;
  }
  for (size_t i = 1 + 2 * define_dimensions; i < context->children.size();) {
    if (dynamic_cast<antlr4::tree::TerminalNode *>(context->children[i]) != nullptr &&
        dynamic_cast<antlr4::tree::TerminalNode *>(context->children[i])->getSymbol()->getType() ==
            MXParser::SEMICOLON) {
      break;
    }
    if (i != 1 + 2 * define_dimensions) i++;
    if (dynamic_cast<antlr4::tree::TerminalNode *>(context->children[i]) != nullptr &&
        dynamic_cast<antlr4::tree::TerminalNode *>(context->children[i])->getSymbol()->getType() == MXParser::ID) {
      def_stmt->vars.push_back(std::make_pair(context->children[i]->getText(), nullptr));
    } else
      throw std::runtime_error("unknown subnode occurred in visitDefine_statement");
    i++;
    if (dynamic_cast<antlr4::tree::TerminalNode *>(context->children[i]) != nullptr &&
        dynamic_cast<antlr4::tree::TerminalNode *>(context->children[i])->getSymbol()->getType() == MXParser::ASSIGN) {
      i++;
      def_stmt->vars.back().second = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[i]));
      i++;
    }
  }
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Statement_ASTNode>(def_stmt);
}
std::any Visitor::visitGgll_expression(MXParser::Ggll_expressionContext *context) {
  auto ggll_expr = std::make_shared<GGLLExpr_ASTNode>();
  ggll_expr->type = ASTNodeType::GGLLExpr;
  ggll_expr->start_line = context->getStart()->getLine();
  ggll_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  ggll_expr->end_line = context->getStop()->getLine();
  ggll_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::GGLLExpr);
  ggll_expr->op = context->children[1]->getText();
  ggll_expr->left = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[0]));
  ggll_expr->right = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[2]));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(ggll_expr);
}
std::any Visitor::visitBxor_expression(MXParser::Bxor_expressionContext *context) {
  auto bxor_expr = std::make_shared<BXorExpr_ASTNode>();
  bxor_expr->type = ASTNodeType::BXorExpr;
  bxor_expr->start_line = context->getStart()->getLine();
  bxor_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  bxor_expr->end_line = context->getStop()->getLine();
  bxor_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::BXorExpr);
  bxor_expr->op = context->children[1]->getText();
  bxor_expr->left = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[0]));
  bxor_expr->right = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[2]));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(bxor_expr);
}
std::any Visitor::visitSuffix_expression(MXParser::Suffix_expressionContext *context) {
  auto suffix_expr = std::make_shared<SuffixExpr_ASTNode>();
  suffix_expr->type = ASTNodeType::SuffixExpr;
  suffix_expr->start_line = context->getStart()->getLine();
  suffix_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  suffix_expr->end_line = context->getStop()->getLine();
  suffix_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::SuffixExpr);
  suffix_expr->op = context->children[1]->getText();
  suffix_expr->base = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->expr()));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(suffix_expr);
}
std::any Visitor::visitLand_expression(MXParser::Land_expressionContext *context) {
  auto land_expr = std::make_shared<LAndExpr_ASTNode>();
  land_expr->type = ASTNodeType::LAndExpr;
  land_expr->start_line = context->getStart()->getLine();
  land_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  land_expr->end_line = context->getStop()->getLine();
  land_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::LAndExpr);
  land_expr->op = context->children[1]->getText();
  land_expr->left = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[0]));
  land_expr->right = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[2]));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(land_expr);
}
std::any Visitor::visitPm_expression(MXParser::Pm_expressionContext *context) {
  auto pm_expr = std::make_shared<PMExpr_ASTNode>();
  pm_expr->type = ASTNodeType::PMExpr;
  pm_expr->start_line = context->getStart()->getLine();
  pm_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  pm_expr->end_line = context->getStop()->getLine();
  pm_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::PMExpr);
  pm_expr->op = context->children[1]->getText();
  pm_expr->left = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[0]));
  pm_expr->right = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[2]));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(pm_expr);
}
std::any Visitor::visitIndex_expression(MXParser::Index_expressionContext *context) {
  auto idx_expr = std::make_shared<IndexExpr_ASTNode>();
  idx_expr->type = ASTNodeType::IndexExpr;
  idx_expr->start_line = context->getStart()->getLine();
  idx_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  idx_expr->end_line = context->getStop()->getLine();
  idx_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::IndexExpr);
  auto sub_exprs = context->expr();
  idx_expr->base = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(sub_exprs[0]));
  for (size_t i = 1; i < sub_exprs.size(); i++) {
    idx_expr->indices.push_back(std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(sub_exprs[i])));
  }
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(idx_expr);
}
std::any Visitor::visitOpposite_expression(MXParser::Opposite_expressionContext *context) {
  auto oppsite_expr = std::make_shared<OppositeExpr_ASTNode>();
  oppsite_expr->type = ASTNodeType::OppositeExpr;
  oppsite_expr->start_line = context->getStart()->getLine();
  oppsite_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  oppsite_expr->end_line = context->getStop()->getLine();
  oppsite_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::OppositeExpr);
  oppsite_expr->base = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->expr()));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(oppsite_expr);
}
std::any Visitor::visitNew_array_expression(MXParser::New_array_expressionContext *context) {
  auto new_array = std::make_shared<NewArrayExpr_ASTNode>();
  new_array->type = ASTNodeType::NewArrayExpr;
  new_array->start_line = context->getStart()->getLine();
  new_array->start_char_pos = context->getStart()->getCharPositionInLine();
  new_array->end_line = context->getStop()->getLine();
  new_array->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::NewArrayExpr);

  size_t total_dimensions = context->LBRACKET().size();
  std::string base_type = context->type()->getText();
  new_array->expr_type_info = ArrayType{true, base_type, total_dimensions};
  size_t total_dim_count = 0;
  new_array->dim_size.resize(total_dimensions);
  for (size_t i = 3; i < context->children.size() && total_dim_count < total_dimensions; i++) {
    if (dynamic_cast<antlr4::tree::TerminalNode *>(context->children[i]) != nullptr &&
        dynamic_cast<antlr4::tree::TerminalNode *>(context->children[i])->getSymbol()->getType() ==
            MXParser::RBRACKET) {
    } else if (dynamic_cast<MXParser::ExprContext *>(context->children[i]) != nullptr) {
      new_array->dim_size[total_dim_count] = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[i]));
    }
    total_dim_count++;
  }
  if (context->constant() != nullptr) {
    new_array->has_initial_value = true;
    new_array->initial_value = std::dynamic_pointer_cast<ConstantExpr_ASTNode>(
        std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->constant())));
  }

  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(new_array);
}
std::any Visitor::visitBasic_expression(MXParser::Basic_expressionContext *context) {
  return visit(context->basic_expr());
}
std::any Visitor::visitAccess_expression(MXParser::Access_expressionContext *context) {
  auto access_expr = std::make_shared<AccessExpr_ASTNode>();
  access_expr->start_line = context->getStart()->getLine();
  access_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  access_expr->end_line = context->getStop()->getLine();
  access_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  if (context->LPAREN() == nullptr) {
    access_expr->type = ASTNodeType::MemberVariableAccessExpr;
    access_expr->is_function = false;
  } else {
    access_expr->type = ASTNodeType::MemberFunctionAccessExpr;
    access_expr->is_function = true;
  }
  nodetype_stk.push_back(access_expr->type);
  auto sub_exprs = context->expr();
  access_expr->base = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(sub_exprs[0]));
  access_expr->member = context->ID()->getText();
  for (size_t i = 1; i < sub_exprs.size(); i++) {
    access_expr->arguments.push_back(std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(sub_exprs[i])));
  }
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(access_expr);
}
std::any Visitor::visitBand_expression(MXParser::Band_expressionContext *context) {
  auto band_expr = std::make_shared<BAndExpr_ASTNode>();
  band_expr->type = ASTNodeType::BAndExpr;
  band_expr->start_line = context->getStart()->getLine();
  band_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  band_expr->end_line = context->getStop()->getLine();
  band_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::BAndExpr);
  band_expr->op = context->children[1]->getText();
  band_expr->left = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[0]));
  band_expr->right = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[2]));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(band_expr);
}
std::any Visitor::visitNew_construct_expression(MXParser::New_construct_expressionContext *context) {
  auto new_construct_expr = std::make_shared<NewConstructExpr_ASTNode>();
  new_construct_expr->type = ASTNodeType::NewConstructExpr;
  new_construct_expr->start_line = context->getStart()->getLine();
  new_construct_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  new_construct_expr->end_line = context->getStop()->getLine();
  new_construct_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::NewConstructExpr);
  new_construct_expr->expr_type_info = context->type()->getText();
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(new_construct_expr);
}
std::any Visitor::visitTernary_expression(MXParser::Ternary_expressionContext *context) {
  auto ternary_expr = std::make_shared<TernaryExpr_ASTNode>();
  ternary_expr->type = ASTNodeType::TernaryExpr;
  ternary_expr->start_line = context->getStart()->getLine();
  ternary_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  ternary_expr->end_line = context->getStop()->getLine();
  ternary_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::TernaryExpr);
  auto expr_subnodes = context->expr();
  ternary_expr->condition = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(expr_subnodes[0]));
  ternary_expr->src1 = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(expr_subnodes[1]));
  ternary_expr->src2 = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(expr_subnodes[2]));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(ternary_expr);
}
std::any Visitor::visitBnot_expression(MXParser::Bnot_expressionContext *context) {
  auto bnot_expr = std::make_shared<BNotExpr_ASTNode>();
  bnot_expr->type = ASTNodeType::BNotExpr;
  bnot_expr->start_line = context->getStart()->getLine();
  bnot_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  bnot_expr->end_line = context->getStop()->getLine();
  bnot_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::BNotExpr);
  bnot_expr->base = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->expr()));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(bnot_expr);
}
std::any Visitor::visitLnot_expression(MXParser::Lnot_expressionContext *context) {
  auto lnot_expr = std::make_shared<LNotExpr_ASTNode>();
  lnot_expr->type = ASTNodeType::LNotExpr;
  lnot_expr->start_line = context->getStart()->getLine();
  lnot_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  lnot_expr->end_line = context->getStop()->getLine();
  lnot_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::LNotExpr);
  lnot_expr->base = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->expr()));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(lnot_expr);
}
std::any Visitor::visitPrefix_expression(MXParser::Prefix_expressionContext *context) {
  auto prefix_expr = std::make_shared<PrefixExpr_ASTNode>();
  prefix_expr->type = ASTNodeType::PrefixExpr;
  prefix_expr->start_line = context->getStart()->getLine();
  prefix_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  prefix_expr->end_line = context->getStop()->getLine();
  prefix_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::PrefixExpr);
  prefix_expr->op = context->children[0]->getText();
  prefix_expr->base = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->expr()));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(prefix_expr);
}
std::any Visitor::visitRl_expression(MXParser::Rl_expressionContext *context) {
  auto rl_expr = std::make_shared<RLExpr_ASTNode>();
  rl_expr->type = ASTNodeType::RLExpr;
  rl_expr->start_line = context->getStart()->getLine();
  rl_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  rl_expr->end_line = context->getStop()->getLine();
  rl_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::RLExpr);
  rl_expr->op = context->children[1]->getText();
  rl_expr->left = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[0]));
  rl_expr->right = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[2]));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(rl_expr);
}
std::any Visitor::visitAssign_expression(MXParser::Assign_expressionContext *context) {
  auto assign_expr = std::make_shared<AssignExpr_ASTNode>();
  assign_expr->type = ASTNodeType::AssignExpr;
  assign_expr->start_line = context->getStart()->getLine();
  assign_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  assign_expr->end_line = context->getStop()->getLine();
  assign_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::AssignExpr);
  assign_expr->dest = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->expr(0)));
  assign_expr->src = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->expr(1)));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(assign_expr);
}
std::any Visitor::visitMdm_expression(MXParser::Mdm_expressionContext *context) {
  auto mdm_expr = std::make_shared<MDMExpr_ASTNode>();
  mdm_expr->type = ASTNodeType::MDMExpr;
  mdm_expr->start_line = context->getStart()->getLine();
  mdm_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  mdm_expr->end_line = context->getStop()->getLine();
  mdm_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::MDMExpr);
  mdm_expr->op = context->children[1]->getText();
  mdm_expr->left = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[0]));
  mdm_expr->right = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[2]));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(mdm_expr);
}
std::any Visitor::visitNew_expression(MXParser::New_expressionContext *context) {
  auto new_expr = std::make_shared<NewExpr_ASTNode>();
  new_expr->type = ASTNodeType::NewExpr;
  new_expr->start_line = context->getStart()->getLine();
  new_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  new_expr->end_line = context->getStop()->getLine();
  new_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::NewExpr);
  new_expr->expr_type_info = context->type()->getText();
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(new_expr);
}
std::any Visitor::visitNe_expression(MXParser::Ne_expressionContext *context) {
  auto ne_expr = std::make_shared<NEExpr_ASTNode>();
  ne_expr->type = ASTNodeType::NEExpr;
  ne_expr->start_line = context->getStart()->getLine();
  ne_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  ne_expr->end_line = context->getStop()->getLine();
  ne_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::NEExpr);
  ne_expr->op = context->children[1]->getText();
  ne_expr->left = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[0]));
  ne_expr->right = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[2]));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(ne_expr);
}
std::any Visitor::visitBor_expression(MXParser::Bor_expressionContext *context) {
  auto bor_expr = std::make_shared<BOrExpr_ASTNode>();
  bor_expr->type = ASTNodeType::BOrExpr;
  bor_expr->start_line = context->getStart()->getLine();
  bor_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  bor_expr->end_line = context->getStop()->getLine();
  bor_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::BOrExpr);
  bor_expr->op = context->children[1]->getText();
  bor_expr->left = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[0]));
  bor_expr->right = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[2]));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(bor_expr);
}
std::any Visitor::visitLor_expression(MXParser::Lor_expressionContext *context) {
  auto lor_expr = std::make_shared<LOrExpr_ASTNode>();
  lor_expr->type = ASTNodeType::LOrExpr;
  lor_expr->start_line = context->getStart()->getLine();
  lor_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  lor_expr->end_line = context->getStop()->getLine();
  lor_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::LOrExpr);
  lor_expr->op = context->children[1]->getText();
  lor_expr->left = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[0]));
  lor_expr->right = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->children[2]));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(lor_expr);
}
std::any Visitor::visitThis_expr(MXParser::This_exprContext *context) {
  auto this_expr = std::make_shared<ThisExpr_ASTNode>();
  this_expr->type = ASTNodeType::ThisExpr;
  this_expr->start_line = context->getStart()->getLine();
  this_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  this_expr->end_line = context->getStop()->getLine();
  this_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::ThisExpr);
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(this_expr);
}
std::any Visitor::visitParen_expr(MXParser::Paren_exprContext *context) {
  auto paren_expr = std::make_shared<ParenExpr_ASTNode>();
  paren_expr->type = ASTNodeType::ParenExpr;
  paren_expr->start_line = context->getStart()->getLine();
  paren_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  paren_expr->end_line = context->getStop()->getLine();
  paren_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::ParenExpr);
  paren_expr->expr = std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(context->expr()));
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(paren_expr);
}
std::any Visitor::visitId_expr(MXParser::Id_exprContext *context) {
  auto id_expr = std::make_shared<IDExpr_ASTNode>();
  id_expr->type = ASTNodeType::IDExpr;
  id_expr->start_line = context->getStart()->getLine();
  id_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  id_expr->end_line = context->getStop()->getLine();
  id_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::IDExpr);
  id_expr->id = IdentifierType{context->ID()->getText()};
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(id_expr);
}
std::any Visitor::visitFunction_call_expr(MXParser::Function_call_exprContext *context) {
  auto func_call_expr = std::make_shared<FunctionCallExpr_ASTNode>();
  func_call_expr->type = ASTNodeType::FunctionCallExpr;
  func_call_expr->start_line = context->getStart()->getLine();
  func_call_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  func_call_expr->end_line = context->getStop()->getLine();
  func_call_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::FunctionCallExpr);
  func_call_expr->func_name = IdentifierType{context->ID()->getText()};
  auto expr_subnodes = context->expr();
  for (auto expr_subnode : expr_subnodes) {
    func_call_expr->arguments.push_back(std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(expr_subnode)));
  }
  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(func_call_expr);
}
std::any Visitor::visitFormatted_string_expr(MXParser::Formatted_string_exprContext *context) {
  return visit(context->formatted_string());
}
std::any Visitor::visitConstant_expr(MXParser::Constant_exprContext *context) { return visit(context->constant()); }
std::any Visitor::visitFormatted_string(MXParser::Formatted_stringContext *context) {
  auto fmt_expr = std::make_shared<FormattedStringExpr_ASTNode>();
  fmt_expr->type = ASTNodeType::FormattedStringExpr;
  fmt_expr->start_line = context->getStart()->getLine();
  fmt_expr->start_char_pos = context->getStart()->getCharPositionInLine();
  fmt_expr->end_line = context->getStop()->getLine();
  fmt_expr->end_char_pos = context->getStop()->getCharPositionInLine();
  nodetype_stk.push_back(ASTNodeType::FormattedStringExpr);

  if (context->FORMAT_STRING_WHOLE() != nullptr) {
    fmt_expr->literals.push_back(context->FORMAT_STRING_WHOLE()->getText());
  } else {
    auto expr_subnodes = context->expr();
    auto body_subnodes = context->FORMAT_STRING_BODY();
    fmt_expr->literals.push_back(context->FORMAT_STRING_HEAD()->getText());
    for (size_t i = 0; i < expr_subnodes.size(); i++) {
      fmt_expr->literals.push_back(body_subnodes[i]->getText());
    }
    fmt_expr->literals.push_back(context->FORMAT_STRING_TAIL()->getText());
    for (auto expr_subnode : expr_subnodes) {
      fmt_expr->exprs.push_back(std::any_cast<std::shared_ptr<Expr_ASTNode>>(visit(expr_subnode)));
    }
  }

  nodetype_stk.pop_back();
  return std::static_pointer_cast<Expr_ASTNode>(fmt_expr);
}
std::any Visitor::visitConstant(MXParser::ConstantContext *context) {
  // TODO
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitType(MXParser::TypeContext *context) {
  throw std::runtime_error("Visitor::visitType should not be called");
}
