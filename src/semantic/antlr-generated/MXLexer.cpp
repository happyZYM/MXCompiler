
// Generated from MXLexer.g4 by ANTLR 4.13.2


#include "MXLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct MXLexerStaticData final {
  MXLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MXLexerStaticData(const MXLexerStaticData&) = delete;
  MXLexerStaticData(MXLexerStaticData&&) = delete;
  MXLexerStaticData& operator=(const MXLexerStaticData&) = delete;
  MXLexerStaticData& operator=(MXLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag mxlexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<MXLexerStaticData> mxlexerLexerStaticData = nullptr;

void mxlexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (mxlexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(mxlexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<MXLexerStaticData>(
    std::vector<std::string>{
      "INT", "VOID", "IF", "ELSE", "RETURN", "PLUS", "MINUS", "MULTIPLY", 
      "DIVIDE", "ASSIGN", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "SEMICOLON", 
      "ID", "INT_LITERAL", "WS", "COMMENT"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
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
  	4,0,19,113,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,1,0,1,0,1,0,1,0,1,1,1,1,
  	1,1,1,1,1,1,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,
  	4,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,
  	12,1,13,1,13,1,14,1,14,1,15,1,15,5,15,86,8,15,10,15,12,15,89,9,15,1,16,
  	4,16,92,8,16,11,16,12,16,93,1,17,4,17,97,8,17,11,17,12,17,98,1,17,1,17,
  	1,18,1,18,1,18,1,18,5,18,107,8,18,10,18,12,18,110,9,18,1,18,1,18,0,0,
  	19,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,
  	14,29,15,31,16,33,17,35,18,37,19,1,0,5,3,0,65,90,95,95,97,122,4,0,48,
  	57,65,90,95,95,97,122,1,0,48,57,3,0,9,10,13,13,32,32,2,0,10,10,13,13,
  	116,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,
  	1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,
  	0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,
  	0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,1,39,1,0,0,0,3,43,1,0,0,0,5,48,
  	1,0,0,0,7,51,1,0,0,0,9,56,1,0,0,0,11,63,1,0,0,0,13,65,1,0,0,0,15,67,1,
  	0,0,0,17,69,1,0,0,0,19,71,1,0,0,0,21,73,1,0,0,0,23,75,1,0,0,0,25,77,1,
  	0,0,0,27,79,1,0,0,0,29,81,1,0,0,0,31,83,1,0,0,0,33,91,1,0,0,0,35,96,1,
  	0,0,0,37,102,1,0,0,0,39,40,5,105,0,0,40,41,5,110,0,0,41,42,5,116,0,0,
  	42,2,1,0,0,0,43,44,5,118,0,0,44,45,5,111,0,0,45,46,5,105,0,0,46,47,5,
  	100,0,0,47,4,1,0,0,0,48,49,5,105,0,0,49,50,5,102,0,0,50,6,1,0,0,0,51,
  	52,5,101,0,0,52,53,5,108,0,0,53,54,5,115,0,0,54,55,5,101,0,0,55,8,1,0,
  	0,0,56,57,5,114,0,0,57,58,5,101,0,0,58,59,5,116,0,0,59,60,5,117,0,0,60,
  	61,5,114,0,0,61,62,5,110,0,0,62,10,1,0,0,0,63,64,5,43,0,0,64,12,1,0,0,
  	0,65,66,5,45,0,0,66,14,1,0,0,0,67,68,5,42,0,0,68,16,1,0,0,0,69,70,5,47,
  	0,0,70,18,1,0,0,0,71,72,5,61,0,0,72,20,1,0,0,0,73,74,5,40,0,0,74,22,1,
  	0,0,0,75,76,5,41,0,0,76,24,1,0,0,0,77,78,5,123,0,0,78,26,1,0,0,0,79,80,
  	5,125,0,0,80,28,1,0,0,0,81,82,5,59,0,0,82,30,1,0,0,0,83,87,7,0,0,0,84,
  	86,7,1,0,0,85,84,1,0,0,0,86,89,1,0,0,0,87,85,1,0,0,0,87,88,1,0,0,0,88,
  	32,1,0,0,0,89,87,1,0,0,0,90,92,7,2,0,0,91,90,1,0,0,0,92,93,1,0,0,0,93,
  	91,1,0,0,0,93,94,1,0,0,0,94,34,1,0,0,0,95,97,7,3,0,0,96,95,1,0,0,0,97,
  	98,1,0,0,0,98,96,1,0,0,0,98,99,1,0,0,0,99,100,1,0,0,0,100,101,6,17,0,
  	0,101,36,1,0,0,0,102,103,5,47,0,0,103,104,5,47,0,0,104,108,1,0,0,0,105,
  	107,8,4,0,0,106,105,1,0,0,0,107,110,1,0,0,0,108,106,1,0,0,0,108,109,1,
  	0,0,0,109,111,1,0,0,0,110,108,1,0,0,0,111,112,6,18,0,0,112,38,1,0,0,0,
  	5,0,87,93,98,108,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  mxlexerLexerStaticData = std::move(staticData);
}

}

MXLexer::MXLexer(CharStream *input) : Lexer(input) {
  MXLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *mxlexerLexerStaticData->atn, mxlexerLexerStaticData->decisionToDFA, mxlexerLexerStaticData->sharedContextCache);
}

MXLexer::~MXLexer() {
  delete _interpreter;
}

std::string MXLexer::getGrammarFileName() const {
  return "MXLexer.g4";
}

const std::vector<std::string>& MXLexer::getRuleNames() const {
  return mxlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& MXLexer::getChannelNames() const {
  return mxlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& MXLexer::getModeNames() const {
  return mxlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& MXLexer::getVocabulary() const {
  return mxlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView MXLexer::getSerializedATN() const {
  return mxlexerLexerStaticData->serializedATN;
}

const atn::ATN& MXLexer::getATN() const {
  return *mxlexerLexerStaticData->atn;
}




void MXLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  mxlexerLexerInitialize();
#else
  ::antlr4::internal::call_once(mxlexerLexerOnceFlag, mxlexerLexerInitialize);
#endif
}
