#ifndef SEMANTIC_H
#define SEMANTIC_H
#include <ios>
#include "ast/ast.h"
#include "visitor.h"

class SemanticError : public std::exception {
  std::string msg;
  int error_code;

 public:
  SemanticError(const std::string &msg, int error_code) : msg(msg), error_code(error_code) {}
  const char *what() const noexcept override { return msg.c_str(); }
  int GetErrorCode() const { return error_code; }
};
std::shared_ptr<ASTNodeBase> BuildAST(Visitor *visitor, antlr4::tree::ParseTree *tree);
void SemanticCheck(std::istream &fin, std::shared_ptr<ASTNodeBase> &ast);
#endif