%{
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
#include "AST/AST.hpp"

double vars[26];    

extern int yylex();
extern FILE *yyin;
extern int line;         // ERR line number from the scanner!!
extern int numErrors;    // ERR err count
extern char *yytext;
extern std::vector<TokenData*> tokens;
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
    AST::Decl::Type type;
    AST::Node *node;
    TokenData *tokenData;
    double value;
}

%token <tokenData> WHILE IF FOR TO RETURN BREAK BY DO
%token <tokenData> NOT AND OR
%token <tokenData> ADD RAND MUL DIV MOD SUB ASGN ADDASGN SUBASGN MULASGN DIVASGN
%token <tokenData> THEN ELSE BGN END
%token <tokenData> RPAREN LPAREN RBRACK LBRACK
%token <tokenData> STATIC
%token <tokenData> SEMI LT LEQ GT GEQ EQ NEQ INC DEC COL COM
%token <type> INT BOOL CHAR 

%token <tokenData> ID NUMCONST CHARCONST STRINGCONST BOOLCONST
%type <node> program
%type <node> declList
%type <node> decl
%type <node> varDecl
%type <node> scopedVarDecl
%type <node> varDeclList
%type <node> varDeclInit
%type <node> varDeclId
%type <type> typeSpec
%type <node> funDecl
%type <node> parms
%type <node> parmList
%type <node> parmTypeList
%type <node> parmIdList
%type <node> parmId
%type <node> stmt
%type <node> expStmt
%type <node> compoundStmt
%type <node> localDecls
%type <node> stmtList
%type <node> closedStmt
%type <node> openStmt
%type <node> selectStmtOpen
%type <node> selectStmtClosed
%type <node> iterStmtOpen
%type <node> iterStmtClosed
%type <node> iterRange
%type <node> returnStmt
%type <node> breakStmt
%type <node> exp
%type <node> assignop
%type <node> simpleExp
%type <node> andExp
%type <node> unaryRelExp
%type <node> relExp
%type <node> relop
%type <node> sumExp
%type <node> sumop
%type <node> mulExp
%type <node> mulop
%type <node> unaryExp
%type <node> unaryop
%type <node> factor
%type <node> mutable
%type <node> immutable
%type <node> call
%type <node> argList
%type <node> constant


%%

program             : declList
                    {
                        $$ = $1;
                        tree_root = $$;
                    }
                    ;

declList            : declList decl
                    {
                        $$ = $1;
                        $$->addSibling($2);
                    }
                    | decl
                    {
                        $$ = $1;
                    }
                    ;

decl                : varDecl
                    {
                        $$ = $1;
					}
                    | funDecl
                    {
                        $$ = $1;
					}
                    ;

varDecl             : typeSpec varDeclList SEMI
                    {
                        AST::Decl::Var *var = (AST::Decl::Var *)$2;
                        var->setType($1);
                        $$ = var;
					}
                    ;

scopedVarDecl       : STATIC typeSpec varDeclList SEMI
                    {
                        AST::Decl::Var *var = (AST::Decl::Var *)$3;
                        var->setType($2);
                        var->setStatic();
                        $$ = var;
					}
                    | typeSpec varDeclList SEMI
                    {
                        AST::Decl::Var *var = (AST::Decl::Var *)$2;
                        var->setType($1);
                        $$ = var;
					}
                    ;

varDeclList         : varDeclList COM varDeclInit
                    {
                        $$ = $1;
                        $$->addSibling($3);
                    }
                    | varDeclInit
                    {
                        $$ = $1;
					}
                    ;

varDeclInit         : varDeclId
                    {
                        $$ = $1;
					}
                    | varDeclId COL simpleExp
                    {
                        $$ = $1;
                        $$->addChild($3);
                    }
                    ;
                
varDeclId           : ID
                    {
                        $$ = new AST::Decl::Var($1->linenum, $1->tokenstr, false);
                    }
                    | ID LBRACK NUMCONST RBRACK
                    {
                        $$ = new AST::Decl::Var($1->linenum, $1->tokenstr, true);
                    }
                    ;

typeSpec            : BOOL
                    {
                        $$ = AST::Decl::Type::Bool;
                    }
                    | CHAR
                    {
                        $$ = AST::Decl::Type::Char;
                    }
                    | INT
                    {
                        $$ = AST::Decl::Type::Int;
                    }
                    ;

funDecl             : typeSpec ID LPAREN parms RPAREN compoundStmt
                    {
                        $$ = new AST::Decl::Func($1->linenum, $1, $2->tokenstr, $4, $6);
                    }
                    | ID LPAREN parms RPAREN compoundStmt
                    {
                        $$ = new AST::Decl::Func($1->linenum, $1->tokenstr, $3, $5);
                    }
                    ;

parms               :
                    {
                        $$ = nullptr;
					}
                    | parmList
                    {
                        $$ = $1;
					}
                    ;

parmList            : parmList SEMI parmTypeList
                    {
                        $$ = $1;
                        $$->addSibling($3);
                    }
                    | parmTypeList
                    {
                        $$ = $1;
					}
                    ;

parmTypeList        : typeSpec parmIdList
                    {
                        AST::Decl::Parm *parms = (AST::Decl::Parm *)$2;
                        parms->setType($1);
                        $$ = parms;
					}
                    ;

parmIdList          : parmIdList COM parmId
                    {
                        $$ = $1;
                        $$->addSibling($3);
                    }
                    | parmId
                    {
                        $$ = $1;
					}
                    ;

parmId              : ID
                    {
                        $$ = new AST::Decl::Parm($1->linenum, $1->tokenstr, false);
					}
                    | ID LBRACK RBRACK
                    {
                        $$ = new AST::Decl::Parm($1->linenum, $1->tokenstr, true);
					}
                    ;

stmt                : closedStmt
                    {
                        $$ = $1;
					}
                    | openStmt
                    {
                        $$ = $1;
					}
                    ;

expStmt             : exp SEMI
                    {
                        $$ = $1;
					}
                    | SEMI
                    {
                        $$ = nullptr;
					}
                    ;

compoundStmt        : BGN localDecls stmtList END
                    {
                        $$ = new AST::Stmt::Compound($1->linenum, $2, $3);
                    }
                    ;

localDecls          :
                    {
                        $$ = nullptr;
					}
                    | localDecls scopedVarDecl
                    {
                        if ($1 == nullptr) {
                            $$ = $2;
                        } else {
                            $$ = $1;
                            $$->addSibling($2);
                        }
                    }
                    ;

stmtList            :
                    {
                        $$ = nullptr;
					}
                    | stmtList stmt
                    {
                        if ($1 == nullptr) {
                            $$ = $2;
                        } else {
                            $$ = $1;
                            $$->addSibling($2);
                        }
                    }
                    ;

closedStmt          : selectStmtClosed
                    {
                        $$ = $1;
					}
                    | iterStmtClosed
                    {
                        $$ = $1;
					}
                    | expStmt
                    {
                        $$ = $1;
					}
                    | compoundStmt
                    {
                        $$ = $1;
					}
                    | returnStmt 
                    {
                        $$ = $1;
					}
                    | breakStmt
                    {
                        $$ = $1;
					}
                    ;

openStmt            : selectStmtOpen
                    {
                        $$ = $1;
					}
                    | iterStmtOpen
                    {
                        $$ = $1;
					}
                    ;

selectStmtOpen      : IF simpleExp THEN stmt
                    {
                        $$ = new AST::Stmt::Select($1->linenum, $2, $4);
                    }
                    | IF simpleExp THEN closedStmt ELSE openStmt
                    {
                        $$ = new AST::Stmt::Select($1->linenum, $2, $4, $6);
                    }
                    ;

selectStmtClosed    : IF simpleExp THEN closedStmt ELSE closedStmt
                    {
                        $$ = new AST::Stmt::Select($1->linenum, $2, $4, $6);
                    }
                    ;

iterStmtOpen        : WHILE simpleExp DO openStmt
                    {
                        $$ = new AST::Stmt::While($1->linenum, $2, $4);
                    }
                    | FOR ID ASGN iterRange DO openStmt
                    {
                        AST::Decl::Var *iterator = new AST::Decl::Var($1->linenum, $2->tokenstr, false);
                        iterator->setType(AST::Decl::Type::Int);
                        $$ = new AST::Stmt::For($1->linenum, iterator, $4, $6);
                    }
                    ;

iterStmtClosed      : WHILE simpleExp DO closedStmt
                    {
                        $$ = new AST::Stmt::While($1->linenum, $2, $4);
                    }
                    | FOR ID ASGN iterRange DO closedStmt
                    {
                        AST::Decl::Var *iterator = new AST::Decl::Var($1->linenum, $2->tokenstr, false);
                        iterator->setType(AST::Decl::Type::Int);
                        $$ = new AST::Stmt::For($1->linenum, iterator, $4, $6);
                    }
                    ;

iterRange           : simpleExp TO simpleExp
                    {
                        $$ = new AST::Exp::Range($1->lineNumber(), $1, $3);
                    }
                    | simpleExp TO simpleExp BY simpleExp
                    {
                        $$ = new AST::Exp::Range($1->lineNumber(), $1, $3, $5);
                    }
                    ;

returnStmt          : RETURN SEMI
                    {
                        $$ = new AST::Stmt::Return($1->linenum, nullptr);
                    }
                    | RETURN exp SEMI
                    {
                        $$ = new AST::Stmt::Return($1->linenum, $2);
                    }
                    ;

breakStmt           : BREAK SEMI
                    {
                        $$ = new AST::Stmt::Break($1->linenum);
                    }
                    ;

exp                 : mutable assignop exp
                    {
                        AST::Op::Asgn *op = (AST::Op::Asgn *)$2;
                        op->addChildren($1, $3);
                        $$ = op;
                    }
                    | mutable INC
                    {
                        $$ = new AST::Op::Unary($1->lineNumber(), AST::Op::Unary::Type::Inc, $1);
                    }
                    | mutable DEC
                    {
                        $$ = new AST::Op::Unary($1->lineNumber(), AST::Op::Unary::Type::Dec, $1);
                    }
                    | simpleExp
                    {
                        $$ = $1;
					}
                    ;

assignop            : ASGN
                    {
                        $$ = new AST::Op::Asgn($1->linenum, AST::Op::Asgn::Type::Asgn);
					}
                    | ADDASGN
                    {
                        $$ = new AST::Op::Asgn($1->linenum, AST::Op::Asgn::Type::AddAsgn);
					}
                    | SUBASGN
                    {
                        $$ = new AST::Op::Asgn($1->linenum, AST::Op::Asgn::Type::SubAsgn);
					}
                    | DIVASGN
                    {
                        $$ = new AST::Op::Asgn($1->linenum, AST::Op::Asgn::Type::DivAsgn);
					}
                    | MULASGN
                    {
                        $$ = new AST::Op::Asgn($1->linenum, AST::Op::Asgn::Type::MulAsgn);
					}
                    ;

simpleExp           : simpleExp OR andExp
                    {
                        $$ = new AST::Op::Binary($1->lineNumber(), AST::Op::Binary::Type::Or, $1, $3);
                    }
                    | andExp
                    {
                        $$ = $1;
					}
                    ;

andExp              : andExp AND unaryRelExp
                    {
                        $$ = new AST::Op::Binary($1->lineNumber(), AST::Op::Binary::Type::And, $1, $3);
                    }
                    | unaryRelExp
                    {
                        $$ = $1;
					}
                    ;

unaryRelExp         : NOT unaryRelExp
                    {
                        $$ = new AST::Op::Unary($1->linenum, AST::Op::Unary::Type::Not, $2);
                    }
                    | relExp
                    {
                        $$ = $1;
					}
                    ;

relExp              : sumExp relop sumExp
                    {
                        AST::Op::Binary *op = (AST::Op::Binary *)$2;
                        op->addChildren($1, $3);
                        $$ = op;
                    }
                    | sumExp
                    {
                        $$ = $1;
					}
                    ;

relop               : LT
                    {
                        $$ = new AST::Op::Binary($1->linenum, AST::Op::Binary::Type::LT);
					}
                    | LEQ
                    {
                        $$ = new AST::Op::Binary($1->linenum, AST::Op::Binary::Type::LEQ);
					}
                    | GT
                    {
                        $$ = new AST::Op::Binary($1->linenum, AST::Op::Binary::Type::GT);
					}
                    | GEQ
                    {
                        $$ = new AST::Op::Binary($1->linenum, AST::Op::Binary::Type::GEQ);
					}
                    | EQ
                    {
                        $$ = new AST::Op::Binary($1->linenum, AST::Op::Binary::Type::EQ);
					}
                    | NEQ
                    {
                        $$ = new AST::Op::Binary($1->linenum, AST::Op::Binary::Type::NEQ);
					}
                    ;

sumExp              : sumExp sumop mulExp
                    {
                        AST::Op::Binary *op = (AST::Op::Binary *)$2;
                        op->addChildren($1, $3);
                        $$ = op;
					}
                    | mulExp
                    {
                        $$ = $1;
					}
                    ;

sumop               : ADD
                    {
                        $$ = new AST::Op::Binary($1->linenum, AST::Op::Binary::Type::Add);
					}
                    | SUB
                    {
                        $$ = new AST::Op::Binary($1->linenum, AST::Op::Binary::Type::Subtract);
					}
                    ;

mulExp              : mulExp mulop unaryExp
                    {
                        AST::Op::Binary *op = (AST::Op::Binary *)$2;
                        op->addChildren($1, $3);
                        $$ = op;
					}
                    | unaryExp
                    {
                        $$ = $1;
					}
                    ;

mulop               : MUL
                    {
                        $$ = new AST::Op::Binary($1->linenum, AST::Op::Binary::Type::Mul);
					}
                    | DIV
                    {
                        $$ = new AST::Op::Binary($1->linenum, AST::Op::Binary::Type::Div);
					}
                    | MOD
                    {
                        $$ = new AST::Op::Binary($1->linenum, AST::Op::Binary::Type::Mod);
					}
                    ;

unaryExp            : unaryop unaryExp
                    {
                        AST::Op::Unary *op = (AST::Op::Unary *)$1;
                        op->addExp($2);
                        $$ = op;
					}
                    | factor
                    {
                        $$ = $1;
					}
                    ;

unaryop             : SUB
                    {
                        $$ = new AST::Op::Unary($1->linenum, AST::Op::Unary::Type::Chsign);
					}
                    | MUL
                    {
                        $$ = new AST::Op::Unary($1->linenum, AST::Op::Unary::Type::Sizeof);
					}
                    | RAND
                    {
                        $$ = new AST::Op::Unary($1->linenum, AST::Op::Unary::Type::Random);
					}
                    ;

factor              : mutable
                    {
                        $$ = $1;
					}
                    | immutable
                    {
                        $$ = $1;
					}
                    ;

mutable             : ID
                    {
                        $$ = new AST::Exp::Id($1->linenum, $1->tokenstr);
					}
                    | ID LBRACK exp RBRACK
                    {
                        $$ = new AST::Op::Binary($1->linenum, AST::Op::Binary::Type::Index, new AST::Exp::Id($1->linenum, $1->tokenstr), $3);
                    }
                    ;

immutable           : LPAREN exp RPAREN
                    {
                        $$ = $2;
                    }
                    | call
                    {
                        $$ = $1;
                    }
                    | constant
                    {
                        $$ = $1;
                    }
                    ;

call                : ID LPAREN argList RPAREN
                    {
                        $$ = new AST::Exp::Call($1->linenum, $1->tokenstr, $3);
                    }
                    | ID LPAREN RPAREN
                    {
                        $$ = new AST::Exp::Call($1->linenum, $1->tokenstr);
                    }
                    ;

argList             : argList COM exp
                    {
                        $$ = $1;
                        $$->addSibling($3);
                    }
                    | exp
                    {
                        $$ = $1;
                    }
                    ;

constant            : NUMCONST
                    {
                        int i = std::atoi(yytext);
                        $$ = new AST::Exp::Const($1->linenum, i);
                    }
                    | CHARCONST
                    {
                        char c = strutil::get_first_char(strutil::remove_quotes(yytext));
                        $$ = new AST::Exp::Const($1->linenum, c);
                    }
                    | STRINGCONST
                    {
                        std::string s = strutil::make_str(strutil::remove_quotes(yytext));
                        $$ = new AST::Exp::Const($1->linenum, s);
                    }
                    | BOOLCONST
                    {
                        bool b = std::string(yytext) == "true";
                        $$ = new AST::Exp::Const($1->linenum, b);
                    }
                    ;

%%
extern int yydebug;
int main(int argc, char *argv[])
{
    bool print = false;
    std::string file;

    for (unsigned i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "-p") {
            print = true;
        } else {
            file = std::string(argv[i]);
            break;
        }
    }

    if ((yyin = fopen(file.c_str(), "r"))) {
        // file open successful
    }
    else {
        // failed to open file
        printf("ERROR: failed to open \'%s\'\n", argv[1]);
        exit(1);
    }

    // init variables a through z
    for (int i=0; i<26; i++) vars[i] = 0.0;

    // do the parsing
    numErrors = 0;
    yyparse();

    if (tree_root != nullptr && print) {
        tree_root->print();
    }

    for (auto& token : tokens) {
        delete token;
    }

    return 0;
}
