%{
// this *order* of these includes is mandatory
#include <algorithm>
#include <string>
#include <cstring>

#include "scanType.hpp"  // TokenData Type
#include "c-.tab.h"  // token definitions from the bison
#include "strutil.hpp"

int line = 1;
int numErrors;    // ERR err count

static int setValue(int linenum, int tokenClass, char *svalue)
{
    int i = 0;
    // create the pass-back data space
    yylval.tokenData = new TokenData;

    // fill it up
    yylval.tokenData->linenum = linenum;
    yylval.tokenData->tokenstr = std::string(svalue);
  
    switch (tokenClass) {
        case ID:
            break;
        case NUMCONST:
            yylval.tokenData->numConst = std::atoi(svalue);
            break;
        case CHARCONST:
            yylval.tokenData->charConst = strutil::get_first_char(strutil::remove_quotes(svalue));
            break;
        case BOOLCONST:
            yylval.tokenData->boolConst = yylval.tokenData->tokenstr == "true";
            break;
        case STRINGCONST:
            yylval.tokenData->stringConst = strutil::make_str(strutil::remove_quotes(svalue));
            break;
        default:
            break;

    }

    // return the tokenclass
    return tokenClass;
}

%}

%option noyywrap

%%
\#\#.*\n                    { line++; }
\"((\\\")|([^\n\"]))*\"     { return setValue(line, STRINGCONST, yytext); }
\'((\\\')|([^\n\']))*\'     { return setValue(line, CHARCONST, yytext); }
\n                          { line++; }
"while"                     { return setValue(line, WHILE, yytext); }
"if"                        { return setValue(line, IF, yytext); }
"for"                       { return setValue(line, FOR, yytext); }
"to"                        { return setValue(line, TO, yytext); }
"return"                    { return setValue(line, RETURN, yytext); }
"break"                     { return setValue(line, BREAK, yytext); }
"not"                       { return setValue(line, NOT, yytext); }
"and"                       { return setValue(line, AND, yytext); }
"or"                        { return setValue(line, OR, yytext); }
"by"                        { return setValue(line, BY, yytext); }
"do"                        { return setValue(line, DO, yytext); }
"then"                      { return setValue(line, THEN, yytext); }
"else"                      { return setValue(line, ELSE, yytext); }
"begin"                     { return setValue(line, BGN, yytext); }
"end"                       { return setValue(line, END, yytext); }
"static"                    { return setValue(line, STATIC, yytext); }
"int"|"bool"|"char"         { return setValue(line, TYPESPEC, yytext); }
"true"|"false"              { return setValue(line, BOOLCONST, yytext); }
"("                         { return setValue(line, LPAREN, yytext); }
")"                         { return setValue(line, RPAREN, yytext); }
"["                         { return setValue(line, LBRACK, yytext); }
"]"                         { return setValue(line, RBRACK, yytext); }
"?"                         { return setValue(line, RAND, yytext); }
"*"                         { return setValue(line, MUL, yytext); }
"/"                         { return setValue(line, DIV, yytext); }
"%"                         { return setValue(line, MOD, yytext); }
"+"                         { return setValue(line, ADD, yytext); }
"-"                         { return setValue(line, SUB, yytext); }
"<-"                        { return setValue(line, ASGN, yytext); }
"+="                        { return setValue(line, ADDASGN, yytext); }
"-="                        { return setValue(line, SUBASGN, yytext); }
"*="                        { return setValue(line, MULASGN, yytext); }
"/="                        { return setValue(line, DIVASGN, yytext); }
";"                         { return setValue(line, SEMI, yytext); }
"<"                         { return setValue(line, LT, yytext); }
"<="                        { return setValue(line, LEQ, yytext); }
">"                         { return setValue(line, GT, yytext); }
">="                        { return setValue(line, GEQ, yytext); }
"="                         { return setValue(line, EQ, yytext); }
"!="                        { return setValue(line, NEQ, yytext); }
"++"                        { return setValue(line, INC, yytext); }
"--"                        { return setValue(line, DEC, yytext); }
":"                         { return setValue(line, COL, yytext); }
","                         { return setValue(line, COM, yytext); }
[a-zA-Z][a-zA-Z0-9]*        { return setValue(line, ID, yytext); }
[0-9]+                      { return setValue(line, NUMCONST, yytext); }
[ \t]                       ;
.                           { printf("ERROR(%d): Invalid or misplaced input character: \'%c\'. Character Ignored.\n", line, yytext[0]); numErrors++; }
%%