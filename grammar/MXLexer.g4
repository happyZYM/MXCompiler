lexer grammar MXLexer;

// Keywords
VOID: 'void';
BOOL: 'bool';
INT: 'int';
STRING: 'string';
NEW: 'new';
CLASS: 'class';
NULL: 'null';
TRUE: 'true';
FALSE: 'false';
THIS: 'this';
IF: 'if';
ELSE: 'else';
FOR: 'for';
WHILE: 'while';
BREAK: 'break';
CONTINUE: 'continue';
RETURN: 'return';

// Operators
PLUS: '+';
MINUS: '-';
MULTIPLY: '*';
DIVIDE: '/';
MOD: '%';
GN: '>=';
GE: '>';
LN: '<=';
LE: '<';
NE: '!=';
EQ: '==';
LAND: '&&';
LOR: '||';
LNOT: '!';
ARS: '>>';
ALS: '<<';
BAND: '&';
BOR: '|';
BXOR: '^';
BNOT: '~';
ASSIGN: '=';
SELF_PLUS: '++';
SELF_MINUS: '--';
DOT: '.';
QUESTION_MARK: '?';
COLON: ':';

// Punctuation
LPAREN: '(';
RPAREN: ')';
LBRACKET: '[';
RBRACKET: ']';
LBRACE: '{';
RBRACE: '}';
SEMICOLON: ';';
COMMA: ',';
FORMAT_STRING_WHOLE: 'f"' FORMAT_STR_INTERNAL '"';
FORMAT_STRING_HEAD: 'f"' FORMAT_STR_INTERNAL '$';
FORMAT_STRING_TAIL: '$' FORMAT_STR_INTERNAL '"';
FORMAT_STRING_BODY: '$' FORMAT_STR_INTERNAL '$';
fragment FORMAT_STR_INTERNAL : (DOLLAR_IN_FORMAT_STR | ESC | ~[$"\\])*;
fragment FORMAT_STR_BEG: 'f"';
fragment FORMAT_STR_END: '"';
fragment DOLLAR_IN_FORMAT_STR: '$$';
fragment DOLLAR: '$';

// Identifiers
ID: [a-zA-Z][a-zA-Z_0-9]*;

// Literals
INT_LITERAL: [0-9]+;
STRING_LITERAL: '"' (ESC|~["\\])*? '"';
fragment ESC : '\\n'| '\\"' | '\\\\';

// Whitespace and comments
WS: [ \t\r\n]+ -> skip;
LINE_COMMENT : '//' .*? ('\r\n'|'\r'|'\n'|EOF) -> skip;
BLOCK_COMMENT: '/*' .*? '*/'       -> skip;