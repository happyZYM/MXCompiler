
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
  	4,1,61,349,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,1,0,1,0,1,0,4,0,30,
  	8,0,11,0,12,0,31,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,1,
  	46,8,1,10,1,12,1,49,9,1,3,1,51,8,1,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,2,1,
  	2,5,2,62,8,2,10,2,12,2,65,9,2,1,2,1,2,1,2,1,3,1,3,1,3,5,3,73,8,3,10,3,
  	12,3,76,9,3,1,3,1,3,1,3,5,3,81,8,3,10,3,12,3,84,9,3,1,3,1,3,1,4,1,4,1,
  	4,1,4,1,4,1,5,1,5,5,5,95,8,5,10,5,12,5,98,9,5,1,5,1,5,1,6,1,6,1,6,1,6,
  	1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,3,6,114,8,6,1,6,1,6,1,6,1,6,1,6,1,6,1,
  	6,1,6,1,6,1,6,1,6,1,6,1,6,3,6,129,8,6,1,6,3,6,132,8,6,1,6,1,6,1,6,3,6,
  	137,8,6,1,6,1,6,1,6,1,6,1,6,1,6,3,6,145,8,6,3,6,147,8,6,1,6,1,6,3,6,151,
  	8,6,1,7,1,7,1,7,5,7,156,8,7,10,7,12,7,159,9,7,1,7,1,7,1,7,3,7,164,8,7,
  	1,7,1,7,1,7,1,7,3,7,170,8,7,5,7,172,8,7,10,7,12,7,175,9,7,1,7,1,7,1,8,
  	1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,
  	8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,5,8,205,8,8,10,8,12,8,208,9,8,1,8,1,8,5,
  	8,212,8,8,10,8,12,8,215,9,8,1,8,3,8,218,8,8,3,8,220,8,8,1,8,1,8,1,8,1,
  	8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,
  	1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,
  	8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,5,8,269,8,8,10,8,12,8,272,9,8,3,8,274,
  	8,8,1,8,3,8,277,8,8,1,8,1,8,1,8,1,8,1,8,4,8,284,8,8,11,8,12,8,285,1,8,
  	1,8,5,8,290,8,8,10,8,12,8,293,9,8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,5,9,302,
  	8,9,10,9,12,9,305,9,9,3,9,307,8,9,1,9,1,9,1,9,3,9,312,8,9,1,10,1,10,1,
  	10,1,10,1,10,5,10,319,8,10,10,10,12,10,322,9,10,1,10,1,10,3,10,326,8,
  	10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,5,11,337,8,11,10,11,12,
  	11,340,9,11,3,11,342,8,11,1,11,3,11,345,8,11,1,12,1,12,1,12,1,320,1,16,
  	13,0,2,4,6,8,10,12,14,16,18,20,22,24,0,7,1,0,39,40,1,0,20,22,1,0,18,19,
  	1,0,32,33,1,0,23,26,1,0,27,28,2,0,1,4,56,56,411,0,29,1,0,0,0,2,35,1,0,
  	0,0,4,55,1,0,0,0,6,69,1,0,0,0,8,87,1,0,0,0,10,92,1,0,0,0,12,150,1,0,0,
  	0,14,152,1,0,0,0,16,219,1,0,0,0,18,311,1,0,0,0,20,325,1,0,0,0,22,344,
  	1,0,0,0,24,346,1,0,0,0,26,30,3,4,2,0,27,30,3,14,7,0,28,30,3,2,1,0,29,
  	26,1,0,0,0,29,27,1,0,0,0,29,28,1,0,0,0,30,31,1,0,0,0,31,29,1,0,0,0,31,
  	32,1,0,0,0,32,33,1,0,0,0,33,34,5,0,0,1,34,1,1,0,0,0,35,36,3,24,12,0,36,
  	37,5,56,0,0,37,50,5,44,0,0,38,39,3,24,12,0,39,40,5,56,0,0,40,47,1,0,0,
  	0,41,42,5,51,0,0,42,43,3,24,12,0,43,44,5,56,0,0,44,46,1,0,0,0,45,41,1,
  	0,0,0,46,49,1,0,0,0,47,45,1,0,0,0,47,48,1,0,0,0,48,51,1,0,0,0,49,47,1,
  	0,0,0,50,38,1,0,0,0,50,51,1,0,0,0,51,52,1,0,0,0,52,53,5,45,0,0,53,54,
  	3,10,5,0,54,3,1,0,0,0,55,56,5,6,0,0,56,57,5,56,0,0,57,63,5,48,0,0,58,
  	62,3,6,3,0,59,62,3,8,4,0,60,62,3,2,1,0,61,58,1,0,0,0,61,59,1,0,0,0,61,
  	60,1,0,0,0,62,65,1,0,0,0,63,61,1,0,0,0,63,64,1,0,0,0,64,66,1,0,0,0,65,
  	63,1,0,0,0,66,67,5,49,0,0,67,68,5,50,0,0,68,5,1,0,0,0,69,74,3,24,12,0,
  	70,71,5,46,0,0,71,73,5,47,0,0,72,70,1,0,0,0,73,76,1,0,0,0,74,72,1,0,0,
  	0,74,75,1,0,0,0,75,77,1,0,0,0,76,74,1,0,0,0,77,82,5,56,0,0,78,79,5,51,
  	0,0,79,81,5,56,0,0,80,78,1,0,0,0,81,84,1,0,0,0,82,80,1,0,0,0,82,83,1,
  	0,0,0,83,85,1,0,0,0,84,82,1,0,0,0,85,86,5,50,0,0,86,7,1,0,0,0,87,88,5,
  	56,0,0,88,89,5,44,0,0,89,90,5,45,0,0,90,91,3,10,5,0,91,9,1,0,0,0,92,96,
  	5,48,0,0,93,95,3,12,6,0,94,93,1,0,0,0,95,98,1,0,0,0,96,94,1,0,0,0,96,
  	97,1,0,0,0,97,99,1,0,0,0,98,96,1,0,0,0,99,100,5,49,0,0,100,11,1,0,0,0,
  	101,151,5,50,0,0,102,151,3,14,7,0,103,104,3,16,8,0,104,105,5,50,0,0,105,
  	151,1,0,0,0,106,107,5,11,0,0,107,108,5,44,0,0,108,109,3,16,8,0,109,110,
  	5,45,0,0,110,113,3,12,6,0,111,112,5,12,0,0,112,114,3,12,6,0,113,111,1,
  	0,0,0,113,114,1,0,0,0,114,151,1,0,0,0,115,116,5,14,0,0,116,117,5,44,0,
  	0,117,118,3,16,8,0,118,119,5,45,0,0,119,120,3,12,6,0,120,151,1,0,0,0,
  	121,122,5,13,0,0,122,128,5,44,0,0,123,129,3,14,7,0,124,125,3,16,8,0,125,
  	126,5,50,0,0,126,129,1,0,0,0,127,129,5,50,0,0,128,123,1,0,0,0,128,124,
  	1,0,0,0,128,127,1,0,0,0,129,131,1,0,0,0,130,132,3,16,8,0,131,130,1,0,
  	0,0,131,132,1,0,0,0,132,133,1,0,0,0,133,136,5,50,0,0,134,137,3,14,7,0,
  	135,137,3,16,8,0,136,134,1,0,0,0,136,135,1,0,0,0,136,137,1,0,0,0,137,
  	138,1,0,0,0,138,139,5,45,0,0,139,151,3,12,6,0,140,147,5,15,0,0,141,147,
  	5,16,0,0,142,144,5,17,0,0,143,145,3,16,8,0,144,143,1,0,0,0,144,145,1,
  	0,0,0,145,147,1,0,0,0,146,140,1,0,0,0,146,141,1,0,0,0,146,142,1,0,0,0,
  	147,148,1,0,0,0,148,151,5,50,0,0,149,151,3,10,5,0,150,101,1,0,0,0,150,
  	102,1,0,0,0,150,103,1,0,0,0,150,106,1,0,0,0,150,115,1,0,0,0,150,121,1,
  	0,0,0,150,146,1,0,0,0,150,149,1,0,0,0,151,13,1,0,0,0,152,157,3,24,12,
  	0,153,154,5,46,0,0,154,156,5,47,0,0,155,153,1,0,0,0,156,159,1,0,0,0,157,
  	155,1,0,0,0,157,158,1,0,0,0,158,160,1,0,0,0,159,157,1,0,0,0,160,163,5,
  	56,0,0,161,162,5,38,0,0,162,164,3,16,8,0,163,161,1,0,0,0,163,164,1,0,
  	0,0,164,173,1,0,0,0,165,166,5,51,0,0,166,169,5,56,0,0,167,168,5,38,0,
  	0,168,170,3,16,8,0,169,167,1,0,0,0,169,170,1,0,0,0,170,172,1,0,0,0,171,
  	165,1,0,0,0,172,175,1,0,0,0,173,171,1,0,0,0,173,174,1,0,0,0,174,176,1,
  	0,0,0,175,173,1,0,0,0,176,177,5,50,0,0,177,15,1,0,0,0,178,179,6,8,-1,
  	0,179,220,3,18,9,0,180,181,5,44,0,0,181,182,3,16,8,0,182,183,5,45,0,0,
  	183,220,1,0,0,0,184,185,7,0,0,0,185,220,3,16,8,19,186,187,5,19,0,0,187,
  	220,3,16,8,18,188,189,5,31,0,0,189,220,3,16,8,17,190,191,5,37,0,0,191,
  	220,3,16,8,16,192,193,5,5,0,0,193,220,5,56,0,0,194,195,5,5,0,0,195,196,
  	5,56,0,0,196,197,5,44,0,0,197,220,5,45,0,0,198,199,5,5,0,0,199,206,5,
  	56,0,0,200,201,5,46,0,0,201,202,3,16,8,0,202,203,5,47,0,0,203,205,1,0,
  	0,0,204,200,1,0,0,0,205,208,1,0,0,0,206,204,1,0,0,0,206,207,1,0,0,0,207,
  	213,1,0,0,0,208,206,1,0,0,0,209,210,5,46,0,0,210,212,5,47,0,0,211,209,
  	1,0,0,0,212,215,1,0,0,0,213,211,1,0,0,0,213,214,1,0,0,0,214,217,1,0,0,
  	0,215,213,1,0,0,0,216,218,3,22,11,0,217,216,1,0,0,0,217,218,1,0,0,0,218,
  	220,1,0,0,0,219,178,1,0,0,0,219,180,1,0,0,0,219,184,1,0,0,0,219,186,1,
  	0,0,0,219,188,1,0,0,0,219,190,1,0,0,0,219,192,1,0,0,0,219,194,1,0,0,0,
  	219,198,1,0,0,0,220,291,1,0,0,0,221,222,10,15,0,0,222,223,7,1,0,0,223,
  	290,3,16,8,16,224,225,10,14,0,0,225,226,7,2,0,0,226,290,3,16,8,15,227,
  	228,10,13,0,0,228,229,7,3,0,0,229,290,3,16,8,14,230,231,10,12,0,0,231,
  	232,7,4,0,0,232,290,3,16,8,13,233,234,10,11,0,0,234,235,7,5,0,0,235,290,
  	3,16,8,12,236,237,10,10,0,0,237,238,5,34,0,0,238,290,3,16,8,11,239,240,
  	10,9,0,0,240,241,5,36,0,0,241,290,3,16,8,10,242,243,10,8,0,0,243,244,
  	5,35,0,0,244,290,3,16,8,9,245,246,10,7,0,0,246,247,5,29,0,0,247,290,3,
  	16,8,8,248,249,10,6,0,0,249,250,5,30,0,0,250,290,3,16,8,7,251,252,10,
  	5,0,0,252,253,5,42,0,0,253,254,3,16,8,0,254,255,5,43,0,0,255,256,3,16,
  	8,6,256,290,1,0,0,0,257,258,10,4,0,0,258,259,5,38,0,0,259,290,3,16,8,
  	4,260,261,10,22,0,0,261,276,5,41,0,0,262,277,5,56,0,0,263,264,5,56,0,
  	0,264,273,5,44,0,0,265,270,3,16,8,0,266,267,5,51,0,0,267,269,3,16,8,0,
  	268,266,1,0,0,0,269,272,1,0,0,0,270,268,1,0,0,0,270,271,1,0,0,0,271,274,
  	1,0,0,0,272,270,1,0,0,0,273,265,1,0,0,0,273,274,1,0,0,0,274,275,1,0,0,
  	0,275,277,5,45,0,0,276,262,1,0,0,0,276,263,1,0,0,0,277,290,1,0,0,0,278,
  	283,10,21,0,0,279,280,5,46,0,0,280,281,3,16,8,0,281,282,5,47,0,0,282,
  	284,1,0,0,0,283,279,1,0,0,0,284,285,1,0,0,0,285,283,1,0,0,0,285,286,1,
  	0,0,0,286,290,1,0,0,0,287,288,10,20,0,0,288,290,7,0,0,0,289,221,1,0,0,
  	0,289,224,1,0,0,0,289,227,1,0,0,0,289,230,1,0,0,0,289,233,1,0,0,0,289,
  	236,1,0,0,0,289,239,1,0,0,0,289,242,1,0,0,0,289,245,1,0,0,0,289,248,1,
  	0,0,0,289,251,1,0,0,0,289,257,1,0,0,0,289,260,1,0,0,0,289,278,1,0,0,0,
  	289,287,1,0,0,0,290,293,1,0,0,0,291,289,1,0,0,0,291,292,1,0,0,0,292,17,
  	1,0,0,0,293,291,1,0,0,0,294,312,5,10,0,0,295,312,5,56,0,0,296,297,5,56,
  	0,0,297,306,5,44,0,0,298,303,3,16,8,0,299,300,5,51,0,0,300,302,3,16,8,
  	0,301,299,1,0,0,0,302,305,1,0,0,0,303,301,1,0,0,0,303,304,1,0,0,0,304,
  	307,1,0,0,0,305,303,1,0,0,0,306,298,1,0,0,0,306,307,1,0,0,0,307,308,1,
  	0,0,0,308,312,5,45,0,0,309,312,3,20,10,0,310,312,3,22,11,0,311,294,1,
  	0,0,0,311,295,1,0,0,0,311,296,1,0,0,0,311,309,1,0,0,0,311,310,1,0,0,0,
  	312,19,1,0,0,0,313,326,5,52,0,0,314,315,5,53,0,0,315,320,3,16,8,0,316,
  	317,5,55,0,0,317,319,3,16,8,0,318,316,1,0,0,0,319,322,1,0,0,0,320,321,
  	1,0,0,0,320,318,1,0,0,0,321,323,1,0,0,0,322,320,1,0,0,0,323,324,5,54,
  	0,0,324,326,1,0,0,0,325,313,1,0,0,0,325,314,1,0,0,0,326,21,1,0,0,0,327,
  	345,5,8,0,0,328,345,5,9,0,0,329,345,5,57,0,0,330,345,5,58,0,0,331,345,
  	5,7,0,0,332,341,5,48,0,0,333,338,3,22,11,0,334,335,5,51,0,0,335,337,3,
  	22,11,0,336,334,1,0,0,0,337,340,1,0,0,0,338,336,1,0,0,0,338,339,1,0,0,
  	0,339,342,1,0,0,0,340,338,1,0,0,0,341,333,1,0,0,0,341,342,1,0,0,0,342,
  	343,1,0,0,0,343,345,5,49,0,0,344,327,1,0,0,0,344,328,1,0,0,0,344,329,
  	1,0,0,0,344,330,1,0,0,0,344,331,1,0,0,0,344,332,1,0,0,0,345,23,1,0,0,
  	0,346,347,7,6,0,0,347,25,1,0,0,0,38,29,31,47,50,61,63,74,82,96,113,128,
  	131,136,144,146,150,157,163,169,173,206,213,217,219,270,273,276,285,289,
  	291,303,306,311,320,325,338,341,344
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
    setState(36);
    match(MXParser::ID);
    setState(37);
    match(MXParser::LPAREN);
    setState(50);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72057594037927966) != 0)) {
      setState(38);
      type();
      setState(39);
      match(MXParser::ID);
      setState(47);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == MXParser::COMMA) {
        setState(41);
        match(MXParser::COMMA);
        setState(42);
        type();
        setState(43);
        match(MXParser::ID);
        setState(49);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(52);
    match(MXParser::RPAREN);
    setState(53);
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
    setState(55);
    match(MXParser::CLASS);
    setState(56);
    match(MXParser::ID);
    setState(57);
    match(MXParser::LBRACE);
    setState(63);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72057594037927966) != 0)) {
      setState(61);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
      case 1: {
        setState(58);
        class_var_def();
        break;
      }

      case 2: {
        setState(59);
        class_constructor();
        break;
      }

      case 3: {
        setState(60);
        function_def();
        break;
      }

      default:
        break;
      }
      setState(65);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(66);
    match(MXParser::RBRACE);
    setState(67);
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
    setState(69);
    type();
    setState(74);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MXParser::LBRACKET) {
      setState(70);
      match(MXParser::LBRACKET);
      setState(71);
      match(MXParser::RBRACKET);
      setState(76);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(77);
    match(MXParser::ID);
    setState(82);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MXParser::COMMA) {
      setState(78);
      match(MXParser::COMMA);
      setState(79);
      match(MXParser::ID);
      setState(84);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(85);
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
    setState(87);
    match(MXParser::ID);
    setState(88);
    match(MXParser::LPAREN);
    setState(89);
    match(MXParser::RPAREN);
    setState(90);
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
    setState(92);
    match(MXParser::LBRACE);
    setState(96);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 519340713071865790) != 0)) {
      setState(93);
      statement();
      setState(98);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(99);
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

std::vector<tree::TerminalNode *> MXParser::StatementContext::SEMICOLON() {
  return getTokens(MXParser::SEMICOLON);
}

tree::TerminalNode* MXParser::StatementContext::SEMICOLON(size_t i) {
  return getToken(MXParser::SEMICOLON, i);
}

std::vector<MXParser::Define_statementContext *> MXParser::StatementContext::define_statement() {
  return getRuleContexts<MXParser::Define_statementContext>();
}

MXParser::Define_statementContext* MXParser::StatementContext::define_statement(size_t i) {
  return getRuleContext<MXParser::Define_statementContext>(i);
}

std::vector<MXParser::ExprContext *> MXParser::StatementContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::StatementContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

tree::TerminalNode* MXParser::StatementContext::IF() {
  return getToken(MXParser::IF, 0);
}

tree::TerminalNode* MXParser::StatementContext::LPAREN() {
  return getToken(MXParser::LPAREN, 0);
}

tree::TerminalNode* MXParser::StatementContext::RPAREN() {
  return getToken(MXParser::RPAREN, 0);
}

std::vector<MXParser::StatementContext *> MXParser::StatementContext::statement() {
  return getRuleContexts<MXParser::StatementContext>();
}

MXParser::StatementContext* MXParser::StatementContext::statement(size_t i) {
  return getRuleContext<MXParser::StatementContext>(i);
}

tree::TerminalNode* MXParser::StatementContext::ELSE() {
  return getToken(MXParser::ELSE, 0);
}

tree::TerminalNode* MXParser::StatementContext::WHILE() {
  return getToken(MXParser::WHILE, 0);
}

tree::TerminalNode* MXParser::StatementContext::FOR() {
  return getToken(MXParser::FOR, 0);
}

tree::TerminalNode* MXParser::StatementContext::BREAK() {
  return getToken(MXParser::BREAK, 0);
}

tree::TerminalNode* MXParser::StatementContext::CONTINUE() {
  return getToken(MXParser::CONTINUE, 0);
}

tree::TerminalNode* MXParser::StatementContext::RETURN() {
  return getToken(MXParser::RETURN, 0);
}

MXParser::SuiteContext* MXParser::StatementContext::suite() {
  return getRuleContext<MXParser::SuiteContext>(0);
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
    setState(150);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(101);
      match(MXParser::SEMICOLON);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(102);
      define_statement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(103);
      expr(0);
      setState(104);
      match(MXParser::SEMICOLON);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(106);
      match(MXParser::IF);
      setState(107);
      match(MXParser::LPAREN);
      setState(108);
      expr(0);
      setState(109);
      match(MXParser::RPAREN);
      setState(110);
      statement();
      setState(113);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
      case 1: {
        setState(111);
        match(MXParser::ELSE);
        setState(112);
        statement();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(115);
      match(MXParser::WHILE);
      setState(116);
      match(MXParser::LPAREN);
      setState(117);
      expr(0);
      setState(118);
      match(MXParser::RPAREN);
      setState(119);
      statement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(121);
      match(MXParser::FOR);
      setState(122);
      match(MXParser::LPAREN);
      setState(128);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
      case 1: {
        setState(123);
        define_statement();
        break;
      }

      case 2: {
        setState(124);
        expr(0);
        setState(125);
        match(MXParser::SEMICOLON);
        break;
      }

      case 3: {
        setState(127);
        match(MXParser::SEMICOLON);
        break;
      }

      default:
        break;
      }
      setState(131);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 518214813164767136) != 0)) {
        setState(130);
        expr(0);
      }
      setState(133);
      match(MXParser::SEMICOLON);
      setState(136);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
      case 1: {
        setState(134);
        define_statement();
        break;
      }

      case 2: {
        setState(135);
        expr(0);
        break;
      }

      default:
        break;
      }
      setState(138);
      match(MXParser::RPAREN);
      setState(139);
      statement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(146);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case MXParser::BREAK: {
          setState(140);
          match(MXParser::BREAK);
          break;
        }

        case MXParser::CONTINUE: {
          setState(141);
          match(MXParser::CONTINUE);
          break;
        }

        case MXParser::RETURN: {
          setState(142);
          match(MXParser::RETURN);
          setState(144);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 518214813164767136) != 0)) {
            setState(143);
            expr(0);
          }
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(148);
      match(MXParser::SEMICOLON);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(149);
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
    setState(152);
    type();
    setState(157);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MXParser::LBRACKET) {
      setState(153);
      match(MXParser::LBRACKET);
      setState(154);
      match(MXParser::RBRACKET);
      setState(159);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(160);
    match(MXParser::ID);
    setState(163);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MXParser::ASSIGN) {
      setState(161);
      match(MXParser::ASSIGN);
      setState(162);
      expr(0);
    }
    setState(173);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MXParser::COMMA) {
      setState(165);
      match(MXParser::COMMA);
      setState(166);
      match(MXParser::ID);
      setState(169);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == MXParser::ASSIGN) {
        setState(167);
        match(MXParser::ASSIGN);
        setState(168);
        expr(0);
      }
      setState(175);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(176);
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

MXParser::Basic_exprContext* MXParser::ExprContext::basic_expr() {
  return getRuleContext<MXParser::Basic_exprContext>(0);
}

tree::TerminalNode* MXParser::ExprContext::LPAREN() {
  return getToken(MXParser::LPAREN, 0);
}

std::vector<MXParser::ExprContext *> MXParser::ExprContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::ExprContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

tree::TerminalNode* MXParser::ExprContext::RPAREN() {
  return getToken(MXParser::RPAREN, 0);
}

tree::TerminalNode* MXParser::ExprContext::SELF_PLUS() {
  return getToken(MXParser::SELF_PLUS, 0);
}

tree::TerminalNode* MXParser::ExprContext::SELF_MINUS() {
  return getToken(MXParser::SELF_MINUS, 0);
}

tree::TerminalNode* MXParser::ExprContext::MINUS() {
  return getToken(MXParser::MINUS, 0);
}

tree::TerminalNode* MXParser::ExprContext::LNOT() {
  return getToken(MXParser::LNOT, 0);
}

tree::TerminalNode* MXParser::ExprContext::BNOT() {
  return getToken(MXParser::BNOT, 0);
}

tree::TerminalNode* MXParser::ExprContext::NEW() {
  return getToken(MXParser::NEW, 0);
}

tree::TerminalNode* MXParser::ExprContext::ID() {
  return getToken(MXParser::ID, 0);
}

std::vector<tree::TerminalNode *> MXParser::ExprContext::LBRACKET() {
  return getTokens(MXParser::LBRACKET);
}

tree::TerminalNode* MXParser::ExprContext::LBRACKET(size_t i) {
  return getToken(MXParser::LBRACKET, i);
}

std::vector<tree::TerminalNode *> MXParser::ExprContext::RBRACKET() {
  return getTokens(MXParser::RBRACKET);
}

tree::TerminalNode* MXParser::ExprContext::RBRACKET(size_t i) {
  return getToken(MXParser::RBRACKET, i);
}

MXParser::ConstantContext* MXParser::ExprContext::constant() {
  return getRuleContext<MXParser::ConstantContext>(0);
}

tree::TerminalNode* MXParser::ExprContext::MULTIPLY() {
  return getToken(MXParser::MULTIPLY, 0);
}

tree::TerminalNode* MXParser::ExprContext::DIVIDE() {
  return getToken(MXParser::DIVIDE, 0);
}

tree::TerminalNode* MXParser::ExprContext::MOD() {
  return getToken(MXParser::MOD, 0);
}

tree::TerminalNode* MXParser::ExprContext::PLUS() {
  return getToken(MXParser::PLUS, 0);
}

tree::TerminalNode* MXParser::ExprContext::ARS() {
  return getToken(MXParser::ARS, 0);
}

tree::TerminalNode* MXParser::ExprContext::ALS() {
  return getToken(MXParser::ALS, 0);
}

tree::TerminalNode* MXParser::ExprContext::GN() {
  return getToken(MXParser::GN, 0);
}

tree::TerminalNode* MXParser::ExprContext::GE() {
  return getToken(MXParser::GE, 0);
}

tree::TerminalNode* MXParser::ExprContext::LN() {
  return getToken(MXParser::LN, 0);
}

tree::TerminalNode* MXParser::ExprContext::LE() {
  return getToken(MXParser::LE, 0);
}

tree::TerminalNode* MXParser::ExprContext::NE() {
  return getToken(MXParser::NE, 0);
}

tree::TerminalNode* MXParser::ExprContext::EQ() {
  return getToken(MXParser::EQ, 0);
}

tree::TerminalNode* MXParser::ExprContext::BAND() {
  return getToken(MXParser::BAND, 0);
}

tree::TerminalNode* MXParser::ExprContext::BXOR() {
  return getToken(MXParser::BXOR, 0);
}

tree::TerminalNode* MXParser::ExprContext::BOR() {
  return getToken(MXParser::BOR, 0);
}

tree::TerminalNode* MXParser::ExprContext::LAND() {
  return getToken(MXParser::LAND, 0);
}

tree::TerminalNode* MXParser::ExprContext::LOR() {
  return getToken(MXParser::LOR, 0);
}

tree::TerminalNode* MXParser::ExprContext::QUESTION_MARK() {
  return getToken(MXParser::QUESTION_MARK, 0);
}

tree::TerminalNode* MXParser::ExprContext::COLON() {
  return getToken(MXParser::COLON, 0);
}

tree::TerminalNode* MXParser::ExprContext::ASSIGN() {
  return getToken(MXParser::ASSIGN, 0);
}

tree::TerminalNode* MXParser::ExprContext::DOT() {
  return getToken(MXParser::DOT, 0);
}

std::vector<tree::TerminalNode *> MXParser::ExprContext::COMMA() {
  return getTokens(MXParser::COMMA);
}

tree::TerminalNode* MXParser::ExprContext::COMMA(size_t i) {
  return getToken(MXParser::COMMA, i);
}


size_t MXParser::ExprContext::getRuleIndex() const {
  return MXParser::RuleExpr;
}


std::any MXParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
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
    setState(219);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      setState(179);
      basic_expr();
      break;
    }

    case 2: {
      setState(180);
      match(MXParser::LPAREN);
      setState(181);
      expr(0);
      setState(182);
      match(MXParser::RPAREN);
      break;
    }

    case 3: {
      setState(184);
      _la = _input->LA(1);
      if (!(_la == MXParser::SELF_PLUS

      || _la == MXParser::SELF_MINUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(185);
      expr(19);
      break;
    }

    case 4: {
      setState(186);
      match(MXParser::MINUS);
      setState(187);
      expr(18);
      break;
    }

    case 5: {
      setState(188);
      match(MXParser::LNOT);
      setState(189);
      expr(17);
      break;
    }

    case 6: {
      setState(190);
      match(MXParser::BNOT);
      setState(191);
      expr(16);
      break;
    }

    case 7: {
      setState(192);
      match(MXParser::NEW);
      setState(193);
      match(MXParser::ID);
      break;
    }

    case 8: {
      setState(194);
      match(MXParser::NEW);
      setState(195);
      match(MXParser::ID);
      setState(196);
      match(MXParser::LPAREN);
      setState(197);
      match(MXParser::RPAREN);
      break;
    }

    case 9: {
      setState(198);
      match(MXParser::NEW);
      setState(199);
      match(MXParser::ID);
      setState(206);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(200);
          match(MXParser::LBRACKET);
          setState(201);
          expr(0);
          setState(202);
          match(MXParser::RBRACKET); 
        }
        setState(208);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
      }
      setState(213);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(209);
          match(MXParser::LBRACKET);
          setState(210);
          match(MXParser::RBRACKET); 
        }
        setState(215);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
      }
      setState(217);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
      case 1: {
        setState(216);
        constant();
        break;
      }

      default:
        break;
      }
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(291);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(289);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(221);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(222);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 7340032) != 0))) {
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

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(224);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(225);
          _la = _input->LA(1);
          if (!(_la == MXParser::PLUS

          || _la == MXParser::MINUS)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(226);
          expr(15);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(227);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(228);
          _la = _input->LA(1);
          if (!(_la == MXParser::ARS

          || _la == MXParser::ALS)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(229);
          expr(14);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(230);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(231);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 125829120) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(232);
          expr(13);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(233);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(234);
          _la = _input->LA(1);
          if (!(_la == MXParser::NE

          || _la == MXParser::EQ)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(235);
          expr(12);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(236);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(237);
          match(MXParser::BAND);
          setState(238);
          expr(11);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(239);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(240);
          match(MXParser::BXOR);
          setState(241);
          expr(10);
          break;
        }

        case 8: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(242);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(243);
          match(MXParser::BOR);
          setState(244);
          expr(9);
          break;
        }

        case 9: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(245);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(246);
          match(MXParser::LAND);
          setState(247);
          expr(8);
          break;
        }

        case 10: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(248);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(249);
          match(MXParser::LOR);
          setState(250);
          expr(7);
          break;
        }

        case 11: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(251);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(252);
          match(MXParser::QUESTION_MARK);
          setState(253);
          expr(0);
          setState(254);
          match(MXParser::COLON);
          setState(255);
          expr(6);
          break;
        }

        case 12: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(257);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(258);
          match(MXParser::ASSIGN);
          setState(259);
          expr(4);
          break;
        }

        case 13: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(260);

          if (!(precpred(_ctx, 22))) throw FailedPredicateException(this, "precpred(_ctx, 22)");
          setState(261);
          match(MXParser::DOT);
          setState(276);
          _errHandler->sync(this);
          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
          case 1: {
            setState(262);
            match(MXParser::ID);
            break;
          }

          case 2: {
            setState(263);
            match(MXParser::ID);
            setState(264);
            match(MXParser::LPAREN);
            setState(273);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if ((((_la & ~ 0x3fULL) == 0) &&
              ((1ULL << _la) & 518214813164767136) != 0)) {
              setState(265);
              expr(0);
              setState(270);
              _errHandler->sync(this);
              _la = _input->LA(1);
              while (_la == MXParser::COMMA) {
                setState(266);
                match(MXParser::COMMA);
                setState(267);
                expr(0);
                setState(272);
                _errHandler->sync(this);
                _la = _input->LA(1);
              }
            }
            setState(275);
            match(MXParser::RPAREN);
            break;
          }

          default:
            break;
          }
          break;
        }

        case 14: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(278);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(283); 
          _errHandler->sync(this);
          alt = 1;
          do {
            switch (alt) {
              case 1: {
                    setState(279);
                    match(MXParser::LBRACKET);
                    setState(280);
                    expr(0);
                    setState(281);
                    match(MXParser::RBRACKET);
                    break;
                  }

            default:
              throw NoViableAltException(this);
            }
            setState(285); 
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
          } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
          break;
        }

        case 15: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(287);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(288);
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
      setState(293);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
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

tree::TerminalNode* MXParser::Basic_exprContext::THIS() {
  return getToken(MXParser::THIS, 0);
}

tree::TerminalNode* MXParser::Basic_exprContext::ID() {
  return getToken(MXParser::ID, 0);
}

tree::TerminalNode* MXParser::Basic_exprContext::LPAREN() {
  return getToken(MXParser::LPAREN, 0);
}

tree::TerminalNode* MXParser::Basic_exprContext::RPAREN() {
  return getToken(MXParser::RPAREN, 0);
}

std::vector<MXParser::ExprContext *> MXParser::Basic_exprContext::expr() {
  return getRuleContexts<MXParser::ExprContext>();
}

MXParser::ExprContext* MXParser::Basic_exprContext::expr(size_t i) {
  return getRuleContext<MXParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> MXParser::Basic_exprContext::COMMA() {
  return getTokens(MXParser::COMMA);
}

tree::TerminalNode* MXParser::Basic_exprContext::COMMA(size_t i) {
  return getToken(MXParser::COMMA, i);
}

MXParser::Formatted_stringContext* MXParser::Basic_exprContext::formatted_string() {
  return getRuleContext<MXParser::Formatted_stringContext>(0);
}

MXParser::ConstantContext* MXParser::Basic_exprContext::constant() {
  return getRuleContext<MXParser::ConstantContext>(0);
}


size_t MXParser::Basic_exprContext::getRuleIndex() const {
  return MXParser::RuleBasic_expr;
}


std::any MXParser::Basic_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MXParserVisitor*>(visitor))
    return parserVisitor->visitBasic_expr(this);
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
    setState(311);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(294);
      match(MXParser::THIS);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(295);
      match(MXParser::ID);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(296);
      match(MXParser::ID);
      setState(297);
      match(MXParser::LPAREN);
      setState(306);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 518214813164767136) != 0)) {
        setState(298);
        expr(0);
        setState(303);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == MXParser::COMMA) {
          setState(299);
          match(MXParser::COMMA);
          setState(300);
          expr(0);
          setState(305);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(308);
      match(MXParser::RPAREN);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(309);
      formatted_string();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(310);
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
    setState(325);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MXParser::FORMAT_STRING_WHOLE: {
        enterOuterAlt(_localctx, 1);
        setState(313);
        match(MXParser::FORMAT_STRING_WHOLE);
        break;
      }

      case MXParser::FORMAT_STRING_HEAD: {
        enterOuterAlt(_localctx, 2);
        setState(314);
        match(MXParser::FORMAT_STRING_HEAD);
        setState(315);
        expr(0);
        setState(320);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
        while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1 + 1) {
            setState(316);
            match(MXParser::FORMAT_STRING_BODY);
            setState(317);
            expr(0); 
          }
          setState(322);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
        }
        setState(323);
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
    setState(344);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MXParser::TRUE: {
        enterOuterAlt(_localctx, 1);
        setState(327);
        match(MXParser::TRUE);
        break;
      }

      case MXParser::FALSE: {
        enterOuterAlt(_localctx, 2);
        setState(328);
        match(MXParser::FALSE);
        break;
      }

      case MXParser::INT_LITERAL: {
        enterOuterAlt(_localctx, 3);
        setState(329);
        match(MXParser::INT_LITERAL);
        break;
      }

      case MXParser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 4);
        setState(330);
        match(MXParser::STRING_LITERAL);
        break;
      }

      case MXParser::NULL_: {
        enterOuterAlt(_localctx, 5);
        setState(331);
        match(MXParser::NULL_);
        break;
      }

      case MXParser::LBRACE: {
        enterOuterAlt(_localctx, 6);
        setState(332);
        match(MXParser::LBRACE);
        setState(341);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 432627039204279168) != 0)) {
          setState(333);
          constant();
          setState(338);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == MXParser::COMMA) {
            setState(334);
            match(MXParser::COMMA);
            setState(335);
            constant();
            setState(340);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(343);
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
    setState(346);
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
    case 0: return precpred(_ctx, 15);
    case 1: return precpred(_ctx, 14);
    case 2: return precpred(_ctx, 13);
    case 3: return precpred(_ctx, 12);
    case 4: return precpred(_ctx, 11);
    case 5: return precpred(_ctx, 10);
    case 6: return precpred(_ctx, 9);
    case 7: return precpred(_ctx, 8);
    case 8: return precpred(_ctx, 7);
    case 9: return precpred(_ctx, 6);
    case 10: return precpred(_ctx, 5);
    case 11: return precpred(_ctx, 4);
    case 12: return precpred(_ctx, 22);
    case 13: return precpred(_ctx, 21);
    case 14: return precpred(_ctx, 20);

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
