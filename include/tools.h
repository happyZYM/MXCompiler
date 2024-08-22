#pragma once
#include <bits/types/struct_sched_param.h>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <variant>
#include <vector>
enum class ASTNodeType {
  // Expression nodes
  NewArrayExpr,
  NewConstructExpr,
  NewExpr,
  MemberVariableAccessExpr,
  MemberFunctionAccessExpr,
  IndexExpr,
  SuffixExpr,
  PrefixExpr,
  OppositeExpr,
  LNotExpr,
  BNotExpr,
  MDMExpr,
  PMExpr,
  RLExpr,
  GGLLExpr,
  NEExpr,
  BAndExpr,
  BXorExpr,
  BOrExpr,
  LAndExpr,
  LOrExpr,
  TernaryExpr,
  AssignExpr,
  ThisExpr,
  ParenExpr,
  IDExpr,
  FunctionCallExpr,
  FormattedStringExpr,
  ConstantExpr,

  // Statement nodes
  EmptyStatement,
  DefinitionStatement,
  ExprStatement,
  IfStatement,
  WhileStatement,
  ForStatement,
  JmpStatement,
  SuiteStatement,

  // Structural nodes
  FuncDef,
  Constructor,
  ClassVariable,
  ClassDef,
  Program
};

class SemanticError : public std::exception {
  std::string msg;
  int error_code;

 public:
  SemanticError(const std::string &msg, int error_code) : msg(msg), error_code(error_code) {}
  const char *what() const noexcept override { return msg.c_str(); }
  int GetErrorCode() const { return error_code; }
};

using IdentifierType = std::string;
struct ArrayType {
  bool has_base_type;
  IdentifierType basetype;
  size_t level;
};
inline bool operator==(const ArrayType &l, const ArrayType &r) {
  if (!r.has_base_type) {
    return l.level >= r.level;
  }
  return l.has_base_type == r.has_base_type && l.basetype == r.basetype && l.level == r.level;
}
using ExprTypeInfo = std::variant<IdentifierType, ArrayType>;

inline bool operator==(const ExprTypeInfo &l, const ExprTypeInfo &r) {
  if (std::holds_alternative<IdentifierType>(r) && std::get<IdentifierType>(r) == "null") {
    if (std::holds_alternative<IdentifierType>(l)) {
      std::string l_type = std::get<IdentifierType>(l);
      if (l_type == "int" || l_type == "bool" || l_type == "string") {
        return false;
      }
      return true;
    }
    return true;
  }
  if (std::holds_alternative<IdentifierType>(l)) {
    bool x = std::holds_alternative<IdentifierType>(r);
    std::string a = std::get<IdentifierType>(l);
    std::string b = std::get<IdentifierType>(r);
    return std::holds_alternative<IdentifierType>(r) && std::get<IdentifierType>(l) == std::get<IdentifierType>(r);
  }
  if (std::holds_alternative<ArrayType>(l)) {
    bool x = std::holds_alternative<ArrayType>(r);
    return std::holds_alternative<ArrayType>(r) && std::get<ArrayType>(l) == std::get<ArrayType>(r);
  }
  throw std::runtime_error("something strange happened");
}
inline bool operator!=(const ExprTypeInfo &l, const ExprTypeInfo &r) { return !(l == r); }
class LLVMIRIntType {
 public:
  size_t bits;
  LLVMIRIntType() = default;
  LLVMIRIntType(size_t bits) : bits(bits) {}
};
struct LLVMIRPTRType {};
struct LLVMVOIDType {};
struct LLVMIRCLASSTYPE {
  std::string class_name_full;
};
using LLVMType = std::variant<LLVMIRIntType, LLVMIRPTRType, LLVMVOIDType, LLVMIRCLASSTYPE>;
class IRClassInfo {
 public:
  std::string class_name_raw;           // This data must be provided by user
  std::vector<size_t> member_var_size;  // This data must be provided by user. Each of them is the size of a member
                                        // variable, which must be in [1,4]
  std::unordered_map<std::string, size_t> member_var_offset;  // This data must be provided by user
  std::vector<size_t> member_var_pos_after_align;
  size_t class_size_after_align;
  void ArrangeSpace() {
    size_t cur_pos = 0;
    size_t align_size = 1;
    for (size_t cur_size : member_var_size) {
      if (cur_size != 1 && cur_size != 4) throw std::runtime_error("Invalid member variable size");
      if (cur_pos % cur_size == 0) {
        member_var_pos_after_align.push_back(cur_pos);
        cur_pos += cur_size;
      } else {
        cur_pos += cur_size - (cur_pos % cur_size);
        member_var_pos_after_align.push_back(cur_pos);
        cur_pos += cur_size;
      }
      if (cur_size > align_size) align_size = cur_size;
      if (cur_pos % align_size != 0) cur_pos += align_size - (cur_pos % align_size);
      class_size_after_align = cur_pos;
    }
  }
  std::string GenerateFullName() { return "%.class." + class_name_raw; }
};
class IRVariableInfo {
 public:
  enum class VariableType { global_variable, local_variable, member_variable };
  std::string class_name;
  std::string variable_name_raw;
  size_t scope_id;
  uint8_t variable_type;  // 0: global, 1: local, 2: member, 3: argument
  LLVMType ty;
  std::string GenerateFullName() {
    if (variable_type == 2) {
      throw std::runtime_error("Member variable should not be used in this function");
    } else if (variable_type == 0) {
      return "@.var.global." + variable_name_raw + ".addrkp";
    } else if (variable_type == 1) {
      return "%.var.local." + std::to_string(scope_id) + "." + variable_name_raw + ".addrkp";
    } else if (variable_type == 3) {
      return "%.var.local." + std::to_string(scope_id) + "." + variable_name_raw + ".val";
    } else {
      throw std::runtime_error("Invalid scope id");
    }
  }
};

inline LLVMType Type_AST2LLVM(const ExprTypeInfo &src) {
  if (std::holds_alternative<ArrayType>(src)) return LLVMIRPTRType();
  std::string tname = std::get<IdentifierType>(src);
  if (tname == "bool") return LLVMIRIntType(1);
  if (tname == "int") return LLVMIRIntType(32);
  if (tname == "void") return LLVMVOIDType();
  return LLVMIRPTRType();
}

inline std::string StringLiteralDeEscape(const std::string src) {
  std::stringstream ss;
  for (size_t i = 1; i < src.size() - 1; i++) {
    if (src[i] != '\\')
      ss << src[i];
    else {
      i++;
      if (src[i] == 'n')
        ss << '\n';
      else if (src[i] == 'r')
        ss << '\r';
      else if (src[i] == 't')
        ss << '\t';
      else if (src[i] == '\\')
        ss << '\\';
      else if (src[i] == '\'')
        ss << '\'';
      else if (src[i] == '\"')
        ss << '\"';
      else if (src[i] == '0')
        ss << '\0';
      else
        throw std::runtime_error("Invalid escape character");
    }
  }
  return ss.str();
}