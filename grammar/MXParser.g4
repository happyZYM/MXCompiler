parser grammar MXParser;

options { tokenVocab=MXLexer; }

mxprog
    : (class_def|define_statement|function_def)+ EOF
    ;

function_def
    : type (LBRACKET RBRACKET)* ID LPAREN ((type (LBRACKET RBRACKET)* ID)(COMMA type (LBRACKET RBRACKET)* ID)*)? RPAREN suite
    ;

class_def : CLASS ID LBRACE (class_var_def|class_constructor|function_def)* RBRACE SEMICOLON;
class_var_def : type (LBRACKET RBRACKET)* ID (COMMA ID )* SEMICOLON;
class_constructor : ID LPAREN RPAREN suite;
suite : LBRACE statement* RBRACE;
statement
    : SEMICOLON #empty_statement
    | define_statement #definition_statement
    | expr SEMICOLON #expr_statement
    | IF LPAREN expr RPAREN statement (ELSE statement)? #if_statement
    | WHILE LPAREN expr RPAREN statement #while_statement
    | FOR LPAREN (define_statement|(expr SEMICOLON)|SEMICOLON) expr? SEMICOLON expr? RPAREN statement #for_statement
    | (BREAK|CONTINUE|(RETURN expr?)) SEMICOLON #jmp_statement
    | suite #suite_statement
    ;
define_statement : type (LBRACKET RBRACKET)* ID (ASSIGN expr)? (COMMA ID (ASSIGN expr)?)* SEMICOLON;
expr
    : basic_expr #basic_expression
    | NEW type (LBRACKET expr? RBRACKET)+constant? #new_array_expression
    | NEW type LPAREN RPAREN #new_construct_expression
    | NEW type #new_expression
    | expr DOT (ID|(ID LPAREN (expr (COMMA expr)*)? RPAREN)) #access_expression
    | expr (LBRACKET expr RBRACKET)+ #index_expression
    | expr (SELF_PLUS | SELF_MINUS) #suffix_expression
    | (SELF_PLUS | SELF_MINUS) expr #prefix_expression
    | MINUS expr #opposite_expression
    | LNOT expr #lnot_expression
    | BNOT expr #bnot_expression
    | expr (MULTIPLY|DIVIDE|MOD) expr #mdm_expression
    | expr (PLUS|MINUS) expr #pm_expression
    | expr (ARS|ALS) expr #rl_expression
    | expr (GN|GE|LN|LE) expr #ggll_expression
    | expr (NE|EQ) expr #ne_expression
    | expr BAND expr #band_expression
    | expr BXOR expr #bxor_expression
    | expr BOR expr #bor_expression
    | expr LAND expr #land_expression
    | expr LOR expr #lor_expression
    | <assoc=right> expr QUESTION_MARK expr COLON expr #ternary_expression
    | <assoc=right> expr ASSIGN expr #assign_expression
    ;

basic_expr
    : THIS #this_expr
    | LPAREN expr RPAREN #paren_expr
    | ID #id_expr
    | ID LPAREN (expr (COMMA expr)*)? RPAREN #function_call_expr
    | formatted_string #formatted_string_expr
    | constant #constant_expr
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