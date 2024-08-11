#ifndef STATEMENT_ASTNODE_H
#define STATEMENT_ASTNODE_H
#include <vector>
#include "astnode.h"
#include "expr_astnode.h"
class Statement_ASTNode : public ASTNodeBase {
 public:
  virtual ~Statement_ASTNode() = default;
};

class EmptyStatement_ASTNode : public Statement_ASTNode {
  friend Visitor;
};
class DefinitionStatement_ASTNode : public Statement_ASTNode {
  friend Visitor;
  ExprTypeInfo var_type;
  std::vector<std::pair<IdentifierType, std::shared_ptr<Expr_ASTNode>>> vars;
};
class ExprStatement_ASTNode : public Statement_ASTNode {
  friend Visitor;
  std::shared_ptr<Expr_ASTNode> expr;
};
class IfStatement_ASTNode : public Statement_ASTNode {
  friend Visitor;
  bool has_else_clause;
  std::shared_ptr<Expr_ASTNode> condition;
  std::shared_ptr<Statement_ASTNode> if_clause;
  std::shared_ptr<Statement_ASTNode> else_clause;
};
class WhileStatement_ASTNode : public Statement_ASTNode {
  friend Visitor;
  std::shared_ptr<Expr_ASTNode> condition;
  std::shared_ptr<Statement_ASTNode> loop_body;
};
class ForStatement_ASTNode : public Statement_ASTNode {
  friend Visitor;
  std::shared_ptr<Statement_ASTNode> initial;
  std::shared_ptr<Expr_ASTNode> condition;
  std::shared_ptr<Statement_ASTNode> update;
  std::shared_ptr<Statement_ASTNode> loop_body;
};
class JmpStatement_ASTNode : public Statement_ASTNode {
  friend Visitor;
  std::shared_ptr<Expr_ASTNode> return_value;
};
class SuiteStatement_ASTNode : public Statement_ASTNode {
  friend Visitor;
  std::vector<std::shared_ptr<Statement_ASTNode>> statements;
};

#endif  // STATEMENT_ASTNODE_H