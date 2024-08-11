#ifndef VISITOR_H
#define VISITOR_H

#include <stack>
#include <vector>
#include "MXParserVisitor.h"
#include "tools.h"
class Visitor : public MXParserVisitor {
  std::vector<ASTNodeType> nodetype_stk;

 public:
  std::any visitMxprog(MXParser::MxprogContext *context) override;
  std::any visitFunction_def(MXParser::Function_defContext *context) override;
  std::any visitClass_def(MXParser::Class_defContext *context) override;
  std::any visitClass_var_def(MXParser::Class_var_defContext *context) override;
  std::any visitClass_constructor(MXParser::Class_constructorContext *context) override;
  std::any visitSuite(MXParser::SuiteContext *context) override;
  std::any visitEmpty_statement(MXParser::Empty_statementContext *context) override;
  std::any visitDefinition_statement(MXParser::Definition_statementContext *context) override;
  std::any visitExpr_statement(MXParser::Expr_statementContext *context) override;
  std::any visitIf_statement(MXParser::If_statementContext *context) override;
  std::any visitWhile_statement(MXParser::While_statementContext *context) override;
  std::any visitFor_statement(MXParser::For_statementContext *context) override;
  std::any visitJmp_statement(MXParser::Jmp_statementContext *context) override;
  std::any visitSuite_statement(MXParser::Suite_statementContext *context) override;
  std::any visitDefine_statement(MXParser::Define_statementContext *context) override;
  std::any visitGgll_expression(MXParser::Ggll_expressionContext *context) override;
  std::any visitBxor_expression(MXParser::Bxor_expressionContext *context) override;
  std::any visitSuffix_expression(MXParser::Suffix_expressionContext *context) override;
  std::any visitLand_expression(MXParser::Land_expressionContext *context) override;
  std::any visitPm_expression(MXParser::Pm_expressionContext *context) override;
  std::any visitIndex_expression(MXParser::Index_expressionContext *context) override;
  std::any visitOpposite_expression(MXParser::Opposite_expressionContext *context) override;
  std::any visitNew_array_expression(MXParser::New_array_expressionContext *context) override;
  std::any visitBasic_expression(MXParser::Basic_expressionContext *context) override;
  std::any visitAccess_expression(MXParser::Access_expressionContext *context) override;
  std::any visitBand_expression(MXParser::Band_expressionContext *context) override;
  std::any visitNew_construct_expression(MXParser::New_construct_expressionContext *context) override;
  std::any visitTernary_expression(MXParser::Ternary_expressionContext *context) override;
  std::any visitBnot_expression(MXParser::Bnot_expressionContext *context) override;
  std::any visitLnot_expression(MXParser::Lnot_expressionContext *context) override;
  std::any visitPrefix_expression(MXParser::Prefix_expressionContext *context) override;
  std::any visitRl_expression(MXParser::Rl_expressionContext *context) override;
  std::any visitAssign_expression(MXParser::Assign_expressionContext *context) override;
  std::any visitMdm_expression(MXParser::Mdm_expressionContext *context) override;
  std::any visitNew_expression(MXParser::New_expressionContext *context) override;
  std::any visitNe_expression(MXParser::Ne_expressionContext *context) override;
  std::any visitBor_expression(MXParser::Bor_expressionContext *context) override;
  std::any visitLor_expression(MXParser::Lor_expressionContext *context) override;
  std::any visitThis_expr(MXParser::This_exprContext *context) override;
  std::any visitParen_expr(MXParser::Paren_exprContext *context) override;
  std::any visitId_expr(MXParser::Id_exprContext *context) override;
  std::any visitFunction_call_expr(MXParser::Function_call_exprContext *context) override;
  std::any visitFormatted_string_expr(MXParser::Formatted_string_exprContext *context) override;
  std::any visitConstant_expr(MXParser::Constant_exprContext *context) override;
  std::any visitFormatted_string(MXParser::Formatted_stringContext *context) override;
  std::any visitConstant(MXParser::ConstantContext *context) override;
  std::any visitType(MXParser::TypeContext *context) override;
};

#endif  // VISITOR_H