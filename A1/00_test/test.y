%{
#include <stdio.h>

int yylex();
int yyerror(char *s);

%}

%token <number> NUM
%token <identifier> IDENTIFIER
%token <other> OTHER

%union{
    char name[20];
    int numdata;
}

%%
stmt_list
    : statement '\n'
    | stmt_list statement '\n'
    ;

statement
    : NUM { printf("You entered a number: %d", $1); }
    | IDENTIFIER { printf("You entered an identifier: %s", $1); }
    | OTHER { printf("You entered something else idk: %s", $1); }
    ;

%%

struct sym * sym_lookup(char * s)
{
    char * p;
    struct sym * sp;

    for (sp=sym_tbl; sp < &sym_tbl[NSYMS]; sp++)
    {
        if (sp->name && strcmp(sp->name, s) == 0)
            return sp;

        if (sp->name)
            continue;

        sp->name = strdup(s);
        return sp; 
    }
   
    yyerror("Too many symbols");
    exit(-1);
    return NULL; /* unreachable */
}