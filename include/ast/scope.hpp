#pragma once
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "tools.h"
class ScopeBase {
  friend class Visitor;
  friend class LocalScope;
  friend class MemberFunctionScope;
  friend class FunctionScope;
  friend class ClassDefScope;
  friend class GlobalScope;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;

 protected:
  ScopeBase *parent;  // cannot use std::shared_ptr<ScopeBase> because of circular dependency
  size_t scope_id;
  virtual bool VariableNameAvailable(const std::string &name, int ttl) = 0;
  virtual bool add_variable(const std::string &name, const ExprTypeInfo &type) = 0;
  virtual ExprTypeInfo fetch_varaible(const std::string &name) = 0;
  virtual IRVariableInfo fetch_variable_for_IR(const std::string &name) = 0;
  static inline bool IsKeyWord(const std::string &name) {
    static const std::unordered_set<std::string> keywords = {"void", "bool",  "int",   "string",   "new",   "class",
                                                             "null", "true",  "false", "this",     "if",    "else",
                                                             "for",  "while", "break", "continue", "return"};
    return keywords.find(name) != keywords.end();
  }

 public:
  ScopeBase() {
    static size_t scope_counter = 0;
    scope_id = scope_counter++;
  }
};
class LocalScope : public ScopeBase {
  friend class Visitor;
  std::unordered_map<std::string, ExprTypeInfo> local_variables;
  bool add_variable(const std::string &name, const ExprTypeInfo &type) override {
    if (!VariableNameAvailable(name, 0)) {
      return false;
    }
    if (std::holds_alternative<IdentifierType>(type) && std::get<IdentifierType>(type) == "void") {
      throw SemanticError("Invalid Type", 1);
    }
    if (std::holds_alternative<ArrayType>(type) && std::get<ArrayType>(type).has_base_type &&
        std::get<ArrayType>(type).basetype == "void") {
      throw SemanticError("Invalid Type", 1);
    }
    local_variables[name] = type;
    return true;
  }
  virtual ExprTypeInfo fetch_varaible(const std::string &name) override {
    if (local_variables.find(name) != local_variables.end()) {
      return local_variables[name];
    }
    return parent->fetch_varaible(name);
  }
  IRVariableInfo fetch_variable_for_IR(const std::string &name) override {
    if (local_variables.find(name) != local_variables.end()) {
      IRVariableInfo res;
      res.variable_name_raw = name;
      res.scope_id = scope_id;
      res.variable_type = 1;
      res.ty = Type_AST2LLVM(local_variables[name]);
      return res;
    }
    return parent->fetch_variable_for_IR(name);
  }
  bool VariableNameAvailable(const std::string &name, int ttl) override {
    if (ttl == 0 && IsKeyWord(name)) {
      return false;
    }
    if (ttl == 0) {
      if (local_variables.find(name) != local_variables.end()) {
        return false;
      }
    }
    return parent->VariableNameAvailable(name, ttl + 1);
  }
};
struct FunctionSchema {
  friend class Visitor;
  ExprTypeInfo return_type;
  std::vector<std::pair<ExprTypeInfo, std::string>> arguments;
};
class FunctionScope : public ScopeBase {
  friend std::shared_ptr<class Program_ASTNode> CheckAndDecorate(std::shared_ptr<class Program_ASTNode> src);
  friend class Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class GlobalScope;
  FunctionSchema schema;
  bool add_variable([[maybe_unused]] const std::string &name, [[maybe_unused]] const ExprTypeInfo &type) override {
    throw std::runtime_error("FunctionScope does not support add_variable");
  }
  virtual ExprTypeInfo fetch_varaible(const std::string &name) override {
    for (const auto &arg : schema.arguments) {
      if (arg.second == name) {
        return arg.first;
      }
    }
    return parent->fetch_varaible(name);
  }
  IRVariableInfo fetch_variable_for_IR(const std::string &name) override {
    for (const auto &arg : schema.arguments) {
      if (arg.second == name) {
        IRVariableInfo res;
        res.variable_name_raw = name;
        res.scope_id = scope_id;
        res.variable_type = 3;
        res.ty = Type_AST2LLVM(arg.first);
        return res;
      }
    }
    return parent->fetch_variable_for_IR(name);
  }
  bool VariableNameAvailable(const std::string &name, int ttl) override {
    if (ttl == 0 && IsKeyWord(name)) {
      return false;
    }
    if (ttl == 1) {
      for (const auto &arg : schema.arguments) {
        if (arg.second == name) {
          return false;
        }
      }
    }
    return parent->VariableNameAvailable(name, ttl + 1);
  }
};
class ClassDefScope : public ScopeBase {
  friend class Visitor;
  friend class GlobalScope;
  friend std::shared_ptr<Program_ASTNode> CheckAndDecorate(std::shared_ptr<Program_ASTNode> src);
  std::unordered_map<std::string, ExprTypeInfo> member_variables;
  std::unordered_map<std::string, std::shared_ptr<FunctionScope>> member_functions;
  IRClassInfo llvm_class_info;
  bool add_variable(const std::string &name, const ExprTypeInfo &type) override {
    if (!VariableNameAvailable(name, 0)) {
      return false;
    }
    if (std::holds_alternative<IdentifierType>(type) && std::get<IdentifierType>(type) == "void") {
      throw SemanticError("Invalid Type", 1);
    }
    if (std::holds_alternative<ArrayType>(type) && std::get<ArrayType>(type).has_base_type &&
        std::get<ArrayType>(type).basetype == "void") {
      throw SemanticError("Invalid Type", 1);
    }
    member_variables[name] = type;
    return true;
  }
  virtual ExprTypeInfo fetch_varaible(const std::string &name) override {
    if (member_variables.find(name) != member_variables.end()) {
      return member_variables[name];
    }
    return parent->fetch_varaible(name);
  }
  IRVariableInfo fetch_variable_for_IR(const std::string &name) override {
    if (member_variables.find(name) != member_variables.end()) {
      IRVariableInfo res;
      res.variable_name_raw = name;
      res.scope_id = scope_id;
      res.variable_type = 2;
      res.ty = Type_AST2LLVM(member_variables[name]);
      return res;
    }
    return parent->fetch_variable_for_IR(name);
  }
  bool add_function(const std::string &name, std::shared_ptr<FunctionScope> ptr) {
    if (IsKeyWord(name)) return false;
    if (member_variables.find(name) != member_variables.end()) {
      return false;
    }
    if (member_functions.find(name) != member_functions.end()) {
      return false;
    }
    member_functions[name] = ptr;
    return true;
  }
  bool VariableNameAvailable(const std::string &name, int ttl) override {
    if (ttl == 0 && IsKeyWord(name)) {
      return false;
    }
    if (ttl == 0) {
      if (member_variables.find(name) != member_variables.end()) {
        return false;
      }
    }
    if (ttl == 0) {
      if (member_functions.find(name) != member_functions.end()) {
        return false;
      }
    }
    return parent->VariableNameAvailable(name, ttl + 1);
  }
};
class GlobalScope : public ScopeBase {
  friend class Visitor;
  friend class ASTSemanticCheckVisitor;
  friend class IRBuilder;
  friend std::shared_ptr<class Program_ASTNode> CheckAndDecorate(std::shared_ptr<class Program_ASTNode> src);
  std::unordered_map<std::string, ExprTypeInfo> global_variables;
  std::unordered_map<std::string, std::shared_ptr<FunctionScope>> global_functions;
  std::unordered_map<std::string, std::shared_ptr<ClassDefScope>> classes;
  ExprTypeInfo FetchClassMemberVariable(const std::string &class_name, const std::string &var_name) {
    if (classes.find(class_name) == classes.end()) {
      throw SemanticError("Undefined Identifier", 1);
    }
    auto ptr = classes[class_name];
    if (ptr->member_variables.find(var_name) == ptr->member_variables.end()) {
      throw SemanticError("Undefined Identifier", 1);
    }
    return ptr->member_variables[var_name];
  }
  FunctionSchema FetchClassMemberFunction(const std::string &class_name, const std::string &func_name) {
    if (classes.find(class_name) == classes.end()) {
      throw SemanticError("Undefined Identifier", 1);
    }
    auto ptr = classes[class_name];
    if (ptr->member_functions.find(func_name) == ptr->member_functions.end()) {
      throw SemanticError("Undefined Identifier", 1);
    }
    return ptr->member_functions[func_name]->schema;
  }
  FunctionSchema FetchFunction(const std::string &name) {
    if (global_functions.find(name) == global_functions.end()) {
      throw SemanticError("Undefined Identifier", 1);
    }
    return global_functions[name]->schema;
  }
  bool add_class(const std::string &name, std::shared_ptr<ClassDefScope> ptr) {
    if (IsKeyWord(name)) return false;
    if (classes.find(name) != classes.end()) {
      return false;
    }
    if (global_functions.find(name) != global_functions.end()) {
      return false;
    }
    if (global_variables.find(name) != global_variables.end()) {
      return false;
    }
    classes[name] = ptr;
    return true;
  }
  bool add_function(const std::string &name, std::shared_ptr<FunctionScope> ptr) {
    if (IsKeyWord(name)) return false;
    if (classes.find(name) != classes.end()) {
      return false;
    }
    if (global_functions.find(name) != global_functions.end()) {
      return false;
    }
    if (global_variables.find(name) != global_variables.end()) {
      return false;
    }
    global_functions[name] = ptr;
    return true;
  }
  bool add_variable(const std::string &name, const ExprTypeInfo &type) override {
    if (!VariableNameAvailable(name, 0)) {
      return false;
    }
    if (std::holds_alternative<IdentifierType>(type) && std::get<IdentifierType>(type) == "void") {
      throw SemanticError("Invalid Type", 1);
    }
    if (std::holds_alternative<ArrayType>(type) && std::get<ArrayType>(type).has_base_type &&
        std::get<ArrayType>(type).basetype == "void") {
      throw SemanticError("Invalid Type", 1);
    }
    global_variables[name] = type;
    return true;
  }
  bool VariableNameAvailable(const std::string &name, [[maybe_unused]] int ttl) override {
    if (ttl == 0 && IsKeyWord(name)) {
      return false;
    }
    if (ttl == 0) {
      if (global_variables.find(name) != global_variables.end()) {
        return false;
      }
    }
    // if (classes.find(name) != classes.end()) {
    //   return false;
    // }
    if (global_functions.find(name) != global_functions.end()) {
      return false;
    }
    return true;
  }
  virtual ExprTypeInfo fetch_varaible(const std::string &name) override {
    if (global_variables.find(name) != global_variables.end()) {
      return global_variables[name];
    }
    throw SemanticError("Undefined Identifier", 1);
  }
  IRVariableInfo fetch_variable_for_IR(const std::string &name) override {
    if (global_variables.find(name) != global_variables.end()) {
      IRVariableInfo res;
      res.variable_name_raw = name;
      res.scope_id = scope_id;
      res.variable_type = 0;
      res.ty = Type_AST2LLVM(global_variables[name]);
      return res;
    }
    return parent->fetch_variable_for_IR(name);
  }

 public:
  GlobalScope() { parent = nullptr; }
};