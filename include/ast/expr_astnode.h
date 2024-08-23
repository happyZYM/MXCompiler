#ifndef EXPR_ASTNODE_H
#define EXPR_ASTNODE_H
#include <cstdint>
#include <string>
#include <variant>
#include "astnode.h"

class Expr_ASTNode : public ASTNodeBase {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  ExprTypeInfo expr_type_info;
  bool assignable;
  std::string IR_result_full;
  bool is_requiring_lvalue;

 public:
  Expr_ASTNode() : assignable(false), is_requiring_lvalue(false){};
  virtual ~Expr_ASTNode() = default;
};

class BasicExpr_ASTNode : public Expr_ASTNode {};  // This is a virtual class

class NewArrayExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  bool has_initial_value;
  std::vector<std::shared_ptr<Expr_ASTNode>> dim_size;
  std::shared_ptr<class ConstantExpr_ASTNode> initial_value;

 public:
  NewArrayExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class NewConstructExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;

 public:
  NewConstructExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class NewExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;

 public:
  NewExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class AccessExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::shared_ptr<Expr_ASTNode> base;
  IdentifierType member;
  bool is_function;
  std::vector<std::shared_ptr<Expr_ASTNode>> arguments;

 public:
  AccessExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class IndexExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::shared_ptr<Expr_ASTNode> base;
  std::vector<std::shared_ptr<Expr_ASTNode>> indices;

 public:
  IndexExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class SuffixExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::string op;
  std::shared_ptr<Expr_ASTNode> base;

 public:
  SuffixExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class PrefixExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::string op;
  std::shared_ptr<Expr_ASTNode> base;

 public:
  PrefixExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class OppositeExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::shared_ptr<Expr_ASTNode> base;

 public:
  OppositeExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class LNotExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::shared_ptr<Expr_ASTNode> base;

 public:
  LNotExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class BNotExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::shared_ptr<Expr_ASTNode> base;

 public:
  BNotExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class MDMExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::string op;
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;

 public:
  MDMExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class PMExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::string op;
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;

 public:
  PMExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class RLExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::string op;
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;

 public:
  RLExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class GGLLExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::string op;
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;

 public:
  GGLLExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class NEExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::string op;
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;

 public:
  NEExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class BAndExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::string op;
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;

 public:
  BAndExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class BXorExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::string op;
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;

 public:
  BXorExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class BOrExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::string op;
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;

 public:
  BOrExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class LAndExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::string op;
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;

 public:
  LAndExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class LOrExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::string op;
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;

 public:
  LOrExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class TernaryExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::shared_ptr<Expr_ASTNode> condition;
  std::shared_ptr<Expr_ASTNode> src1;
  std::shared_ptr<Expr_ASTNode> src2;

 public:
  TernaryExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class AssignExpr_ASTNode : public Expr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::string op;
  std::shared_ptr<Expr_ASTNode> dest;
  std::shared_ptr<Expr_ASTNode> src;

 public:
  AssignExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class ThisExpr_ASTNode : public BasicExpr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;

 public:
  ThisExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class ParenExpr_ASTNode : public BasicExpr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::shared_ptr<Expr_ASTNode> expr;

 public:
  ParenExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class IDExpr_ASTNode : public BasicExpr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  IdentifierType id;
  IRVariableInfo cached_var_info;

 public:
  IDExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class FunctionCallExpr_ASTNode : public BasicExpr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  IdentifierType func_name;
  std::vector<std::shared_ptr<Expr_ASTNode>> arguments;

 public:
  FunctionCallExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

class FormattedStringExpr_ASTNode : public BasicExpr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  std::vector<std::string> literals;
  std::vector<std::shared_ptr<Expr_ASTNode>> exprs;

 public:
  FormattedStringExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

struct NullType {};

using AtomicConstantType = std::variant<uint32_t, bool, std::string, NullType>;

class ConstantExpr_ASTNode : public BasicExpr_ASTNode {
  friend Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  size_t level;
  std::variant<AtomicConstantType, std::vector<std::shared_ptr<ConstantExpr_ASTNode>>> value;

 public:
  ConstantExpr_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};

#endif  // EXPR_ASTNODE_H
