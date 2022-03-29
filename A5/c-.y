%{
#include "AST/AST.hpp"
#include "scanType.hpp"  // TokenData Type
#include "strutil.hpp"
#include "Options/Options.hpp"
#include "SemanticsChecker/SemanticsChecker.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>

extern int yylex();
extern FILE *yyin;
extern int line;         // ERR line number from the scanner!!
extern int numErrors;    // ERR err count
extern char *yytext;
AST::Node* tree_root;

#define YYERROR_VERBOSE
void yyerror(const char *msg)
{
    std::cout << "ERROR(" << line << "): " << msg << std::endl;
    numErrors++;
}

%}

// this is included in the tab.h file
// so scanType.hpp must be included before the tab.h file!!!!
%union {
    AST::Type type;
    AST::Node *node;
    TokenData *tokenData;
    double value;
}

%token <tokenData> WHILE IF FOR TO RETURN BREAK BY DO
%token <tokenData> NOT AND OR
%token <tokenData> ADD DASH RAND ASTERISK DIV MOD ASGN ADDASGN SUBASGN MULASGN DIVASGN
%token <tokenData> THEN ELSE BGN END
%token <tokenData> RPAREN LPAREN RBRACK LBRACK
%token <tokenData> STATIC
%token <tokenData> SEMI LT LEQ GT GEQ EQ NEQ INC DEC COL COM
%token <type> INT BOOL CHAR 

%token <tokenData> ID NUMCONST CHARCONST STRINGCONST BOOLCONST
%type <node> program
%type <node> declList decl varDecl scopedVarDecl varDeclList varDeclInit varDeclId
%type <type> typeSpec
%type <node> funDecl parms parmList parmTypeList parmIdList parmId
%type <node> stmt expStmt compoundStmt localDecls stmtList closedStmt openStmt selectStmtOpen selectStmtClosed iterStmtOpen iterStmtClosed iterRange returnStmt breakStmt
%type <node> exp assignop simpleExp andExp unaryRelExp relExp relop sumExp sumop mulExp mulop unaryExp unaryop
%type <node> factor mutable immutable call argList constant


%%

program             : declList {
                        $$ = $1;
                        tree_root = $$;
                        yyerrok;
                    }
                    | error { $$ = nullptr; yyerrok; }
                    ;

declList            : declList decl {
                        $$ = $1;
                        $$->addSibling($2);
                        yyerrok;
                    }
                    | decl { $$ = $1; yyerrok; }
                    | declList error { $$ = nullptr; yyerrok; }
                    | error decl { $$ = nullptr; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

decl                : varDecl { $$ = $1; yyerrok; }
                    | funDecl { $$ = $1; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

varDecl             : typeSpec varDeclList SEMI {
                        auto *var = $2->cast<AST::Decl::Var *>();
                        var->setType($1);
                        $$ = var;
                        yyerrok;
					}
                    | error varDeclList SEMI { $$ = nullptr; yyerrok; }
                    | typeSpec error SEMI { $$ = nullptr; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

scopedVarDecl       : STATIC typeSpec varDeclList SEMI {
                        auto *var = $3->cast<AST::Decl::Var *>();
                        var->setType($2);
                        var->setIsStatic(true);
                        $$ = var;
                        yyerrok;
					}
                    | typeSpec varDeclList SEMI {
                        auto *var = $2->cast<AST::Decl::Var *>();
                        var->setType($1);
                        $$ = var;
                        yyerrok;
					}
                    | STATIC error varDeclList SEMI { $$ = nullptr; yyerrok; }
                    | STATIC typeSpec error SEMI { $$ = nullptr; yyerrok; }
                    | STATIC error SEMI { $$ = nullptr; yyerrok; }
                    | error varDeclList SEMI { $$ = nullptr; yyerrok; }
                    | typeSpec error SEMI { $$ = nullptr; yyerrok; }
                    | error SEMI { $$ = nullptr; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

varDeclList         : varDeclList COM varDeclInit {
                        $$ = $1;
                        $$->addSibling($3);
                        yyerrok;
                    }
                    | varDeclInit { $$ = $1; yyerrok; }
                    | error COM varDeclInit { $$ = nullptr; yyerrok; }
                    | error COM error { $$ = nullptr; yyerrok; }
                    | varDeclList COM error { $$ = nullptr; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

varDeclInit         : varDeclId { $$ = $1; yyerrok; }
                    | varDeclId COL simpleExp {
                        $$ = $1;
                        $$->addChild($3);
                        yyerrok;
                    }
                    | varDeclId COL error {
                        $$ = nullptr;
                        yyerrok;
                    }
                    | error { $$ = nullptr; yyerrok; }
                    | error COL simpleExp { $$ = nullptr; yyerrok; }
                    | error COL error { $$ = nullptr; yyerrok; }
                    ;
                
varDeclId           : ID {
                        $$ = new AST::Decl::Var($1->linenum, $1->tokenstr, false);
                        yyerrok;
                    }
                    | ID LBRACK NUMCONST RBRACK {
                        $$ = new AST::Decl::Var($1->linenum, $1->tokenstr, true);
                        yyerrok;
                    }
                    | error { $$ = nullptr; yyerrok; }
                    | error RBRACK { $$ = nullptr; yyerrok; }
                    | ID LBRACK error { $$ = nullptr; yyerrok; }
                    ;

typeSpec            : BOOL { $$ = AST::Type::Bool; }
                    | CHAR { $$ = AST::Type::Char; }
                    | INT { $$ = AST::Type::Int; }
                    ;

funDecl             : typeSpec ID LPAREN parms RPAREN compoundStmt {
                        $$ = new AST::Decl::Func($2->linenum, $1, $2->tokenstr, $4, $6);
                        yyerrok;
                    }
                    | ID LPAREN parms RPAREN compoundStmt {
                        $$ = new AST::Decl::Func($1->linenum, $1->tokenstr, $3, $5);
                        yyerrok;
                    }
                    | error ID LPAREN parms RPAREN compoundStmt { $$ = nullptr; yyerrok; }
                    | typeSpec error LPAREN parms RPAREN compoundStmt { $$ = nullptr; yyerrok; }
                    | typeSpec ID error parms RPAREN compoundStmt { $$ = nullptr; yyerrok; }
                    | typeSpec ID LPAREN error RPAREN compoundStmt { $$ = nullptr; yyerrok; }
                    | typeSpec ID LPAREN parms error compoundStmt { $$ = nullptr; yyerrok; }
                    | typeSpec ID LPAREN parms RPAREN error { $$ = nullptr; yyerrok; }
                    | error LPAREN parms RPAREN compoundStmt { $$ = nullptr; yyerrok; }
                    | ID error parms RPAREN compoundStmt { $$ = nullptr; yyerrok; }
                    | ID LPAREN error RPAREN compoundStmt { $$ = nullptr; yyerrok; }
                    | ID LPAREN parms error compoundStmt { $$ = nullptr; yyerrok; }
                    | ID LPAREN parms RPAREN error { $$ = nullptr; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

parms               : { $$ = nullptr; yyerrok; }
                    | parmList { $$ = $1; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

parmList            : parmList SEMI parmTypeList {
                        $$ = $1;
                        $$->addSibling($3);
                        yyerrok;
                    }
                    | parmTypeList { $$ = $1; yyerrok; }
                    | error SEMI parmTypeList { $$ = nullptr; yyerrok; }
                    | parmList SEMI error { $$ = nullptr; yyerrok; }
                    | error SEMI error { $$ = nullptr; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

parmTypeList        : typeSpec parmIdList {
                        auto *parms = $2->cast<AST::Decl::Parm *>();
                        parms->setType($1);
                        $$ = parms;
                        yyerrok;
					}
                    | error parmIdList { $$ = nullptr; yyerrok; }
                    | typeSpec error { $$ = nullptr; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

parmIdList          : parmIdList COM parmId {
                        $$ = $1;
                        $$->addSibling($3);
                        yyerrok;
                    }
                    | parmId { $$ = $1; yyerrok; }
                    | error COM parmId { $$ = nullptr; yyerrok; }
                    | parmIdList COM error { $$ = nullptr; yyerrok; }
                    | error COM error { $$ = nullptr; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

parmId              : ID {
                        $$ = new AST::Decl::Parm($1->linenum, $1->tokenstr, false);
                        yyerrok;
					}
                    | ID LBRACK RBRACK {
                        $$ = new AST::Decl::Parm($1->linenum, $1->tokenstr, true);
                        yyerrok;
					}
                    | error LBRACK RBRACK { $$ = nullptr; yyerrok; }
                    | ID error RBRACK { $$ = nullptr; yyerrok; }
                    | ID LBRACK error { $$ = nullptr; yyerrok; }
                    | error RBRACK { $$ = nullptr; yyerrok; }
                    | ID error { $$ = nullptr; yyerrok; }
                    | error ID error { $$ = nullptr; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

stmt                : closedStmt { $$ = $1; yyerrok; }
                    | openStmt { $$ = $1; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

expStmt             : exp SEMI { $$ = $1; yyerrok; }
                    | SEMI { $$ = nullptr; yyerrok; }
                    | error SEMI { $$ = nullptr; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

compoundStmt        : BGN localDecls stmtList END {
                        $$ = new AST::Stmt::Compound($1->linenum, $2, $3);
                        yyerrok;
                    }
                    | error localDecls stmtList END { $$ = nullptr; yyerrok; }
                    | BGN error stmtList END { $$ = nullptr; yyerrok; }
                    | BGN localDecls error END { $$ = nullptr; yyerrok; }
                    | BGN localDecls stmtList error { $$ = nullptr; yyerrok; }
                    | BGN localDecls error { $$ = nullptr; yyerrok; }
                    | BGN error END { $$ = nullptr; yyerrok; }
                    | BGN error { $$ = nullptr; yyerrok; }
                    | error stmtList END { $$ = nullptr; yyerrok; }
                    | error END { $$ = nullptr; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

localDecls          : { $$ = nullptr; yyerrok; }
                    | localDecls scopedVarDecl {
                        if ($1 == nullptr) {
                            $$ = $2;
                        } else {
                            $$ = $1;
                            $$->addSibling($2);
                        }
                        yyerrok;
                    }
                    | error scopedVarDecl { $$ = nullptr; yyerrok; }
                    | localDecls error { $$ = nullptr; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

stmtList            : { $$ = nullptr; yyerrok; }
                    | stmtList stmt {
                        if ($1 == nullptr) {
                            $$ = $2;
                        } else {
                            $$ = $1;
                            $$->addSibling($2);
                        }
                        yyerrok;
                    }
                    | error stmt { $$ = nullptr; yyerrok; }
                    | stmtList error { $$ = nullptr; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

closedStmt          : selectStmtClosed { $$ = $1; yyerrok; }
                    | iterStmtClosed { $$ = $1; yyerrok; }
                    | expStmt { $$ = $1; yyerrok; }
                    | compoundStmt { $$ = $1; yyerrok; }
                    | returnStmt  { $$ = $1; yyerrok; }
                    | breakStmt { $$ = $1; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

openStmt            : selectStmtOpen { $$ = $1; yyerrok; }
                    | iterStmtOpen { $$ = $1; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

selectStmtOpen      : IF simpleExp THEN stmt {
                        $$ = new AST::Stmt::Select($1->linenum, $2, $4);
                        yyerrok;
                    }
                    | IF simpleExp THEN closedStmt ELSE openStmt {
                        $$ = new AST::Stmt::Select($1->linenum, $2, $4, $6);
                        yyerrok;
                    }
                    | error simpleExp THEN stmt { $$ = nullptr; yyerrok; }
                    | IF error THEN stmt { $$ = nullptr; yyerrok; }
                    | IF simpleExp error stmt { $$ = nullptr; yyerrok; }
                    | IF simpleExp THEN closedStmt ELSE error { $$ = nullptr; yyerrok; }
                    | IF simpleExp THEN closedStmt error { $$ = nullptr; yyerrok; }
                    | IF simpleExp THEN error { $$ = nullptr; yyerrok; }
                    | IF simpleExp error { $$ = nullptr; yyerrok; }
                    | IF error stmt { $$ = nullptr; yyerrok; }
                    | IF simpleExp THEN error openStmt { $$ = nullptr; yyerrok; }
                    | IF error ELSE openStmt { $$ = nullptr; yyerrok; }
                    | IF simpleExp error ELSE openStmt { $$ = nullptr; yyerrok; }
                    | IF error ELSE openStmt { $$ = nullptr; yyerrok; }
                    | IF simpleExp error openStmt { $$ = nullptr; yyerrok; }
                    | IF error { $$ = nullptr; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

selectStmtClosed    : IF simpleExp THEN closedStmt ELSE closedStmt {
                        $$ = new AST::Stmt::Select($1->linenum, $2, $4, $6);
                        yyerrok;
                    }
                    | error simpleExp THEN closedStmt ELSE closedStmt { $$ = nullptr; yyerrok; }
                    | error THEN closedStmt ELSE closedStmt { $$ = nullptr; yyerrok; }
                    | error closedStmt ELSE closedStmt { $$ = nullptr; yyerrok; }
                    | error ELSE closedStmt { $$ = nullptr; yyerrok; }
                    | error closedStmt { $$ = nullptr; yyerrok; }
                    | IF error THEN closedStmt ELSE closedStmt { $$ = nullptr; yyerrok; }
                    | IF simpleExp error closedStmt ELSE closedStmt { $$ = nullptr; yyerrok; }
                    | IF simpleExp THEN error ELSE closedStmt { $$ = nullptr; yyerrok; }
                    | IF simpleExp THEN closedStmt error closedStmt { $$ = nullptr; yyerrok; }
                    | IF simpleExp THEN closedStmt ELSE error { $$ = nullptr; yyerrok; }
                    | IF simpleExp THEN closedStmt error { $$ = nullptr; yyerrok; }
                    | IF simpleExp THEN error { $$ = nullptr; yyerrok; }
                    | IF simpleExp error { $$ = nullptr; yyerrok; }
                    | IF error { $$ = nullptr; yyerrok; }
                    | IF error closedStmt ELSE closedStmt { $$ = nullptr; yyerrok; }
                    | IF simpleExp error ELSE closedStmt { $$ = nullptr; yyerrok; }
                    | IF simpleExp THEN error closedStmt { $$ = nullptr; yyerrok; }
                    | IF error ELSE closedStmt { $$ = nullptr; yyerrok; }
                    | IF simpleExp error closedStmt { $$ = nullptr; yyerrok; }
                    | IF error closedStmt { $$ = nullptr; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

iterStmtOpen        : WHILE simpleExp DO openStmt {
                        $$ = new AST::Stmt::While($1->linenum, $2, $4);
                        yyerrok;
                    }
                    | error simpleExp DO openStmt { $$ = nullptr; yyerrok; }
                    | WHILE error DO openStmt { $$ = nullptr; yyerrok; }
                    | WHILE simpleExp error openStmt { $$ = nullptr; yyerrok; }
                    | WHILE simpleExp DO error { $$ = nullptr; yyerrok; }
                    | WHILE simpleExp error { $$ = nullptr; yyerrok; }
                    | WHILE error openStmt { $$ = nullptr; yyerrok; }
                    | WHILE error { $$ = nullptr; yyerrok; }
                    | FOR ID ASGN iterRange DO openStmt {
                        auto *iterator = new AST::Decl::Var($1->linenum, $2->tokenstr, false);
                        iterator->setType(AST::Type::Int);
                        $$ = new AST::Stmt::For($1->linenum, iterator, $4, $6);
                        yyerrok;
                    }
                    | error ID ASGN iterRange DO openStmt { $$ = nullptr; yyerrok; }
                    | FOR error iterRange DO openStmt { $$ = nullptr; yyerrok; }
                    | FOR ID error DO openStmt { $$ = nullptr; yyerrok; }
                    | FOR ID ASGN error openStmt { $$ = nullptr; yyerrok; }
                    | FOR error DO openStmt { $$ = nullptr; yyerrok; }
                    | FOR ID error openStmt { $$ = nullptr; yyerrok; }
                    | FOR error openStmt { $$ = nullptr; yyerrok; }
                    | error ASGN iterRange DO openStmt { $$ = nullptr; yyerrok; }
                    | error iterRange DO openStmt { $$ = nullptr; yyerrok; }
                    | FOR error ASGN iterRange DO openStmt { $$ = nullptr; yyerrok; }
                    | FOR ID error iterRange DO openStmt { $$ = nullptr; yyerrok; }
                    | FOR ID ASGN error DO openStmt { $$ = nullptr; yyerrok; }
                    | FOR ID ASGN iterRange error openStmt { $$ = nullptr; yyerrok; }
                    | FOR ID ASGN iterRange DO error { $$ = nullptr; yyerrok; }
                    | FOR ID ASGN iterRange error { $$ = nullptr; yyerrok; }
                    | FOR ID ASGN error { $$ = nullptr; yyerrok; }
                    | FOR ID error { $$ = nullptr; yyerrok; }
                    | FOR error { $$ = nullptr; yyerrok; }

                    | error DO openStmt { $$ = nullptr; yyerrok; }
                    | error openStmt { $$ = nullptr; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

iterStmtClosed      : WHILE simpleExp DO closedStmt {
                        $$ = new AST::Stmt::While($1->linenum, $2, $4);
                        yyerrok;
                    }
                    | error simpleExp DO closedStmt { $$ = nullptr; yyerrok; }
                    | WHILE error DO closedStmt { $$ = nullptr; yyerrok; }
                    | WHILE simpleExp error closedStmt { $$ = nullptr; yyerrok; }
                    | WHILE simpleExp DO error { $$ = nullptr; yyerrok; }
                    | WHILE simpleExp error { $$ = nullptr; yyerrok; }
                    | WHILE error closedStmt { $$ = nullptr; yyerrok; }
                    | WHILE error { $$ = nullptr; yyerrok; }
                    | FOR ID ASGN iterRange DO closedStmt {
                        auto *iterator = new AST::Decl::Var($1->linenum, $2->tokenstr, false);
                        iterator->setType(AST::Type::Int);
                        $$ = new AST::Stmt::For($1->linenum, iterator, $4, $6);
                        yyerrok;
                    }
                    | error ID ASGN iterRange DO closedStmt { $$ = nullptr; yyerrok; }
                    | FOR error iterRange DO closedStmt { $$ = nullptr; yyerrok; }
                    | FOR ID error DO closedStmt { $$ = nullptr; yyerrok; }
                    | FOR ID ASGN error closedStmt { $$ = nullptr; yyerrok; }
                    | FOR error DO closedStmt { $$ = nullptr; yyerrok; }
                    | FOR ID error closedStmt { $$ = nullptr; yyerrok; }
                    | FOR error closedStmt { $$ = nullptr; yyerrok; }
                    | error ASGN iterRange DO closedStmt { $$ = nullptr; yyerrok; }
                    | error iterRange DO closedStmt { $$ = nullptr; yyerrok; }
                    | FOR error ASGN iterRange DO closedStmt { $$ = nullptr; yyerrok; }
                    | FOR ID error iterRange DO closedStmt { $$ = nullptr; yyerrok; }
                    | FOR ID ASGN error DO closedStmt { $$ = nullptr; yyerrok; }
                    | FOR ID ASGN iterRange error closedStmt { $$ = nullptr; yyerrok; }
                    | FOR ID ASGN iterRange DO error { $$ = nullptr; yyerrok; }
                    | FOR ID ASGN iterRange error { $$ = nullptr; yyerrok; }
                    | FOR ID ASGN error { $$ = nullptr; yyerrok; }
                    | FOR ID error { $$ = nullptr; yyerrok; }
                    | FOR error { $$ = nullptr; yyerrok; }

                    | error DO closedStmt { $$ = nullptr; yyerrok; }
                    | error closedStmt { $$ = nullptr; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;
                    ;

iterRange           : simpleExp TO simpleExp {
                        $$ = new AST::Stmt::Range($1->lineNumber(), $1, $3);
                        yyerrok;
                    }
                    | simpleExp TO simpleExp BY simpleExp {
                        $$ = new AST::Stmt::Range($1->lineNumber(), $1, $3, $5);
                        yyerrok;
                    }
                    | error TO simpleExp { $$ = nullptr; yyerrok; }
                    | error simpleExp { $$ = nullptr; yyerrok; }
                    | simpleExp TO simpleExp error simpleExp { $$ = nullptr; yyerrok; }
                    | simpleExp error simpleExp { $$ = nullptr; yyerrok; }
                    | simpleExp TO simpleExp BY error { $$ = nullptr; yyerrok; }
                    | simpleExp TO simpleExp error { $$ = nullptr; yyerrok; }
                    | simpleExp TO error { $$ = nullptr; yyerrok; }
                    | simpleExp error { $$ = nullptr; yyerrok; }
                    | simpleExp error BY simpleExp { $$ = nullptr; yyerrok; }
                    | simpleExp TO error simpleExp { $$ = nullptr; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

returnStmt          : RETURN SEMI {
                        $$ = new AST::Stmt::Return($1->linenum, nullptr);
                        yyerrok;
                    }
                    | RETURN exp SEMI {
                        $$ = new AST::Stmt::Return($1->linenum, $2);
                        yyerrok;
                    }
                    | error SEMI { $$ = nullptr; yyerrok; }
                    | RETURN error SEMI { $$ = nullptr; yyerrok; }
                    | RETURN exp error { $$ = nullptr; yyerrok; }
                    | RETURN error { $$ = nullptr; yyerrok; }
                    | error { $$ = nullptr; yyerrok; }
                    ;

breakStmt           : BREAK SEMI {
                        $$ = new AST::Stmt::Break($1->linenum);
                    }
                    ;

exp                 : mutable assignop exp {
                        auto *op = $2->cast<AST::Exp::Op::Asgn *>();
                        op->addChildren($1, $3);
                        $$ = op;
                    }
                    | mutable INC {
                        $$ = new AST::Exp::Op::UnaryAsgn($1->lineNumber(), AST::UnaryAsgnType::Inc, $1);
                    }
                    | mutable DEC {
                        $$ = new AST::Exp::Op::UnaryAsgn($1->lineNumber(), AST::UnaryAsgnType::Dec, $1);
                    }
                    | simpleExp {
                        $$ = $1;
					}
                    ;

assignop            : ASGN {
                        $$ = new AST::Exp::Op::Asgn($1->linenum, AST::AsgnType::Asgn);
					}
                    | ADDASGN {
                        $$ = new AST::Exp::Op::Asgn($1->linenum, AST::AsgnType::AddAsgn);
					}
                    | SUBASGN {
                        $$ = new AST::Exp::Op::Asgn($1->linenum, AST::AsgnType::SubAsgn);
					}
                    | DIVASGN {
                        $$ = new AST::Exp::Op::Asgn($1->linenum, AST::AsgnType::DivAsgn);
					}
                    | MULASGN {
                        $$ = new AST::Exp::Op::Asgn($1->linenum, AST::AsgnType::MulAsgn);
					}
                    ;

simpleExp           : simpleExp OR andExp {
                        auto *boolop = new AST::Exp::Op::Bool($1->lineNumber(), AST::BoolOpType::Or);
                        boolop->addChildren($1, $3);
                        $$ = boolop;
                    }
                    | andExp {
                        $$ = $1;
					}
                    ;

andExp              : andExp AND unaryRelExp {
                        auto *boolop = new AST::Exp::Op::Bool($1->lineNumber(), AST::BoolOpType::And);
                        boolop->addChildren($1, $3);
                        $$ = boolop;
                    }
                    | unaryRelExp {
                        $$ = $1;
					}
                    ;

unaryRelExp         : NOT unaryRelExp {
                        $$ = new AST::Exp::Op::Unary($1->linenum, AST::UnaryOpType::Not, $2);
                    }
                    | relExp {
                        $$ = $1;
					}
                    ;

relExp              : sumExp relop sumExp {
                        auto *op = $2->cast<AST::Exp::Op::Binary *>();
                        op->addChildren($1, $3);
                        $$ = op;
                    }
                    | sumExp {
                        $$ = $1;
					}
                    ;

relop               : LT {
                        $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::LT);
					}
                    | LEQ {
                        $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::LEQ);
					}
                    | GT {
                        $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::GT);
					}
                    | GEQ {
                        $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::GEQ);
					}
                    | EQ {
                        $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::EQ);
					}
                    | NEQ {
                        $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::NEQ);
					}
                    ;

sumExp              : sumExp sumop mulExp {
                        auto *op = $2->cast<AST::Exp::Op::Binary *>();
                        op->addChildren($1, $3);
                        $$ = op;
					}
                    | mulExp {
                        $$ = $1;
					}
                    ;

sumop               : ADD {
                        $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Add);
					}
                    | DASH {
                        $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Subtract);
					}
                    ;

mulExp              : mulExp mulop unaryExp {
                        auto *op = $2->cast<AST::Exp::Op::Binary *>();
                        op->addChildren($1, $3);
                        $$ = op;
					}
                    | unaryExp {
                        $$ = $1;
					}
                    ;

mulop               : ASTERISK {
                        $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Mul);
					}
                    | DIV {
                        $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Div);
					}
                    | MOD {
                        $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Mod);
					}
                    ;

unaryExp            : unaryop unaryExp {
                        auto *op = $1->cast<AST::Exp::Op::Unary *>();
                        op->addExp($2);
                        $$ = op;
					}
                    | factor {
                        $$ = $1;
					}
                    ;

unaryop             : DASH {
                        $$ = new AST::Exp::Op::Unary($1->linenum, AST::UnaryOpType::Chsign);
					}
                    | ASTERISK {
                        $$ = new AST::Exp::Op::Unary($1->linenum, AST::UnaryOpType::Sizeof);
					}
                    | RAND {
                        $$ = new AST::Exp::Op::Unary($1->linenum, AST::UnaryOpType::Random);
					}
                    ;

factor              : mutable {
                        $$ = $1;
					}
                    | immutable {
                        $$ = $1;
					}
                    ;

mutable             : ID {
                        $$ = new AST::Exp::Id($1->linenum, $1->tokenstr);
					}
                    | ID LBRACK exp RBRACK {
                        $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Index, new AST::Exp::Id($1->linenum, $1->tokenstr), $3);
                    }
                    ;

immutable           : LPAREN exp RPAREN {
                        $$ = $2;
                    }
                    | call {
                        $$ = $1;
                    }
                    | constant {
                        $$ = $1;
                    }
                    ;

call                : ID LPAREN argList RPAREN {
                        $$ = new AST::Exp::Call($1->linenum, $1->tokenstr, $3);
                    }
                    | ID LPAREN RPAREN {
                        $$ = new AST::Exp::Call($1->linenum, $1->tokenstr);
                    }
                    ;

argList             : argList COM exp {
                        $$ = $1;
                        $$->addSibling($3);
                    }
                    | exp {
                        $$ = $1;
                    }
                    ;

constant            : NUMCONST {
                        AST::TypeInfo type = {AST::Type::Int, false, false};
                        $$ = new AST::Exp::Const($1->linenum, type, $1->tokenstr);
                    }
                    | CHARCONST {
                        AST::TypeInfo type = {AST::Type::Char, false, false};
                        $$ = new AST::Exp::Const($1->linenum, type, $1->tokenstr);
                    }
                    | STRINGCONST {
                        AST::TypeInfo type = {AST::Type::Char, true, false};
                        $$ = new AST::Exp::Const($1->linenum, type, $1->tokenstr);
                    }
                    | BOOLCONST {
                        AST::TypeInfo type = {AST::Type::Bool, false, false};
                        $$ = new AST::Exp::Const($1->linenum, type, $1->tokenstr);
                    }
                    ;

%%
extern int yydebug;
extern std::vector<std::unique_ptr<TokenData>> tokens;
int main(int argc, char *argv[])
{
    Options options(argc, argv);
    bool fileExists = true;
    yydebug = options.debug();
    std::optional<std::string> file = options.file();

    if (file.has_value()) {
        SemanticsChecker semantics = SemanticsChecker(options.debugSymbolTable());
        if ((yyin = fopen(file.value().c_str(), "r"))) {
            // file open successful
            // do the parsing
            numErrors = 0;
            yyparse();

            semantics.analyze(tree_root);

            if (options.printTypeInfo()) {
                semantics.print();
            }

            if (tree_root != nullptr && semantics.numErrors() == 0) {
                if (options.printTypeInfo()) {
                    tree_root->print(options.printTypeInfo());
                } else if (options.print()) {
                    tree_root->print(false);
                }
            }

            

            // Free memory
            if (tree_root != nullptr) {
                delete tree_root;
            }
            tokens.clear();
        }
        else {
            std::cout << "ERROR(ARGLIST): source file \"" + file.value() + "\" could not be opened." << std::endl;
            fileExists = false;
        }
        std::cout << "Number of warnings: " << semantics.numWarnings() << std::endl;
        std::cout << "Number of errors: " << semantics.numErrors() + !fileExists << std::endl;
    } else {
        yyparse();
    }
    
    return 0;
}