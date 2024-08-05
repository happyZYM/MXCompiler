
// Generated from MXLexer.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  MXLexer : public antlr4::Lexer {
public:
  enum {
    INT = 1, VOID = 2, IF = 3, ELSE = 4, RETURN = 5, PLUS = 6, MINUS = 7, 
    MULTIPLY = 8, DIVIDE = 9, ASSIGN = 10, LPAREN = 11, RPAREN = 12, LBRACE = 13, 
    RBRACE = 14, SEMICOLON = 15, ID = 16, INT_LITERAL = 17, WS = 18, COMMENT = 19
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

