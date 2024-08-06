
// Generated from MXParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  MXParser : public antlr4::Parser {
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

  enum {
    RuleMxprog = 0, RuleFunction_def = 1, RuleClass_def = 2, RuleClass_var_def = 3, 
    RuleClass_constructor = 4, RuleSuite = 5, RuleStatement = 6, RuleDefine_statement = 7, 
    RuleExpr = 8, RuleBasic_expr = 9, RuleFormatted_string = 10, RuleConstant = 11, 
    RuleType = 12
  };

  explicit MXParser(antlr4::TokenStream *input);

  MXParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~MXParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class MxprogContext;
  class Function_defContext;
  class Class_defContext;
  class Class_var_defContext;
  class Class_constructorContext;
  class SuiteContext;
  class StatementContext;
  class Define_statementContext;
  class ExprContext;
  class Basic_exprContext;
  class Formatted_stringContext;
  class ConstantContext;
  class TypeContext; 

  class  MxprogContext : public antlr4::ParserRuleContext {
  public:
    MxprogContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<Class_defContext *> class_def();
    Class_defContext* class_def(size_t i);
    std::vector<Define_statementContext *> define_statement();
    Define_statementContext* define_statement(size_t i);
    std::vector<Function_defContext *> function_def();
    Function_defContext* function_def(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MxprogContext* mxprog();

  class  Function_defContext : public antlr4::ParserRuleContext {
  public:
    Function_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    SuiteContext *suite();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_defContext* function_def();

  class  Class_defContext : public antlr4::ParserRuleContext {
  public:
    Class_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CLASS();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    antlr4::tree::TerminalNode *SEMICOLON();
    std::vector<Class_var_defContext *> class_var_def();
    Class_var_defContext* class_var_def(size_t i);
    std::vector<Class_constructorContext *> class_constructor();
    Class_constructorContext* class_constructor(size_t i);
    std::vector<Function_defContext *> function_def();
    Function_defContext* function_def(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Class_defContext* class_def();

  class  Class_var_defContext : public antlr4::ParserRuleContext {
  public:
    Class_var_defContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    antlr4::tree::TerminalNode *SEMICOLON();
    std::vector<antlr4::tree::TerminalNode *> LBRACKET();
    antlr4::tree::TerminalNode* LBRACKET(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RBRACKET();
    antlr4::tree::TerminalNode* RBRACKET(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Class_var_defContext* class_var_def();

  class  Class_constructorContext : public antlr4::ParserRuleContext {
  public:
    Class_constructorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    SuiteContext *suite();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Class_constructorContext* class_constructor();

  class  SuiteContext : public antlr4::ParserRuleContext {
  public:
    SuiteContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SuiteContext* suite();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> SEMICOLON();
    antlr4::tree::TerminalNode* SEMICOLON(size_t i);
    std::vector<Define_statementContext *> define_statement();
    Define_statementContext* define_statement(size_t i);
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    antlr4::tree::TerminalNode *ELSE();
    antlr4::tree::TerminalNode *WHILE();
    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *BREAK();
    antlr4::tree::TerminalNode *CONTINUE();
    antlr4::tree::TerminalNode *RETURN();
    SuiteContext *suite();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  Define_statementContext : public antlr4::ParserRuleContext {
  public:
    Define_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    antlr4::tree::TerminalNode *SEMICOLON();
    std::vector<antlr4::tree::TerminalNode *> LBRACKET();
    antlr4::tree::TerminalNode* LBRACKET(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RBRACKET();
    antlr4::tree::TerminalNode* RBRACKET(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ASSIGN();
    antlr4::tree::TerminalNode* ASSIGN(size_t i);
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Define_statementContext* define_statement();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Basic_exprContext *basic_expr();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SELF_PLUS();
    antlr4::tree::TerminalNode *SELF_MINUS();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *LNOT();
    antlr4::tree::TerminalNode *BNOT();
    antlr4::tree::TerminalNode *NEW();
    antlr4::tree::TerminalNode *ID();
    std::vector<antlr4::tree::TerminalNode *> LBRACKET();
    antlr4::tree::TerminalNode* LBRACKET(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RBRACKET();
    antlr4::tree::TerminalNode* RBRACKET(size_t i);
    ConstantContext *constant();
    antlr4::tree::TerminalNode *MULTIPLY();
    antlr4::tree::TerminalNode *DIVIDE();
    antlr4::tree::TerminalNode *MOD();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *ARS();
    antlr4::tree::TerminalNode *ALS();
    antlr4::tree::TerminalNode *GN();
    antlr4::tree::TerminalNode *GE();
    antlr4::tree::TerminalNode *LN();
    antlr4::tree::TerminalNode *LE();
    antlr4::tree::TerminalNode *NE();
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *BAND();
    antlr4::tree::TerminalNode *BXOR();
    antlr4::tree::TerminalNode *BOR();
    antlr4::tree::TerminalNode *LAND();
    antlr4::tree::TerminalNode *LOR();
    antlr4::tree::TerminalNode *QUESTION_MARK();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *ASSIGN();
    antlr4::tree::TerminalNode *DOT();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprContext* expr();
  ExprContext* expr(int precedence);
  class  Basic_exprContext : public antlr4::ParserRuleContext {
  public:
    Basic_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *THIS();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    Formatted_stringContext *formatted_string();
    ConstantContext *constant();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Basic_exprContext* basic_expr();

  class  Formatted_stringContext : public antlr4::ParserRuleContext {
  public:
    Formatted_stringContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FORMAT_STRING_WHOLE();
    antlr4::tree::TerminalNode *FORMAT_STRING_HEAD();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *FORMAT_STRING_TAIL();
    std::vector<antlr4::tree::TerminalNode *> FORMAT_STRING_BODY();
    antlr4::tree::TerminalNode* FORMAT_STRING_BODY(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Formatted_stringContext* formatted_string();

  class  ConstantContext : public antlr4::ParserRuleContext {
  public:
    ConstantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TRUE();
    antlr4::tree::TerminalNode *FALSE();
    antlr4::tree::TerminalNode *INT_LITERAL();
    antlr4::tree::TerminalNode *STRING_LITERAL();
    antlr4::tree::TerminalNode *NULL_();
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<ConstantContext *> constant();
    ConstantContext* constant(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstantContext* constant();

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT();
    antlr4::tree::TerminalNode *BOOL();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *VOID();
    antlr4::tree::TerminalNode *ID();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeContext* type();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool exprSempred(ExprContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

