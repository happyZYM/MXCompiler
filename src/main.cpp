#include <argparse/argparse.hpp>
#include <fstream>
#include <iostream>
#include "IR/IR.h"
#include "naivebackend/naivebackend.h"
#include "opt/opt.h"
#include "semantic/semantic.h"

int main(int argc, char **argv) {
  argparse::ArgumentParser program("zmxcc");

  program.add_argument("input").help("input file path").required();

  program.add_argument("-o", "--output").help("output file path").nargs(1).required();

  program.add_argument("--naive-IR").help("output unoptimized LLVM IR code").default_value(false).implicit_value(true);

  program.add_argument("--optimize-all").help("enable all optimizations").default_value(false).implicit_value(true);

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error &err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  auto input_file = program.get<std::string>("input");
  auto output_file = program.get<std::string>("output");
  bool output_naive_ir = program.get<bool>("--naive-IR");
  bool optimize_all = program.get<bool>("--optimize-all");

  std::ifstream fin(input_file);
  std::ofstream fout(output_file);
  std::shared_ptr<Program_ASTNode> ast;

  try {
    SemanticCheck(fin, ast);
    auto IR = BuildIR(ast);

    if (output_naive_ir) {
      IR->RecursivePrint(fout);
      return 0;
    }
    if (!optimize_all) {
      GenerateNaiveASM(fout, IR);
    } else {
      auto IR_with_out_allocas = Mem2Reg(IR);
      IR_with_out_allocas->RecursivePrint(fout);
      auto IR_with_out_phis = PhiEliminate(IR_with_out_allocas);
      // IR_with_out_phis->RecursivePrint(fout);
      auto alloced_code = RegAlloc(IR_with_out_phis);
    }
  } catch (const SemanticError &err) {
    std::cout << err.what() << std::endl;
    return err.GetErrorCode();
  } catch (const std::exception &err) {
    std::cout << "Unknown error: " << err.what() << std::endl;
    return 254;
  } catch (...) {
    std::cout << "Unknown error without message" << std::endl;
    return 255;
  }
  return 0;
}