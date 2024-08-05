#include "semantic.h"
#include <iostream>
#include "MXLexer.h"
#include "MXParser.h"
#include "antlr4-runtime.h"
#include "visitor.h"
int SemanticCheck(std::istream &fin) {
  antlr4::ANTLRInputStream input(fin);
  MXLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  tokens.fill();
  MXParser parser(&tokens);
  antlr4::tree::ParseTree *tree = parser.mxprog();
  Visitor visitor;
  visitor.visit(tree);
  return 0;
}