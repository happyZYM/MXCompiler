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
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;

 public:
  EmptyStatement_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};
class DefinitionStatement_ASTNode : public Statement_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  ExprTypeInfo var_type;
  std::vector<std::pair<IdentifierType, std::shared_ptr<Expr_ASTNode>>> vars;

 public:
  DefinitionStatement_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};
class ExprStatement_ASTNode : public Statement_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::shared_ptr<Expr_ASTNode> expr;

 public:
  ExprStatement_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};
class IfStatement_ASTNode : public Statement_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  bool has_else_clause;
  std::shared_ptr<Expr_ASTNode> condition;
  std::shared_ptr<Statement_ASTNode> if_clause;
  std::shared_ptr<Statement_ASTNode> else_clause;

 public:
  IfStatement_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};
class WhileStatement_ASTNode : public Statement_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::shared_ptr<Expr_ASTNode> condition;
  std::shared_ptr<Statement_ASTNode> loop_body;

 public:
  WhileStatement_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};
class ForStatement_ASTNode : public Statement_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::shared_ptr<Statement_ASTNode> initial;
  std::shared_ptr<Expr_ASTNode> condition;
  std::shared_ptr<Statement_ASTNode> update;
  std::shared_ptr<Statement_ASTNode> loop_body;

 public:
  ForStatement_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};
class JmpStatement_ASTNode : public Statement_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  uint8_t jmp_type;  // 0: return, 1: break, 2: continue
  std::shared_ptr<Expr_ASTNode> return_value;

 public:
  JmpStatement_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};
class SuiteStatement_ASTNode : public Statement_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::vector<std::shared_ptr<Statement_ASTNode>> statements;

 public:
  SuiteStatement_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

#endif  // STATEMENT_ASTNODE_H