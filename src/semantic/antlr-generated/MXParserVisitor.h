
// Generated from MXParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "MXParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by MXParser.
 */
class  MXParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by MXParser.
   */
    virtual std::any visitMxprog(MXParser::MxprogContext *context) = 0;

    virtual std::any visitFunction_def(MXParser::Function_defContext *context) = 0;

    virtual std::any visitClass_def(MXParser::Class_defContext *context) = 0;

    virtual std::any visitClass_var_def(MXParser::Class_var_defContext *context) = 0;

    virtual std::any visitClass_constructor(MXParser::Class_constructorContext *context) = 0;

    virtual std::any visitSuite(MXParser::SuiteContext *context) = 0;

    virtual std::any visitEmpty_statement(MXParser::Empty_statementContext *context) = 0;

    virtual std::any visitDefinition_statement(MXParser::Definition_statementContext *context) = 0;

    virtual std::any visitExpr_statement(MXParser::Expr_statementContext *context) = 0;

    virtual std::any visitIf_statement(MXParser::If_statementContext *context) = 0;

    virtual std::any visitWhile_statement(MXParser::While_statementContext *context) = 0;

    virtual std::any visitFor_statement(MXParser::For_statementContext *context) = 0;

    virtual std::any visitJmp_statement(MXParser::Jmp_statementContext *context) = 0;

    virtual std::any visitSuite_statement(MXParser::Suite_statementContext *context) = 0;

    virtual std::any visitDefine_statement(MXParser::Define_statementContext *context) = 0;

    virtual std::any visitGgll_expression(MXParser::Ggll_expressionContext *context) = 0;

    virtual std::any visitBxor_expression(MXParser::Bxor_expressionContext *context) = 0;

    virtual std::any visitSuffix_expression(MXParser::Suffix_expressionContext *context) = 0;

    virtual std::any visitLand_expression(MXParser::Land_expressionContext *context) = 0;

    virtual std::any visitPm_expression(MXParser::Pm_expressionContext *context) = 0;

    virtual std::any visitIndex_expression(MXParser::Index_expressionContext *context) = 0;

    virtual std::any visitOpposite_expression(MXParser::Opposite_expressionContext *context) = 0;

    virtual std::any visitNew_array_expression(MXParser::New_array_expressionContext *context) = 0;

    virtual std::any visitBasic_expression(MXParser::Basic_expressionContext *context) = 0;

    virtual std::any visitAccess_expression(MXParser::Access_expressionContext *context) = 0;

    virtual std::any visitBand_expression(MXParser::Band_expressionContext *context) = 0;

    virtual std::any visitNew_construct_expression(MXParser::New_construct_expressionContext *context) = 0;

    virtual std::any visitTernary_expression(MXParser::Ternary_expressionContext *context) = 0;

    virtual std::any visitBnot_expression(MXParser::Bnot_expressionContext *context) = 0;

    virtual std::any visitLnot_expression(MXParser::Lnot_expressionContext *context) = 0;

    virtual std::any visitPrefix_expression(MXParser::Prefix_expressionContext *context) = 0;

    virtual std::any visitRl_expression(MXParser::Rl_expressionContext *context) = 0;

    virtual std::any visitAssign_expression(MXParser::Assign_expressionContext *context) = 0;

    virtual std::any visitMdm_expression(MXParser::Mdm_expressionContext *context) = 0;

    virtual std::any visitNew_expression(MXParser::New_expressionContext *context) = 0;

    virtual std::any visitNe_expression(MXParser::Ne_expressionContext *context) = 0;

    virtual std::any visitBor_expression(MXParser::Bor_expressionContext *context) = 0;

    virtual std::any visitLor_expression(MXParser::Lor_expressionContext *context) = 0;

    virtual std::any visitThis_expr(MXParser::This_exprContext *context) = 0;

    virtual std::any visitParen_expr(MXParser::Paren_exprContext *context) = 0;

    virtual std::any visitId_expr(MXParser::Id_exprContext *context) = 0;

    virtual std::any visitFunction_call_expr(MXParser::Function_call_exprContext *context) = 0;

    virtual std::any visitFormatted_string_expr(MXParser::Formatted_string_exprContext *context) = 0;

    virtual std::any visitConstant_expr(MXParser::Constant_exprContext *context) = 0;

    virtual std::any visitFormatted_string(MXParser::Formatted_stringContext *context) = 0;

    virtual std::any visitConstant(MXParser::ConstantContext *context) = 0;

    virtual std::any visitType(MXParser::TypeContext *context) = 0;


};

