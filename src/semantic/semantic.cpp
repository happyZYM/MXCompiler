#include "semantic.h"
#include <iostream>
#include "MXLexer.h"
#include "MXParser.h"
#include "antlr4-runtime.h"
#include "ast/ast.h"
#include "ast/astnode_visitor.h"
#include "visitor.h"

class MXErrorListener : public antlr4::BaseErrorListener {
  bool no_problem;

 public:
  MXErrorListener() : no_problem(true) {}
  void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line,
                   size_t charPositionInLine, const std::string &msg, std::exception_ptr e) override {
    // std::cerr << "line " << line << ":" << charPositionInLine << " AT " << offendingSymbol->getText() << ": " << msg
    //           << std::endl;
    no_problem = false;
  }
  bool IsOk() { return no_problem; }
};
std::shared_ptr<Program_ASTNode> BuildAST(Visitor *visitor, antlr4::tree::ParseTree *tree) {
  return std::any_cast<std::shared_ptr<Program_ASTNode>>(visitor->visit(tree));
}
std::shared_ptr<Program_ASTNode> CheckAndDecorate(std::shared_ptr<Program_ASTNode> src) {
  auto global_scope = std::dynamic_pointer_cast<GlobalScope>(src->current_scope);
  if (global_scope->global_functions.find("main") == global_scope->global_functions.end()) {
    throw SemanticError("No main() function", 1);
  } else {
    const auto &main_schema = global_scope->global_functions["main"]->schema;
    if ((!std::holds_alternative<IdentifierType>(main_schema.return_type)) ||
        std::get<IdentifierType>(main_schema.return_type) != "int" || main_schema.arguments.size() != 0) {
      throw SemanticError("main() function should be int main()", 1);
    }
  }
  ASTSemanticCheckVisitor visitor;
  visitor.global_scope = global_scope;
  global_scope->classes["string"] = std::make_shared<ClassDefScope>();
  global_scope->classes["string"]->member_functions["length"] = std::make_shared<FunctionScope>();
  global_scope->classes["string"]->member_functions["length"]->schema.return_type = "int";
  global_scope->classes["string"]->member_functions["substring"] = std::make_shared<FunctionScope>();
  global_scope->classes["string"]->member_functions["substring"]->schema.return_type = "string";
  global_scope->classes["string"]->member_functions["substring"]->schema.arguments = {{"int", "left"},
                                                                                      {"int", "right"}};
  global_scope->classes["string"]->member_functions["parseInt"] = std::make_shared<FunctionScope>();
  global_scope->classes["string"]->member_functions["parseInt"]->schema.return_type = "int";
  global_scope->classes["string"]->member_functions["ord"] = std::make_shared<FunctionScope>();
  global_scope->classes["string"]->member_functions["ord"]->schema.return_type = "int";
  global_scope->classes["string"]->member_functions["ord"]->schema.arguments = {{"int", "pos"}};
  global_scope->global_functions["print"] = std::make_shared<FunctionScope>();
  global_scope->global_functions["print"]->schema.return_type = "void";
  global_scope->global_functions["print"]->schema.arguments = {{"string", "str"}};
  global_scope->global_functions["println"] = std::make_shared<FunctionScope>();
  global_scope->global_functions["println"]->schema.return_type = "void";
  global_scope->global_functions["println"]->schema.arguments = {{"string", "str"}};
  global_scope->global_functions["printInt"] = std::make_shared<FunctionScope>();
  global_scope->global_functions["printInt"]->schema.return_type = "void";
  global_scope->global_functions["printInt"]->schema.arguments = {{"int", "n"}};
  global_scope->global_functions["printlnInt"] = std::make_shared<FunctionScope>();
  global_scope->global_functions["printlnInt"]->schema.return_type = "void";
  global_scope->global_functions["printlnInt"]->schema.arguments = {{"int", "n"}};
  global_scope->global_functions["getString"] = std::make_shared<FunctionScope>();
  global_scope->global_functions["getString"]->schema.return_type = "string";
  global_scope->global_functions["getInt"] = std::make_shared<FunctionScope>();
  global_scope->global_functions["getInt"]->schema.return_type = "int";
  global_scope->global_functions["toString"] = std::make_shared<FunctionScope>();
  global_scope->global_functions["toString"]->schema.return_type = "string";
  global_scope->global_functions["toString"]->schema.arguments = {{"int", "n"}};
  visitor.visit(src.get());
  return src;
}

void SemanticCheck(std::istream &fin, std::shared_ptr<Program_ASTNode> &ast_out) {
  antlr4::ANTLRInputStream input(fin);
  MXLexer lexer(&input);
  MXErrorListener error_listener;
  lexer.removeErrorListeners();
  lexer.addErrorListener(&error_listener);
  antlr4::CommonTokenStream tokens(&lexer);
  tokens.fill();
  if (!error_listener.IsOk()) throw SemanticError("Invalid Identifier", 1);
  MXParser parser(&tokens);
  parser.removeErrorListeners();
  parser.addErrorListener(&error_listener);
  antlr4::tree::ParseTree *tree = parser.mxprog();
  if (!error_listener.IsOk()) throw SemanticError("Invalid Identifier", 1);
  Visitor visitor;
  std::shared_ptr<Program_ASTNode> ast = BuildAST(&visitor, tree);
  ast_out = CheckAndDecorate(ast);
}