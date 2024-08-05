#ifndef VISITOR_H
#define VISITOR_H
#include "MXParserVisitor.h"
class Visitor : public MXParserVisitor {
 public:
  virtual std::any visitMxprog(MXParser::MxprogContext *context);
  virtual std::any visitFunction(MXParser::FunctionContext *context);
  virtual std::any visitType(MXParser::TypeContext *context);
  virtual std::any visitBlock(MXParser::BlockContext *context);
  virtual std::any visitStatement(MXParser::StatementContext *context);
  virtual std::any visitExpression(MXParser::ExpressionContext *context);
  virtual std::any visitReturnStmt(MXParser::ReturnStmtContext *context);
  virtual std::any visitIfStmt(MXParser::IfStmtContext *context);
};
#endif