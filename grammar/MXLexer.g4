lexer grammar MXLexer;

// Keywords
INT: 'int';
VOID: 'void';
IF: 'if';
ELSE: 'else';
RETURN: 'return';

// Operators
PLUS: '+';
MINUS: '-';
MULTIPLY: '*';
DIVIDE: '/';
ASSIGN: '=';

// Punctuation
LPAREN: '(';
RPAREN: ')';
LBRACE: '{';
RBRACE: '}';
SEMICOLON: ';';

// Identifiers
ID: [a-zA-Z_][a-zA-Z_0-9]*;

// Literals
INT_LITERAL: [0-9]+;

// Whitespace and comments
WS: [ \t\r\n]+ -> skip;
COMMENT: '//' ~[\r\n]* -> skip;
