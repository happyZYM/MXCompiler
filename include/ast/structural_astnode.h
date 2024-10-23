#ifndef STRUCTURAL_ASTNODE_H
#define STRUCTURAL_ASTNODE_H
#include <memory>
#include <variant>
#include <vector>
#include "astnode.h"

#include "expr_astnode.h"
#include "statement_astnode.h"
class FuncDef_ASTNode : public ASTNodeBase {
 public:
  bool is_constructor;
  IdentifierType func_name;
  ExprTypeInfo return_type;
  std::vector<std::pair<IdentifierType, ExprTypeInfo>> params;
  std::shared_ptr<SuiteStatement_ASTNode> func_body;

 public:
  FuncDef_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};
class ClassDef_ASTNode : public ASTNodeBase {
 public:
  std::string class_name;
  std::vector<std::shared_ptr<DefinitionStatement_ASTNode>> member_variables;
  std::vector<std::shared_ptr<FuncDef_ASTNode>> member_functions;
  std::shared_ptr<FuncDef_ASTNode> constructor;
  std::vector<std::shared_ptr<ASTNodeBase>> sorted_children;

 public:
  ClassDef_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};
class Program_ASTNode : public ASTNodeBase {
 public:
  std::vector<std::shared_ptr<DefinitionStatement_ASTNode>> global_variables;
  std::vector<std::shared_ptr<ClassDef_ASTNode>> classes;
  std::vector<std::shared_ptr<FuncDef_ASTNode>> functions;
  std::vector<std::shared_ptr<ASTNodeBase>> sorted_children;

  Program_ASTNode() = default;
  virtual void accept(class ASTNodeVisitorBase *visitor) override;
};
#endif