
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

    virtual std::any visitStatement(MXParser::StatementContext *context) = 0;

    virtual std::any visitDefine_statement(MXParser::Define_statementContext *context) = 0;

    virtual std::any visitExpr(MXParser::ExprContext *context) = 0;

    virtual std::any visitBasic_expr(MXParser::Basic_exprContext *context) = 0;

    virtual std::any visitFormatted_string(MXParser::Formatted_stringContext *context) = 0;

    virtual std::any visitConstant(MXParser::ConstantContext *context) = 0;

    virtual std::any visitType(MXParser::TypeContext *context) = 0;


};

