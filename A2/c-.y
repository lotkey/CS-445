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
// so scanType.h must be included before the tab.h file!!!!
%union {
    TokenData *tokenData;
    double value;
}

%token <tokenData> ID NUMCONST CHARCONST STRINGCONST BOOLCONST TOKEN KEYWORD

%%

program             : declList
                    ;

declList            : declList decl | decl
                    ;

decl                : varDecl | funDecl
                    ;

varDecl             : typeSpec varDeclList ";"
                    ;

scopedVarDecl       : "static" typeSpec varDeclList ";"
                    | typeSpec varDeclList ";"
                    ;

varDeclList         : varDeclList "," varDeclInit | varDeclInit
                    ;

varDeclInit         : varDeclId
                    | varDeclId ":" simpleExp
                    ;
                
varDeclId           : ID | ID "[" NUMCONST "]"
                    ;

typeSpec            : "bool" | "char" | "int"
                    ;

funDecl             : typeSpec ID "(" parms ")" compoundStmt
                    | ID "(" parms ")" compoundStmt
                    ;

parms               : | parmList
                    ;

parmList            : parmList ";" parmTypeList | parmTypeList
                    ;

parmTypeList        : typeSpec parmIdList
                    ;

parmIdList          : parmIdList "," parmId | parmId
                    ;

parmId              : ID | ID "[" "]"
                    ;

stmt                : expStmt | compoundStmt | returnStmt 
                    | breakStmt | closedStmt | openStmt
                    ;

expStmt             : exp ";" | ";"
                    ;

compoundStmt        : "begin" localDecls stmtList "end"
                    ;

localDecls          : | localDecls scopedVarDecl
                    ;

stmtList            : | stmtList stmt
                    ;

closedStmt          : selectStmtClosed | iterStmtClosed
                    ;

openStmt            : selectStmtOpen | iterStmtOpen
                    ;

selectStmtOpen      : "if" simpleExp "then" closedStmt
                    | "if" simpleExp "then" openStmt
                    | "if" simpleExp "then" closedStmt "else" openStmt
                    ;

selectStmtClosed    : "if" simpleExp "then" closedStmt "else" closedStmt
                    | expStmt | compoundStmt | returnStmt | breakStmt
                    ;

iterStmtOpen        : "while" simpleExp "do" openStmt
                    | "for" ID "<-" iterRange "do" openStmt
                    ;

iterStmtClosed      : "while" simpleExp "do" closedStmt
                    | "for" ID "<-" iterRange "do" closedStmt
                    ;

iterRange           : simpleExp "to" simpleExp
                    | simpleExp "to" simpleExp "by" simpleExp
                    ;

returnStmt          : "return" ";" | "return" exp ";"
                    ;

breakStmt           : "break" ";"
                    ;

exp                 : mutable assignop exp
                    | mutable "++" | mutable "--" | simpleExp
                    ;

assignop            : "<-" | "+=" | "-=" | "/=" | "*-"
                    ;

simpleExp           : simpleExp "or" andExp | andExp
                    ;

andExp              : andExp "and" unaryRelExp | unaryRelExp
                    ;

unaryRelExp         : "not" unaryRelExp | relExp
                    ;

relExp              : sumExp relop sumExp | sumExp
                    ;

relop               : "<" | "<=" | ">" | ">=" | "=" | "!="
                    ;

sumExp              : sumExp sumop mulExp | mulExp
                    ;

sumop               : "+" | "-"
                    ;

mulExp              : mulExp mulop unaryExp | unaryExp
                    ;

mulop               : "*" | "/" | "%"
                    ;

unaryExp            : unaryop unaryExp | factor
                    ;

unaryop             : "-" | "*" | "?"
                    ;

factor              : mutable | immutable
                    ;

mutable             : ID | ID "[" exp "]"
                    ;

immutable           : "(" exp ")" | call | constant
                    ;

call                : ID "(" args ")"
                    ;

args                : | argList
                    ;

argList             : argList "," exp | exp
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
