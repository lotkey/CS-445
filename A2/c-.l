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
\"((\\\")|([^\n\"]))*\"     { return STRINGCONST; }
\'((\\\')|([^\n\']))*\'     { return CHARCONST; }
\n                          { line++; }
"while"                     { return WHILE; }
"if"                        { return IF; }
"for"                       { return FOR; }
"to"                        { return TO; }
"return"                    { return RETURN; }
"break"                     { return BREAK; }
"not"                       { return NOT; }
"and"                       { return AND; }
"or"                        { return OR; }
"by"                        { return BY; }
"do"                        { return DO; }
"then"                      { return THEN; }
"else"                      { return ELSE; }
"begin"                     { return BGN; }
"end"                       { return END; }
"static"                    { return STATIC; }
"int"                       { return INT; }
"bool"                      { return BOOL; }
"char"                      { return CHAR; }
"true"|"false"              { return BOOLCONST; }
"("                         { return LPAREN; }
")"                         { return RPAREN; }
"["                         { return LBRACK; }
"]"                         { return RBRACK; }
"?"                         { return RAND; }
"*"                         { return MUL; }
"/"                         { return DIV; }
"%"                         { return MOD; }
"+"                         { return ADD; }
"-"                         { return SUB; }
"<-"                        { return ASGN; }
"+="                        { return ADDASGN; }
"-="                        { return SUBASGN; }
"*="                        { return MULASGN; }
"/="                        { return DIVASGN; }
";"                         { return SEMI; }
"<"                         { return LT; }
"<="                        { return LEQ; }
">"                         { return GT; }
">="                        { return GEQ; }
"="                         { return EQ; }
"!="                        { return NEQ; }
"++"                        { return INC; }
"--"                        { return DEC; }
":"                         { return COL; }
","                         { return COM; }
[a-zA-Z][a-zA-Z0-9]*        { return ID; }
[0-9]+                      { return NUMCONST; }
[ \t]                       ;
.                           { printf("ERROR(%d): Invalid or misplaced input character: \'%c\'. Character Ignored.\n", line, yytext[0]); numErrors++; }
%%