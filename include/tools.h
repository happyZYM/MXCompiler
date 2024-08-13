#pragma once
#include <stdexcept>
#include <variant>
enum class ASTNodeType {
  // Expression nodes
  NewArrayExpr,
  NewConstructExpr,
  NewExpr,
  MemberVariableAccessExpr,
  MemberFunctionAccessExpr,
  IndexExpr,
  SuffixExpr,
  PrefixExpr,
  OppositeExpr,
  LNotExpr,
  BNotExpr,
  MDMExpr,
  PMExpr,
  RLExpr,
  GGLLExpr,
  NEExpr,
  BAndExpr,
  BXorExpr,
  BOrExpr,
  LAndExpr,
  LOrExpr,
  TernaryExpr,
  AssignExpr,
  ThisExpr,
  ParenExpr,
  IDExpr,
  FunctionCallExpr,
  FormattedStringExpr,
  ConstantExpr,

  // Statement nodes
  EmptyStatement,
  DefinitionStatement,
  ExprStatement,
  IfStatement,
  WhileStatement,
  ForStatement,
  JmpStatement,
  SuiteStatement,

  // Structural nodes
  FuncDef,
  Constructor,
  ClassVariable,
  ClassDef,
  Program
};

class SemanticError : public std::exception {
  std::string msg;
  int error_code;

 public:
  SemanticError(const std::string &msg, int error_code) : msg(msg), error_code(error_code) {}
  const char *what() const noexcept override { return msg.c_str(); }
  int GetErrorCode() const { return error_code; }
};

using IdentifierType = std::string;
struct ArrayType {
  bool has_base_type;
  IdentifierType basetype;
  size_t level;
};
using ExprTypeInfo = std::variant<IdentifierType, ArrayType>;