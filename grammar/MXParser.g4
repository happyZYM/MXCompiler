parser grammar MXParser;

options { tokenVocab=MXLexer; }

mxprog
    : (class_def|define_statement|function_def)+ EOF
    ;

function_def
    : type ID LPAREN ((type ID)(COMMA type ID)*)? RPAREN suite
    ;

class_def : CLASS ID LBRACE (class_var_def|class_constructor|function_def)* RBRACE SEMICOLON;
class_var_def : type (LBRACKET RBRACKET)* ID (COMMA ID )* SEMICOLON;
class_constructor : ID LPAREN RPAREN suite;
suite : LBRACE statement* RBRACE;
statement
    : SEMICOLON
    | define_statement
    | expr SEMICOLON
    | IF LPAREN expr RPAREN statement (ELSE statement)?
    | WHILE LPAREN expr RPAREN statement
    | FOR LPAREN (define_statement|(expr SEMICOLON)|SEMICOLON) expr? SEMICOLON (define_statement|expr)? RPAREN statement
    | (BREAK|CONTINUE|(RETURN expr?)) SEMICOLON
    | suite
    ;
define_statement : type (LBRACKET RBRACKET)* ID (ASSIGN expr)? (COMMA ID (ASSIGN expr)?)* SEMICOLON;
expr
    : basic_expr
    | LPAREN expr RPAREN
    | expr DOT (ID|(ID LPAREN (expr (COMMA expr)*)? RPAREN))
    | expr (LBRACKET expr RBRACKET)+
    | expr (SELF_PLUS | SELF_MINUS)
    | (SELF_PLUS | SELF_MINUS) expr
    | MINUS expr
    | LNOT expr
    | BNOT expr
    | expr (MULTIPLY|DIVIDE|MOD) expr
    | expr (PLUS|MINUS) expr
    | expr (ARS|ALS) expr
    | expr (GN|GE|LN|LE) expr
    | expr (NE|EQ) expr
    | expr BAND expr
    | expr BXOR expr
    | expr BOR expr
    | expr LAND expr
    | expr LOR expr
    | expr QUESTION_MARK expr COLON expr
    | <assoc=right> expr ASSIGN expr
    | NEW ID
    | NEW ID LPAREN RPAREN
    | NEW ID (LBRACKET expr RBRACKET)*(LBRACKET RBRACKET)*constant?
    ;

basic_expr
    : THIS
    | ID
    | ID LPAREN (expr (COMMA expr)*)? RPAREN
    | formatted_string
    | constant
    ;

formatted_string : FORMAT_STRING_WHOLE | (FORMAT_STRING_HEAD expr (FORMAT_STRING_BODY expr)*? FORMAT_STRING_TAIL);
constant : TRUE
          |FALSE
          |INT_LITERAL
          |STRING_LITERAL
          |NULL
          |LBRACE (constant (COMMA constant)*)? RBRACE;
type
    : INT
    | BOOL
    | STRING
    | VOID
    | ID
    ;