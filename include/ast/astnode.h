#ifndef ASTNODE_H
#define ASTNODE_H
#include <memory>
#include <variant>
#include <vector>
#include "../semantic/visitor.h"
#include "tools.h"
using IdentifierType = std::string;
struct ArrayType {
  bool has_base_type;
  IdentifierType basetype;
  size_t level;
};
using ExprTypeInfo = std::variant<IdentifierType, ArrayType>;
class ASTNodeVisitorBase {
 public:
  virtual ~ASTNodeVisitorBase() = default;
  virtual void visit(class ASTNodeBase *context) = 0;
};

class ASTNodeBase {
  friend Visitor;
  ASTNodeType type;
  // std::vector<std::shared_ptr<ASTNodeBase>> children;
  size_t start_line, start_char_pos, end_line, end_char_pos;

 public:
  virtual ~ASTNodeBase() = default;
  // virtual void accept(class ASTNodeVisitorBase *visitor) = 0;
};
#endif