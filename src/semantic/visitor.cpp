#include "visitor.h"
#include <stdexcept>

std::any Visitor::visitMxprog(MXParser::MxprogContext *context) { throw std::runtime_error("Not implemented"); }
std::any Visitor::visitFunction_def(MXParser::Function_defContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitClass_def(MXParser::Class_defContext *context) { throw std::runtime_error("Not implemented"); }
std::any Visitor::visitClass_var_def(MXParser::Class_var_defContext *context) {
  throw std::runtime_error("Not implemented");
}
std::any Visitor::visitClass_constructor(MXParser::Class_constructorContext *context) {
  throw std::runtime_error("Not implemented");
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
