#pragma once
#include <ios>
#include <memory>
#include <string>
#include <variant>
#include <vector>
#include "ast/astnode.h"
struct LLVMIRIntType {
  size_t bits;
};
struct LLVMIRPTRType {};
struct LLVMIRCLASSTYPE {};
using LLVMType = std::variant<LLVMIRIntType, LLVMIRPTRType, LLVMIRCLASSTYPE>;
class LLVMIRItemBase {
 public:
  LLVMIRItemBase() = default;
  virtual ~LLVMIRItemBase() = default;
  virtual void RecursivePrint(std::ostream &os) const;
};

class TypeDefItem : public LLVMIRItemBase {
 public:
  void RecursivePrint(std::ostream &os) const { ; }
};
class GlobalVarDefItem : public LLVMIRItemBase {
  LLVMType type;
  std::string name;

 public:
  void RecursivePrint(std::ostream &os) const { ; }
};
class ActionItem : public LLVMIRItemBase {
 public:
  void RecursivePrint(std::ostream &os) const { ; }
};
class JMPActionItem : public ActionItem {
  std::string label;
 public:
  void RecursivePrint(std::ostream &os) const { ; }
};
class BRAction: public JMPActionItem {
  std::string cond;
  std::string true_label;
  std::string false_label;
 public:
  void RecursivePrint(std::ostream &os) const { ; }
};
class UNConditionJMPAction: public JMPActionItem {
  std::string label;
 public:
  void RecursivePrint(std::ostream &os) const { ; }
};
class RETAction : public JMPActionItem {
  std::string value;
 public:
  void RecursivePrint(std::ostream &os) const { ; }
};
class BinaryOperationAction : public ActionItem {
  std::string op;
  std::string lhs;
  std::string rhs;
  std::string result;
  LLVMType type;
 public:
  void RecursivePrint(std::ostream &os) const { ; }
};
class AllocaAction : public ActionItem {
  std::string name;
  LLVMType type;
  size_t num;
 public:
  void RecursivePrint(std::ostream &os) const { ; }
};
class LoadAction : public ActionItem {
  std::string result;
  LLVMType ty;
  std::string ptr;
 public:
  void RecursivePrint(std::ostream &os) const { ; }
};
class StoreAction : public ActionItem {
  LLVMType ty;
  std::string value;
  std::string ptr;
 public:
  void RecursivePrint(std::ostream &os) const { ; }
};
class GetElementPtrAction : public ActionItem {
  std::string result;
  LLVMType ty;
  std::string ptr;
  std::vector<std::string> indices;
 public:
  void RecursivePrint(std::ostream &os) const { ; }
};
class ICMPAction : public ActionItem {
  std::string op;
  std::string lhs;
  std::string rhs;
  std::string result;
  LLVMType ty;
 public:
  void RecursivePrint(std::ostream &os) const { ; }
};
class BlockItem : public LLVMIRItemBase {
  std::string label;
  std::vector<std::shared_ptr<ActionItem>> actions;
  std::shared_ptr<JMPActionItem> exit_action;
 public:
  void RecursivePrint(std::ostream &os) const { ; }
};
class FunctionDefItem : public LLVMIRItemBase {
  std::vector<std::shared_ptr<BlockItem>> basic_blocks;

 public:
  void RecursivePrint(std::ostream &os) const {
    for (auto &item : basic_blocks) {
      item->RecursivePrint(os);
      os << '\n';
    }
  }
};
class ModuleItem : public LLVMIRItemBase {
  std::vector<std::shared_ptr<TypeDefItem>> type_defs;
  std::vector<std::shared_ptr<GlobalVarDefItem>> global_var_defs;
  std::vector<std::shared_ptr<FunctionDefItem>> function_defs;

 public:
  void RecursivePrint(std::ostream &os) const {
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