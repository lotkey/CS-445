#define NAME 257
#define NUMBER 258
#define UMINUS 259
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
extern YYSTYPE yylval;
