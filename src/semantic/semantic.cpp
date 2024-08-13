#include "semantic.h"
#include <iostream>
#include "MXLexer.h"
#include "MXParser.h"
#include "antlr4-runtime.h"
#include "ast/ast.h"
#include "visitor.h"

class MXErrorListener : public antlr4::BaseErrorListener {
  bool no_problem;

 public:
  MXErrorListener() : no_problem(true) {}
  void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line,
                   size_t charPositionInLine, const std::string &msg, std::exception_ptr e) override {
    std::cout << "line " << line << ":" << charPositionInLine << " AT " << offendingSymbol->getText() << ": " << msg
              << std::endl;
    no_problem = false;
  }
  bool IsOk() { return no_problem; }
};
std::shared_ptr<Program_ASTNode> BuildAST(Visitor *visitor, antlr4::tree::ParseTree *tree) {
  return std::any_cast<std::shared_ptr<Program_ASTNode>>(visitor->visit(tree));
}
std::shared_ptr<Program_ASTNode> CheckAndDecorate(std::shared_ptr<Program_ASTNode> src) { return nullptr; }

void SemanticCheck(std::istream &fin, std::shared_ptr<Program_ASTNode> &ast_out) {
  antlr4::ANTLRInputStream input(fin);
  MXLexer lexer(&input);
  MXErrorListener error_listener;
  lexer.removeErrorListeners();
  lexer.addErrorListener(&error_listener);
  antlr4::CommonTokenStream tokens(&lexer);
  tokens.fill();
  MXParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(&error_listener);
  antlr4::tree::ParseTree *tree = parser.mxprog();
  if (!error_listener.IsOk()) throw SemanticError("Invalid Identifier", 1);
  Visitor visitor;
  std::shared_ptr<Program_ASTNode> ast = BuildAST(&visitor, tree);
  ast_out = CheckAndDecorate(ast);
}