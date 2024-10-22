#pragma once
#include <cctype>
#include <cstddef>
#include <ios>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include "IR/IR_basic.h"
class RISCVAsmItemBase {
 public:
  RISCVAsmItemBase() = default;
  virtual ~RISCVAsmItemBase() = default;
  virtual void RecursivePrint(std::ostream &os) const = 0;
};
namespace NaiveBackend {
class RISCVConstStrItem : public RISCVAsmItemBase {
 public:
  std::string full_label;
  std::string content;
  RISCVConstStrItem() = default;
  ~RISCVConstStrItem() = default;
  void RecursivePrint(std::ostream &os) const override {
    os << full_label << ":\n";
    os << "    .asciz  \"";
    for (auto c : content) {
      if (c == '\n') {
        os << "\\n";
      } else if (c == '\t') {
        os << "\\t";
      } else if (c == '\"') {
        os << "\\\"";
      } else if (c == '\\') {
        os << "\\\\";
      } else {
        os << c;
      }
    }
    os << "\"\n";
  }
};
class RISCVGlobalVarItem : public RISCVAsmItemBase {
 public:
  std::string full_label;
  RISCVGlobalVarItem() = default;
  ~RISCVGlobalVarItem() = default;
  void RecursivePrint(std::ostream &os) const override {
    os << ".globl  " << full_label << "\n";
    os << ".p2align        2, 0x0\n";
    os << full_label << ":\n";
    os << "    .word   0\n";
  }
};
class RISCVFuncItem : public RISCVAsmItemBase {
 public:
  std::string full_label;
  std::vector<std::string> code_lines;
  RISCVFuncItem() = default;
  ~RISCVFuncItem() = default;
  void RecursivePrint(std::ostream &os) const override {
    os << ".globl  " << full_label << "\n";
    os << ".p2align        2, 0x0\n";
    os << full_label << ":\n";
    for (auto &line : code_lines) {
      os << line << "\n";
    }
  }
};
class RISCVProgItem : public RISCVAsmItemBase {
 public:
  std::vector<std::shared_ptr<RISCVConstStrItem>> const_strs;
  std::vector<std::shared_ptr<RISCVGlobalVarItem>> global_vars;
  std::vector<std::shared_ptr<RISCVFuncItem>> funcs;
  RISCVProgItem() = default;
  ~RISCVProgItem() = default;
  void RecursivePrint(std::ostream &os) const override {
    os << ".section .rodata\n";
    for (auto &item : const_strs) {
      item->RecursivePrint(os);
    }
    os << ".section .sbss\n";
    for (auto &item : global_vars) {
      item->RecursivePrint(os);
    }
    os << ".section .text\n";
    for (auto &item : funcs) {
      item->RecursivePrint(os);
    }
  }
};
class FuncLayout {
 public:
  std::unordered_map<std::string, size_t> local_items;
  std::unordered_map<std::string, size_t> arg_offset;
  size_t cur_pos;
  size_t total_frame_size;  // should align to 16 bytes

  FuncLayout() : cur_pos(8), total_frame_size(16) {}
  void AllocateItem(const std::string &name, size_t sz, size_t num = 1) {
    if (local_items.find(name) != local_items.end()) throw std::runtime_error("Local item already exists");
    if (cur_pos % sz != 0) {
      cur_pos += sz - cur_pos % sz;
    }
    cur_pos += sz * num;
    local_items[name] = cur_pos;
    total_frame_size = ((cur_pos + 15) / 16) * 16;
    std::cerr << "allocating stack memory for " << name << " at " << cur_pos << std::endl;
  }
  size_t QueryOffeset(const std::string &name) {
    if (local_items.find(name) == local_items.end()) throw std::runtime_error("Local item not found");
    return local_items[name];
  }
  size_t QueryFrameSize() const { return total_frame_size; }
};

inline void GenerateReadAccess(std::string val, size_t bytes, std::string output_reg, FuncLayout &layout,
                               std::vector<std::string> &code_lines) {
  if (val.size() > 4 && val.substr(val.size() - 4, 4) == ".val") {
    // parameter
    if (layout.arg_offset.find(val) == layout.arg_offset.end()) {
      throw std::runtime_error("Unknown argument with name=" + val);
    }
    size_t offset = layout.arg_offset.at(val);
    if (offset < 8) {
      std::string src_reg = "a" + std::to_string(offset);
      code_lines.push_back("mv " + output_reg + ", " + src_reg);
    } else {
      size_t spilled_offset = (offset - 8) * 4;  // just*4, which is different from the real riscv
      std::string cmd;
      if (bytes == 1)
        cmd = "lb";
      else if (bytes == 4)
        cmd = "lw";
      else
        throw std::runtime_error("Unknown bytes");
      cmd += " " + output_reg + ", " + std::to_string(spilled_offset) + "(s0)";
      code_lines.push_back(cmd);
    }
  } else if (val.size() > 13 && val.substr(0, 13) == "@.var.global.") {
    // global variable address keeper
    std::string label_in_asm = val.substr(1, val.size() - 1);
    code_lines.push_back("la " + output_reg + ", " + label_in_asm);
  } else if (val.size() > 12 && val.substr(0, 12) == "%.var.local.") {
    // local variable address keeper
    size_t offset = layout.QueryOffeset(val);
    if (offset < 2048) {
      code_lines.push_back("addi " + output_reg + ", s0, -" + std::to_string(offset));
    } else {
      code_lines.push_back("li " + output_reg + ", -" + std::to_string(offset));
      code_lines.push_back("add " + output_reg + ", s0, " + output_reg);
    }
  } else if (val.size() > 10 && val.substr(0, 10) == "%.var.tmp.") {
    // tmp variable, not address keeper
    size_t offset = layout.QueryOffeset(val);
    if (bytes == 1) {
      if (offset < 2048) {
        code_lines.push_back("lb " + output_reg + ", -" + std::to_string(offset) + "(s0)");
      } else {
        code_lines.push_back("li " + output_reg + ", -" + std::to_string(offset));
        code_lines.push_back("add " + output_reg + ", s0, " + output_reg);
        code_lines.push_back("lb " + output_reg + ", 0(" + output_reg + ")");
      }
    } else if (bytes == 4) {
      if (offset < 2048) {
        code_lines.push_back("lw " + output_reg + ", -" + std::to_string(offset) + "(s0)");
      } else {
        code_lines.push_back("li " + output_reg + ", -" + std::to_string(offset));
        code_lines.push_back("add " + output_reg + ", s0, " + output_reg);
        code_lines.push_back("lw " + output_reg + ", 0(" + output_reg + ")");
      }
    } else {
      throw std::runtime_error("Unknown bytes");
    }
  } else if (val.size() > 6 && val.substr(0, 6) == "@.str.") {
    code_lines.push_back("la " + output_reg + ", " + val.substr(1, val.size() - 1));
  } else {
    throw std::runtime_error("Unknown variable type with name=" + val);
  }
}
inline void StoreImmToReg(int imm, std::string reg, std::vector<std::string> &code_lines) {
  // if (imm >= 2048) {
  //   code_lines.push_back("lui " + reg + ", " + std::to_string(imm >> 12));
  //   code_lines.push_back("ori " + reg + ", " + reg + ", " + std::to_string(imm & 0x7ff));
  // } else {
  //   code_lines.push_back("ori " + reg + ", x0, " + std::to_string(imm));
  // }
  code_lines.push_back("li " + reg + ", " + std::to_string(imm));
}
inline void IRVar2RISCVReg(std::string val, size_t bytes, std::string output_reg, FuncLayout &layout,
                           std::vector<std::string> &code_lines) {
  if (val[0] == '-') {
    if (val == "-1") {
      StoreImmToReg(-1, output_reg, code_lines);
      return;
    }
    throw std::runtime_error("Negative imm in IR is not supported");
  }
  if (val == "null") {
    StoreImmToReg(0, output_reg, code_lines);
  } else if (std::isdigit(val[0])) {
    StoreImmToReg(std::stoull(val), output_reg, code_lines);
  } else {
    GenerateReadAccess(val, bytes, output_reg, layout, code_lines);
  }
}
inline void GenerateWriteAccess(std::string val, size_t bytes, std::string data_reg, FuncLayout &layout,
                                std::vector<std::string> &code_lines) {
  if (val.size() > 4 && val.substr(val.size() - 4, 4) == ".val") {
    // parameter
    throw std::runtime_error("Cannot write to a parameter");
  } else if (val.size() > 13 && val.substr(0, 13) == "@.var.global.") {
    // global variable address keeper
    throw std::runtime_error("Cannot write to a global variable address keeper");
  } else if (val.size() > 12 && val.substr(0, 12) == "%.var.local.") {
    // local variable address keeper
    throw std::runtime_error("Cannot write to a local variable address keeper");
  } else if (val.size() > 10 && val.substr(0, 10) == "%.var.tmp.") {
    // tmp variable, not address keeper
    size_t offset = layout.QueryOffeset(val);
    if (bytes == 1) {
      if (offset < 2048) {
        code_lines.push_back("sb " + data_reg + ", -" + std::to_string(offset) + "(s0)");
      } else {
        code_lines.push_back("li t0, -" + std::to_string(offset));
        code_lines.push_back("add t0, s0, t0");
        code_lines.push_back("sb " + data_reg + ", 0(t0)");
      }
    } else if (bytes == 4) {
      if (offset < 2048) {
        code_lines.push_back("sw " + data_reg + ", -" + std::to_string(offset) + "(s0)");
      } else {
        code_lines.push_back("li t0, -" + std::to_string(offset));
        code_lines.push_back("add t0, s0, t0");
        code_lines.push_back("sw " + data_reg + ", 0(t0)");
      }
    } else {
      throw std::runtime_error("Unknown bytes");
    }
  } else {
    throw std::runtime_error("Unknown variable type with name=" + val);
  }
}
inline size_t CalcSize(const LLVMType &tp) {
  if (std::holds_alternative<LLVMIRIntType>(tp)) {
    auto &int_tp = std::get<LLVMIRIntType>(tp);
    return (int_tp.bits + 7) / 8;
  } else if (std::holds_alternative<LLVMIRPTRType>(tp)) {
    return 4;
  } else if (std::holds_alternative<LLVMVOIDType>(tp)) {
    throw std::runtime_error("Cannot calculate size of void type");
    return 0;
  } else if (std::holds_alternative<LLVMIRCLASSTYPE>(tp)) {
    throw std::runtime_error("Cannot calculate size of class type");
  } else
    throw std::runtime_error("Unknown type");
}
}  // namespace NaiveBackend

void GenerateNaiveASM(std::ostream &os, std::shared_ptr<ModuleItem> prog);