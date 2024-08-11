#ifndef SEMANTIC_H
#define SEMANTIC_H
#include <ios>
#include "ast/ast.h"
#include "visitor.h"

std::shared_ptr<ASTNodeBase> BuildAST(Visitor *visitor, antlr4::tree::ParseTree *tree);
void SemanticCheck(std::istream &fin, std::shared_ptr<ASTNodeBase> &ast);
#endif