
// Generated from MXParser.g4 by ANTLR 4.13.2


#include "MXParserVisitor.h"

#include "MXParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct MXParserStaticData final {
  MXParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MXParserStaticData(const MXParserStaticData&) = delete;
  MXParserStaticData(MXParserStaticData&&) = delete;
  MXParserStaticData& operator=(const MXParserStaticData&) = delete;
  MXParserStaticData& operator=(MXParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag mxparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<MXParserStaticData> mxparserParserStaticData = nullptr;

void mxparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (mxparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(mxparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<MXParserStaticData>(
    std::vector<std::string>{
      "mxprog", "function", "type", "block", "statement", "expression", 
      "returnStmt", "ifStmt"
    },
    std::vector<std::string>{
      "", "'int'", "'void'", "'if'", "'else'", "'return'", "'+'", "'-'", 
      "'*'", "'/'", "'='", "'('", "')'", "'{'", "'}'", "';'"
    },
    std::vector<std::string>{
      "", "INT", "VOID", "IF", "ELSE", "RETURN", "PLUS", "MINUS", "MULTIPLY", 
      "DIVIDE", "ASSIGN", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "SEMICOLON", 
      "ID", "INT_LITERAL", "WS", "COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,19,81,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,7,
  	7,7,1,0,5,0,18,8,0,10,0,12,0,21,9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	2,1,2,1,3,1,3,5,3,35,8,3,10,3,12,3,38,9,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,
  	3,4,47,8,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,56,8,5,1,5,1,5,1,5,5,5,61,
  	8,5,10,5,12,5,64,9,5,1,6,1,6,3,6,68,8,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,
  	7,1,7,3,7,79,8,7,1,7,0,1,10,8,0,2,4,6,8,10,12,14,0,2,1,0,1,2,1,0,6,9,
  	81,0,19,1,0,0,0,2,24,1,0,0,0,4,30,1,0,0,0,6,32,1,0,0,0,8,46,1,0,0,0,10,
  	55,1,0,0,0,12,65,1,0,0,0,14,71,1,0,0,0,16,18,3,2,1,0,17,16,1,0,0,0,18,
  	21,1,0,0,0,19,17,1,0,0,0,19,20,1,0,0,0,20,22,1,0,0,0,21,19,1,0,0,0,22,
  	23,5,0,0,1,23,1,1,0,0,0,24,25,3,4,2,0,25,26,5,16,0,0,26,27,5,11,0,0,27,
  	28,5,12,0,0,28,29,3,6,3,0,29,3,1,0,0,0,30,31,7,0,0,0,31,5,1,0,0,0,32,
  	36,5,13,0,0,33,35,3,8,4,0,34,33,1,0,0,0,35,38,1,0,0,0,36,34,1,0,0,0,36,
  	37,1,0,0,0,37,39,1,0,0,0,38,36,1,0,0,0,39,40,5,14,0,0,40,7,1,0,0,0,41,
  	42,3,10,5,0,42,43,5,15,0,0,43,47,1,0,0,0,44,47,3,12,6,0,45,47,3,14,7,
  	0,46,41,1,0,0,0,46,44,1,0,0,0,46,45,1,0,0,0,47,9,1,0,0,0,48,49,6,5,-1,
  	0,49,56,5,17,0,0,50,56,5,16,0,0,51,52,5,11,0,0,52,53,3,10,5,0,53,54,5,
  	12,0,0,54,56,1,0,0,0,55,48,1,0,0,0,55,50,1,0,0,0,55,51,1,0,0,0,56,62,
  	1,0,0,0,57,58,10,2,0,0,58,59,7,1,0,0,59,61,3,10,5,3,60,57,1,0,0,0,61,
  	64,1,0,0,0,62,60,1,0,0,0,62,63,1,0,0,0,63,11,1,0,0,0,64,62,1,0,0,0,65,
  	67,5,5,0,0,66,68,3,10,5,0,67,66,1,0,0,0,67,68,1,0,0,0,68,69,1,0,0,0,69,
  	70,5,15,0,0,70,13,1,0,0,0,71,72,5,3,0,0,72,73,5,11,0,0,73,74,3,10,5,0,
  	74,75,5,12,0,0,75,78,3,8,4,0,76,77,5,4,0,0,77,79,3,8,4,0,78,76,1,0,0,
  	0,78,79,1,0,0,0,79,15,1,0,0,0,7,19,36,46,55,62,67,78
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  mxparserParserStaticData = std::move(staticData);
}

}

MXParser::MXParser(TokenStream *input) : MXParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

MXParser::MXParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  MXParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *mxparserParserStaticData->atn, mxparserParserStaticData->decisionToDFA, mxparserParserStaticData->sharedContextCache, options);
}

MXParser::~MXParser() {
  delete _interpreter;
}

const atn::ATN& MXParser::getATN() const {
  return *mxparserParserStaticData->atn;
}

std::string MXParser::getGrammarFileName() const {
  return "MXParser.g4";
}

const std::vector<std::string>& MXParser::getRuleNames() const {
  return mxparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& MXParser::getVocabulary() const {
  return mxparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView MXParser::getSerializedATN() const {
  return mxparserParserStaticData->serializedATN;
}


//----------------- MxprogContext ------------------------------------------------------------------

MXParser::MxprogContext::MxprogContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MXParser::MxprogContext::EOF() {
  return getToken(MXParser::EOF, 0);
}

std::vector<MXParser::FunctionContext *> MXParser::MxprogContext::function() {
  return getRuleContexts<MXParser::FunctionContext>();
}

MXParser::FunctionContext* MXParser::MxprogContext::function(size_t i) {
  return getRuleContext<MXParser::FunctionContext>(i);
}


size_t MXParser::MxprogContext::getRuleIndex() const {
  return MXParser::RuleMxprog;
}


std::any MXParser::MxprogContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitMxprog(this);
  else
    return visitor->visitChildren(this);
}

MXParser::MxprogContext* MXParser::mxprog() {
  MxprogContext *_localctx = _tracker.createInstance<MxprogContext>(_ctx, getState());
  enterRule(_localctx, 0, MXParser::RuleMxprog);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(19);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MXParser::INT

    || _la == MXParser::VOID) {
      setState(16);
      function();
      setState(21);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(22);
    match(MXParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionContext ------------------------------------------------------------------

MXParser::FunctionContext::FunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MXParser::TypeContext* MXParser::FunctionContext::type() {
  return getRuleContext<MXParser::TypeContext>(0);
}

tree::TerminalNode* MXParser::FunctionContext::ID() {
  return getToken(MXParser::ID, 0);
}

tree::TerminalNode* MXParser::FunctionContext::LPAREN() {
  return getToken(MXParser::LPAREN, 0);
}

tree::TerminalNode* MXParser::FunctionContext::RPAREN() {
  return getToken(MXParser::RPAREN, 0);
}

MXParser::BlockContext* MXParser::FunctionContext::block() {
  return getRuleContext<MXParser::BlockContext>(0);
}


size_t MXParser::FunctionContext::getRuleIndex() const {
  return MXParser::RuleFunction;
}


std::any MXParser::FunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitFunction(this);
  else
    return visitor->visitChildren(this);
}

MXParser::FunctionContext* MXParser::function() {
  FunctionContext *_localctx = _tracker.createInstance<FunctionContext>(_ctx, getState());
  enterRule(_localctx, 2, MXParser::RuleFunction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(24);
    type();
    setState(25);
    match(MXParser::ID);
    setState(26);
    match(MXParser::LPAREN);
    setState(27);
    match(MXParser::RPAREN);
    setState(28);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

MXParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MXParser::TypeContext::INT() {
  return getToken(MXParser::INT, 0);
}

tree::TerminalNode* MXParser::TypeContext::VOID() {
  return getToken(MXParser::VOID, 0);
}


size_t MXParser::TypeContext::getRuleIndex() const {
  return MXParser::RuleType;
}


std::any MXParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

MXParser::TypeContext* MXParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 4, MXParser::RuleType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(30);
    _la = _input->LA(1);
    if (!(_la == MXParser::INT

    || _la == MXParser::VOID)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

MXParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MXParser::BlockContext::LBRACE() {
  return getToken(MXParser::LBRACE, 0);
}

tree::TerminalNode* MXParser::BlockContext::RBRACE() {
  return getToken(MXParser::RBRACE, 0);
}

std::vector<MXParser::StatementContext *> MXParser::BlockContext::statement() {
  return getRuleContexts<MXParser::StatementContext>();
}

MXParser::StatementContext* MXParser::BlockContext::statement(size_t i) {
  return getRuleContext<MXParser::StatementContext>(i);
}


size_t MXParser::BlockContext::getRuleIndex() const {
  return MXParser::RuleBlock;
}


std::any MXParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

MXParser::BlockContext* MXParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 6, MXParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(32);
    match(MXParser::LBRACE);
    setState(36);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 198696) != 0)) {
      setState(33);
      statement();
      setState(38);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(39);
    match(MXParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

MXParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MXParser::ExpressionContext* MXParser::StatementContext::expression() {
  return getRuleContext<MXParser::ExpressionContext>(0);
}

tree::TerminalNode* MXParser::StatementContext::SEMICOLON() {
  return getToken(MXParser::SEMICOLON, 0);
}

MXParser::ReturnStmtContext* MXParser::StatementContext::returnStmt() {
  return getRuleContext<MXParser::ReturnStmtContext>(0);
}

MXParser::IfStmtContext* MXParser::StatementContext::ifStmt() {
  return getRuleContext<MXParser::IfStmtContext>(0);
}


size_t MXParser::StatementContext::getRuleIndex() const {
  return MXParser::RuleStatement;
}


std::any MXParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

MXParser::StatementContext* MXParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 8, MXParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(46);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MXParser::LPAREN:
      case MXParser::ID:
      case MXParser::INT_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(41);
        expression(0);
        setState(42);
        match(MXParser::SEMICOLON);
        break;
      }

      case MXParser::RETURN: {
        enterOuterAlt(_localctx, 2);
        setState(44);
        returnStmt();
        break;
      }

      case MXParser::IF: {
        enterOuterAlt(_localctx, 3);
        setState(45);
        ifStmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

MXParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MXParser::ExpressionContext::INT_LITERAL() {
  return getToken(MXParser::INT_LITERAL, 0);
}

tree::TerminalNode* MXParser::ExpressionContext::ID() {
  return getToken(MXParser::ID, 0);
}

tree::TerminalNode* MXParser::ExpressionContext::LPAREN() {
  return getToken(MXParser::LPAREN, 0);
}

std::vector<MXParser::ExpressionContext *> MXParser::ExpressionContext::expression() {
  return getRuleContexts<MXParser::ExpressionContext>();
}

MXParser::ExpressionContext* MXParser::ExpressionContext::expression(size_t i) {
  return getRuleContext<MXParser::ExpressionContext>(i);
}

tree::TerminalNode* MXParser::ExpressionContext::RPAREN() {
  return getToken(MXParser::RPAREN, 0);
}

tree::TerminalNode* MXParser::ExpressionContext::PLUS() {
  return getToken(MXParser::PLUS, 0);
}

tree::TerminalNode* MXParser::ExpressionContext::MINUS() {
  return getToken(MXParser::MINUS, 0);
}

tree::TerminalNode* MXParser::ExpressionContext::MULTIPLY() {
  return getToken(MXParser::MULTIPLY, 0);
}

tree::TerminalNode* MXParser::ExpressionContext::DIVIDE() {
  return getToken(MXParser::DIVIDE, 0);
}


size_t MXParser::ExpressionContext::getRuleIndex() const {
  return MXParser::RuleExpression;
}


std::any MXParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}


MXParser::ExpressionContext* MXParser::expression() {
   return expression(0);
}

MXParser::ExpressionContext* MXParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  MXParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  MXParser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 10;
  enterRecursionRule(_localctx, 10, MXParser::RuleExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(55);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MXParser::INT_LITERAL: {
        setState(49);
        match(MXParser::INT_LITERAL);
        break;
      }

      case MXParser::ID: {
        setState(50);
        match(MXParser::ID);
        break;
      }

      case MXParser::LPAREN: {
        setState(51);
        match(MXParser::LPAREN);
        setState(52);
        expression(0);
        setState(53);
        match(MXParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(62);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleExpression);
        setState(57);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(58);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 960) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(59);
        expression(3); 
      }
      setState(64);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ReturnStmtContext ------------------------------------------------------------------

MXParser::ReturnStmtContext::ReturnStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MXParser::ReturnStmtContext::RETURN() {
  return getToken(MXParser::RETURN, 0);
}

tree::TerminalNode* MXParser::ReturnStmtContext::SEMICOLON() {
  return getToken(MXParser::SEMICOLON, 0);
}

MXParser::ExpressionContext* MXParser::ReturnStmtContext::expression() {
  return getRuleContext<MXParser::ExpressionContext>(0);
}


size_t MXParser::ReturnStmtContext::getRuleIndex() const {
  return MXParser::RuleReturnStmt;
}


std::any MXParser::ReturnStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitReturnStmt(this);
  else
    return visitor->visitChildren(this);
}

MXParser::ReturnStmtContext* MXParser::returnStmt() {
  ReturnStmtContext *_localctx = _tracker.createInstance<ReturnStmtContext>(_ctx, getState());
  enterRule(_localctx, 12, MXParser::RuleReturnStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(65);
    match(MXParser::RETURN);
    setState(67);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 198656) != 0)) {
      setState(66);
      expression(0);
    }
    setState(69);
    match(MXParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStmtContext ------------------------------------------------------------------

MXParser::IfStmtContext::IfStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MXParser::IfStmtContext::IF() {
  return getToken(MXParser::IF, 0);
}

tree::TerminalNode* MXParser::IfStmtContext::LPAREN() {
  return getToken(MXParser::LPAREN, 0);
}

MXParser::ExpressionContext* MXParser::IfStmtContext::expression() {
  return getRuleContext<MXParser::ExpressionContext>(0);
}

tree::TerminalNode* MXParser::IfStmtContext::RPAREN() {
  return getToken(MXParser::RPAREN, 0);
}

std::vector<MXParser::StatementContext *> MXParser::IfStmtContext::statement() {
  return getRuleContexts<MXParser::StatementContext>();
}

MXParser::StatementContext* MXParser::IfStmtContext::statement(size_t i) {
  return getRuleContext<MXParser::StatementContext>(i);
}

tree::TerminalNode* MXParser::IfStmtContext::ELSE() {
  return getToken(MXParser::ELSE, 0);
}


size_t MXParser::IfStmtContext::getRuleIndex() const {
  return MXParser::RuleIfStmt;
}


std::any MXParser::IfStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitIfStmt(this);
  else
    return visitor->visitChildren(this);
}

MXParser::IfStmtContext* MXParser::ifStmt() {
  IfStmtContext *_localctx = _tracker.createInstance<IfStmtContext>(_ctx, getState());
  enterRule(_localctx, 14, MXParser::RuleIfStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(71);
    match(MXParser::IF);
    setState(72);
    match(MXParser::LPAREN);
    setState(73);
    expression(0);
    setState(74);
    match(MXParser::RPAREN);
    setState(75);
    statement();
    setState(78);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      setState(76);
      match(MXParser::ELSE);
      setState(77);
      statement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool MXParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 5: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool MXParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

void MXParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  mxparserParserInitialize();
#else
  ::antlr4::internal::call_once(mxparserParserOnceFlag, mxparserParserInitialize);
#endif
}
