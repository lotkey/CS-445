#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20130304

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "calc.y"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sym.h"
#include "symlist.h"
  /* declare the symlist*/
  /* this will contain all the syms*/
  /* it is dynamically allocated*/
  /*   so that there is no limit enforced by this program*/
  /*   to the amount of syms allowed*/
  struct symlist list;
#line 16 "calc.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
  double dval;
  /* instead of a symptr, the symname is now a char**/
  /* this makes it easier to add a new sym to the symlist*/
  char* symname;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 46 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define NAME 257
#define NUMBER 258
#define UMINUS 259
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,    2,    2,    2,    1,    1,    1,    1,    1,
    1,    1,    1,
};
static const short yylen[] = {                            2,
    2,    3,    3,    1,    1,    3,    3,    3,    3,    2,
    3,    1,    1,
};
static const short yydefred[] = {                         0,
    0,   12,    0,    4,    0,    0,    0,    0,    0,   13,
   10,    0,    0,    0,    0,    0,    0,    1,    0,   11,
    2,    0,    0,    8,    9,
};
static const short yydgoto[] = {                          6,
    7,    8,
};
static const short yysindex[] = {                       -40,
  -58,    0,  -38,    0,  -38,  -40,  -32,    4,  -38,    0,
    0,  -17,   12,  -38,  -38,  -38,  -38,    0,  -32,    0,
    0,  -26,  -26,    0,    0,
};
static const short yyrindex[] = {                         0,
   -9,    0,    0,    0,    0,    0,   17,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   19,    0,
    0,   -6,   -1,    0,    0,
};
static const short yygindex[] = {                         0,
    3,   25,
};
#define YYTABLESIZE 220
static const short yytable[] = {                          5,
   13,    5,    9,    7,    3,   11,    3,   12,    6,   16,
   15,   19,   14,   18,   17,   16,   22,   23,   24,   25,
   17,   21,    4,   20,   16,   15,    5,   14,    3,   17,
   13,    0,   13,   13,    7,   13,    7,   13,    7,    6,
    0,    6,    0,    6,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    1,    2,   10,    2,
};
static const short yycheck[] = {                         40,
   10,   40,   61,   10,   45,    3,   45,    5,   10,   42,
   43,    9,   45,   10,   47,   42,   14,   15,   16,   17,
   47,   10,   63,   41,   42,   43,   10,   45,   10,   47,
    6,   -1,   42,   43,   41,   45,   43,   47,   45,   41,
   -1,   43,   -1,   45,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  257,  258,
};
#define YYFINAL 6
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 259
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,"'\\n'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,"'('","')'","'*'","'+'",0,"'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,
0,0,"'='",0,"'?'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,"NAME","NUMBER","UMINUS",
};
static const char *yyrule[] = {
"$accept : statement_list",
"statement_list : statement '\\n'",
"statement_list : statement_list statement '\\n'",
"statement : NAME '=' expression",
"statement : '?'",
"statement : expression",
"expression : expression '+' expression",
"expression : expression '-' expression",
"expression : expression '*' expression",
"expression : expression '/' expression",
"expression : '-' expression",
"expression : '(' expression ')'",
"expression : NUMBER",
"expression : NAME",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 75 "calc.y"

int main(){
  // initialize the symlist
  symlistinit(&list);
  // parse
  yyparse();
}

void symlistinit(struct symlist* list){
  // initalize the symlist by allocating memory for 10 slots
  symlistinitwithlen(list, 10);
}

void symlistinitwithlen(struct symlist* list, int listlen){
  // if listlen is not a valid number, intialize the bufsize to 10
  // the bufsize is the amount of memory that is added when reallocating
  (*list).bufsize = listlen > 0 ? listlen : 10;
  // initialize the size to bufsize
  (*list).size = (*list).bufsize;
  // allocate memory for the sym*
  (*list).syms = malloc(sizeof(struct sym) * (*list).bufsize);
  // allocate memory for the bool*
  (*list).modifiable = malloc(sizeof(bool) * (*list).bufsize);
  // len is the amount of valid syms there are
  // size is different
  //   size is the amount of syms that there are memory for
  //   the max capacity of syms
  (*list).len = 0;
  struct sym pi;
  pi.name = "PI";
  pi.value = 3.14159;
  struct sym phi;
  phi.name = "PHI";
  phi.value = 1.61803;
  // add PI and PHI and make them not modifiable
  symlistappend(list, phi, false);
  symlistappend(list, pi, false);
}

bool symlistappend(struct symlist* list, struct sym newsym, bool mod){
  // if the item is in the list and is not modifiable
  if(symlistinlist(list, newsym.name) && !(*list).modifiable[symlistindexof(list, newsym.name)]){
    // do nothing, return false
    return false;
  }
  // if the item is in the list but modifiable
  else if(symlistinlist(list, newsym.name)){
    // modify it and return true
    (*list).syms[symlistindexof(list, newsym.name)].value = newsym.value;
    return true;
  }
  else{
    // add it to the list
    // if the max capacity has been reached,
    // allocate more memory
    if((*list).len >= (*list).size){
      (*list).size += (*list).bufsize;
      (*list).syms = realloc((*list).syms, (*list).size * sizeof(struct sym));
      (*list).modifiable = realloc((*list).modifiable, (*list).size * sizeof(bool));
    }
    int i, j;
    bool b = false;
    // loop through and add alphabetically
    for(i = 0; i < (*list).len && !b; i++){
      if(strcmp(newsym.name, (*list).syms[i].name) == -1 && (*list).modifiable[i]){
	// shift elements to the right
	for(j = (*list).len; j > i; j--){
	  (*list).syms[j] = (*list).syms[j - 1];
	}
	i--;
	b = true;
      }
    }
    // allocate memory for the sym
    (*list).syms[i].name = malloc(sizeof(char) * (strlen(newsym.name) + 1));
    strcpy((*list).syms[i].name, newsym.name);
    (*list).syms[i].value = newsym.value;
    (*list).modifiable[i] = mod;   
    (*list).len++;
    return true;
  }
}

bool symlistinlist(struct symlist* list, char* symname){
  int i;
  // loop through the sym list
  for(i = 0; i < (*list).len; i++){
    // if found, return true
    if(strcmp((*list).syms[i].name, symname) == 0){
      return true;
    }
  }
  // otherwise, return false
  return false;
}

int symlistindexof(struct symlist* list, char* symname){
  // same approach as symlistinlist()
  // if found, return the index
  // otherwise, return -1
  int i;
  for(i = 0; i < (*list).len; i++){
    if(strcmp((*list).syms[i].name, symname) == 0){
      return i;
    }
  }
  return -1;
}

void symlistprint(struct symlist* list){
  // loop through the list and print
  //   in the format required by the homework
  printf("num-syms: %i\n", (*list).len);
  int i;
  for(i = 0; i < (*list).len; i++){
    printf("\t%s => %f\n", (*list).syms[i].name, (*list).syms[i].value);
  }
}

struct sym* symlistlookup(struct symlist* list, char* symname){
  // return the address of the specific sym
  return &((*list).syms[symlistindexof(list, symname)]);
}

double symlistgetval(struct symlist* list, char* symname){
  int i;
  // loop through the sym list
  for(i = 0; i < (*list).len; i++){
    // if found, return the value associated with it
    if(strcmp((*list).syms[i].name, symname) == 0){
      return (*list).syms[i].value;
    }
  }
  // otherwise, return 0
  return 0.0;
}
#line 367 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 3:
#line 37 "calc.y"
	{ 
      /* add a new sym into the symlist*/
      struct sym s;
      /* assign the value the expression returns as the value*/
      s.value = yystack.l_mark[0].dval;
      /* assign NAME as the name*/
      strcpy(s.name, yystack.l_mark[-2].symname);
      /* add it and make it modifiable*/
      symlistappend(&list, s, true);
 }
break;
case 4:
#line 47 "calc.y"
	{ symlistprint(&list); }
break;
case 5:
#line 48 "calc.y"
	{ printf("= %g\n", yystack.l_mark[0].dval); }
break;
case 6:
#line 52 "calc.y"
	{ yyval.dval = yystack.l_mark[-2].dval + yystack.l_mark[0].dval; }
break;
case 7:
#line 53 "calc.y"
	{ yyval.dval = yystack.l_mark[-2].dval - yystack.l_mark[0].dval; }
break;
case 8:
#line 54 "calc.y"
	{ yyval.dval = yystack.l_mark[-2].dval * yystack.l_mark[0].dval; }
break;
case 9:
#line 55 "calc.y"
	{
  if(yystack.l_mark[0].dval == 0){
    /* return the value of the first operand*/
    yyval.dval = yystack.l_mark[-2].dval;
    /* print the error message*/
    printf("divide by zero\n");
  }else{
    /* otherwise, business as normal*/
    yyval.dval = yystack.l_mark[-2].dval / yystack.l_mark[0].dval;
  }
  }
break;
case 10:
#line 66 "calc.y"
	{ yyval.dval = -yystack.l_mark[0].dval; }
break;
case 11:
#line 67 "calc.y"
	{ yyval.dval = yystack.l_mark[-1].dval; }
break;
case 13:
#line 69 "calc.y"
	{
      yyval.dval = symlistgetval(&list, yystack.l_mark[0].symname);
      }
break;
#line 634 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
