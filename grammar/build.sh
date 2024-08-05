#!/bin/bash
# Get the directory of the script
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
# Change to the script directory
cd "$SCRIPT_DIR"
# Set the output directory
OUTPUT_DIR="../src/semantic/antlr-generated"
# Create the output directory if it doesn't exist
mkdir -p "$OUTPUT_DIR"
# Run ANTLR to generate lexer and parser
antlr4 -Dlanguage=Cpp -no-listener -visitor MXLexer.g4 MXParser.g4 -o "$OUTPUT_DIR"
# Return to the original directory
cd - > /dev/null
