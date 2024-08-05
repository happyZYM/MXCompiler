
// Generated from MXParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "MXParserVisitor.h"


/**
 * This class provides an empty implementation of MXParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  MXParserBaseVisitor : public MXParserVisitor {
public:

  virtual std::any visitMxprog(MXParser::MxprogContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction(MXParser::FunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType(MXParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(MXParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(MXParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(MXParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStmt(MXParser::ReturnStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStmt(MXParser::IfStmtContext *ctx) override {
    return visitChildren(ctx);
  }


};

