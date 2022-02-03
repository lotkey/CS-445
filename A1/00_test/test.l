%{
#include <stdio.h>
void showError();
%}

digit           [0-9]
number          {digit}+
alphachar       [a-zA-Z]
identifier      {alphachar}[{alphachar}{digit}]*
whitespace      [ \t]

%%
{identifier}    {return (IDENTIFIER);}
{number}        {return (NUM);}
.               {return (OTHER);}

%%

void showError() {
    printf("Other input");
}