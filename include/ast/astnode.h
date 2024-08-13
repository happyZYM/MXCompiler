#ifndef ASTNODE_H
#define ASTNODE_H
#include <memory>
#include <variant>
#include <vector>
#include "../semantic/visitor.h"
#include "scope.hpp"
#include "tools.h"
class ASTNodeVisitorBase {
  friend Visitor;

 public:
  virtual ~ASTNodeVisitorBase() = default;
  virtual void visit(class ASTNodeBase *context) = 0;
};

class ASTNodeBase {
  friend Visitor;
  friend std::shared_ptr<Program_ASTNode> CheckAndDecorate(std::shared_ptr<Program_ASTNode> src);

 protected:
  std::shared_ptr<ScopeBase> current_scope;
  ASTNodeType type;
  // std::vector<std::shared_ptr<ASTNodeBase>> children;
  size_t start_line, start_char_pos, end_line, end_char_pos;

 public:
  virtual ~ASTNodeBase() = default;
  // virtual void accept(class ASTNodeVisitorBase *visitor) = 0;
};
#endif