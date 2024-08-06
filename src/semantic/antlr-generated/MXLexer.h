
// Generated from MXLexer.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  MXLexer : public antlr4::Lexer {
public:
  enum {
    VOID = 1, BOOL = 2, INT = 3, STRING = 4, NEW = 5, CLASS = 6, NULL_ = 7, 
    TRUE = 8, FALSE = 9, THIS = 10, IF = 11, ELSE = 12, FOR = 13, WHILE = 14, 
    BREAK = 15, CONTINUE = 16, RETURN = 17, PLUS = 18, MINUS = 19, MULTIPLY = 20, 
    DIVIDE = 21, MOD = 22, GN = 23, GE = 24, LN = 25, LE = 26, NE = 27, 
    EQ = 28, LAND = 29, LOR = 30, LNOT = 31, ARS = 32, ALS = 33, BAND = 34, 
    BOR = 35, BXOR = 36, BNOT = 37, ASSIGN = 38, SELF_PLUS = 39, SELF_MINUS = 40, 
    DOT = 41, QUESTION_MARK = 42, COLON = 43, LPAREN = 44, RPAREN = 45, 
    LBRACKET = 46, RBRACKET = 47, LBRACE = 48, RBRACE = 49, SEMICOLON = 50, 
    COMMA = 51, FORMAT_STRING_WHOLE = 52, FORMAT_STRING_HEAD = 53, FORMAT_STRING_TAIL = 54, 
    FORMAT_STRING_BODY = 55, ID = 56, INT_LITERAL = 57, STRING_LITERAL = 58, 
    WS = 59, LINE_COMMENT = 60, BLOCK_COMMENT = 61
  };

  explicit MXLexer(antlr4::CharStream *input);

  ~MXLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

