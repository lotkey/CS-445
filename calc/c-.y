%{
// // // // // // // // // // // // // // // // // // // // // // // 
// CS445 - Calculator Example Program written in the style of the C-
// compiler for the class.
//
// Robert Heckendorn
// Jan 21, 2021    

#include <stdio.h>
#include <string.h>
#include "scanType.h"  // TokenData Type
#include "strutil.h"

double vars[26];    

extern int yylex();
extern FILE *yyin;
extern int line;         // ERR line number from the scanner!!
extern int numErrors;    // ERR err count

#define YYERROR_VERBOSE
void yyerror(const char *msg)
{
    printf("ERROR(%d): %s\n", line, msg);
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
statementlist : statementlist statement
              | statement
              ;

statement     : '\n'
              | ID                      { printf("Line %i Token: ID Value: %s\n", $1->linenum, $1->tokenstr); }
              | KEYWORD                 { printf("Line %i Token: %s\n", $1->linenum, $1->tokenstr); }
              | NUMCONST                { printf("Line %i Token: NUMCONST Value: %d  Input: %s\n", $1->linenum, $1->numConst, $1->tokenstr); }
              | CHARCONST               {
                    if (getStrLen($1->tokenstr) > 3) {
                        printf("WARNING(%i): character is %i characters long and not a single character: \'%s\'. The first char will be used.\n", $1->linenum, (int)strlen($1->tokenstr) - 2, $1->tokenstr);
                    }
                    printf("Line %i Token: CHARCONST Value: \'%c\'  Input: %s\n", $1->linenum, $1->charConst, $1->tokenstr); 
                  }
              | STRINGCONST             { printf("Line %i Token: STRINGCONST Value: \"%s\"  Len: %i  Input: %s\n", $1->linenum, $1->stringConst, (int)strlen($1->stringConst), $1->tokenstr); }
              | BOOLCONST               { printf("Line %i Token: BOOLCONST Value: %d  Input: %s\n", $1->linenum, $1->boolConst, $1->tokenstr); }
              | TOKEN                   {
                    printf("Line %i Token: ", $1->linenum); //%s\n", $1->linenum, $1->tokenstr);
                    if (strcmp($1->tokenstr, "<-") == 0) {
                        printf("ASGN\n");
                    } else if (strcmp($1->tokenstr, "+=") == 0) {
                        printf("ADDASGN\n");
                    } else if (strcmp($1->tokenstr, "++") == 0) {
                        printf("INC\n");
                    } else if (strcmp($1->tokenstr, "--") == 0) {
                        printf("DEC\n");
                    } else if (strcmp($1->tokenstr, ">=") == 0) {
                        printf("GEQ\n");
                    } else if (strcmp($1->tokenstr, "<=") == 0) {
                        printf("LEQ\n");
                    } else if (strcmp($1->tokenstr, "!=") == 0) {
                        printf("NEQ\n");
                    } else {
                        printf("%s\n", $1->tokenstr);
                    }
                  }

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
