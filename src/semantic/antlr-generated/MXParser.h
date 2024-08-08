
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
    std::vector<antlr4::tree::TerminalNode *> LBRACKET();
    antlr4::tree::TerminalNode* LBRACKET(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RBRACKET();
    antlr4::tree::TerminalNode* RBRACKET(size_t i);
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
   
    StatementContext() = default;
    void copyFrom(StatementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  For_statementContext : public StatementContext {
  public:
    For_statementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<antlr4::tree::TerminalNode *> SEMICOLON();
    antlr4::tree::TerminalNode* SEMICOLON(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    StatementContext *statement();
    std::vector<Define_statementContext *> define_statement();
    Define_statementContext* define_statement(size_t i);
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Suite_statementContext : public StatementContext {
  public:
    Suite_statementContext(StatementContext *ctx);

    SuiteContext *suite();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Expr_statementContext : public StatementContext {
  public:
    Expr_statementContext(StatementContext *ctx);

    ExprContext *expr();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Jmp_statementContext : public StatementContext {
  public:
    Jmp_statementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *BREAK();
    antlr4::tree::TerminalNode *CONTINUE();
    antlr4::tree::TerminalNode *RETURN();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  If_statementContext : public StatementContext {
  public:
    If_statementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    antlr4::tree::TerminalNode *ELSE();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Definition_statementContext : public StatementContext {
  public:
    Definition_statementContext(StatementContext *ctx);

    Define_statementContext *define_statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  While_statementContext : public StatementContext {
  public:
    While_statementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *WHILE();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    StatementContext *statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Empty_statementContext : public StatementContext {
  public:
    Empty_statementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *SEMICOLON();

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
   
    ExprContext() = default;
    void copyFrom(ExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  Ggll_expressionContext : public ExprContext {
  public:
    Ggll_expressionContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *GN();
    antlr4::tree::TerminalNode *GE();
    antlr4::tree::TerminalNode *LN();
    antlr4::tree::TerminalNode *LE();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Bxor_expressionContext : public ExprContext {
  public:
    Bxor_expressionContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *BXOR();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Suffix_expressionContext : public ExprContext {
  public:
    Suffix_expressionContext(ExprContext *ctx);

    ExprContext *expr();
    antlr4::tree::TerminalNode *SELF_PLUS();
    antlr4::tree::TerminalNode *SELF_MINUS();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Land_expressionContext : public ExprContext {
  public:
    Land_expressionContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *LAND();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Pm_expressionContext : public ExprContext {
  public:
    Pm_expressionContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Index_expressionContext : public ExprContext {
  public:
    Index_expressionContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LBRACKET();
    antlr4::tree::TerminalNode* LBRACKET(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RBRACKET();
    antlr4::tree::TerminalNode* RBRACKET(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Opposite_expressionContext : public ExprContext {
  public:
    Opposite_expressionContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *MINUS();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  New_array_expressionContext : public ExprContext {
  public:
    New_array_expressionContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *NEW();
    TypeContext *type();
    std::vector<antlr4::tree::TerminalNode *> LBRACKET();
    antlr4::tree::TerminalNode* LBRACKET(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RBRACKET();
    antlr4::tree::TerminalNode* RBRACKET(size_t i);
    ConstantContext *constant();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Basic_expressionContext : public ExprContext {
  public:
    Basic_expressionContext(ExprContext *ctx);

    Basic_exprContext *basic_expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Access_expressionContext : public ExprContext {
  public:
    Access_expressionContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Band_expressionContext : public ExprContext {
  public:
    Band_expressionContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *BAND();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  New_construct_expressionContext : public ExprContext {
  public:
    New_construct_expressionContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *NEW();
    TypeContext *type();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Ternary_expressionContext : public ExprContext {
  public:
    Ternary_expressionContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *QUESTION_MARK();
    antlr4::tree::TerminalNode *COLON();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Bnot_expressionContext : public ExprContext {
  public:
    Bnot_expressionContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *BNOT();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Lnot_expressionContext : public ExprContext {
  public:
    Lnot_expressionContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *LNOT();
    ExprContext *expr();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Prefix_expressionContext : public ExprContext {
  public:
    Prefix_expressionContext(ExprContext *ctx);

    ExprContext *expr();
    antlr4::tree::TerminalNode *SELF_PLUS();
    antlr4::tree::TerminalNode *SELF_MINUS();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Rl_expressionContext : public ExprContext {
  public:
    Rl_expressionContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *ARS();
    antlr4::tree::TerminalNode *ALS();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Assign_expressionContext : public ExprContext {
  public:
    Assign_expressionContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *ASSIGN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Mdm_expressionContext : public ExprContext {
  public:
    Mdm_expressionContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *MULTIPLY();
    antlr4::tree::TerminalNode *DIVIDE();
    antlr4::tree::TerminalNode *MOD();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  New_expressionContext : public ExprContext {
  public:
    New_expressionContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *NEW();
    TypeContext *type();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Ne_expressionContext : public ExprContext {
  public:
    Ne_expressionContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *NE();
    antlr4::tree::TerminalNode *EQ();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Bor_expressionContext : public ExprContext {
  public:
    Bor_expressionContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *BOR();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Lor_expressionContext : public ExprContext {
  public:
    Lor_expressionContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *LOR();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExprContext* expr();
  ExprContext* expr(int precedence);
  class  Basic_exprContext : public antlr4::ParserRuleContext {
  public:
    Basic_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    Basic_exprContext() = default;
    void copyFrom(Basic_exprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  Paren_exprContext : public Basic_exprContext {
  public:
    Paren_exprContext(Basic_exprContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Constant_exprContext : public Basic_exprContext {
  public:
    Constant_exprContext(Basic_exprContext *ctx);

    ConstantContext *constant();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  This_exprContext : public Basic_exprContext {
  public:
    This_exprContext(Basic_exprContext *ctx);

    antlr4::tree::TerminalNode *THIS();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Id_exprContext : public Basic_exprContext {
  public:
    Id_exprContext(Basic_exprContext *ctx);

    antlr4::tree::TerminalNode *ID();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Formatted_string_exprContext : public Basic_exprContext {
  public:
    Formatted_string_exprContext(Basic_exprContext *ctx);

    Formatted_stringContext *formatted_string();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  Function_call_exprContext : public Basic_exprContext {
  public:
    Function_call_exprContext(Basic_exprContext *ctx);

    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

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

