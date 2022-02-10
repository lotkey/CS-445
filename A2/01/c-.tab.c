/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "c-.y"

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
#include "AST/AST_node.hpp"

double vars[26];    

extern int yylex();
extern FILE *yyin;
extern int line;         // ERR line number from the scanner!!
extern int numErrors;    // ERR err count
extern std::vector<TokenData*> tokens;
AST_node* tree_root;

#define YYERROR_VERBOSE
void yyerror(const char *msg)
{
    std::cout << "ERROR(" << line << "): " << msg << std::endl;
    numErrors++;
}


#line 105 "c-.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_C_TAB_H_INCLUDED
# define YY_YY_C_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    WHILE = 258,
    IF = 259,
    FOR = 260,
    TO = 261,
    RETURN = 262,
    BREAK = 263,
    BY = 264,
    DO = 265,
    NOT = 266,
    AND = 267,
    OR = 268,
    ADD = 269,
    RAND = 270,
    MUL = 271,
    DIV = 272,
    MOD = 273,
    SUB = 274,
    ASGN = 275,
    ADDASGN = 276,
    SUBASGN = 277,
    MULASGN = 278,
    DIVASGN = 279,
    THEN = 280,
    ELSE = 281,
    BGN = 282,
    END = 283,
    RPAREN = 284,
    LPAREN = 285,
    RBRACK = 286,
    LBRACK = 287,
    STATIC = 288,
    SEMI = 289,
    LT = 290,
    LEQ = 291,
    GT = 292,
    GEQ = 293,
    EQ = 294,
    NEQ = 295,
    INC = 296,
    DEC = 297,
    COL = 298,
    COM = 299,
    INT = 300,
    BOOL = 301,
    CHAR = 302,
    ID = 303,
    NUMCONST = 304,
    CHARCONST = 305,
    STRINGCONST = 306,
    BOOLCONST = 307
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 38 "c-.y"

    Type::ExpressionType type;
    AST_node *node;
    TokenData *tokenData;
    double value;

#line 217 "c-.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_C_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   227

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  111
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  171

#define YYUNDEFTOK  2
#define YYMAXUTOK   307


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   107,   107,   115,   125,   132,   137,   144,   151,   156,
     163,   173,   180,   185,   195,   200,   207,   211,   215,   221,
     231,   244,   248,   255,   265,   272,   279,   289,   296,   301,
     308,   313,   320,   325,   332,   342,   346,   359,   363,   375,
     380,   385,   390,   395,   400,   407,   412,   419,   426,   433,
     443,   453,   460,   469,   476,   485,   492,   502,   507,   515,
     522,   530,   536,   542,   549,   554,   559,   564,   569,   576,
     583,   590,   597,   604,   610,   617,   624,   631,   637,   643,
     649,   655,   661,   669,   676,   683,   689,   697,   704,   711,
     717,   723,   731,   738,   746,   752,   758,   766,   772,   780,
     786,   795,   801,   807,   815,   822,   831,   841,   848,   853,
     858,   863
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "WHILE", "IF", "FOR", "TO", "RETURN",
  "BREAK", "BY", "DO", "NOT", "AND", "OR", "ADD", "RAND", "MUL", "DIV",
  "MOD", "SUB", "ASGN", "ADDASGN", "SUBASGN", "MULASGN", "DIVASGN", "THEN",
  "ELSE", "BGN", "END", "RPAREN", "LPAREN", "RBRACK", "LBRACK", "STATIC",
  "SEMI", "LT", "LEQ", "GT", "GEQ", "EQ", "NEQ", "INC", "DEC", "COL",
  "COM", "INT", "BOOL", "CHAR", "ID", "NUMCONST", "CHARCONST",
  "STRINGCONST", "BOOLCONST", "$accept", "program", "declList", "decl",
  "varDecl", "scopedVarDecl", "varDeclList", "varDeclInit", "varDeclId",
  "typeSpec", "funDecl", "parms", "parmList", "parmTypeList", "parmIdList",
  "parmId", "stmt", "expStmt", "compoundStmt", "localDecls", "stmtList",
  "closedStmt", "openStmt", "selectStmtOpen", "selectStmtClosed",
  "iterStmtOpen", "iterStmtClosed", "iterRange", "returnStmt", "breakStmt",
  "exp", "assignop", "simpleExp", "andExp", "unaryRelExp", "relExp",
  "relop", "sumExp", "sumop", "mulExp", "mulop", "unaryExp", "unaryop",
  "factor", "mutable", "immutable", "call", "argList", "constant", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307
};
# endif

#define YYPACT_NINF (-76)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      62,   -76,   -76,   -76,   -28,    15,    62,   -76,   -76,   -30,
     -76,    70,   -76,   -76,    23,   -23,   -76,    13,    36,    34,
      58,   -76,    70,    50,   -76,    52,   138,    74,    67,   -76,
      94,    70,    95,   100,    93,   -76,   138,   -76,   -76,   -76,
     138,    41,   -76,   -76,   -76,   -76,   113,   122,   -76,   -76,
     187,   102,   -76,   148,   -76,   -76,   -76,   -76,   -76,   104,
      36,   -76,   -76,   -76,    94,   -76,   -76,   109,   113,    25,
      53,   138,   138,   138,   -76,   -76,   -76,   -76,   -76,   -76,
     -76,   -76,   148,   148,   -76,   -76,   -76,   148,   -76,   -76,
     -76,     5,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,
     -76,   138,   -76,   -76,   -21,   108,   122,   -76,    79,   102,
     -76,    70,   -76,    52,     9,   -76,   -76,   138,   -76,    52,
     -15,   138,   138,    97,   131,   114,   -76,   -76,   -76,   -76,
     -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   117,
     -76,    10,   -76,    17,    -3,   136,   -76,   124,   -76,   -76,
     -76,   125,   125,   138,   -76,   -76,   -76,   134,   -76,   152,
      20,   125,   125,   138,   -76,   -76,   -76,   -76,    61,   138,
     113
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    18,    16,    17,     0,     0,     2,     4,     5,     0,
       6,    21,     1,     3,    14,     0,    11,    12,     0,     0,
      22,    24,    21,     0,     7,     0,     0,    28,    25,    27,
       0,     0,     0,     0,    14,    10,     0,    96,    95,    94,
       0,    99,   108,   109,   110,   111,    13,    70,    72,    74,
      76,    84,    88,     0,    93,    97,    98,   102,   103,     0,
       0,    35,    20,    23,     0,    15,    73,     0,    63,    97,
       0,     0,     0,     0,    85,    86,    77,    78,    79,    80,
      81,    82,     0,     0,    89,    90,    91,     0,    92,    29,
      26,    37,    19,   101,    64,    65,    66,    68,    67,    61,
      62,     0,   105,   107,     0,     0,    69,    71,    75,    83,
      87,     0,    36,     0,     0,    60,   104,     0,   100,     0,
       0,     0,     0,     0,     0,     0,    34,    33,    38,    41,
      42,    30,    31,    45,    39,    46,    40,    43,    44,     0,
     106,     0,     9,     0,     0,     0,    57,     0,    59,    32,
       8,     0,     0,     0,    58,    53,    51,    47,    48,     0,
       0,     0,     0,     0,    50,    49,    54,    52,    55,     0,
      56
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -76,   -76,   -76,   160,   -76,   -76,   -22,   144,   -76,     3,
     -76,   149,   -76,   139,   -76,   112,   -76,   -76,   -24,   -76,
     -76,   -75,   -72,   -76,   -76,   -76,   -76,   -76,   -76,   -76,
     -36,   -76,   -26,   119,   -31,   -76,   -76,   103,   -76,   101,
     -76,   -46,   -76,   -76,   -39,   -76,   -76,   -76,   -76
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,     7,     8,   112,    15,    16,    17,    18,
      10,    19,    20,    21,    28,    29,   128,   129,   130,    91,
     114,   131,   132,   133,   134,   135,   136,   159,   137,   138,
     139,   101,    68,    47,    48,    49,    82,    50,    83,    51,
      87,    52,    53,    54,    55,    56,    57,   104,    58
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      46,    69,    11,     9,    67,    66,    62,    88,   116,     9,
      72,    24,   121,   122,   123,    12,   124,   125,    14,   142,
      36,    25,   152,   117,    37,    38,   163,   151,    39,    25,
      72,    69,    69,    72,   103,   105,    61,   126,   111,    40,
      92,   110,   107,   127,   150,    94,    95,    96,    97,    98,
       1,     2,     3,    22,    25,    23,    26,    41,    42,    43,
      44,    45,    69,    30,    36,   115,    99,   100,    37,    38,
     169,    70,    39,    71,    72,    69,   155,   157,    69,   156,
     158,   140,   102,    40,    27,    69,   164,   166,   147,   165,
     167,   120,    31,    74,   113,   143,   144,   141,    75,    33,
      34,    41,    42,    43,    44,    45,    59,     1,     2,     3,
       4,    60,    69,    69,   119,     1,     2,     3,    84,    85,
      86,    61,    69,    69,    64,    23,    72,   160,   121,   122,
     123,    65,   124,   125,    73,    89,    36,   168,    93,   118,
      37,    38,    36,   170,    39,   145,    37,    38,   148,    36,
      39,   149,    61,    37,    38,    40,   153,    39,   154,   127,
     161,    40,   162,    37,    38,   146,    13,    39,    40,    35,
      63,    32,    90,    41,    42,    43,    44,    45,    40,    41,
      42,    43,    44,    45,   109,   108,    41,    42,    43,    44,
      45,   106,     0,     0,     0,     0,    41,    42,    43,    44,
      45,    74,     0,     0,     0,     0,    75,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    76,    77,    78,    79,    80,    81
};

static const yytype_int16 yycheck[] =
{
      26,    40,    30,     0,    40,    36,    30,    53,    29,     6,
      13,    34,     3,     4,     5,     0,     7,     8,    48,    34,
      11,    44,    25,    44,    15,    16,     6,    10,    19,    44,
      13,    70,    71,    13,    70,    71,    27,    28,    33,    30,
      64,    87,    73,    34,    34,    20,    21,    22,    23,    24,
      45,    46,    47,    30,    44,    32,    43,    48,    49,    50,
      51,    52,   101,    29,    11,   101,    41,    42,    15,    16,
       9,    30,    19,    32,    13,   114,   151,   152,   117,   151,
     152,   117,    29,    30,    48,   124,   161,   162,   124,   161,
     162,   113,    34,    14,    91,   121,   122,   119,    19,    49,
      48,    48,    49,    50,    51,    52,    32,    45,    46,    47,
      48,    44,   151,   152,   111,    45,    46,    47,    16,    17,
      18,    27,   161,   162,    29,    32,    13,   153,     3,     4,
       5,    31,     7,     8,    12,    31,    11,   163,    29,    31,
      15,    16,    11,   169,    19,    48,    15,    16,    34,    11,
      19,    34,    27,    15,    16,    30,    20,    19,    34,    34,
      26,    30,    10,    15,    16,    34,     6,    19,    30,    25,
      31,    22,    60,    48,    49,    50,    51,    52,    30,    48,
      49,    50,    51,    52,    83,    82,    48,    49,    50,    51,
      52,    72,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    14,    -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    39,    40
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    45,    46,    47,    48,    54,    55,    56,    57,    62,
      63,    30,     0,    56,    48,    59,    60,    61,    62,    64,
      65,    66,    30,    32,    34,    44,    43,    48,    67,    68,
      29,    34,    64,    49,    48,    60,    11,    15,    16,    19,
      30,    48,    49,    50,    51,    52,    85,    86,    87,    88,
      90,    92,    94,    95,    96,    97,    98,    99,   101,    32,
      44,    27,    71,    66,    29,    31,    87,    83,    85,    97,
      30,    32,    13,    12,    14,    19,    35,    36,    37,    38,
      39,    40,    89,    91,    16,    17,    18,    93,    94,    31,
      68,    72,    71,    29,    20,    21,    22,    23,    24,    41,
      42,    84,    29,    83,   100,    83,    86,    87,    90,    92,
      94,    33,    58,    62,    73,    83,    29,    44,    31,    62,
      59,     3,     4,     5,     7,     8,    28,    34,    69,    70,
      71,    74,    75,    76,    77,    78,    79,    81,    82,    83,
      83,    59,    34,    85,    85,    48,    34,    83,    34,    34,
      34,    10,    25,    20,    34,    74,    75,    74,    75,    80,
      85,    26,    10,     6,    74,    75,    74,    75,    85,     9,
      85
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    57,    58,    58,
      59,    59,    60,    60,    61,    61,    62,    62,    62,    63,
      63,    64,    64,    65,    65,    66,    67,    67,    68,    68,
      69,    69,    70,    70,    71,    72,    72,    73,    73,    74,
      74,    74,    74,    74,    74,    75,    75,    76,    76,    76,
      77,    78,    78,    79,    79,    80,    80,    81,    81,    82,
      83,    83,    83,    83,    84,    84,    84,    84,    84,    85,
      85,    86,    86,    87,    87,    88,    88,    89,    89,    89,
      89,    89,    89,    90,    90,    91,    91,    92,    92,    93,
      93,    93,    94,    94,    95,    95,    95,    96,    96,    97,
      97,    98,    98,    98,    99,    99,   100,   100,   101,   101,
     101,   101
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     4,     3,
       3,     1,     1,     3,     1,     4,     1,     1,     1,     6,
       5,     0,     1,     3,     1,     2,     3,     1,     1,     3,
       1,     1,     2,     1,     4,     0,     2,     0,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     4,     6,
       6,     4,     6,     4,     6,     3,     5,     2,     3,     2,
       3,     2,     2,     1,     1,     1,     1,     1,     1,     3,
       1,     3,     1,     2,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       4,     3,     1,     1,     4,     3,     3,     1,     1,     1,
       1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 108 "c-.y"
                    {
                        std::cout << "program:declList\n";
                        (yyval.node) = (yyvsp[0].node);
                        tree_root = (yyval.node);
                    }
#line 1542 "c-.tab.c"
    break;

  case 3:
#line 116 "c-.y"
                    {
                        std::cout << "declList:declList decl\n";
                        if ((yyvsp[-1].node) != nullptr) {
                            (yyval.node) = (yyvsp[-1].node);
                            (yyval.node)->add_sibling((yyvsp[0].node));
                        } else {
                            (yyval.node) = (yyvsp[0].node);
                        }
                    }
#line 1556 "c-.tab.c"
    break;

  case 4:
#line 126 "c-.y"
                    {
                        std::cout << "declList:decl\n";
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 1565 "c-.tab.c"
    break;

  case 5:
#line 133 "c-.y"
                    {
						std::cout << "decl:varDecl\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 1574 "c-.tab.c"
    break;

  case 6:
#line 138 "c-.y"
                    {
						std::cout << "decl:funDecl\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 1583 "c-.tab.c"
    break;

  case 7:
#line 145 "c-.y"
                    {
						std::cout << "varDecl:typeSpec varDeclList SEMI\n"; 
						(yyval.node) = (yyvsp[-1].node);
					}
#line 1592 "c-.tab.c"
    break;

  case 8:
#line 152 "c-.y"
                    {
						std::cout << "scopedVarDecl:STATIC typeSpec varDeclList SEMI\n"; 
						(yyval.node) = (yyvsp[-1].node);
					}
#line 1601 "c-.tab.c"
    break;

  case 9:
#line 157 "c-.y"
                    {
						std::cout << "scopedVarDecl:typeSpec varDeclList SEMI\n"; 
						(yyval.node) = (yyvsp[-1].node);
					}
#line 1610 "c-.tab.c"
    break;

  case 10:
#line 164 "c-.y"
                    {
						std::cout << "varDeclList:varDeclList COM varDeclInit\n";
                        if ((yyvsp[-2].node) != nullptr) {
                            (yyval.node) = (yyvsp[-2].node);
                            (yyval.node)->add_sibling((yyvsp[0].node));
                        } else {
                            (yyval.node) = (yyvsp[0].node);
                        }
                    }
#line 1624 "c-.tab.c"
    break;

  case 11:
#line 174 "c-.y"
                    {
						std::cout << "varDeclList:varDeclInit\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 1633 "c-.tab.c"
    break;

  case 12:
#line 181 "c-.y"
                    {
						std::cout << "varDeclInit:varDeclId\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 1642 "c-.tab.c"
    break;

  case 13:
#line 186 "c-.y"
                    {
						std::cout << "varDeclInit:varDeclId COL simpleExp\n";
                        if ((yyvsp[-2].node) != nullptr) {
                            (yyval.node) = (yyvsp[-2].node);
                            (yyval.node)->add_sibling((yyvsp[0].node));
                        }
                    }
#line 1654 "c-.tab.c"
    break;

  case 14:
#line 196 "c-.y"
                    {
						std::cout << "varDeclId:ID\n";
                        (yyval.node) = new AST_node(Type::Declaration::Variable);
                    }
#line 1663 "c-.tab.c"
    break;

  case 15:
#line 201 "c-.y"
                    {
						std::cout << "varDeclId:ID LBRACK NUMCONST RBRACK\n";
                        (yyval.node) = new AST_node(Type::Declaration::Variable);
                    }
#line 1672 "c-.tab.c"
    break;

  case 16:
#line 208 "c-.y"
                    {
                        (yyval.type) = Type::ExpressionType::Boolean;
                    }
#line 1680 "c-.tab.c"
    break;

  case 17:
#line 212 "c-.y"
                    {
                        (yyval.type) = Type::ExpressionType::Char;
                    }
#line 1688 "c-.tab.c"
    break;

  case 18:
#line 216 "c-.y"
                    {
                        (yyval.type) = Type::ExpressionType::Integer;
                    }
#line 1696 "c-.tab.c"
    break;

  case 19:
#line 222 "c-.y"
                    {
						std::cout << "typeSpec ID LPAREN parms RPAREN compoundStmt\n";
                        (yyval.node) = new AST_node(Type::Declaration::Function);
                        (yyval.node)->add_child((yyvsp[-4].node));
                        if ((yyvsp[-2].node) != nullptr) {
                            (yyval.node)->add_child((yyvsp[-2].node));
                        }
                        (yyval.node)->add_child((yyvsp[0].node));
                    }
#line 1710 "c-.tab.c"
    break;

  case 20:
#line 232 "c-.y"
                    {
						std::cout << "ID LPAREN parms RPAREN compoundStmt\n";
                        (yyval.node) = new AST_node(Type::Declaration::Function);
                        (yyval.node)->add_child((yyvsp[-4].node));
                        if ((yyvsp[-2].node) != nullptr) {
                            (yyval.node)->add_child((yyvsp[-2].node));
                        }
                        (yyval.node)->add_child((yyvsp[0].node));
                    }
#line 1724 "c-.tab.c"
    break;

  case 21:
#line 244 "c-.y"
                    {
                        std::cout << "parms:\n";
						(yyval.node) = nullptr;
					}
#line 1733 "c-.tab.c"
    break;

  case 22:
#line 249 "c-.y"
                    {
						std::cout << "parms:parmList\n";
						(yyval.node) = (yyvsp[0].node);
					}
#line 1742 "c-.tab.c"
    break;

  case 23:
#line 256 "c-.y"
                    {
						std::cout << "parmList:parmList SEMI parmTypeList\n";
                        if ((yyvsp[-2].node) != nullptr) {
                            (yyval.node) = (yyvsp[-2].node);
                            (yyval.node)->add_sibling((yyvsp[0].node));
                        } else {
                            (yyval.node) = (yyvsp[0].node);
                        }
                    }
#line 1756 "c-.tab.c"
    break;

  case 24:
#line 266 "c-.y"
                    {
						std::cout << "parmList:parmTypeList\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 1765 "c-.tab.c"
    break;

  case 25:
#line 273 "c-.y"
                    {
						std::cout << "parmTypeList:typeSpec parmIdList\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 1774 "c-.tab.c"
    break;

  case 26:
#line 280 "c-.y"
                    {
						std::cout << "parmIdList:parmIdList COM parmId\n";
                        if ((yyvsp[-2].node) != nullptr) {
                            (yyval.node) = (yyvsp[-2].node);
                            (yyval.node)->add_sibling((yyvsp[0].node));
                        } else {
                            (yyval.node) = (yyvsp[0].node);
                        }
                    }
#line 1788 "c-.tab.c"
    break;

  case 27:
#line 290 "c-.y"
                    {
						std::cout << "parmIdList:parmId\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 1797 "c-.tab.c"
    break;

  case 28:
#line 297 "c-.y"
                    {
						std::cout << "parmId:ID\n"; 
						(yyval.node) = new AST_node(Type::Expression::Id);
					}
#line 1806 "c-.tab.c"
    break;

  case 29:
#line 302 "c-.y"
                    {
						std::cout << "parmId:ID LBRACK RBRACK\n"; 
						(yyval.node) = new AST_node(Type::Expression::Id);
					}
#line 1815 "c-.tab.c"
    break;

  case 30:
#line 309 "c-.y"
                    {
						std::cout << "stmt:closedStmt\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 1824 "c-.tab.c"
    break;

  case 31:
#line 314 "c-.y"
                    {
						std::cout << "stmt:openStmt\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 1833 "c-.tab.c"
    break;

  case 32:
#line 321 "c-.y"
                    {
						std::cout << "expStmt:exp SEMI\n"; 
						(yyval.node) = (yyvsp[-1].node);
					}
#line 1842 "c-.tab.c"
    break;

  case 33:
#line 326 "c-.y"
                    {
						std::cout << "expStmt:SEMI\n"; 
						(yyval.node) = nullptr;
					}
#line 1851 "c-.tab.c"
    break;

  case 34:
#line 333 "c-.y"
                    {
						std::cout << "compoundStmt:BGN localDecls stmtList END\n";
                        (yyval.node) = new AST_node(Type::Statement::Compound);
                        (yyval.node)->add_child((yyvsp[-2].node));
                        (yyval.node)->add_child((yyvsp[-1].node));
                    }
#line 1862 "c-.tab.c"
    break;

  case 35:
#line 342 "c-.y"
                    {
                        std::cout << "localDecls:\n";
						(yyval.node) = nullptr;
					}
#line 1871 "c-.tab.c"
    break;

  case 36:
#line 347 "c-.y"
                    {
						std::cout << "localDecls:localDecls scopedVarDecl\n";
                        if ((yyvsp[-1].node) != nullptr) {
                            (yyval.node) = (yyvsp[-1].node);
                            (yyval.node)->add_sibling((yyvsp[0].node));
                        } else {
                            (yyval.node) = (yyvsp[0].node);
                        }
                    }
#line 1885 "c-.tab.c"
    break;

  case 37:
#line 359 "c-.y"
                    { 
                        std::cout << "stmtList:\n";
						(yyval.node) = nullptr;
					}
#line 1894 "c-.tab.c"
    break;

  case 38:
#line 364 "c-.y"
                    {
						std::cout << "stmtList:stmtList stmt\n";
                        if ((yyval.node) != nullptr) {
                            (yyval.node) = (yyvsp[-1].node);
                            (yyval.node)->add_sibling((yyvsp[0].node));
                        } else {
                            (yyval.node) = (yyvsp[0].node);
                        }
                    }
#line 1908 "c-.tab.c"
    break;

  case 39:
#line 376 "c-.y"
                    {
						std::cout << "closedStmt:selectStmtClosed\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 1917 "c-.tab.c"
    break;

  case 40:
#line 381 "c-.y"
                    {
						std::cout << "closedStmt:iterStmtClosed\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 1926 "c-.tab.c"
    break;

  case 41:
#line 386 "c-.y"
                    {
						std::cout << "closedStmt:expStmt\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 1935 "c-.tab.c"
    break;

  case 42:
#line 391 "c-.y"
                    {
						std::cout << "closedStmt:compoundStmt\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 1944 "c-.tab.c"
    break;

  case 43:
#line 396 "c-.y"
                    {
						std::cout << "closedStmt:returnStmt \n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 1953 "c-.tab.c"
    break;

  case 44:
#line 401 "c-.y"
                    {
						std::cout << "closedStmt:breakStmt\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 1962 "c-.tab.c"
    break;

  case 45:
#line 408 "c-.y"
                    {
						std::cout << "openStmt:selectStmtOpen\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 1971 "c-.tab.c"
    break;

  case 46:
#line 413 "c-.y"
                    {
						std::cout << "openStmt:iterStmtOpen\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 1980 "c-.tab.c"
    break;

  case 47:
#line 420 "c-.y"
                    {
						std::cout << "selectStmtOpen:IF simpleExp THEN closedStmt\n";
                        (yyval.node) = new AST_node(Type::Statement::Select);
                        (yyval.node)->add_child((yyvsp[-2].node));
                        (yyval.node)->add_child((yyvsp[0].node));
                    }
#line 1991 "c-.tab.c"
    break;

  case 48:
#line 427 "c-.y"
                    {
						std::cout << "selectStmtOpen:IF simpleExp THEN openStmt\n";
                        (yyval.node) = new AST_node(Type::Statement::Select);
                        (yyval.node)->add_child((yyvsp[-2].node));
                        (yyval.node)->add_child((yyvsp[0].node));
                    }
#line 2002 "c-.tab.c"
    break;

  case 49:
#line 434 "c-.y"
                    {
						std::cout << "IF simpleExp THEN closedStmt ELSE openStmt\n";
                        (yyval.node) = new AST_node(Type::Statement::Select);
                        (yyval.node)->add_child((yyvsp[-4].node));
                        (yyval.node)->add_child((yyvsp[-2].node));
                        (yyval.node)->add_child((yyvsp[0].node));
                    }
#line 2014 "c-.tab.c"
    break;

  case 50:
#line 444 "c-.y"
                    {
						std::cout << "IF simpleExp THEN closedStmt ELSE closedStmt\n";
                        (yyval.node) = new AST_node(Type::Statement::Select);
                        (yyval.node)->add_child((yyvsp[-4].node));
                        (yyval.node)->add_child((yyvsp[-2].node));
                        (yyval.node)->add_child((yyvsp[0].node));
                    }
#line 2026 "c-.tab.c"
    break;

  case 51:
#line 454 "c-.y"
                    {
						std::cout << "WHILE simpleExp DO openStmt\n";
                        (yyval.node) = new AST_node(Type::Statement::Iterative);
                        (yyval.node)->add_child((yyvsp[-2].node));
                        (yyval.node)->add_child((yyvsp[0].node));
                    }
#line 2037 "c-.tab.c"
    break;

  case 52:
#line 461 "c-.y"
                    {
						std::cout << "FOR ID ASGN iterRange DO openStmt\n";
                        (yyval.node) = new AST_node(Type::Statement::Iterative);
                        (yyval.node)->add_child((yyvsp[-2].node));
                        (yyval.node)->add_child((yyvsp[0].node));
                    }
#line 2048 "c-.tab.c"
    break;

  case 53:
#line 470 "c-.y"
                    {
						std::cout << "WHILE simpleExp DO closedStmt\n";
                        (yyval.node) = new AST_node(Type::Statement::Iterative);
                        (yyval.node)->add_child((yyvsp[-2].node));
                        (yyval.node)->add_child((yyvsp[0].node));
                    }
#line 2059 "c-.tab.c"
    break;

  case 54:
#line 477 "c-.y"
                    {
						std::cout << "FOR ID ASGN iterRange DO closedStmt\n";
                        (yyval.node) = new AST_node(Type::Statement::Iterative);
                        (yyval.node)->add_child((yyvsp[-2].node));
                        (yyval.node)->add_child((yyvsp[0].node));
                    }
#line 2070 "c-.tab.c"
    break;

  case 55:
#line 486 "c-.y"
                    {
						std::cout << "simpleExp TO simpleExp\n";
                        (yyval.node) = new AST_node(Type::Expression::Range);
                        (yyval.node)->add_child((yyvsp[-2].node));
                        (yyval.node)->add_child((yyvsp[0].node));
                    }
#line 2081 "c-.tab.c"
    break;

  case 56:
#line 493 "c-.y"
                    {
						std::cout << "simpleExp TO simpleExp\n";
                        (yyval.node) = new AST_node(Type::Expression::Range);
                        (yyval.node)->add_child((yyvsp[-4].node));
                        (yyval.node)->add_child((yyvsp[-2].node));
                        (yyval.node)->add_child((yyvsp[0].node));
                    }
#line 2093 "c-.tab.c"
    break;

  case 57:
#line 503 "c-.y"
                    {
						std::cout << "RETURN SEMI\n";
                        (yyval.node) = new AST_node(Type::Statement::Return);
                    }
#line 2102 "c-.tab.c"
    break;

  case 58:
#line 508 "c-.y"
                    {
						std::cout << "RETURN exp SEMI\n";
                        (yyval.node) = new AST_node(Type::Statement::Return);
                        (yyval.node)->add_child((yyvsp[-1].node));
                    }
#line 2112 "c-.tab.c"
    break;

  case 59:
#line 516 "c-.y"
                    {
						std::cout << "BREAK SEMI\n";
                        (yyval.node) = new AST_node(Type::Statement::Break);
                    }
#line 2121 "c-.tab.c"
    break;

  case 60:
#line 523 "c-.y"
                    {
						std::cout << "mutable assignop exp\n";
                        (yyval.node) = new AST_node(Type::Statement::Assign);
                        (yyval.node)->add_child((yyvsp[-2].node));
                        (yyval.node)->add_child((yyvsp[-1].node));
                        (yyval.node)->add_child((yyvsp[0].node));
                    }
#line 2133 "c-.tab.c"
    break;

  case 61:
#line 531 "c-.y"
                    {
						std::cout << "mutable INC\n";
                        (yyval.node) = new AST_node(Type::Statement::Assign);
                        (yyval.node)->add_child((yyvsp[-1].node));
                    }
#line 2143 "c-.tab.c"
    break;

  case 62:
#line 537 "c-.y"
                    {
						std::cout << "mutable DEC\n";
                        (yyval.node) = new AST_node(Type::Statement::Assign);
                        (yyval.node)->add_child((yyvsp[-1].node)); 
                    }
#line 2153 "c-.tab.c"
    break;

  case 63:
#line 543 "c-.y"
                    {
						std::cout << "simpleExp\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 2162 "c-.tab.c"
    break;

  case 64:
#line 550 "c-.y"
                    {
						std::cout << "ASGN\n"; 
						(yyval.node) = new AST_node(Type::Statement::Assign);
					}
#line 2171 "c-.tab.c"
    break;

  case 65:
#line 555 "c-.y"
                    {
						std::cout << "ADDASGN\n"; 
						(yyval.node) = new AST_node(Type::Statement::Assign);
					}
#line 2180 "c-.tab.c"
    break;

  case 66:
#line 560 "c-.y"
                    {
						std::cout << "SUBASGN\n"; 
						(yyval.node) = new AST_node(Type::Statement::Assign);
					}
#line 2189 "c-.tab.c"
    break;

  case 67:
#line 565 "c-.y"
                    {
						std::cout << "DIVASGN\n"; 
						(yyval.node) = new AST_node(Type::Statement::Assign);
					}
#line 2198 "c-.tab.c"
    break;

  case 68:
#line 570 "c-.y"
                    {
						std::cout << "MULASGN\n"; 
						(yyval.node) = new AST_node(Type::Statement::Assign);
					}
#line 2207 "c-.tab.c"
    break;

  case 69:
#line 577 "c-.y"
                    {
						std::cout << "simpleExp OR andExp\n";
                        (yyval.node) = new AST_node(Type::Expression::Simple);
                        (yyval.node)->add_child((yyvsp[-2].node));
                        (yyval.node)->add_child((yyvsp[0].node));           
                    }
#line 2218 "c-.tab.c"
    break;

  case 70:
#line 584 "c-.y"
                    {
						std::cout << "andExp\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 2227 "c-.tab.c"
    break;

  case 71:
#line 591 "c-.y"
                    {
						std::cout << "andExp AND unaryRelExp\n";
                        (yyval.node) = new AST_node(Type::Expression::And);
                        (yyval.node)->add_child((yyvsp[-2].node));
                        (yyval.node)->add_child((yyvsp[0].node));
                    }
#line 2238 "c-.tab.c"
    break;

  case 72:
#line 598 "c-.y"
                    {
						std::cout << "unaryRelExp\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 2247 "c-.tab.c"
    break;

  case 73:
#line 605 "c-.y"
                    {
						std::cout << "NOT unaryRelExp\n";
                        (yyval.node) = new AST_node(Type::Expression::UnaryRelation);
                        (yyval.node)->add_child((yyvsp[0].node));
                    }
#line 2257 "c-.tab.c"
    break;

  case 74:
#line 611 "c-.y"
                    {
						std::cout << "relExp\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 2266 "c-.tab.c"
    break;

  case 75:
#line 618 "c-.y"
                    {
						std::cout << "sumExp relop sumExp\n";
                        (yyval.node) = new AST_node(Type::Expression::Operator);
                        (yyval.node)->add_child((yyvsp[-2].node));
                        (yyval.node)->add_child((yyvsp[0].node));
                    }
#line 2277 "c-.tab.c"
    break;

  case 76:
#line 625 "c-.y"
                    {
						std::cout << "sumExp\n"; 
						(yyval.node) = (yyvsp[0].node);
					}
#line 2286 "c-.tab.c"
    break;

  case 77:
#line 632 "c-.y"
                    {
						std::cout << "LT\n"; 
                        std::cout << "relop:lt\n";
						(yyval.node) = nullptr;
					}
#line 2296 "c-.tab.c"
    break;

  case 78:
#line 638 "c-.y"
                    {
						std::cout << "LEQ\n"; 
                        std::cout << "relop:leq\n";
						(yyval.node) = nullptr;
					}
#line 2306 "c-.tab.c"
    break;

  case 79:
#line 644 "c-.y"
                    {
						std::cout << "GT\n"; 
                        std::cout << "relop:gt\n";
						(yyval.node) = nullptr;
					}
#line 2316 "c-.tab.c"
    break;

  case 80:
#line 650 "c-.y"
                    {
						std::cout << "GEQ\n"; 
                        std::cout << "relop:geq\n";
						(yyval.node) = nullptr;
					}
#line 2326 "c-.tab.c"
    break;

  case 81:
#line 656 "c-.y"
                    {
						std::cout << "EQ\n"; 
                        std::cout << "relop:eq\n";
						(yyval.node) = nullptr;
					}
#line 2336 "c-.tab.c"
    break;

  case 82:
#line 662 "c-.y"
                    {
						std::cout << "NEQ\n"; 
                        std::cout << "relop:neq\n";
						(yyval.node) = nullptr;
					}
#line 2346 "c-.tab.c"
    break;

  case 83:
#line 670 "c-.y"
                    {
                        std::cout << "sumexp:sumexp sumop mulexp\n";
						(yyval.node) = new AST_node(Type::Expression::Operator);
                        (yyval.node)->add_child((yyvsp[-2].node));
                        (yyval.node)->add_child((yyvsp[0].node));
					}
#line 2357 "c-.tab.c"
    break;

  case 84:
#line 677 "c-.y"
                    {
                        std::cout << "sumexp:mulexp\n";
                        (yyval.node) = (yyvsp[0].node);
					}
#line 2366 "c-.tab.c"
    break;

  case 85:
#line 684 "c-.y"
                    {
						std::cout << "ADD\n"; 
                        std::cout << "sumop:add\n";
						(yyval.node) = nullptr;
					}
#line 2376 "c-.tab.c"
    break;

  case 86:
#line 690 "c-.y"
                    {
						std::cout << "SUB\n"; 
                        std::cout << "sumop:sub\n";
						(yyval.node) = nullptr;
					}
#line 2386 "c-.tab.c"
    break;

  case 87:
#line 698 "c-.y"
                    {
                        std::cout << "mulop:mulexp mulop unaryexp\n";
						(yyval.node) = new AST_node(Type::Expression::Operator);
                        (yyval.node)->add_child((yyvsp[-2].node));
                        (yyval.node)->add_child((yyvsp[0].node));
					}
#line 2397 "c-.tab.c"
    break;

  case 88:
#line 705 "c-.y"
                    {
                        std::cout << "mulop:mulexp\n";
						(yyval.node) = (yyvsp[0].node);
					}
#line 2406 "c-.tab.c"
    break;

  case 89:
#line 712 "c-.y"
                    {
						std::cout << "MUL\n"; 
                        std::cout << "mulop:mul\n";
						(yyval.node) = nullptr;
					}
#line 2416 "c-.tab.c"
    break;

  case 90:
#line 718 "c-.y"
                    {
						std::cout << "DIV\n"; 
                        std::cout << "mulop:div\n";
						(yyval.node) = nullptr;
					}
#line 2426 "c-.tab.c"
    break;

  case 91:
#line 724 "c-.y"
                    {
						std::cout << "MOD\n"; 
                        std::cout << "mulop:mod\n";
						(yyval.node) = nullptr;
					}
#line 2436 "c-.tab.c"
    break;

  case 92:
#line 732 "c-.y"
                    {
						std::cout << "unaryop unaryExp\n"; 
                        std::cout << "unaryexp:unaryop unaryexp\n";
						(yyval.node) = new AST_node(Type::Expression::Operator);
                        (yyval.node)->add_child((yyvsp[0].node));
					}
#line 2447 "c-.tab.c"
    break;

  case 93:
#line 739 "c-.y"
                    {
						std::cout << "factor\n"; 
                        std::cout << "unaryexp:factor\n";
						(yyval.node) = (yyvsp[0].node);
					}
#line 2457 "c-.tab.c"
    break;

  case 94:
#line 747 "c-.y"
                    {
						std::cout << "SUB\n"; 
                        std::cout << "unaryop:sub\n";
						(yyval.node) = nullptr;
					}
#line 2467 "c-.tab.c"
    break;

  case 95:
#line 753 "c-.y"
                    {
						std::cout << "MUL\n"; 
                        std::cout << "unaryop:mul\n";
						(yyval.node) = nullptr;
					}
#line 2477 "c-.tab.c"
    break;

  case 96:
#line 759 "c-.y"
                    {
						std::cout << "RAND\n"; 
                        std::cout << "unaryop:rand\n";
						(yyval.node) = nullptr;
					}
#line 2487 "c-.tab.c"
    break;

  case 97:
#line 767 "c-.y"
                    {
						std::cout << "mutable\n"; 
                        std::cout << "factor:mutable\n";
						(yyval.node) = (yyvsp[0].node);
					}
#line 2497 "c-.tab.c"
    break;

  case 98:
#line 773 "c-.y"
                    {
						std::cout << "immutable\n"; 
                        std::cout << "factor:immutable\n";
						(yyval.node) = (yyvsp[0].node);
					}
#line 2507 "c-.tab.c"
    break;

  case 99:
#line 781 "c-.y"
                    {
						std::cout << "ID\n"; 
                        std::cout << "immutable:id\n";
						(yyval.node) = new AST_node(Type::Expression::Id);
					}
#line 2517 "c-.tab.c"
    break;

  case 100:
#line 787 "c-.y"
                    {
						std::cout << "ID LBRACK exp RBRACK\n";
                        std::cout << "immutable:lparen exp rparen\n";
                        (yyval.node) = new AST_node(Type::Expression::Operator);
                        (yyval.node)->add_sibling((yyvsp[-1].node));
                    }
#line 2528 "c-.tab.c"
    break;

  case 101:
#line 796 "c-.y"
                    {
						std::cout << "LPAREN exp RPAREN\n";
                        std::cout << "immutable:lparen exp rparen\n";
                        (yyval.node) = (yyvsp[-1].node);
                    }
#line 2538 "c-.tab.c"
    break;

  case 102:
#line 802 "c-.y"
                    {
						std::cout << "call\n";
                        std::cout << "immutable:call\n";
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2548 "c-.tab.c"
    break;

  case 103:
#line 808 "c-.y"
                    {
						std::cout << "constant\n";
                        std::cout << "immutable:constant\n";
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2558 "c-.tab.c"
    break;

  case 104:
#line 816 "c-.y"
                    {
                        std::cout << "call:id lparen arglist rparen\n";
                        (yyval.node) = new AST_node(Type::Statement::Call);
                        (yyval.node)->add_child(new AST_node(Type::Expression::Id));
                        (yyval.node)->add_child((yyvsp[-1].node));
                    }
#line 2569 "c-.tab.c"
    break;

  case 105:
#line 823 "c-.y"
                    {
						std::cout << "ID LPAREN RPAREN\n";
                        std::cout << "call:id lparen rparen\n";
                        (yyval.node) = new AST_node(Type::Statement::Call);
                        (yyval.node)->add_child(new AST_node(Type::Expression::Id));
                    }
#line 2580 "c-.tab.c"
    break;

  case 106:
#line 832 "c-.y"
                    {
                        std::cout << "argList:arglist com exp\n";
                        if ((yyvsp[-2].node) != nullptr) {
                            (yyval.node) = (yyvsp[-2].node);
                            (yyval.node)->add_sibling((yyvsp[0].node));
                        } else {
                            (yyval.node) = (yyvsp[0].node);
                        }
                    }
#line 2594 "c-.tab.c"
    break;

  case 107:
#line 842 "c-.y"
                    {
                        std::cout << "argList:exp\n";
                        (yyval.node) = (yyvsp[0].node);
                    }
#line 2603 "c-.tab.c"
    break;

  case 108:
#line 849 "c-.y"
                    {
                        std::cout << "constant:numconst\n";
                        (yyval.node) = new AST_node(Type::Declaration::Variable);
                    }
#line 2612 "c-.tab.c"
    break;

  case 109:
#line 854 "c-.y"
                    {
                        std::cout << "constant:charconst\n";
                        (yyval.node) = new AST_node(Type::Declaration::Variable);
                    }
#line 2621 "c-.tab.c"
    break;

  case 110:
#line 859 "c-.y"
                    {
                        std::cout << "constant:stringconst\n";
                        (yyval.node) = new AST_node(Type::Declaration::Variable);
                    }
#line 2630 "c-.tab.c"
    break;

  case 111:
#line 864 "c-.y"
                    {
                        std::cout << "constant:boolconst\n";
                        (yyval.node) = new AST_node(Type::Declaration::Variable);
                    }
#line 2639 "c-.tab.c"
    break;


#line 2643 "c-.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 870 "c-.y"

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
    std::cout << "\n";
    if (tree_root != nullptr) {
        tree_root->print();
        std::cout << tree_root->number_of_nodes() << std::endl;
    }

    for (auto& token : tokens) {
        delete token;
    }

    return 0;
}
