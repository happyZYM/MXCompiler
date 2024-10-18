#pragma once
#include <cstddef>
#include <ios>
#include <list>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include "ast/astnode.h"
#include "tools.h"

class LLVMIRItemBase {
 public:
  LLVMIRItemBase() = default;
  virtual ~LLVMIRItemBase() = default;
  virtual void RecursivePrint(std::ostream &os) const = 0;
};

class TypeDefItem : public LLVMIRItemBase {
  friend class IRBuilder;
  std::string class_name_raw;
  std::vector<LLVMType> elements;

 public:
  TypeDefItem() = default;
  void RecursivePrint(std::ostream &os) const {
    os << "%.class." << class_name_raw;
    os << " = type {";
    for (size_t i = 0; i < elements.size(); i++) {
      if (std::holds_alternative<LLVMIRIntType>(elements[i])) {
        os << "i" << std::get<LLVMIRIntType>(elements[i]).bits;
      } else if (std::holds_alternative<LLVMIRPTRType>(elements[i])) {
        os << "ptr";
      } else if (std::holds_alternative<LLVMVOIDType>(elements[i])) {
        os << "void";
      } else if (std::holds_alternative<LLVMIRCLASSTYPE>(elements[i])) {
        throw std::runtime_error("In MX* language, class types are referenced by pointers");
      }
      if (i != elements.size() - 1) {
        os << ",";
      }
    }
    os << "}\n";
  }
};
class GlobalVarDefItem : public LLVMIRItemBase {
  friend class IRBuilder;
  friend void GenerateNaiveASM(std::ostream &os, std::shared_ptr<ModuleItem> prog);
  LLVMType type;
  std::string name_raw;

 public:
  GlobalVarDefItem() = default;
  void RecursivePrint(std::ostream &os) const {
    std::string name_full = "@.var.global." + name_raw + ".addrkp";
    os << name_full << " = global ";
    if (std::holds_alternative<LLVMIRIntType>(type)) {
      os << "i" << std::get<LLVMIRIntType>(type).bits << " 0\n";
    } else if (std::holds_alternative<LLVMIRPTRType>(type)) {
      os << "ptr null\n";
    } else {
      throw std::runtime_error("something strange happened");
    }
  }
};
class ActionItem : public LLVMIRItemBase {};
class JMPActionItem : public ActionItem {
 public:
  std::shared_ptr<class PhiItem> corresponding_phi;
};
namespace NaiveBackend {
void ScanForVar(class FuncLayout &layout, std::shared_ptr<ActionItem> action,
                const std::unordered_map<std::string, IRClassInfo> &low_level_class_info);
void GenerateASM(std::shared_ptr<ActionItem> act, std::vector<std::string> &code_lines, FuncLayout &layout,
                 const std::unordered_map<std::string, IRClassInfo> &low_level_class_info, bool process_phi);
}  // namespace NaiveBackend
class BRAction : public JMPActionItem {
 public:
  std::string cond;
  std::string true_label_full;
  std::string false_label_full;

  BRAction() = default;
  void RecursivePrint(std::ostream &os) const {
    os << "br i1 " << cond << ", label %" << true_label_full << ", label %" << false_label_full << "\n";
  }
};
class UNConditionJMPAction : public JMPActionItem {
  friend class IRBuilder;
  friend class FunctionDefItem;
  friend void GenerateNaiveASM(std::ostream &os, std::shared_ptr<ModuleItem> prog);
  friend void NaiveBackend::GenerateASM(std::shared_ptr<ActionItem> act, std::vector<std::string> &code_lines,
                                        NaiveBackend::FuncLayout &layout,
                                        const std::unordered_map<std::string, IRClassInfo> &low_level_class_info,
                                        bool process_phi);
  friend class CFGType BuildCFGForFunction(const std::shared_ptr<class FunctionDefItem> &func);
  std::string label_full;

 public:
  UNConditionJMPAction() = default;
  void RecursivePrint(std::ostream &os) const { os << "br label %" << label_full << "\n"; }
};
class RETAction : public JMPActionItem {
 public:
  LLVMType type;
  std::string value;

  RETAction() = default;
  void RecursivePrint(std::ostream &os) const {
    if (std::holds_alternative<LLVMVOIDType>(type)) {
      os << "ret void\n";
    } else if (std::holds_alternative<LLVMIRIntType>(type)) {
      os << "ret i" << std::get<LLVMIRIntType>(type).bits << " " << value << "\n";
    } else if (std::holds_alternative<LLVMIRPTRType>(type)) {
      os << "ret ptr " << value << "\n";
    } else {
      throw std::runtime_error("something strange happened");
    }
  }
};

class BinaryOperationAction : public ActionItem {
 public:
  std::string op;
  std::string operand1_full;
  std::string operand2_full;
  std::string result_full;
  LLVMType type;

  BinaryOperationAction() = default;
  void RecursivePrint(std::ostream &os) const {
    os << result_full << " = " << op << " ";
    if (std::holds_alternative<LLVMIRIntType>(type)) {
      os << "i" << std::get<LLVMIRIntType>(type).bits;
    } else if (std::holds_alternative<LLVMIRPTRType>(type)) {
      os << "ptr";
    } else if (std::holds_alternative<LLVMVOIDType>(type)) {
      os << "void";
    } else if (std::holds_alternative<LLVMIRCLASSTYPE>(type)) {
      throw std::runtime_error("In MX* language, class types are referenced by pointers");
    }
    os << " " << operand1_full << ", " << operand2_full << "\n";
  }
};
class AllocaAction : public ActionItem {
 public:
  std::string name_full;
  LLVMType type;
  size_t num;

  AllocaAction() : num(1){};
  void RecursivePrint(std::ostream &os) const {
    os << name_full << " = alloca ";
    if (std::holds_alternative<LLVMIRIntType>(type)) {
      os << "i" << std::get<LLVMIRIntType>(type).bits;
    } else if (std::holds_alternative<LLVMIRPTRType>(type)) {
      os << "ptr";
    } else {
      throw std::runtime_error("something strange happened");
    }
    if (num > 1) {
      os << ", i32 " << num;
    }
    os << "\n";
  }
};
class LoadAction : public ActionItem {
 public:
  std::string result_full;
  LLVMType ty;
  std::string ptr_full;

  LoadAction() = default;
  void RecursivePrint(std::ostream &os) const {
    os << result_full << " = load ";
    if (std::holds_alternative<LLVMIRIntType>(ty)) {
      os << "i" << std::get<LLVMIRIntType>(ty).bits;
    } else if (std::holds_alternative<LLVMIRPTRType>(ty)) {
      os << "ptr";
    } else {
      throw std::runtime_error("something strange happened");
    }
    os << ", ptr " << ptr_full << '\n';
  }
};
class StoreAction : public ActionItem {
 public:
  LLVMType ty;
  std::string value_full;
  std::string ptr_full;

  StoreAction() = default;
  void RecursivePrint(std::ostream &os) const {
    os << "store ";
    if (std::holds_alternative<LLVMIRIntType>(ty)) {
      os << "i" << std::get<LLVMIRIntType>(ty).bits;
    } else if (std::holds_alternative<LLVMIRPTRType>(ty)) {
      os << "ptr";
    } else {
      throw std::runtime_error("something strange happened");
    }
    os << ' ' << value_full << ", ptr " << ptr_full << '\n';
  }
};
class GetElementPtrAction : public ActionItem {
 public:
  std::string result_full;
  LLVMType ty;
  std::string ptr_full;
  std::vector<std::string> indices;

  GetElementPtrAction() = default;
  void RecursivePrint(std::ostream &os) const {
    os << result_full << " = getelementptr ";
    if (std::holds_alternative<LLVMIRIntType>(ty)) {
      os << "i" << std::get<LLVMIRIntType>(ty).bits;
    } else if (std::holds_alternative<LLVMIRPTRType>(ty)) {
      os << "ptr";
    } else if (std::holds_alternative<LLVMIRCLASSTYPE>(ty)) {
      os << std::get<LLVMIRCLASSTYPE>(ty).class_name_full;
    } else {
      throw std::runtime_error("something strange happened");
    }
    os << ", ptr " << ptr_full;
    for (auto &index : indices) {
      os << ", i32 " << index;
    }
    os << '\n';
  }
};
class ICMPAction : public ActionItem {
 public:
  std::string op;
  std::string operand1_full;
  std::string operand2_full;
  std::string result_full;
  LLVMType type;

  ICMPAction() = default;
  void RecursivePrint(std::ostream &os) const {
    os << result_full << " = icmp " << op << " ";
    if (std::holds_alternative<LLVMIRIntType>(type)) {
      os << "i" << std::get<LLVMIRIntType>(type).bits;
    } else if (std::holds_alternative<LLVMIRPTRType>(type)) {
      os << "ptr";
    } else {
      throw std::runtime_error("something strange happened");
    }
    os << ' ' << operand1_full << ", " << operand2_full << '\n';
  }
};
class BlockItem : public LLVMIRItemBase {
 public:
  std::string label_full;
  std::unordered_map<std::string, std::shared_ptr<PhiItem>> phi_map;  // this is used to store phi items when optimizing
  std::vector<std::shared_ptr<ActionItem>> actions;
  std::shared_ptr<JMPActionItem> exit_action;

  BlockItem() = default;
  void RecursivePrint(std::ostream &os) const {
    os << label_full << ":\n";
    for (auto &kv : phi_map) {
      std::static_pointer_cast<ActionItem>(kv.second)->RecursivePrint(os);
    }
    for (auto &action : actions) {
      action->RecursivePrint(os);
    }
    if (exit_action) exit_action->RecursivePrint(os);
  }
};
class CallItem : public ActionItem {
 public:
  std::string result_full;
  LLVMType return_type;
  std::string func_name_raw;
  std::vector<LLVMType> args_ty;
  std::vector<std::string> args_val_full;

  CallItem() = default;
  void RecursivePrint(std::ostream &os) const {
    if (std::holds_alternative<LLVMVOIDType>(return_type)) {
      os << "call ";
    } else {
      os << result_full << " = call ";
    }
    if (std::holds_alternative<LLVMIRIntType>(return_type)) {
      os << "i" << std::get<LLVMIRIntType>(return_type).bits;
    } else if (std::holds_alternative<LLVMIRPTRType>(return_type)) {
      os << "ptr";
    } else if (std::holds_alternative<LLVMVOIDType>(return_type)) {
      os << "void";
    } else if (std::holds_alternative<LLVMIRCLASSTYPE>(return_type)) {
      throw std::runtime_error("In MX* language, class types are referenced by pointers");
    }
    os << " @" << func_name_raw << "(";
    for (size_t i = 0; i < args_val_full.size(); i++) {
      auto &ty = args_ty[i];
      if (std::holds_alternative<LLVMIRIntType>(ty)) {
        os << "i" << std::get<LLVMIRIntType>(ty).bits;
      } else if (std::holds_alternative<LLVMIRPTRType>(ty)) {
        os << "ptr";
      } else if (std::holds_alternative<LLVMVOIDType>(ty)) {
        throw std::runtime_error("void type is not allowed in function call");
      } else if (std::holds_alternative<LLVMIRCLASSTYPE>(ty)) {
        throw std::runtime_error("In MX* language, class types are referenced by pointers");
      } else {
        throw std::runtime_error("something strange happened");
      }
      os << ' ' << args_val_full[i];
      if (i != args_val_full.size() - 1) {
        os << ", ";
      }
    }
    os << ")\n";
  }
};

class PhiItem : public ActionItem {
 public:
  std::string result_full;
  LLVMType ty;
  std::vector<std::pair<std::string, std::string>> values;  // (val_i_full, label_i_full)
  PhiItem() = default;
  void RecursivePrint(std::ostream &os) const {
    os << result_full << " = phi ";
    if (std::holds_alternative<LLVMIRIntType>(ty)) {
      os << "i" << std::get<LLVMIRIntType>(ty).bits;
    } else if (std::holds_alternative<LLVMIRPTRType>(ty)) {
      os << "ptr";
    } else {
      throw std::runtime_error("something strange happened");
    }
    os << " ";
    for (size_t i = 0; i < values.size(); i++) {
      os << " [" << values[i].first << ", %" << values[i].second << "]";
      if (i != values.size() - 1) {
        os << ", ";
      }
    }
    os << "\n";
  }
};
class SelectItem : public ActionItem {
 public:
  std::string result_full;
  std::string cond_full;
  std::string true_val_full;
  std::string false_val_full;
  LLVMType ty;

  SelectItem() = default;
  void RecursivePrint(std::ostream &os) const {
    os << result_full << " = select i1 " << cond_full << ", ";
    if (std::holds_alternative<LLVMIRIntType>(ty)) {
      os << "i" << std::get<LLVMIRIntType>(ty).bits;
    } else if (std::holds_alternative<LLVMIRPTRType>(ty)) {
      os << "ptr";
    } else {
      throw std::runtime_error("something strange happened");
    }
    os << " " << true_val_full << ", ";
    if (std::holds_alternative<LLVMIRIntType>(ty)) {
      os << "i" << std::get<LLVMIRIntType>(ty).bits;
    } else if (std::holds_alternative<LLVMIRPTRType>(ty)) {
      os << "ptr";
    } else {
      throw std::runtime_error("something strange happened");
    }
    os << false_val_full << "\n";
  }
};
class FunctionDefItem : public LLVMIRItemBase {
  friend class IRBuilder;
  friend void GenerateNaiveASM(std::ostream &os, std::shared_ptr<ModuleItem> prog);
  friend class CFGType BuildCFGForFunction(const std::shared_ptr<FunctionDefItem> &func);
  LLVMType return_type;
  std::string func_name_raw;
  std::vector<LLVMType> args;
  std::vector<std::string> args_full_name;
  std::shared_ptr<BlockItem> init_block;
  std::vector<std::shared_ptr<BlockItem>> basic_blocks;

 public:
  FunctionDefItem() = default;
  void RecursivePrint(std::ostream &os) const {
    os << "define ";
    if (std::holds_alternative<LLVMIRIntType>(return_type)) {
      os << "i" << std::get<LLVMIRIntType>(return_type).bits;
    } else if (std::holds_alternative<LLVMIRPTRType>(return_type)) {
      os << "ptr";
    } else if (std::holds_alternative<LLVMVOIDType>(return_type)) {
      os << "void";
    } else if (std::holds_alternative<LLVMIRCLASSTYPE>(return_type)) {
      throw std::runtime_error("In MX* language, class types are referenced by pointers");
    }
    os << " @" << func_name_raw << "(";
    for (size_t i = 0; i < args.size(); i++) {
      if (std::holds_alternative<LLVMIRIntType>(args[i])) {
        os << "i" << std::get<LLVMIRIntType>(args[i]).bits;
      } else if (std::holds_alternative<LLVMIRPTRType>(args[i])) {
        os << "ptr";
      } else if (std::holds_alternative<LLVMVOIDType>(args[i])) {
        os << "void";
      } else if (std::holds_alternative<LLVMIRCLASSTYPE>(args[i])) {
        throw std::runtime_error("In MX* language, class types are referenced by pointers");
      }
      os << ' ' << args_full_name[i];
      if (i != args.size() - 1) {
        os << ",";
      }
    }
    os << ")\n{\n";
    if (init_block) init_block->RecursivePrint(os);
    for (auto &item : basic_blocks) {
      item->RecursivePrint(os);
    }
    os << "}\n";
  }
};
class FunctionDeclareItem : public LLVMIRItemBase {
  friend class IRBuilder;
  friend std::shared_ptr<class ModuleItem> BuildIR(std::shared_ptr<Program_ASTNode> src);
  LLVMType return_type;
  std::string func_name_raw;
  std::vector<LLVMType> args;

 public:
  FunctionDeclareItem() = default;
  void RecursivePrint(std::ostream &os) const {
    os << "declare ";
    if (std::holds_alternative<LLVMIRIntType>(return_type)) {
      os << "i" << std::get<LLVMIRIntType>(return_type).bits;
    } else if (std::holds_alternative<LLVMIRPTRType>(return_type)) {
      os << "ptr";
    } else if (std::holds_alternative<LLVMVOIDType>(return_type)) {
      os << "void";
    } else if (std::holds_alternative<LLVMIRCLASSTYPE>(return_type)) {
      throw std::runtime_error("In MX* language, class types are referenced by pointers");
    }
    os << " @" << func_name_raw << "(";
    for (size_t i = 0; i < args.size(); i++) {
      if (std::holds_alternative<LLVMIRIntType>(args[i])) {
        os << "i" << std::get<LLVMIRIntType>(args[i]).bits;
      } else if (std::holds_alternative<LLVMIRPTRType>(args[i])) {
        os << "ptr";
      } else if (std::holds_alternative<LLVMVOIDType>(args[i])) {
        os << "void";
      } else if (std::holds_alternative<LLVMIRCLASSTYPE>(args[i])) {
        throw std::runtime_error("In MX* language, class types are referenced by pointers");
      }
      if (i != args.size() - 1) {
        os << ",";
      }
    }
    os << ")\n";
  }
};
class ConstStrItem : public LLVMIRItemBase {
  friend std::shared_ptr<ModuleItem> BuildIR(std::shared_ptr<Program_ASTNode> src);
  friend void GenerateNaiveASM(std::ostream &os, std::shared_ptr<ModuleItem> prog);
  friend class IRBuilder;
  std::string string_raw;
  size_t const_str_id;
  static std::string Escape(const std::string &src) {
    std::stringstream ss;
    for (auto &ch : src) {
      if (ch == '\n') {
        ss << "\\0A";
      } else if (ch == '\t') {
        ss << "\\09";
      } else if (ch == '\r') {
        ss << "\\0D";
      } else if (ch == '\"') {
        ss << "\\22";
      } else if (ch == '\\') {
        ss << "\\5C";
      } else {
        ss << ch;
      }
    }
    return ss.str();
  }

 public:
  ConstStrItem() = default;
  void RecursivePrint(std::ostream &os) const {
    os << "@.str." << const_str_id << " = private unnamed_addr constant [" << string_raw.size() + 1 << " x i8] c\""
       << Escape(string_raw) << "\\00\"\n";
  }
};
class ModuleItem : public LLVMIRItemBase {
  friend class IRBuilder;
  friend std::shared_ptr<ModuleItem> BuildIR(std::shared_ptr<Program_ASTNode> src);
  friend void GenerateNaiveASM(std::ostream &os, std::shared_ptr<ModuleItem> prog);
  friend std::shared_ptr<ModuleItem> Mem2Reg(std::shared_ptr<ModuleItem> src);
  std::vector<std::shared_ptr<ConstStrItem>> const_strs;
  std::vector<std::shared_ptr<FunctionDeclareItem>> function_declares;
  std::vector<std::shared_ptr<TypeDefItem>> type_defs;
  std::vector<std::shared_ptr<GlobalVarDefItem>> global_var_defs;
  std::vector<std::shared_ptr<FunctionDefItem>> function_defs;
  std::unordered_map<std::string, IRClassInfo> low_level_class_info;

 public:
  ModuleItem() = default;
  void RecursivePrint(std::ostream &os) const {
    for (auto &item : const_strs) {
      item->RecursivePrint(os);
    }
    for (auto &item : function_declares) {
      item->RecursivePrint(os);
    }
    for (auto &item : type_defs) {
      item->RecursivePrint(os);
      os << '\n';
    }
    for (auto &item : global_var_defs) {
      item->RecursivePrint(os);
      os << '\n';
    }
    for (auto &item : function_defs) {
      item->RecursivePrint(os);
      os << '\n';
    }
  }
};