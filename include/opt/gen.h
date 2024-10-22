#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "IR/IR_basic.h"
#include "cfg.h"
#include "liveanalysis.h"

namespace OptBackend {
class RISCVAsmItemBase {
 public:
  RISCVAsmItemBase() = default;
  virtual ~RISCVAsmItemBase() = default;
  virtual void RecursivePrint(std::ostream &os) const = 0;
};
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

  FuncLayout() : cur_pos(12), total_frame_size(16) {}
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

inline void StoreImmToReg(int imm, std::string reg, std::vector<std::string> &code_lines) {
  code_lines.push_back("li " + reg + ", " + std::to_string(imm));
}

void GenerateOptASM(std::ostream &os, std::shared_ptr<ModuleItem> prog);

extern std::string cur_block_label_for_phi;

std::string AllocateTmpReg(std::vector<std::string> &available_tmp_regs);

std::string ExtractRegName(const std::string &raw);

void FetchValueToReg(std::string original_val, std::string &out_reg, FuncLayout &layout,
                     std::vector<std::string> &code_lines, std::vector<std::string> &available_tmp_regs);

void WriteToSpilledVar(std::string val, std::string reg, FuncLayout &layout, std::vector<std::string> &code_lines,
                       std::vector<std::string> &available_tmp_regs);
size_t CalcSize(const LLVMType &tp);
void GenerateASM(std::shared_ptr<ActionItem> act, std::vector<std::string> &code_lines, FuncLayout &layout,
                 const std::unordered_map<std::string, IRClassInfo> &low_level_class_info);
}  // namespace OptBackend