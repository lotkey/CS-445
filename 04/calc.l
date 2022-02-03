%{ 
#include <string.h>
#include "y.tab.h"
#include "symlist.h"
%}

%%
([0-9]+|([0-9]*\.[0-9]+)([eE][+-]?[0-9]+)?) {
    yylval.dval = atof(yytext);
    return NUMBER;
    }

[ \t] ; /* ignore whitespace */

[A-Za-z][A-Za-z0-9]* {
    /* return symbol string */
    /* instead of a pointer to a symbol like previously */    
    yylval.symname = malloc(sizeof(yytext) + 1);
    strcpy(yylval.symname, yytext);
    return NAME;
    }

"$" { return 0; }
\n |
. { return yytext[0]; };
%%
int yywrap() { return 1; }
