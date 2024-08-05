
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

    virtual std::any visitFunction(MXParser::FunctionContext *context) = 0;

    virtual std::any visitType(MXParser::TypeContext *context) = 0;

    virtual std::any visitBlock(MXParser::BlockContext *context) = 0;

    virtual std::any visitStatement(MXParser::StatementContext *context) = 0;

    virtual std::any visitExpression(MXParser::ExpressionContext *context) = 0;

    virtual std::any visitReturnStmt(MXParser::ReturnStmtContext *context) = 0;

    virtual std::any visitIfStmt(MXParser::IfStmtContext *context) = 0;


};

