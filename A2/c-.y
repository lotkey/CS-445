%{
// // // // // // // // // // // // // // // // // // // // // // // 
// CS445 - Calculator Example Program written in the style of the C-
// compiler for the class.
//
// Robert Heckendorn
// Jan 21, 2021    

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>

#include "scanType.hpp"  // TokenData Type
#include "strutil.hpp"

double vars[26];    

extern int yylex();
extern FILE *yyin;
extern int line;         // ERR line number from the scanner!!
extern int numErrors;    // ERR err count

#define YYERROR_VERBOSE
void yyerror(const char *msg)
{
    std::cout << "ERROR(" << line << "): " << msg << std::endl;
    numErrors++;
}

%}

// this is included in the tab.h file
// so scanType.hpp must be included before the tab.h file!!!!
%union {
    TokenData *tokenData;
    double value;
}

%token <tokenData> ID NUMCONST CHARCONST STRINGCONST BOOLCONST
%token WHILE IF FOR TO RETURN BREAK BY DO
%token NOT AND OR
%token ADD RAND MUL DIV MOD SUB ASGN ADDASGN SUBASGN MULASGN DIVASGN
%token THEN ELSE BGN END
%token RPAREN LPAREN RBRACK LBRACK
%token STATIC TYPESPEC 
%token SEMI LT LEQ GT GEQ EQ NEQ INC DEC COL COM

%%

program             : declList
                    ;

declList            : declList decl | decl
                    ;

decl                : varDecl | funDecl
                    ;

varDecl             : TYPESPEC varDeclList SEMI
                    ;

scopedVarDecl       : STATIC TYPESPEC varDeclList SEMI
                    | TYPESPEC varDeclList SEMI
                    ;

varDeclList         : varDeclList COM varDeclInit | varDeclInit
                    ;

varDeclInit         : varDeclId
                    | varDeclId COL simpleExp
                    ;
                
varDeclId           : ID | ID LBRACK NUMCONST RBRACK
                    ;

funDecl             : TYPESPEC ID LPAREN parms RPAREN compoundStmt
                    | ID LPAREN parms RPAREN compoundStmt
                    ;

parms               : 
                    | parmList
                    ;

parmList            : parmList SEMI parmTypeList | parmTypeList
                    ;

parmTypeList        : TYPESPEC parmIdList
                    ;

parmIdList          : parmIdList COM parmId | parmId
                    ;

parmId              : ID | ID LBRACK RBRACK
                    ;

stmt                : expStmt | compoundStmt | returnStmt 
                    | breakStmt | closedStmt | openStmt
                    ;

expStmt             : exp SEMI | SEMI
                    ;

compoundStmt        : BGN localDecls stmtList END
                    | BGN stmtList END
                    | BGN localDecls END
                    | BGN END
                    ;

localDecls          : localDecls scopedVarDecl
                    ;

stmtList            : stmtList stmt
                    ;

closedStmt          : selectStmtClosed | iterStmtClosed
                    ;

openStmt            : selectStmtOpen | iterStmtOpen
                    ;

selectStmtOpen      : IF simpleExp THEN closedStmt
                    | IF simpleExp THEN openStmt
                    | IF simpleExp THEN closedStmt ELSE openStmt
                    ;

selectStmtClosed    : IF simpleExp THEN closedStmt ELSE closedStmt
                    | expStmt | compoundStmt | returnStmt | breakStmt
                    ;

iterStmtOpen        : WHILE simpleExp DO openStmt
                    | FOR ID ASGN iterRange DO openStmt
                    ;

iterStmtClosed      : WHILE simpleExp DO closedStmt
                    | FOR ID ASGN iterRange DO closedStmt
                    ;

iterRange           : simpleExp TO simpleExp
                    | simpleExp TO simpleExp BY simpleExp
                    ;

returnStmt          : RETURN SEMI | RETURN exp SEMI
                    ;

breakStmt           : BREAK SEMI
                    ;

exp                 : mutable assignop exp
                    | mutable INC | mutable DEC | simpleExp
                    ;

assignop            : ASGN | ADDASGN | SUBASGN | DIVASGN | MULASGN
                    ;

simpleExp           : simpleExp OR andExp | andExp
                    ;

andExp              : andExp AND unaryRelExp | unaryRelExp
                    ;

unaryRelExp         : NOT unaryRelExp | relExp
                    ;

relExp              : sumExp relop sumExp | sumExp
                    ;

relop               : LT | LEQ | GT | GEQ | EQ | NEQ
                    ;

sumExp              : sumExp sumop mulExp | mulExp
                    ;

sumop               : ADD | SUB
                    ;

mulExp              : mulExp mulop unaryExp | unaryExp
                    ;

mulop               : MUL | DIV | MOD
                    ;

unaryExp            : unaryop unaryExp | factor
                    ;

unaryop             : SUB | MUL | RAND
                    ;

factor              : mutable | immutable
                    ;

mutable             : ID | ID LBRACK exp RBRACK
                    ;

immutable           : LPAREN exp RPAREN | call | constant
                    ;

call                : ID LPAREN argList RPAREN
                    | ID LPAREN RPAREN
                    ;

argList             : argList COM exp | exp
                    ;

constant            : NUMCONST | CHARCONST | STRINGCONST | BOOLCONST
                    ;

%%
extern int yydebug;
int main(int argc, char *argv[])
{
    if (argc > 1) {
        if ((yyin = fopen(argv[1], "r"))) {
            // file open successful
        }
        else {
            // failed to open file
            printf("ERROR: failed to open \'%s\'\n", argv[1]);
            exit(1);
        }
    }

    // init variables a through z
    for (int i=0; i<26; i++) vars[i] = 0.0;

    // do the parsing
    numErrors = 0;
    yyparse();

    return 0;
}
