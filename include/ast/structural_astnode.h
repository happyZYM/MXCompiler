#ifndef STRUCTURAL_ASTNODE_H
#define STRUCTURAL_ASTNODE_H
#include <memory>
#include <variant>
#include <vector>
#include "astnode.h"
#include "expr_astnode.h"
#include "statement_astnode.h"
class FuncDef_ASTNode : public ASTNodeBase {
  IdentifierType func_name;
  std::vector<std::pair<IdentifierType, ExprTypeInfo>> params;
  std::shared_ptr<SuiteStatement_ASTNode> func_body;
};
class Constructor_ASTNode : public FuncDef_ASTNode {};
class ClassVariable_ASTNode : public DefinitionStatement_ASTNode {};
class ClassDef_ASTNode : public ASTNodeBase {
 private:
  using ClassElement = std::variant<std::shared_ptr<Constructor_ASTNode>, std::shared_ptr<ClassVariable_ASTNode>,
                                    std::shared_ptr<FuncDef_ASTNode>>;
  std::vector<ClassElement> elements;
};
class Program_ASTNode : public ASTNodeBase {
  using ProgramElement = std::variant<std::shared_ptr<FuncDef_ASTNode>, std::shared_ptr<ClassDef_ASTNode>,
                                      std::shared_ptr<DefinitionStatement_ASTNode>>;
  std::vector<ProgramElement> elements;
};
#endif