
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
      "mxprog", "function_def", "class_def", "class_var_def", "class_constructor", 
      "suite", "statement", "define_statement", "expr", "basic_expr", "formatted_string", 
      "constant", "type"
    },
    std::vector<std::string>{
      "", "'void'", "'bool'", "'int'", "'string'", "'new'", "'class'", "'null'", 
      "'true'", "'false'", "'this'", "'if'", "'else'", "'for'", "'while'", 
      "'break'", "'continue'", "'return'", "'+'", "'-'", "'*'", "'/'", "'%'", 
      "'>='", "'>'", "'<='", "'<'", "'!='", "'=='", "'&&'", "'||'", "'!'", 
      "'>>'", "'<<'", "'&'", "'|'", "'^'", "'~'", "'='", "'++'", "'--'", 
      "'.'", "'\\u003F'", "':'", "'('", "')'", "'['", "']'", "'{'", "'}'", 
      "';'", "','"
    },
    std::vector<std::string>{
      "", "VOID", "BOOL", "INT", "STRING", "NEW", "CLASS", "NULL", "TRUE", 
      "FALSE", "THIS", "IF", "ELSE", "FOR", "WHILE", "BREAK", "CONTINUE", 
      "RETURN", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MOD", "GN", "GE", 
      "LN", "LE", "NE", "EQ", "LAND", "LOR", "LNOT", "ARS", "ALS", "BAND", 
      "BOR", "BXOR", "BNOT", "ASSIGN", "SELF_PLUS", "SELF_MINUS", "DOT", 
      "QUESTION_MARK", "COLON", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", 
      "LBRACE", "RBRACE", "SEMICOLON", "COMMA", "FORMAT_STRING_WHOLE", "FORMAT_STRING_HEAD", 
      "FORMAT_STRING_TAIL", "FORMAT_STRING_BODY", "ID", "INT_LITERAL", "STRING_LITERAL", 
      "WS", "LINE_COMMENT", "BLOCK_COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,61,364,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,1,0,1,0,1,0,4,0,30,
  	8,0,11,0,12,0,31,1,0,1,0,1,1,1,1,1,1,5,1,39,8,1,10,1,12,1,42,9,1,1,1,
  	1,1,1,1,1,1,1,1,5,1,49,8,1,10,1,12,1,52,9,1,1,1,1,1,1,1,1,1,1,1,1,1,5,
  	1,60,8,1,10,1,12,1,63,9,1,1,1,1,1,5,1,67,8,1,10,1,12,1,70,9,1,3,1,72,
  	8,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,2,5,2,83,8,2,10,2,12,2,86,9,2,1,
  	2,1,2,1,2,1,3,1,3,1,3,5,3,94,8,3,10,3,12,3,97,9,3,1,3,1,3,1,3,5,3,102,
  	8,3,10,3,12,3,105,9,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,5,1,5,5,5,116,8,5,
  	10,5,12,5,119,9,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,
  	1,6,3,6,135,8,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,3,
  	6,150,8,6,1,6,3,6,153,8,6,1,6,1,6,1,6,3,6,158,8,6,1,6,1,6,1,6,1,6,1,6,
  	1,6,3,6,166,8,6,3,6,168,8,6,1,6,1,6,3,6,172,8,6,1,7,1,7,1,7,5,7,177,8,
  	7,10,7,12,7,180,9,7,1,7,1,7,1,7,3,7,185,8,7,1,7,1,7,1,7,1,7,3,7,191,8,
  	7,5,7,193,8,7,10,7,12,7,196,9,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,3,8,206,
  	8,8,1,8,4,8,209,8,8,11,8,12,8,210,1,8,3,8,214,8,8,1,8,1,8,1,8,1,8,1,8,
  	1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,3,8,231,8,8,1,8,1,8,1,8,1,8,1,
  	8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,
  	1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,
  	8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,5,8,280,8,8,10,8,12,8,283,9,8,3,8,285,8,
  	8,1,8,3,8,288,8,8,1,8,1,8,1,8,1,8,1,8,4,8,295,8,8,11,8,12,8,296,1,8,1,
  	8,5,8,301,8,8,10,8,12,8,304,9,8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,
  	9,1,9,5,9,317,8,9,10,9,12,9,320,9,9,3,9,322,8,9,1,9,1,9,1,9,3,9,327,8,
  	9,1,10,1,10,1,10,1,10,1,10,5,10,334,8,10,10,10,12,10,337,9,10,1,10,1,
  	10,3,10,341,8,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,5,11,352,
  	8,11,10,11,12,11,355,9,11,3,11,357,8,11,1,11,3,11,360,8,11,1,12,1,12,
  	1,12,1,335,1,16,13,0,2,4,6,8,10,12,14,16,18,20,22,24,0,7,1,0,39,40,1,
  	0,20,22,1,0,18,19,1,0,32,33,1,0,23,26,1,0,27,28,2,0,1,4,56,56,429,0,29,
  	1,0,0,0,2,35,1,0,0,0,4,76,1,0,0,0,6,90,1,0,0,0,8,108,1,0,0,0,10,113,1,
  	0,0,0,12,171,1,0,0,0,14,173,1,0,0,0,16,230,1,0,0,0,18,326,1,0,0,0,20,
  	340,1,0,0,0,22,359,1,0,0,0,24,361,1,0,0,0,26,30,3,4,2,0,27,30,3,14,7,
  	0,28,30,3,2,1,0,29,26,1,0,0,0,29,27,1,0,0,0,29,28,1,0,0,0,30,31,1,0,0,
  	0,31,29,1,0,0,0,31,32,1,0,0,0,32,33,1,0,0,0,33,34,5,0,0,1,34,1,1,0,0,
  	0,35,40,3,24,12,0,36,37,5,46,0,0,37,39,5,47,0,0,38,36,1,0,0,0,39,42,1,
  	0,0,0,40,38,1,0,0,0,40,41,1,0,0,0,41,43,1,0,0,0,42,40,1,0,0,0,43,44,5,
  	56,0,0,44,71,5,44,0,0,45,50,3,24,12,0,46,47,5,46,0,0,47,49,5,47,0,0,48,
  	46,1,0,0,0,49,52,1,0,0,0,50,48,1,0,0,0,50,51,1,0,0,0,51,53,1,0,0,0,52,
  	50,1,0,0,0,53,54,5,56,0,0,54,68,1,0,0,0,55,56,5,51,0,0,56,61,3,24,12,
  	0,57,58,5,46,0,0,58,60,5,47,0,0,59,57,1,0,0,0,60,63,1,0,0,0,61,59,1,0,
  	0,0,61,62,1,0,0,0,62,64,1,0,0,0,63,61,1,0,0,0,64,65,5,56,0,0,65,67,1,
  	0,0,0,66,55,1,0,0,0,67,70,1,0,0,0,68,66,1,0,0,0,68,69,1,0,0,0,69,72,1,
  	0,0,0,70,68,1,0,0,0,71,45,1,0,0,0,71,72,1,0,0,0,72,73,1,0,0,0,73,74,5,
  	45,0,0,74,75,3,10,5,0,75,3,1,0,0,0,76,77,5,6,0,0,77,78,5,56,0,0,78,84,
  	5,48,0,0,79,83,3,6,3,0,80,83,3,8,4,0,81,83,3,2,1,0,82,79,1,0,0,0,82,80,
  	1,0,0,0,82,81,1,0,0,0,83,86,1,0,0,0,84,82,1,0,0,0,84,85,1,0,0,0,85,87,
  	1,0,0,0,86,84,1,0,0,0,87,88,5,49,0,0,88,89,5,50,0,0,89,5,1,0,0,0,90,95,
  	3,24,12,0,91,92,5,46,0,0,92,94,5,47,0,0,93,91,1,0,0,0,94,97,1,0,0,0,95,
  	93,1,0,0,0,95,96,1,0,0,0,96,98,1,0,0,0,97,95,1,0,0,0,98,103,5,56,0,0,
  	99,100,5,51,0,0,100,102,5,56,0,0,101,99,1,0,0,0,102,105,1,0,0,0,103,101,
  	1,0,0,0,103,104,1,0,0,0,104,106,1,0,0,0,105,103,1,0,0,0,106,107,5,50,
  	0,0,107,7,1,0,0,0,108,109,5,56,0,0,109,110,5,44,0,0,110,111,5,45,0,0,
  	111,112,3,10,5,0,112,9,1,0,0,0,113,117,5,48,0,0,114,116,3,12,6,0,115,
  	114,1,0,0,0,116,119,1,0,0,0,117,115,1,0,0,0,117,118,1,0,0,0,118,120,1,
  	0,0,0,119,117,1,0,0,0,120,121,5,49,0,0,121,11,1,0,0,0,122,172,5,50,0,
  	0,123,172,3,14,7,0,124,125,3,16,8,0,125,126,5,50,0,0,126,172,1,0,0,0,
  	127,128,5,11,0,0,128,129,5,44,0,0,129,130,3,16,8,0,130,131,5,45,0,0,131,
  	134,3,12,6,0,132,133,5,12,0,0,133,135,3,12,6,0,134,132,1,0,0,0,134,135,
  	1,0,0,0,135,172,1,0,0,0,136,137,5,14,0,0,137,138,5,44,0,0,138,139,3,16,
  	8,0,139,140,5,45,0,0,140,141,3,12,6,0,141,172,1,0,0,0,142,143,5,13,0,
  	0,143,149,5,44,0,0,144,150,3,14,7,0,145,146,3,16,8,0,146,147,5,50,0,0,
  	147,150,1,0,0,0,148,150,5,50,0,0,149,144,1,0,0,0,149,145,1,0,0,0,149,
  	148,1,0,0,0,150,152,1,0,0,0,151,153,3,16,8,0,152,151,1,0,0,0,152,153,
  	1,0,0,0,153,154,1,0,0,0,154,157,5,50,0,0,155,158,3,14,7,0,156,158,3,16,
  	8,0,157,155,1,0,0,0,157,156,1,0,0,0,157,158,1,0,0,0,158,159,1,0,0,0,159,
  	160,5,45,0,0,160,172,3,12,6,0,161,168,5,15,0,0,162,168,5,16,0,0,163,165,
  	5,17,0,0,164,166,3,16,8,0,165,164,1,0,0,0,165,166,1,0,0,0,166,168,1,0,
  	0,0,167,161,1,0,0,0,167,162,1,0,0,0,167,163,1,0,0,0,168,169,1,0,0,0,169,
  	172,5,50,0,0,170,172,3,10,5,0,171,122,1,0,0,0,171,123,1,0,0,0,171,124,
  	1,0,0,0,171,127,1,0,0,0,171,136,1,0,0,0,171,142,1,0,0,0,171,167,1,0,0,
  	0,171,170,1,0,0,0,172,13,1,0,0,0,173,178,3,24,12,0,174,175,5,46,0,0,175,
  	177,5,47,0,0,176,174,1,0,0,0,177,180,1,0,0,0,178,176,1,0,0,0,178,179,
  	1,0,0,0,179,181,1,0,0,0,180,178,1,0,0,0,181,184,5,56,0,0,182,183,5,38,
  	0,0,183,185,3,16,8,0,184,182,1,0,0,0,184,185,1,0,0,0,185,194,1,0,0,0,
  	186,187,5,51,0,0,187,190,5,56,0,0,188,189,5,38,0,0,189,191,3,16,8,0,190,
  	188,1,0,0,0,190,191,1,0,0,0,191,193,1,0,0,0,192,186,1,0,0,0,193,196,1,
  	0,0,0,194,192,1,0,0,0,194,195,1,0,0,0,195,197,1,0,0,0,196,194,1,0,0,0,
  	197,198,5,50,0,0,198,15,1,0,0,0,199,200,6,8,-1,0,200,231,3,18,9,0,201,
  	202,5,5,0,0,202,208,3,24,12,0,203,205,5,46,0,0,204,206,3,16,8,0,205,204,
  	1,0,0,0,205,206,1,0,0,0,206,207,1,0,0,0,207,209,5,47,0,0,208,203,1,0,
  	0,0,209,210,1,0,0,0,210,208,1,0,0,0,210,211,1,0,0,0,211,213,1,0,0,0,212,
  	214,3,22,11,0,213,212,1,0,0,0,213,214,1,0,0,0,214,231,1,0,0,0,215,216,
  	5,5,0,0,216,217,3,24,12,0,217,218,5,44,0,0,218,219,5,45,0,0,219,231,1,
  	0,0,0,220,221,5,5,0,0,221,231,3,24,12,0,222,223,7,0,0,0,223,231,3,16,
  	8,16,224,225,5,19,0,0,225,231,3,16,8,15,226,227,5,31,0,0,227,231,3,16,
  	8,14,228,229,5,37,0,0,229,231,3,16,8,13,230,199,1,0,0,0,230,201,1,0,0,
  	0,230,215,1,0,0,0,230,220,1,0,0,0,230,222,1,0,0,0,230,224,1,0,0,0,230,
  	226,1,0,0,0,230,228,1,0,0,0,231,302,1,0,0,0,232,233,10,12,0,0,233,234,
  	7,1,0,0,234,301,3,16,8,13,235,236,10,11,0,0,236,237,7,2,0,0,237,301,3,
  	16,8,12,238,239,10,10,0,0,239,240,7,3,0,0,240,301,3,16,8,11,241,242,10,
  	9,0,0,242,243,7,4,0,0,243,301,3,16,8,10,244,245,10,8,0,0,245,246,7,5,
  	0,0,246,301,3,16,8,9,247,248,10,7,0,0,248,249,5,34,0,0,249,301,3,16,8,
  	8,250,251,10,6,0,0,251,252,5,36,0,0,252,301,3,16,8,7,253,254,10,5,0,0,
  	254,255,5,35,0,0,255,301,3,16,8,6,256,257,10,4,0,0,257,258,5,29,0,0,258,
  	301,3,16,8,5,259,260,10,3,0,0,260,261,5,30,0,0,261,301,3,16,8,4,262,263,
  	10,2,0,0,263,264,5,42,0,0,264,265,3,16,8,0,265,266,5,43,0,0,266,267,3,
  	16,8,2,267,301,1,0,0,0,268,269,10,1,0,0,269,270,5,38,0,0,270,301,3,16,
  	8,1,271,272,10,19,0,0,272,287,5,41,0,0,273,288,5,56,0,0,274,275,5,56,
  	0,0,275,284,5,44,0,0,276,281,3,16,8,0,277,278,5,51,0,0,278,280,3,16,8,
  	0,279,277,1,0,0,0,280,283,1,0,0,0,281,279,1,0,0,0,281,282,1,0,0,0,282,
  	285,1,0,0,0,283,281,1,0,0,0,284,276,1,0,0,0,284,285,1,0,0,0,285,286,1,
  	0,0,0,286,288,5,45,0,0,287,273,1,0,0,0,287,274,1,0,0,0,288,301,1,0,0,
  	0,289,294,10,18,0,0,290,291,5,46,0,0,291,292,3,16,8,0,292,293,5,47,0,
  	0,293,295,1,0,0,0,294,290,1,0,0,0,295,296,1,0,0,0,296,294,1,0,0,0,296,
  	297,1,0,0,0,297,301,1,0,0,0,298,299,10,17,0,0,299,301,7,0,0,0,300,232,
  	1,0,0,0,300,235,1,0,0,0,300,238,1,0,0,0,300,241,1,0,0,0,300,244,1,0,0,
  	0,300,247,1,0,0,0,300,250,1,0,0,0,300,253,1,0,0,0,300,256,1,0,0,0,300,
  	259,1,0,0,0,300,262,1,0,0,0,300,268,1,0,0,0,300,271,1,0,0,0,300,289,1,
  	0,0,0,300,298,1,0,0,0,301,304,1,0,0,0,302,300,1,0,0,0,302,303,1,0,0,0,
  	303,17,1,0,0,0,304,302,1,0,0,0,305,327,5,10,0,0,306,307,5,44,0,0,307,
  	308,3,16,8,0,308,309,5,45,0,0,309,327,1,0,0,0,310,327,5,56,0,0,311,312,
  	5,56,0,0,312,321,5,44,0,0,313,318,3,16,8,0,314,315,5,51,0,0,315,317,3,
  	16,8,0,316,314,1,0,0,0,317,320,1,0,0,0,318,316,1,0,0,0,318,319,1,0,0,
  	0,319,322,1,0,0,0,320,318,1,0,0,0,321,313,1,0,0,0,321,322,1,0,0,0,322,
  	323,1,0,0,0,323,327,5,45,0,0,324,327,3,20,10,0,325,327,3,22,11,0,326,
  	305,1,0,0,0,326,306,1,0,0,0,326,310,1,0,0,0,326,311,1,0,0,0,326,324,1,
  	0,0,0,326,325,1,0,0,0,327,19,1,0,0,0,328,341,5,52,0,0,329,330,5,53,0,
  	0,330,335,3,16,8,0,331,332,5,55,0,0,332,334,3,16,8,0,333,331,1,0,0,0,
  	334,337,1,0,0,0,335,336,1,0,0,0,335,333,1,0,0,0,336,338,1,0,0,0,337,335,
  	1,0,0,0,338,339,5,54,0,0,339,341,1,0,0,0,340,328,1,0,0,0,340,329,1,0,
  	0,0,341,21,1,0,0,0,342,360,5,8,0,0,343,360,5,9,0,0,344,360,5,57,0,0,345,
  	360,5,58,0,0,346,360,5,7,0,0,347,356,5,48,0,0,348,353,3,22,11,0,349,350,
  	5,51,0,0,350,352,3,22,11,0,351,349,1,0,0,0,352,355,1,0,0,0,353,351,1,
  	0,0,0,353,354,1,0,0,0,354,357,1,0,0,0,355,353,1,0,0,0,356,348,1,0,0,0,
  	356,357,1,0,0,0,357,358,1,0,0,0,358,360,5,49,0,0,359,342,1,0,0,0,359,
  	343,1,0,0,0,359,344,1,0,0,0,359,345,1,0,0,0,359,346,1,0,0,0,359,347,1,
  	0,0,0,360,23,1,0,0,0,361,362,7,6,0,0,362,25,1,0,0,0,41,29,31,40,50,61,
  	68,71,82,84,95,103,117,134,149,152,157,165,167,171,178,184,190,194,205,
  	210,213,230,281,284,287,296,300,302,318,321,326,335,340,353,356,359
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

std::vector<MXParser::Class_defContext *> MXParser::MxprogContext::class_def() {
  return getRuleContexts<MXParser::Class_defContext>();
}

MXParser::Class_defContext* MXParser::MxprogContext::class_def(size_t i) {
  return getRuleContext<MXParser::Class_defContext>(i);
}

std::vector<MXParser::Define_statementContext *> MXParser::MxprogContext::define_statement() {
  return getRuleContexts<MXParser::Define_statementContext>();
}

MXParser::Define_statementContext* MXParser::MxprogContext::define_statement(size_t i) {
  return getRuleContext<MXParser::Define_statementContext>(i);
}

std::vector<MXParser::Function_defContext *> MXParser::MxprogContext::function_def() {
  return getRuleContexts<MXParser::Function_defContext>();
}

MXParser::Function_defContext* MXParser::MxprogContext::function_def(size_t i) {
  return getRuleContext<MXParser::Function_defContext>(i);
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
    setState(29); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(29);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(26);
        class_def();
        break;
      }

      case 2: {
        setState(27);
        define_statement();
        break;
      }

      case 3: {
        setState(28);
        function_def();
        break;
      }

      default:
        break;
      }
      setState(31); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72057594037928030) != 0));
    setState(33);
    match(MXParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Function_defContext ------------------------------------------------------------------

MXParser::Function_defContext::Function_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MXParser::TypeContext *> MXParser::Function_defContext::type() {
  return getRuleContexts<MXParser::TypeContext>();
}

MXParser::TypeContext* MXParser::Function_defContext::type(size_t i) {
  return getRuleContext<MXParser::TypeContext>(i);
}

std::vector<tree::TerminalNode *> MXParser::Function_defContext::ID() {
  return getTokens(MXParser::ID);
}

tree::TerminalNode* MXParser::Function_defContext::ID(size_t i) {
  return getToken(MXParser::ID, i);
}

tree::TerminalNode* MXParser::Function_defContext::LPAREN() {
  return getToken(MXParser::LPAREN, 0);
}

tree::TerminalNode* MXParser::Function_defContext::RPAREN() {
  return getToken(MXParser::RPAREN, 0);
}

MXParser::SuiteContext* MXParser::Function_defContext::suite() {
  return getRuleContext<MXParser::SuiteContext>(0);
}

std::vector<tree::TerminalNode *> MXParser::Function_defContext::LBRACKET() {
  return getTokens(MXParser::LBRACKET);
}

tree::TerminalNode* MXParser::Function_defContext::LBRACKET(size_t i) {
  return getToken(MXParser::LBRACKET, i);
}

std::vector<tree::TerminalNode *> MXParser::Function_defContext::RBRACKET() {
  return getTokens(MXParser::RBRACKET);
}

tree::TerminalNode* MXParser::Function_defContext::RBRACKET(size_t i) {
  return getToken(MXParser::RBRACKET, i);
}

std::vector<tree::TerminalNode *> MXParser::Function_defContext::COMMA() {
  return getTokens(MXParser::COMMA);
}

tree::TerminalNode* MXParser::Function_defContext::COMMA(size_t i) {
  return getToken(MXParser::COMMA, i);
}


size_t MXParser::Function_defContext::getRuleIndex() const {
  return MXParser::RuleFunction_def;
}


std::any MXParser::Function_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitFunction_def(this);
  else
    return visitor->visitChildren(this);
}

MXParser::Function_defContext* MXParser::function_def() {
  Function_defContext *_localctx = _tracker.createInstance<Function_defContext>(_ctx, getState());
  enterRule(_localctx, 2, MXParser::RuleFunction_def);
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
    setState(35);
    type();
    setState(40);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MXParser::LBRACKET) {
      setState(36);
      match(MXParser::LBRACKET);
      setState(37);
      match(MXParser::RBRACKET);
      setState(42);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(43);
    match(MXParser::ID);
    setState(44);
    match(MXParser::LPAREN);
    setState(71);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72057594037927966) != 0)) {
      setState(45);
      type();
      setState(50);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == MXParser::LBRACKET) {
        setState(46);
        match(MXParser::LBRACKET);
        setState(47);
        match(MXParser::RBRACKET);
        setState(52);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(53);
      match(MXParser::ID);
      setState(68);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == MXParser::COMMA) {
        setState(55);
        match(MXParser::COMMA);
        setState(56);
        type();
        setState(61);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == MXParser::LBRACKET) {
          setState(57);
          match(MXParser::LBRACKET);
          setState(58);
          match(MXParser::RBRACKET);
          setState(63);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(64);
        match(MXParser::ID);
        setState(70);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(73);
    match(MXParser::RPAREN);
    setState(74);
    suite();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Class_defContext ------------------------------------------------------------------

MXParser::Class_defContext::Class_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MXParser::Class_defContext::CLASS() {
  return getToken(MXParser::CLASS, 0);
}

tree::TerminalNode* MXParser::Class_defContext::ID() {
  return getToken(MXParser::ID, 0);
}

tree::TerminalNode* MXParser::Class_defContext::LBRACE() {
  return getToken(MXParser::LBRACE, 0);
}

tree::TerminalNode* MXParser::Class_defContext::RBRACE() {
  return getToken(MXParser::RBRACE, 0);
}

tree::TerminalNode* MXParser::Class_defContext::SEMICOLON() {
  return getToken(MXParser::SEMICOLON, 0);
}

std::vector<MXParser::Class_var_defContext *> MXParser::Class_defContext::class_var_def() {
  return getRuleContexts<MXParser::Class_var_defContext>();
}

MXParser::Class_var_defContext* MXParser::Class_defContext::class_var_def(size_t i) {
  return getRuleContext<MXParser::Class_var_defContext>(i);
}

std::vector<MXParser::Class_constructorContext *> MXParser::Class_defContext::class_constructor() {
  return getRuleContexts<MXParser::Class_constructorContext>();
}

MXParser::Class_constructorContext* MXParser::Class_defContext::class_constructor(size_t i) {
  return getRuleContext<MXParser::Class_constructorContext>(i);
}

std::vector<MXParser::Function_defContext *> MXParser::Class_defContext::function_def() {
  return getRuleContexts<MXParser::Function_defContext>();
}

MXParser::Function_defContext* MXParser::Class_defContext::function_def(size_t i) {
  return getRuleContext<MXParser::Function_defContext>(i);
}


size_t MXParser::Class_defContext::getRuleIndex() const {
  return MXParser::RuleClass_def;
}


std::any MXParser::Class_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitClass_def(this);
  else
    return visitor->visitChildren(this);
}

MXParser::Class_defContext* MXParser::class_def() {
  Class_defContext *_localctx = _tracker.createInstance<Class_defContext>(_ctx, getState());
  enterRule(_localctx, 4, MXParser::RuleClass_def);
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
    setState(76);
    match(MXParser::CLASS);
    setState(77);
    match(MXParser::ID);
    setState(78);
    match(MXParser::LBRACE);
    setState(84);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72057594037927966) != 0)) {
      setState(82);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
      case 1: {
        setState(79);
        class_var_def();
        break;
      }

      case 2: {
        setState(80);
        class_constructor();
        break;
      }

      case 3: {
        setState(81);
        function_def();
        break;
      }

      default:
        break;
      }
      setState(86);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(87);
    match(MXParser::RBRACE);
    setState(88);
    match(MXParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Class_var_defContext ------------------------------------------------------------------

MXParser::Class_var_defContext::Class_var_defContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MXParser::TypeContext* MXParser::Class_var_defContext::type() {
  return getRuleContext<MXParser::TypeContext>(0);
}

std::vector<tree::TerminalNode *> MXParser::Class_var_defContext::ID() {
  return getTokens(MXParser::ID);
}

tree::TerminalNode* MXParser::Class_var_defContext::ID(size_t i) {
  return getToken(MXParser::ID, i);
}

tree::TerminalNode* MXParser::Class_var_defContext::SEMICOLON() {
  return getToken(MXParser::SEMICOLON, 0);
}

std::vector<tree::TerminalNode *> MXParser::Class_var_defContext::LBRACKET() {
  return getTokens(MXParser::LBRACKET);
}

tree::TerminalNode* MXParser::Class_var_defContext::LBRACKET(size_t i) {
  return getToken(MXParser::LBRACKET, i);
}

std::vector<tree::TerminalNode *> MXParser::Class_var_defContext::RBRACKET() {
  return getTokens(MXParser::RBRACKET);
}

tree::TerminalNode* MXParser::Class_var_defContext::RBRACKET(size_t i) {
  return getToken(MXParser::RBRACKET, i);
}

std::vector<tree::TerminalNode *> MXParser::Class_var_defContext::COMMA() {
  return getTokens(MXParser::COMMA);
}

tree::TerminalNode* MXParser::Class_var_defContext::COMMA(size_t i) {
  return getToken(MXParser::COMMA, i);
}


size_t MXParser::Class_var_defContext::getRuleIndex() const {
  return MXParser::RuleClass_var_def;
}


std::any MXParser::Class_var_defContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitClass_var_def(this);
  else
    return visitor->visitChildren(this);
}

MXParser::Class_var_defContext* MXParser::class_var_def() {
  Class_var_defContext *_localctx = _tracker.createInstance<Class_var_defContext>(_ctx, getState());
  enterRule(_localctx, 6, MXParser::RuleClass_var_def);
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
    setState(90);
    type();
    setState(95);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MXParser::LBRACKET) {
      setState(91);
      match(MXParser::LBRACKET);
      setState(92);
      match(MXParser::RBRACKET);
      setState(97);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(98);
    match(MXParser::ID);
    setState(103);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MXParser::COMMA) {
      setState(99);
      match(MXParser::COMMA);
      setState(100);
      match(MXParser::ID);
      setState(105);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(106);
    match(MXParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Class_constructorContext ------------------------------------------------------------------

MXParser::Class_constructorContext::Class_constructorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MXParser::Class_constructorContext::ID() {
  return getToken(MXParser::ID, 0);
}

tree::TerminalNode* MXParser::Class_constructorContext::LPAREN() {
  return getToken(MXParser::LPAREN, 0);
}

tree::TerminalNode* MXParser::Class_constructorContext::RPAREN() {
  return getToken(MXParser::RPAREN, 0);
}

MXParser::SuiteContext* MXParser::Class_constructorContext::suite() {
  return getRuleContext<MXParser::SuiteContext>(0);
}


size_t MXParser::Class_constructorContext::getRuleIndex() const {
  return MXParser::RuleClass_constructor;
}


std::any MXParser::Class_constructorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitClass_constructor(this);
  else
    return visitor->visitChildren(this);
}

MXParser::Class_constructorContext* MXParser::class_constructor() {
  Class_constructorContext *_localctx = _tracker.createInstance<Class_constructorContext>(_ctx, getState());
  enterRule(_localctx, 8, MXParser::RuleClass_constructor);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(108);
    match(MXParser::ID);
    setState(109);
    match(MXParser::LPAREN);
    setState(110);
    match(MXParser::RPAREN);
    setState(111);
    suite();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SuiteContext ------------------------------------------------------------------

MXParser::SuiteContext::SuiteContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MXParser::SuiteContext::LBRACE() {
  return getToken(MXParser::LBRACE, 0);
}

tree::TerminalNode* MXParser::SuiteContext::RBRACE() {
  return getToken(MXParser::RBRACE, 0);
}

std::vector<MXParser::StatementContext *> MXParser::SuiteContext::statement() {
  return getRuleContexts<MXParser::StatementContext>();
}

MXParser::StatementContext* MXParser::SuiteContext::statement(size_t i) {
  return getRuleContext<MXParser::StatementContext>(i);
}


size_t MXParser::SuiteContext::getRuleIndex() const {
  return MXParser::RuleSuite;
}


std::any MXParser::SuiteContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitSuite(this);
  else
    return visitor->visitChildren(this);
}

MXParser::SuiteContext* MXParser::suite() {
  SuiteContext *_localctx = _tracker.createInstance<SuiteContext>(_ctx, getState());
  enterRule(_localctx, 10, MXParser::RuleSuite);
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
    setState(113);
    match(MXParser::LBRACE);
    setState(117);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 519340713071865790) != 0)) {
      setState(114);
      statement();
      setState(119);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(120);
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


size_t MXParser::StatementContext::getRuleIndex() const {
  return MXParser::RuleStatement;
}

void MXParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- For_statementContext ------------------------------------------------------------------

tree::TerminalNode* MXParser::For_statementContext::FOR() {
  return getToken(MXParser::FOR, 0);
}

tree::TerminalNode* MXParser::For_statementContext::LPAREN() {
  return getToken(MXParser::LPAREN, 0);
}

std::vector<tree::TerminalNode *> MXParser::For_statementContext::SEMICOLON() {
  return getTokens(MXParser::SEMICOLON);
}

tree::TerminalNode* MXParser::For_statementContext::SEMICOLON(size_t i) {
  return getToken(MXParser::SEMICOLON, i);
}

tree::TerminalNode* MXParser::For_statementContext::RPAREN() {
  return getToken(MXParser::RPAREN, 0);
}

MXParser::StatementContext* MXParser::For_statementContext::statement() {
  return getRuleContext<MXParser::StatementContext>(0);
}

std::vector<MXParser::Define_statementContext *> MXParser::For_statementContext::define_statement() {
  return getRuleContexts<MXParser::Define_statementContext>();
}

MXParser::Define_statementContext* MXParser::For_statementContext::define_statement(size_t i) {
  return getRuleContext<MXParser::Define_statementContext>(i);
}

std::vector<MXParser::ExprContext *> MXParser::For_statementContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::For_statementContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

MXParser::For_statementContext::For_statementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MXParser::For_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitFor_statement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Suite_statementContext ------------------------------------------------------------------

MXParser::SuiteContext* MXParser::Suite_statementContext::suite() {
  return getRuleContext<MXParser::SuiteContext>(0);
}

MXParser::Suite_statementContext::Suite_statementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MXParser::Suite_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitSuite_statement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Expr_statementContext ------------------------------------------------------------------

MXParser::ExprContext* MXParser::Expr_statementContext::expr() {
  return getRuleContext<MXParser::ExprContext>(0);
}

tree::TerminalNode* MXParser::Expr_statementContext::SEMICOLON() {
  return getToken(MXParser::SEMICOLON, 0);
}

MXParser::Expr_statementContext::Expr_statementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MXParser::Expr_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitExpr_statement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Jmp_statementContext ------------------------------------------------------------------

tree::TerminalNode* MXParser::Jmp_statementContext::SEMICOLON() {
  return getToken(MXParser::SEMICOLON, 0);
}

tree::TerminalNode* MXParser::Jmp_statementContext::BREAK() {
  return getToken(MXParser::BREAK, 0);
}

tree::TerminalNode* MXParser::Jmp_statementContext::CONTINUE() {
  return getToken(MXParser::CONTINUE, 0);
}

tree::TerminalNode* MXParser::Jmp_statementContext::RETURN() {
  return getToken(MXParser::RETURN, 0);
}

MXParser::ExprContext* MXParser::Jmp_statementContext::expr() {
  return getRuleContext<MXParser::ExprContext>(0);
}

MXParser::Jmp_statementContext::Jmp_statementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MXParser::Jmp_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitJmp_statement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- If_statementContext ------------------------------------------------------------------

tree::TerminalNode* MXParser::If_statementContext::IF() {
  return getToken(MXParser::IF, 0);
}

tree::TerminalNode* MXParser::If_statementContext::LPAREN() {
  return getToken(MXParser::LPAREN, 0);
}

MXParser::ExprContext* MXParser::If_statementContext::expr() {
  return getRuleContext<MXParser::ExprContext>(0);
}

tree::TerminalNode* MXParser::If_statementContext::RPAREN() {
  return getToken(MXParser::RPAREN, 0);
}

std::vector<MXParser::StatementContext *> MXParser::If_statementContext::statement() {
  return getRuleContexts<MXParser::StatementContext>();
}

MXParser::StatementContext* MXParser::If_statementContext::statement(size_t i) {
  return getRuleContext<MXParser::StatementContext>(i);
}

tree::TerminalNode* MXParser::If_statementContext::ELSE() {
  return getToken(MXParser::ELSE, 0);
}

MXParser::If_statementContext::If_statementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MXParser::If_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitIf_statement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Definition_statementContext ------------------------------------------------------------------

MXParser::Define_statementContext* MXParser::Definition_statementContext::define_statement() {
  return getRuleContext<MXParser::Define_statementContext>(0);
}

MXParser::Definition_statementContext::Definition_statementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MXParser::Definition_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitDefinition_statement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- While_statementContext ------------------------------------------------------------------

tree::TerminalNode* MXParser::While_statementContext::WHILE() {
  return getToken(MXParser::WHILE, 0);
}

tree::TerminalNode* MXParser::While_statementContext::LPAREN() {
  return getToken(MXParser::LPAREN, 0);
}

MXParser::ExprContext* MXParser::While_statementContext::expr() {
  return getRuleContext<MXParser::ExprContext>(0);
}

tree::TerminalNode* MXParser::While_statementContext::RPAREN() {
  return getToken(MXParser::RPAREN, 0);
}

MXParser::StatementContext* MXParser::While_statementContext::statement() {
  return getRuleContext<MXParser::StatementContext>(0);
}

MXParser::While_statementContext::While_statementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MXParser::While_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitWhile_statement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Empty_statementContext ------------------------------------------------------------------

tree::TerminalNode* MXParser::Empty_statementContext::SEMICOLON() {
  return getToken(MXParser::SEMICOLON, 0);
}

MXParser::Empty_statementContext::Empty_statementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any MXParser::Empty_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitEmpty_statement(this);
  else
    return visitor->visitChildren(this);
}
MXParser::StatementContext* MXParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 12, MXParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(171);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<MXParser::Empty_statementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(122);
      match(MXParser::SEMICOLON);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<MXParser::Definition_statementContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(123);
      define_statement();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<MXParser::Expr_statementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(124);
      expr(0);
      setState(125);
      match(MXParser::SEMICOLON);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<MXParser::If_statementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(127);
      match(MXParser::IF);
      setState(128);
      match(MXParser::LPAREN);
      setState(129);
      expr(0);
      setState(130);
      match(MXParser::RPAREN);
      setState(131);
      statement();
      setState(134);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
      case 1: {
        setState(132);
        match(MXParser::ELSE);
        setState(133);
        statement();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<MXParser::While_statementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(136);
      match(MXParser::WHILE);
      setState(137);
      match(MXParser::LPAREN);
      setState(138);
      expr(0);
      setState(139);
      match(MXParser::RPAREN);
      setState(140);
      statement();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<MXParser::For_statementContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(142);
      match(MXParser::FOR);
      setState(143);
      match(MXParser::LPAREN);
      setState(149);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
      case 1: {
        setState(144);
        define_statement();
        break;
      }

      case 2: {
        setState(145);
        expr(0);
        setState(146);
        match(MXParser::SEMICOLON);
        break;
      }

      case 3: {
        setState(148);
        match(MXParser::SEMICOLON);
        break;
      }

      default:
        break;
      }
      setState(152);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 518214813164767136) != 0)) {
        setState(151);
        expr(0);
      }
      setState(154);
      match(MXParser::SEMICOLON);
      setState(157);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
      case 1: {
        setState(155);
        define_statement();
        break;
      }

      case 2: {
        setState(156);
        expr(0);
        break;
      }

      default:
        break;
      }
      setState(159);
      match(MXParser::RPAREN);
      setState(160);
      statement();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<MXParser::Jmp_statementContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(167);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case MXParser::BREAK: {
          setState(161);
          match(MXParser::BREAK);
          break;
        }

        case MXParser::CONTINUE: {
          setState(162);
          match(MXParser::CONTINUE);
          break;
        }

        case MXParser::RETURN: {
          setState(163);
          match(MXParser::RETURN);
          setState(165);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 518214813164767136) != 0)) {
            setState(164);
            expr(0);
          }
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(169);
      match(MXParser::SEMICOLON);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<MXParser::Suite_statementContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(170);
      suite();
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

//----------------- Define_statementContext ------------------------------------------------------------------

MXParser::Define_statementContext::Define_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MXParser::TypeContext* MXParser::Define_statementContext::type() {
  return getRuleContext<MXParser::TypeContext>(0);
}

std::vector<tree::TerminalNode *> MXParser::Define_statementContext::ID() {
  return getTokens(MXParser::ID);
}

tree::TerminalNode* MXParser::Define_statementContext::ID(size_t i) {
  return getToken(MXParser::ID, i);
}

tree::TerminalNode* MXParser::Define_statementContext::SEMICOLON() {
  return getToken(MXParser::SEMICOLON, 0);
}

std::vector<tree::TerminalNode *> MXParser::Define_statementContext::LBRACKET() {
  return getTokens(MXParser::LBRACKET);
}

tree::TerminalNode* MXParser::Define_statementContext::LBRACKET(size_t i) {
  return getToken(MXParser::LBRACKET, i);
}

std::vector<tree::TerminalNode *> MXParser::Define_statementContext::RBRACKET() {
  return getTokens(MXParser::RBRACKET);
}

tree::TerminalNode* MXParser::Define_statementContext::RBRACKET(size_t i) {
  return getToken(MXParser::RBRACKET, i);
}

std::vector<tree::TerminalNode *> MXParser::Define_statementContext::ASSIGN() {
  return getTokens(MXParser::ASSIGN);
}

tree::TerminalNode* MXParser::Define_statementContext::ASSIGN(size_t i) {
  return getToken(MXParser::ASSIGN, i);
}

std::vector<MXParser::ExprContext *> MXParser::Define_statementContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::Define_statementContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> MXParser::Define_statementContext::COMMA() {
  return getTokens(MXParser::COMMA);
}

tree::TerminalNode* MXParser::Define_statementContext::COMMA(size_t i) {
  return getToken(MXParser::COMMA, i);
}


size_t MXParser::Define_statementContext::getRuleIndex() const {
  return MXParser::RuleDefine_statement;
}


std::any MXParser::Define_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitDefine_statement(this);
  else
    return visitor->visitChildren(this);
}

MXParser::Define_statementContext* MXParser::define_statement() {
  Define_statementContext *_localctx = _tracker.createInstance<Define_statementContext>(_ctx, getState());
  enterRule(_localctx, 14, MXParser::RuleDefine_statement);
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
    setState(173);
    type();
    setState(178);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MXParser::LBRACKET) {
      setState(174);
      match(MXParser::LBRACKET);
      setState(175);
      match(MXParser::RBRACKET);
      setState(180);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(181);
    match(MXParser::ID);
    setState(184);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MXParser::ASSIGN) {
      setState(182);
      match(MXParser::ASSIGN);
      setState(183);
      expr(0);
    }
    setState(194);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MXParser::COMMA) {
      setState(186);
      match(MXParser::COMMA);
      setState(187);
      match(MXParser::ID);
      setState(190);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MXParser::ASSIGN) {
        setState(188);
        match(MXParser::ASSIGN);
        setState(189);
        expr(0);
      }
      setState(196);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(197);
    match(MXParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

MXParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MXParser::ExprContext::getRuleIndex() const {
  return MXParser::RuleExpr;
}

void MXParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Ggll_expressionContext ------------------------------------------------------------------

std::vector<MXParser::ExprContext *> MXParser::Ggll_expressionContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::Ggll_expressionContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

tree::TerminalNode* MXParser::Ggll_expressionContext::GN() {
  return getToken(MXParser::GN, 0);
}

tree::TerminalNode* MXParser::Ggll_expressionContext::GE() {
  return getToken(MXParser::GE, 0);
}

tree::TerminalNode* MXParser::Ggll_expressionContext::LN() {
  return getToken(MXParser::LN, 0);
}

tree::TerminalNode* MXParser::Ggll_expressionContext::LE() {
  return getToken(MXParser::LE, 0);
}

MXParser::Ggll_expressionContext::Ggll_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Ggll_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitGgll_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Bxor_expressionContext ------------------------------------------------------------------

std::vector<MXParser::ExprContext *> MXParser::Bxor_expressionContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::Bxor_expressionContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

tree::TerminalNode* MXParser::Bxor_expressionContext::BXOR() {
  return getToken(MXParser::BXOR, 0);
}

MXParser::Bxor_expressionContext::Bxor_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Bxor_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitBxor_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Suffix_expressionContext ------------------------------------------------------------------

MXParser::ExprContext* MXParser::Suffix_expressionContext::expr() {
  return getRuleContext<MXParser::ExprContext>(0);
}

tree::TerminalNode* MXParser::Suffix_expressionContext::SELF_PLUS() {
  return getToken(MXParser::SELF_PLUS, 0);
}

tree::TerminalNode* MXParser::Suffix_expressionContext::SELF_MINUS() {
  return getToken(MXParser::SELF_MINUS, 0);
}

MXParser::Suffix_expressionContext::Suffix_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Suffix_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitSuffix_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Land_expressionContext ------------------------------------------------------------------

std::vector<MXParser::ExprContext *> MXParser::Land_expressionContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::Land_expressionContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

tree::TerminalNode* MXParser::Land_expressionContext::LAND() {
  return getToken(MXParser::LAND, 0);
}

MXParser::Land_expressionContext::Land_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Land_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitLand_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Pm_expressionContext ------------------------------------------------------------------

std::vector<MXParser::ExprContext *> MXParser::Pm_expressionContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::Pm_expressionContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

tree::TerminalNode* MXParser::Pm_expressionContext::PLUS() {
  return getToken(MXParser::PLUS, 0);
}

tree::TerminalNode* MXParser::Pm_expressionContext::MINUS() {
  return getToken(MXParser::MINUS, 0);
}

MXParser::Pm_expressionContext::Pm_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Pm_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitPm_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Index_expressionContext ------------------------------------------------------------------

std::vector<MXParser::ExprContext *> MXParser::Index_expressionContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::Index_expressionContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> MXParser::Index_expressionContext::LBRACKET() {
  return getTokens(MXParser::LBRACKET);
}

tree::TerminalNode* MXParser::Index_expressionContext::LBRACKET(size_t i) {
  return getToken(MXParser::LBRACKET, i);
}

std::vector<tree::TerminalNode *> MXParser::Index_expressionContext::RBRACKET() {
  return getTokens(MXParser::RBRACKET);
}

tree::TerminalNode* MXParser::Index_expressionContext::RBRACKET(size_t i) {
  return getToken(MXParser::RBRACKET, i);
}

MXParser::Index_expressionContext::Index_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Index_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitIndex_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Opposite_expressionContext ------------------------------------------------------------------

tree::TerminalNode* MXParser::Opposite_expressionContext::MINUS() {
  return getToken(MXParser::MINUS, 0);
}

MXParser::ExprContext* MXParser::Opposite_expressionContext::expr() {
  return getRuleContext<MXParser::ExprContext>(0);
}

MXParser::Opposite_expressionContext::Opposite_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Opposite_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitOpposite_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- New_array_expressionContext ------------------------------------------------------------------

tree::TerminalNode* MXParser::New_array_expressionContext::NEW() {
  return getToken(MXParser::NEW, 0);
}

MXParser::TypeContext* MXParser::New_array_expressionContext::type() {
  return getRuleContext<MXParser::TypeContext>(0);
}

std::vector<tree::TerminalNode *> MXParser::New_array_expressionContext::LBRACKET() {
  return getTokens(MXParser::LBRACKET);
}

tree::TerminalNode* MXParser::New_array_expressionContext::LBRACKET(size_t i) {
  return getToken(MXParser::LBRACKET, i);
}

std::vector<tree::TerminalNode *> MXParser::New_array_expressionContext::RBRACKET() {
  return getTokens(MXParser::RBRACKET);
}

tree::TerminalNode* MXParser::New_array_expressionContext::RBRACKET(size_t i) {
  return getToken(MXParser::RBRACKET, i);
}

MXParser::ConstantContext* MXParser::New_array_expressionContext::constant() {
  return getRuleContext<MXParser::ConstantContext>(0);
}

std::vector<MXParser::ExprContext *> MXParser::New_array_expressionContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::New_array_expressionContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

MXParser::New_array_expressionContext::New_array_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::New_array_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitNew_array_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Basic_expressionContext ------------------------------------------------------------------

MXParser::Basic_exprContext* MXParser::Basic_expressionContext::basic_expr() {
  return getRuleContext<MXParser::Basic_exprContext>(0);
}

MXParser::Basic_expressionContext::Basic_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Basic_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitBasic_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Access_expressionContext ------------------------------------------------------------------

std::vector<MXParser::ExprContext *> MXParser::Access_expressionContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::Access_expressionContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

tree::TerminalNode* MXParser::Access_expressionContext::DOT() {
  return getToken(MXParser::DOT, 0);
}

tree::TerminalNode* MXParser::Access_expressionContext::ID() {
  return getToken(MXParser::ID, 0);
}

tree::TerminalNode* MXParser::Access_expressionContext::LPAREN() {
  return getToken(MXParser::LPAREN, 0);
}

tree::TerminalNode* MXParser::Access_expressionContext::RPAREN() {
  return getToken(MXParser::RPAREN, 0);
}

std::vector<tree::TerminalNode *> MXParser::Access_expressionContext::COMMA() {
  return getTokens(MXParser::COMMA);
}

tree::TerminalNode* MXParser::Access_expressionContext::COMMA(size_t i) {
  return getToken(MXParser::COMMA, i);
}

MXParser::Access_expressionContext::Access_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Access_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitAccess_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Band_expressionContext ------------------------------------------------------------------

std::vector<MXParser::ExprContext *> MXParser::Band_expressionContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::Band_expressionContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

tree::TerminalNode* MXParser::Band_expressionContext::BAND() {
  return getToken(MXParser::BAND, 0);
}

MXParser::Band_expressionContext::Band_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Band_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitBand_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- New_construct_expressionContext ------------------------------------------------------------------

tree::TerminalNode* MXParser::New_construct_expressionContext::NEW() {
  return getToken(MXParser::NEW, 0);
}

MXParser::TypeContext* MXParser::New_construct_expressionContext::type() {
  return getRuleContext<MXParser::TypeContext>(0);
}

tree::TerminalNode* MXParser::New_construct_expressionContext::LPAREN() {
  return getToken(MXParser::LPAREN, 0);
}

tree::TerminalNode* MXParser::New_construct_expressionContext::RPAREN() {
  return getToken(MXParser::RPAREN, 0);
}

MXParser::New_construct_expressionContext::New_construct_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::New_construct_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitNew_construct_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Ternary_expressionContext ------------------------------------------------------------------

std::vector<MXParser::ExprContext *> MXParser::Ternary_expressionContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::Ternary_expressionContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

tree::TerminalNode* MXParser::Ternary_expressionContext::QUESTION_MARK() {
  return getToken(MXParser::QUESTION_MARK, 0);
}

tree::TerminalNode* MXParser::Ternary_expressionContext::COLON() {
  return getToken(MXParser::COLON, 0);
}

MXParser::Ternary_expressionContext::Ternary_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Ternary_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitTernary_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Bnot_expressionContext ------------------------------------------------------------------

tree::TerminalNode* MXParser::Bnot_expressionContext::BNOT() {
  return getToken(MXParser::BNOT, 0);
}

MXParser::ExprContext* MXParser::Bnot_expressionContext::expr() {
  return getRuleContext<MXParser::ExprContext>(0);
}

MXParser::Bnot_expressionContext::Bnot_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Bnot_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitBnot_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Lnot_expressionContext ------------------------------------------------------------------

tree::TerminalNode* MXParser::Lnot_expressionContext::LNOT() {
  return getToken(MXParser::LNOT, 0);
}

MXParser::ExprContext* MXParser::Lnot_expressionContext::expr() {
  return getRuleContext<MXParser::ExprContext>(0);
}

MXParser::Lnot_expressionContext::Lnot_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Lnot_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitLnot_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Prefix_expressionContext ------------------------------------------------------------------

MXParser::ExprContext* MXParser::Prefix_expressionContext::expr() {
  return getRuleContext<MXParser::ExprContext>(0);
}

tree::TerminalNode* MXParser::Prefix_expressionContext::SELF_PLUS() {
  return getToken(MXParser::SELF_PLUS, 0);
}

tree::TerminalNode* MXParser::Prefix_expressionContext::SELF_MINUS() {
  return getToken(MXParser::SELF_MINUS, 0);
}

MXParser::Prefix_expressionContext::Prefix_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Prefix_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitPrefix_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Rl_expressionContext ------------------------------------------------------------------

std::vector<MXParser::ExprContext *> MXParser::Rl_expressionContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::Rl_expressionContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

tree::TerminalNode* MXParser::Rl_expressionContext::ARS() {
  return getToken(MXParser::ARS, 0);
}

tree::TerminalNode* MXParser::Rl_expressionContext::ALS() {
  return getToken(MXParser::ALS, 0);
}

MXParser::Rl_expressionContext::Rl_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Rl_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitRl_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Assign_expressionContext ------------------------------------------------------------------

std::vector<MXParser::ExprContext *> MXParser::Assign_expressionContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::Assign_expressionContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

tree::TerminalNode* MXParser::Assign_expressionContext::ASSIGN() {
  return getToken(MXParser::ASSIGN, 0);
}

MXParser::Assign_expressionContext::Assign_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Assign_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitAssign_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Mdm_expressionContext ------------------------------------------------------------------

std::vector<MXParser::ExprContext *> MXParser::Mdm_expressionContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::Mdm_expressionContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

tree::TerminalNode* MXParser::Mdm_expressionContext::MULTIPLY() {
  return getToken(MXParser::MULTIPLY, 0);
}

tree::TerminalNode* MXParser::Mdm_expressionContext::DIVIDE() {
  return getToken(MXParser::DIVIDE, 0);
}

tree::TerminalNode* MXParser::Mdm_expressionContext::MOD() {
  return getToken(MXParser::MOD, 0);
}

MXParser::Mdm_expressionContext::Mdm_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Mdm_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitMdm_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- New_expressionContext ------------------------------------------------------------------

tree::TerminalNode* MXParser::New_expressionContext::NEW() {
  return getToken(MXParser::NEW, 0);
}

MXParser::TypeContext* MXParser::New_expressionContext::type() {
  return getRuleContext<MXParser::TypeContext>(0);
}

MXParser::New_expressionContext::New_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::New_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitNew_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Ne_expressionContext ------------------------------------------------------------------

std::vector<MXParser::ExprContext *> MXParser::Ne_expressionContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::Ne_expressionContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

tree::TerminalNode* MXParser::Ne_expressionContext::NE() {
  return getToken(MXParser::NE, 0);
}

tree::TerminalNode* MXParser::Ne_expressionContext::EQ() {
  return getToken(MXParser::EQ, 0);
}

MXParser::Ne_expressionContext::Ne_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Ne_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitNe_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Bor_expressionContext ------------------------------------------------------------------

std::vector<MXParser::ExprContext *> MXParser::Bor_expressionContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::Bor_expressionContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

tree::TerminalNode* MXParser::Bor_expressionContext::BOR() {
  return getToken(MXParser::BOR, 0);
}

MXParser::Bor_expressionContext::Bor_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Bor_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitBor_expression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Lor_expressionContext ------------------------------------------------------------------

std::vector<MXParser::ExprContext *> MXParser::Lor_expressionContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::Lor_expressionContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

tree::TerminalNode* MXParser::Lor_expressionContext::LOR() {
  return getToken(MXParser::LOR, 0);
}

MXParser::Lor_expressionContext::Lor_expressionContext(ExprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Lor_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitLor_expression(this);
  else
    return visitor->visitChildren(this);
}

MXParser::ExprContext* MXParser::expr() {
   return expr(0);
}

MXParser::ExprContext* MXParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  MXParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  MXParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 16;
  enterRecursionRule(_localctx, 16, MXParser::RuleExpr, precedence);

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
    setState(230);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<Basic_expressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(200);
      basic_expr();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<New_array_expressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(201);
      match(MXParser::NEW);
      setState(202);
      type();
      setState(208); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(203);
                match(MXParser::LBRACKET);
                setState(205);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if ((((_la & ~ 0x3fULL) == 0) &&
                  ((1ULL << _la) & 518214813164767136) != 0)) {
                  setState(204);
                  expr(0);
                }
                setState(207);
                match(MXParser::RBRACKET);
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(210); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      setState(213);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
      case 1: {
        setState(212);
        constant();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<New_construct_expressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(215);
      match(MXParser::NEW);
      setState(216);
      type();
      setState(217);
      match(MXParser::LPAREN);
      setState(218);
      match(MXParser::RPAREN);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<New_expressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(220);
      match(MXParser::NEW);
      setState(221);
      type();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<Prefix_expressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(222);
      _la = _input->LA(1);
      if (!(_la == MXParser::SELF_PLUS

      || _la == MXParser::SELF_MINUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(223);
      expr(16);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<Opposite_expressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(224);
      match(MXParser::MINUS);
      setState(225);
      expr(15);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<Lnot_expressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(226);
      match(MXParser::LNOT);
      setState(227);
      expr(14);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<Bnot_expressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(228);
      match(MXParser::BNOT);
      setState(229);
      expr(13);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(302);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(300);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<Mdm_expressionContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(232);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(233);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 7340032) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(234);
          expr(13);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<Pm_expressionContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(235);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(236);
          _la = _input->LA(1);
          if (!(_la == MXParser::PLUS

          || _la == MXParser::MINUS)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(237);
          expr(12);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<Rl_expressionContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(238);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(239);
          _la = _input->LA(1);
          if (!(_la == MXParser::ARS

          || _la == MXParser::ALS)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(240);
          expr(11);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<Ggll_expressionContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(241);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(242);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 125829120) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(243);
          expr(10);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<Ne_expressionContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(244);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(245);
          _la = _input->LA(1);
          if (!(_la == MXParser::NE

          || _la == MXParser::EQ)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(246);
          expr(9);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<Band_expressionContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(247);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(248);
          match(MXParser::BAND);
          setState(249);
          expr(8);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<Bxor_expressionContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(250);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(251);
          match(MXParser::BXOR);
          setState(252);
          expr(7);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<Bor_expressionContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(253);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(254);
          match(MXParser::BOR);
          setState(255);
          expr(6);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<Land_expressionContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(256);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(257);
          match(MXParser::LAND);
          setState(258);
          expr(5);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<Lor_expressionContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(259);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(260);
          match(MXParser::LOR);
          setState(261);
          expr(4);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<Ternary_expressionContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(262);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(263);
          match(MXParser::QUESTION_MARK);
          setState(264);
          expr(0);
          setState(265);
          match(MXParser::COLON);
          setState(266);
          expr(2);
          break;
        }

        case 12: {
          auto newContext = _tracker.createInstance<Assign_expressionContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(268);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(269);
          match(MXParser::ASSIGN);
          setState(270);
          expr(1);
          break;
        }

        case 13: {
          auto newContext = _tracker.createInstance<Access_expressionContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(271);

          if (!(precpred(_ctx, 19))) throw FailedPredicateException(this, "precpred(_ctx, 19)");
          setState(272);
          match(MXParser::DOT);
          setState(287);
          _errHandler->sync(this);
          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
          case 1: {
            setState(273);
            match(MXParser::ID);
            break;
          }

          case 2: {
            setState(274);
            match(MXParser::ID);
            setState(275);
            match(MXParser::LPAREN);
            setState(284);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if ((((_la & ~ 0x3fULL) == 0) &&
              ((1ULL << _la) & 518214813164767136) != 0)) {
              setState(276);
              expr(0);
              setState(281);
              _errHandler->sync(this);
              _la = _input->LA(1);
              while (_la == MXParser::COMMA) {
                setState(277);
                match(MXParser::COMMA);
                setState(278);
                expr(0);
                setState(283);
                _errHandler->sync(this);
                _la = _input->LA(1);
              }
            }
            setState(286);
            match(MXParser::RPAREN);
            break;
          }

          default:
            break;
          }
          break;
        }

        case 14: {
          auto newContext = _tracker.createInstance<Index_expressionContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(289);

          if (!(precpred(_ctx, 18))) throw FailedPredicateException(this, "precpred(_ctx, 18)");
          setState(294); 
          _errHandler->sync(this);
          alt = 1;
          do {
            switch (alt) {
              case 1: {
                    setState(290);
                    match(MXParser::LBRACKET);
                    setState(291);
                    expr(0);
                    setState(292);
                    match(MXParser::RBRACKET);
                    break;
                  }

            default:
              throw NoViableAltException(this);
            }
            setState(296); 
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
          } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
          break;
        }

        case 15: {
          auto newContext = _tracker.createInstance<Suffix_expressionContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(298);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(299);
          _la = _input->LA(1);
          if (!(_la == MXParser::SELF_PLUS

          || _la == MXParser::SELF_MINUS)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          break;
        }

        default:
          break;
        } 
      }
      setState(304);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Basic_exprContext ------------------------------------------------------------------

MXParser::Basic_exprContext::Basic_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MXParser::Basic_exprContext::getRuleIndex() const {
  return MXParser::RuleBasic_expr;
}

void MXParser::Basic_exprContext::copyFrom(Basic_exprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Paren_exprContext ------------------------------------------------------------------

tree::TerminalNode* MXParser::Paren_exprContext::LPAREN() {
  return getToken(MXParser::LPAREN, 0);
}

MXParser::ExprContext* MXParser::Paren_exprContext::expr() {
  return getRuleContext<MXParser::ExprContext>(0);
}

tree::TerminalNode* MXParser::Paren_exprContext::RPAREN() {
  return getToken(MXParser::RPAREN, 0);
}

MXParser::Paren_exprContext::Paren_exprContext(Basic_exprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Paren_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitParen_expr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Constant_exprContext ------------------------------------------------------------------

MXParser::ConstantContext* MXParser::Constant_exprContext::constant() {
  return getRuleContext<MXParser::ConstantContext>(0);
}

MXParser::Constant_exprContext::Constant_exprContext(Basic_exprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Constant_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitConstant_expr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- This_exprContext ------------------------------------------------------------------

tree::TerminalNode* MXParser::This_exprContext::THIS() {
  return getToken(MXParser::THIS, 0);
}

MXParser::This_exprContext::This_exprContext(Basic_exprContext *ctx) { copyFrom(ctx); }


std::any MXParser::This_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitThis_expr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Id_exprContext ------------------------------------------------------------------

tree::TerminalNode* MXParser::Id_exprContext::ID() {
  return getToken(MXParser::ID, 0);
}

MXParser::Id_exprContext::Id_exprContext(Basic_exprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Id_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitId_expr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Formatted_string_exprContext ------------------------------------------------------------------

MXParser::Formatted_stringContext* MXParser::Formatted_string_exprContext::formatted_string() {
  return getRuleContext<MXParser::Formatted_stringContext>(0);
}

MXParser::Formatted_string_exprContext::Formatted_string_exprContext(Basic_exprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Formatted_string_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitFormatted_string_expr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Function_call_exprContext ------------------------------------------------------------------

tree::TerminalNode* MXParser::Function_call_exprContext::ID() {
  return getToken(MXParser::ID, 0);
}

tree::TerminalNode* MXParser::Function_call_exprContext::LPAREN() {
  return getToken(MXParser::LPAREN, 0);
}

tree::TerminalNode* MXParser::Function_call_exprContext::RPAREN() {
  return getToken(MXParser::RPAREN, 0);
}

std::vector<MXParser::ExprContext *> MXParser::Function_call_exprContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::Function_call_exprContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> MXParser::Function_call_exprContext::COMMA() {
  return getTokens(MXParser::COMMA);
}

tree::TerminalNode* MXParser::Function_call_exprContext::COMMA(size_t i) {
  return getToken(MXParser::COMMA, i);
}

MXParser::Function_call_exprContext::Function_call_exprContext(Basic_exprContext *ctx) { copyFrom(ctx); }


std::any MXParser::Function_call_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitFunction_call_expr(this);
  else
    return visitor->visitChildren(this);
}
MXParser::Basic_exprContext* MXParser::basic_expr() {
  Basic_exprContext *_localctx = _tracker.createInstance<Basic_exprContext>(_ctx, getState());
  enterRule(_localctx, 18, MXParser::RuleBasic_expr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(326);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<MXParser::This_exprContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(305);
      match(MXParser::THIS);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<MXParser::Paren_exprContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(306);
      match(MXParser::LPAREN);
      setState(307);
      expr(0);
      setState(308);
      match(MXParser::RPAREN);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<MXParser::Id_exprContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(310);
      match(MXParser::ID);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<MXParser::Function_call_exprContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(311);
      match(MXParser::ID);
      setState(312);
      match(MXParser::LPAREN);
      setState(321);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 518214813164767136) != 0)) {
        setState(313);
        expr(0);
        setState(318);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == MXParser::COMMA) {
          setState(314);
          match(MXParser::COMMA);
          setState(315);
          expr(0);
          setState(320);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(323);
      match(MXParser::RPAREN);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<MXParser::Formatted_string_exprContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(324);
      formatted_string();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<MXParser::Constant_exprContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(325);
      constant();
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

//----------------- Formatted_stringContext ------------------------------------------------------------------

MXParser::Formatted_stringContext::Formatted_stringContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MXParser::Formatted_stringContext::FORMAT_STRING_WHOLE() {
  return getToken(MXParser::FORMAT_STRING_WHOLE, 0);
}

tree::TerminalNode* MXParser::Formatted_stringContext::FORMAT_STRING_HEAD() {
  return getToken(MXParser::FORMAT_STRING_HEAD, 0);
}

std::vector<MXParser::ExprContext *> MXParser::Formatted_stringContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::Formatted_stringContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

tree::TerminalNode* MXParser::Formatted_stringContext::FORMAT_STRING_TAIL() {
  return getToken(MXParser::FORMAT_STRING_TAIL, 0);
}

std::vector<tree::TerminalNode *> MXParser::Formatted_stringContext::FORMAT_STRING_BODY() {
  return getTokens(MXParser::FORMAT_STRING_BODY);
}

tree::TerminalNode* MXParser::Formatted_stringContext::FORMAT_STRING_BODY(size_t i) {
  return getToken(MXParser::FORMAT_STRING_BODY, i);
}


size_t MXParser::Formatted_stringContext::getRuleIndex() const {
  return MXParser::RuleFormatted_string;
}


std::any MXParser::Formatted_stringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitFormatted_string(this);
  else
    return visitor->visitChildren(this);
}

MXParser::Formatted_stringContext* MXParser::formatted_string() {
  Formatted_stringContext *_localctx = _tracker.createInstance<Formatted_stringContext>(_ctx, getState());
  enterRule(_localctx, 20, MXParser::RuleFormatted_string);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(340);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MXParser::FORMAT_STRING_WHOLE: {
        enterOuterAlt(_localctx, 1);
        setState(328);
        match(MXParser::FORMAT_STRING_WHOLE);
        break;
      }

      case MXParser::FORMAT_STRING_HEAD: {
        enterOuterAlt(_localctx, 2);
        setState(329);
        match(MXParser::FORMAT_STRING_HEAD);
        setState(330);
        expr(0);
        setState(335);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
        while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1 + 1) {
            setState(331);
            match(MXParser::FORMAT_STRING_BODY);
            setState(332);
            expr(0); 
          }
          setState(337);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
        }
        setState(338);
        match(MXParser::FORMAT_STRING_TAIL);
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

//----------------- ConstantContext ------------------------------------------------------------------

MXParser::ConstantContext::ConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MXParser::ConstantContext::TRUE() {
  return getToken(MXParser::TRUE, 0);
}

tree::TerminalNode* MXParser::ConstantContext::FALSE() {
  return getToken(MXParser::FALSE, 0);
}

tree::TerminalNode* MXParser::ConstantContext::INT_LITERAL() {
  return getToken(MXParser::INT_LITERAL, 0);
}

tree::TerminalNode* MXParser::ConstantContext::STRING_LITERAL() {
  return getToken(MXParser::STRING_LITERAL, 0);
}

tree::TerminalNode* MXParser::ConstantContext::NULL_() {
  return getToken(MXParser::NULL_, 0);
}

tree::TerminalNode* MXParser::ConstantContext::LBRACE() {
  return getToken(MXParser::LBRACE, 0);
}

tree::TerminalNode* MXParser::ConstantContext::RBRACE() {
  return getToken(MXParser::RBRACE, 0);
}

std::vector<MXParser::ConstantContext *> MXParser::ConstantContext::constant() {
  return getRuleContexts<MXParser::ConstantContext>();
}

MXParser::ConstantContext* MXParser::ConstantContext::constant(size_t i) {
  return getRuleContext<MXParser::ConstantContext>(i);
}

std::vector<tree::TerminalNode *> MXParser::ConstantContext::COMMA() {
  return getTokens(MXParser::COMMA);
}

tree::TerminalNode* MXParser::ConstantContext::COMMA(size_t i) {
  return getToken(MXParser::COMMA, i);
}


size_t MXParser::ConstantContext::getRuleIndex() const {
  return MXParser::RuleConstant;
}


std::any MXParser::ConstantContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitConstant(this);
  else
    return visitor->visitChildren(this);
}

MXParser::ConstantContext* MXParser::constant() {
  ConstantContext *_localctx = _tracker.createInstance<ConstantContext>(_ctx, getState());
  enterRule(_localctx, 22, MXParser::RuleConstant);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(359);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MXParser::TRUE: {
        enterOuterAlt(_localctx, 1);
        setState(342);
        match(MXParser::TRUE);
        break;
      }

      case MXParser::FALSE: {
        enterOuterAlt(_localctx, 2);
        setState(343);
        match(MXParser::FALSE);
        break;
      }

      case MXParser::INT_LITERAL: {
        enterOuterAlt(_localctx, 3);
        setState(344);
        match(MXParser::INT_LITERAL);
        break;
      }

      case MXParser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 4);
        setState(345);
        match(MXParser::STRING_LITERAL);
        break;
      }

      case MXParser::NULL_: {
        enterOuterAlt(_localctx, 5);
        setState(346);
        match(MXParser::NULL_);
        break;
      }

      case MXParser::LBRACE: {
        enterOuterAlt(_localctx, 6);
        setState(347);
        match(MXParser::LBRACE);
        setState(356);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 432627039204279168) != 0)) {
          setState(348);
          constant();
          setState(353);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == MXParser::COMMA) {
            setState(349);
            match(MXParser::COMMA);
            setState(350);
            constant();
            setState(355);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(358);
        match(MXParser::RBRACE);
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

//----------------- TypeContext ------------------------------------------------------------------

MXParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MXParser::TypeContext::INT() {
  return getToken(MXParser::INT, 0);
}

tree::TerminalNode* MXParser::TypeContext::BOOL() {
  return getToken(MXParser::BOOL, 0);
}

tree::TerminalNode* MXParser::TypeContext::STRING() {
  return getToken(MXParser::STRING, 0);
}

tree::TerminalNode* MXParser::TypeContext::VOID() {
  return getToken(MXParser::VOID, 0);
}

tree::TerminalNode* MXParser::TypeContext::ID() {
  return getToken(MXParser::ID, 0);
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
  enterRule(_localctx, 24, MXParser::RuleType);
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
    setState(361);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72057594037927966) != 0))) {
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

bool MXParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 8: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool MXParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 12);
    case 1: return precpred(_ctx, 11);
    case 2: return precpred(_ctx, 10);
    case 3: return precpred(_ctx, 9);
    case 4: return precpred(_ctx, 8);
    case 5: return precpred(_ctx, 7);
    case 6: return precpred(_ctx, 6);
    case 7: return precpred(_ctx, 5);
    case 8: return precpred(_ctx, 4);
    case 9: return precpred(_ctx, 3);
    case 10: return precpred(_ctx, 2);
    case 11: return precpred(_ctx, 1);
    case 12: return precpred(_ctx, 19);
    case 13: return precpred(_ctx, 18);
    case 14: return precpred(_ctx, 17);

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
