/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
#line 39 "c-.y"

    AST::Decl::Type type;
    AST::Node *node;
    TokenData *tokenData;
    double value;

#line 117 "c-.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_C_TAB_H_INCLUDED  */
