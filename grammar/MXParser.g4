parser grammar MXParser;

options { tokenVocab=MXLexer; }

mxprog
    : function* EOF
    ;

function
    : type ID LPAREN RPAREN block
    ;

type
    : INT
    | VOID
    ;

block
    : LBRACE statement* RBRACE
    ;

statement
    : expression SEMICOLON
    | returnStmt
    | ifStmt
    ;

expression
    : INT_LITERAL
    | ID
    | expression (PLUS | MINUS | MULTIPLY | DIVIDE) expression
    | LPAREN expression RPAREN
    ;

returnStmt
    : RETURN expression? SEMICOLON
    ;

ifStmt
    : IF LPAREN expression RPAREN statement (ELSE statement)?
    ;
