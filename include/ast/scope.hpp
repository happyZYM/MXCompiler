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

 protected:
  ScopeBase *parent;  // cannot use std::shared_ptr<ScopeBase> because of circular dependency
  virtual bool VariableNameAvailable(const std::string &name, int ttl) = 0;
  virtual bool add_variable(const std::string &name, const ExprTypeInfo &type) = 0;
  virtual ExprTypeInfo fetch_varaible(const std::string &name) = 0;
  static inline bool IsKeyWord(const std::string &name) {
    static const std::unordered_set<std::string> keywords = {"void", "bool",  "int",   "string",   "new",   "class",
                                                             "null", "true",  "false", "this",     "if",    "else",
                                                             "for",  "while", "break", "continue", "return"};
    return keywords.find(name) != keywords.end();
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
      throw SemanticError("Variable cannot be void", 1);
    }
    if (std::holds_alternative<ArrayType>(type) && std::get<ArrayType>(type).has_base_type &&
        std::get<ArrayType>(type).basetype == "void") {
      throw SemanticError("Variable cannot be void", 1);
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
  std::unordered_map<std::string, ExprTypeInfo> member_variables;
  std::unordered_map<std::string, std::shared_ptr<FunctionScope>> member_functions;
  bool add_variable(const std::string &name, const ExprTypeInfo &type) override {
    if (!VariableNameAvailable(name, 0)) {
      return false;
    }
    if (std::holds_alternative<IdentifierType>(type) && std::get<IdentifierType>(type) == "void") {
      throw SemanticError("Variable cannot be void", 1);
    }
    if (std::holds_alternative<ArrayType>(type) && std::get<ArrayType>(type).has_base_type &&
        std::get<ArrayType>(type).basetype == "void") {
      throw SemanticError("Variable cannot be void", 1);
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
  friend std::shared_ptr<class Program_ASTNode> CheckAndDecorate(std::shared_ptr<class Program_ASTNode> src);
  std::unordered_map<std::string, ExprTypeInfo> global_variables;
  std::unordered_map<std::string, std::shared_ptr<FunctionScope>> global_functions;
  std::unordered_map<std::string, std::shared_ptr<ClassDefScope>> classes;
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
      throw SemanticError("Variable cannot be void", 1);
    }
    if (std::holds_alternative<ArrayType>(type) && std::get<ArrayType>(type).has_base_type &&
        std::get<ArrayType>(type).basetype == "void") {
      throw SemanticError("Variable cannot be void", 1);
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
    throw SemanticError("Variable " + name + " not found", 1);
  }

 public:
  GlobalScope() { parent = nullptr; }
};