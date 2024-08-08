#ifndef EXPR_ASTNODE_H
#define EXPR_ASTNODE_H
#include <cstdint>
#include <string>
#include <variant>
#include "astnode.h"

class Expr_ASTNode : public ASTNodeBase {
  ExprTypeInfo expr_type_info;

 public:
  virtual ~Expr_ASTNode() = default;
};

class BasicExpr_ASTNode : public Expr_ASTNode {};  // This is a virtual class
class NewArrayExpr_ASTNode : public Expr_ASTNode {
  bool has_initial_value;
  std::shared_ptr<class ConstantExpr_ASTNode> initial_value;
};
class NewConstructExpr_ASTNode : public Expr_ASTNode {};
class NewExpr_ASTNode : public Expr_ASTNode {};
class AccessExpr_ASTNode : public Expr_ASTNode {
  std::shared_ptr<Expr_ASTNode> base;
  IdentifierType member;
};
class MemberVariableAccessExpr_ASTNode : public AccessExpr_ASTNode {};
class MemberFunctionAccessExpr_ASTNode : public AccessExpr_ASTNode {
  std::vector<std::shared_ptr<Expr_ASTNode>> arguments;
};
class IndexExpr_ASTNode : public Expr_ASTNode {
  std::shared_ptr<Expr_ASTNode> base;
  std::vector<std::shared_ptr<Expr_ASTNode>> indices;
};
class SuffixExpr_ASTNode : public Expr_ASTNode {
  std::shared_ptr<Expr_ASTNode> base;
};
class PrefixExpr_ASTNode : public Expr_ASTNode {
  std::shared_ptr<Expr_ASTNode> base;
};
class OppositeExpr_ASTNode : public Expr_ASTNode {
  std::shared_ptr<Expr_ASTNode> base;
};
class LNotExpr_ASTNode : public Expr_ASTNode {
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;
};
class BNotExpr_ASTNode : public Expr_ASTNode {
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;
};
class MDMExpr_ASTNode : public Expr_ASTNode {
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;
};
class PMExpr_ASTNode : public Expr_ASTNode {
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;
};
class RLExpr_ASTNode : public Expr_ASTNode {
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;
};
class GGLLExpr_ASTNode : public Expr_ASTNode {
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;
};
class NEExpr_ASTNode : public Expr_ASTNode {
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;
};
class BAndExpr_ASTNode : public Expr_ASTNode {
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;
};
class BXorExpr_ASTNode : public Expr_ASTNode {
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;
};
class BOrExpr_ASTNode : public Expr_ASTNode {
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;
};
class LAndExpr_ASTNode : public Expr_ASTNode {
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;
};
class LOrExpr_ASTNode : public Expr_ASTNode {
  std::shared_ptr<Expr_ASTNode> left;
  std::shared_ptr<Expr_ASTNode> right;
};
class TernaryExpr_ASTNode : public Expr_ASTNode {
  std::shared_ptr<Expr_ASTNode> condition;
  std::shared_ptr<Expr_ASTNode> src1;
  std::shared_ptr<Expr_ASTNode> src2;
};
class AssignExpr_ASTNode : public Expr_ASTNode {
  std::shared_ptr<Expr_ASTNode> dest;
  std::shared_ptr<Expr_ASTNode> src;
};

class ThisExpr_ASTNode : public BasicExpr_ASTNode {};
class ParenExpr_ASTNode : public BasicExpr_ASTNode {
  std::shared_ptr<Expr_ASTNode> expr;
};
class IDExpr_ASTNode : public BasicExpr_ASTNode {
  IdentifierType id;
};
class FunctionCallExpr_ASTNode : public BasicExpr_ASTNode {
  IdentifierType func_name;
  std::vector<std::shared_ptr<Expr_ASTNode>> arguments;
};
class FormattedStringExpr_ASTNode : public BasicExpr_ASTNode {
  using SegmentType = std::variant<std::string, std::shared_ptr<Expr_ASTNode>>;
  std::vector<SegmentType> segments;
};
struct NullType {};
using AtomicConstantType = std::variant<uint32_t, bool, std::string, NullType>;
struct ArrayConstantType {
  std::vector<std::variant<std::shared_ptr<ArrayConstantType>, NullType, AtomicConstantType>> elements;
  size_t level;
};
class ConstantExpr_ASTNode : public BasicExpr_ASTNode {
  std::variant<AtomicConstantType, ArrayConstantType> value;
};

#endif  // EXPR_ASTNODE_H