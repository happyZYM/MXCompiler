#!/bin/bash
# Get the directory of the script
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
# Change to the script directory
cd "$SCRIPT_DIR"
clang-18 -S -emit-llvm --target=riscv32-unknown-elf -O2 -fno-builtin-printf -fno-builtin-memcpy \
        builtin.c -o builtin_intermediate.ll
sed 's/_builtin_/.builtin./g;s/string_/string./g;s/array_/array./g' builtin_intermediate.ll > builtin.ll
rm builtin_intermediate.ll
llc-18 -march=riscv32 -mattr=+m builtin.ll -o builtin_intermediate.s -O2
sed 's/Lfunc/builtin_Lfunc/g;s/L.str/builtin_L.str/g' builtin_intermediate.s > builtin.s
rm builtin_intermediate.s