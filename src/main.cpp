#include <argparse/argparse.hpp>
#include <fstream>
#include <iostream>
#include "semantic/semantic.h"

int main(int argc, char **argv) {
  argparse::ArgumentParser program("mxcompiler");

  program.add_argument("input").help("input file path").required();

  program.add_argument("-o", "--output").help("output file path").nargs(1).required();

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error &err) {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  auto input_file = program.get<std::string>("input");
  auto output_file = program.get<std::string>("output");
  std::ifstream fin(input_file);
  int err_code = SemanticCheck(fin);
  if (err_code != 0) return err_code;

  return 0;
}