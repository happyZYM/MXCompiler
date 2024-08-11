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
std::shared_ptr<ASTNodeBase> BuildAST(Visitor *visitor, antlr4::tree::ParseTree *tree) {
  return std::any_cast<std::shared_ptr<Program_ASTNode>>(visitor->visit(tree));
}
std::shared_ptr<ASTNodeBase> CheckAndDecorate(std::shared_ptr<ASTNodeBase> src) { ; }

void SemanticCheck(std::istream &fin, std::shared_ptr<ASTNodeBase> &ast_out) {
  antlr4::ANTLRInputStream input(fin);
  MXLexer lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  tokens.fill();
  MXParser parser(&tokens);
  parser.removeErrorListeners();
  MXErrorListener error_listener;
  parser.addErrorListener(&error_listener);
  antlr4::tree::ParseTree *tree = parser.mxprog();
  if (!error_listener.IsOk()) throw SemanticError("Fatal error: syntax error", 1);
  Visitor visitor;
  std::shared_ptr<ASTNodeBase> ast = BuildAST(&visitor, tree);
  ast_out = CheckAndDecorate(ast);
}