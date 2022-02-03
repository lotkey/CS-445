%{
// this *order* of these includes is mandatory
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "scanType.h"  // TokenData Type
#include "c-.tab.h"  // token definitions from the bison
#include "strutil.h"

int line = 1;
int numErrors;    // ERR err count

static int setValue(int linenum, int tokenClass, char *svalue)
{
    int i = 0;
    char* newstr;
    // create the pass-back data space
    yylval.tokenData = new TokenData;

    // fill it up
    yylval.tokenData->linenum = linenum;
    yylval.tokenData->tokenstr = strdup(svalue);  // duplicating string!!
  
    switch (tokenClass) {
        case ID:
            break;
        case NUMCONST:
            yylval.tokenData->numConst = atoi(svalue);
            break;
        case CHARCONST:
            i = 1;
            yylval.tokenData->charConst = getChar(svalue, &i);
            break;
        case BOOLCONST:
            if (strcmp(svalue, "true") == 0) {
                yylval.tokenData->boolConst = 1;
            } else if (strcmp(svalue, "false") == 0) {
                yylval.tokenData->boolConst = 0;
            }
            break;
        case STRINGCONST:
            removeQuotes(svalue, &newstr);
            yylval.tokenData->stringConst = makeStr(newstr);
            free(newstr);
            break;
        case KEYWORD:
            for (i = 0; i < strlen(yylval.tokenData->tokenstr); i++) {
                yylval.tokenData->tokenstr[i] = toupper(yylval.tokenData->tokenstr[i]);
            }

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
\"((\\\")|([^\n\"]))*\"    { return setValue(line, STRINGCONST, yytext); }
\'((\\\')|([^\n\']))*\'    { return setValue(line, CHARCONST, yytext); }
(true)|(false)              { return setValue(line, BOOLCONST, yytext); }
while|if|for|to|return|break|not|and|or|by|do|then|else|begin|end|int|static|bool|char   { return setValue(line, KEYWORD, yytext); }
[a-zA-Z][a-zA-Z0-9]*        { return setValue(line, ID, yytext); }
[0-9]+                      { return setValue(line, NUMCONST, yytext); }
\(|\)|\?|\*|\/|\%|\-|\[|\]|\+|\<\-|\+\=|\-\=|\*\=|\/\=|\;|\<|\<\=|\>|\>\=|\=|\!\=|\+\+|\-\-|\:|\, { return setValue(line, TOKEN, yytext); }
[ \t]                       ;
\n                          { line++; return setValue(line, yytext[0], yytext ); }
.                           { printf("ERROR(%d): Invalid or misplaced input character: \'%c\'. Character Ignored.\n", line, yytext[0]); numErrors++; }
%%