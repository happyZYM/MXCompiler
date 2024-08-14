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
inline bool operator==(const ArrayType &l, const ArrayType &r) {
  return l.has_base_type == r.has_base_type && l.basetype == r.basetype && l.level == r.level;
}
using ExprTypeInfo = std::variant<IdentifierType, ArrayType>;

inline bool operator==(const ExprTypeInfo &l, const ExprTypeInfo &r) {
  if (std::holds_alternative<IdentifierType>(r) && std::get<IdentifierType>(r) == "null") {
    if (std::holds_alternative<IdentifierType>(l)) {
      std::string l_type = std::get<IdentifierType>(l);
      if (l_type == "int" || l_type == "bool" || l_type == "string") {
        return false;
      }
      return true;
    }
    return true;
  }
  if (std::holds_alternative<IdentifierType>(l)) {
    return std::holds_alternative<IdentifierType>(r) && std::get<IdentifierType>(l) == std::get<IdentifierType>(r);
  }
  if (std::holds_alternative<ArrayType>(l)) {
    return std::holds_alternative<ArrayType>(r) && std::get<ArrayType>(l) == std::get<ArrayType>(r);
  }
  throw std::runtime_error("something strange happened");
}
inline bool operator!=(const ExprTypeInfo &l, const ExprTypeInfo &r) { return !(l == r); }