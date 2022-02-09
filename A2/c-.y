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
#include "AST/AST_node.hpp"

double vars[26];    

extern int yylex();
extern FILE *yyin;
extern int line;         // ERR line number from the scanner!!
extern int numErrors;    // ERR err count
AST_node* tree_root;

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
    AST_node *node;
    TokenData *tokenData;
    double value;
}

%token <node> WHILE IF FOR TO RETURN BREAK BY DO
%token <node> NOT AND OR
%token <node> ADD RAND MUL DIV MOD SUB ASGN ADDASGN SUBASGN MULASGN DIVASGN
%token <node> THEN ELSE BGN END
%token <node> RPAREN LPAREN RBRACK LBRACK
%token <node> STATIC INT BOOL CHAR 
%token <node> SEMI LT LEQ GT GEQ EQ NEQ INC DEC COL COM
%token <node> ID NUMCONST CHARCONST STRINGCONST BOOLCONST

%type <node> program
%type <node> declList
%type <node> decl
%type <node> varDecl
%type <node> scopedVarDecl
%type <node> varDeclList
%type <node> varDeclInit
%type <node> varDeclId
%type <node> typeSpec
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
                        std::cout << "program:declList\n";
                        $$ = $1;
                        tree_root = $$;
                    }
                    ;

declList            : declList decl
                    {
                        std::cout << "declList:declList decl\n";
                        $$ = $1;
                        $$->add_sibling($2);
                    }
                    | decl
                    {
                        std::cout << "declList:decl\n";
                        $$ = $1;
                    }
                    ;

decl                : varDecl
                    { $$ = $1; }
                    | funDecl
                    { $$ = $1; }
                    ;

varDecl             : typeSpec varDeclList SEMI
                    { $$ = $2; }
                    ;

scopedVarDecl       : STATIC typeSpec varDeclList SEMI
                    { $$ = $3; }
                    | typeSpec varDeclList SEMI
                    { $$ = $3; }
                    ;

varDeclList         : varDeclList COM varDeclInit
                    {
                        $$ = $1;
                        $$->add_sibling($3);
                    }
                    | varDeclInit
                    { $$ = $1; }
                    ;

varDeclInit         : varDeclId
                    { $$ = $1; }
                    | varDeclId COL simpleExp
                    {
                        $$ = $1;
                        $$->add_sibling($3);
                    }
                    ;
                
varDeclId           : ID
                    {
                        $$ = new AST_node(Type::Declaration::Variable);
                    }
                    | ID LBRACK NUMCONST RBRACK
                    {
                        $$ = new AST_node(Type::Declaration::Variable);
                    }
                    ;

typeSpec            : BOOL | CHAR | INT
                    ;

funDecl             : typeSpec ID LPAREN parms RPAREN compoundStmt
                    {
                        $$ = new AST_node(Type::Declaration::Function);
                    }
                    | ID LPAREN parms RPAREN compoundStmt
                    {
                        $$ = new AST_node(Type::Declaration::Function);
                    }
                    ;

parms               :
                    { $$ = nullptr; }
                    | parmList
                    { $$ = $1; }
                    ;

parmList            : parmList SEMI parmTypeList
                    {
                        $$ = $1;
                        $1->add_sibling($3);
                    }
                    | parmTypeList
                    { $$ = $1; }
                    ;

parmTypeList        : typeSpec parmIdList
                    { $$ = $2; }
                    ;

parmIdList          : parmIdList COM parmId
                    {
                        $$ = $1;
                        $$->add_sibling($3);
                    }
                    | parmId
                    { $$ = $1; }
                    ;

parmId              : ID
                    { $$ = $1; }
                    | ID LBRACK RBRACK
                    { $$ = $1; }
                    ;

stmt                : closedStmt
                    { $$ = $1; }
                    | openStmt
                    { $$ = $1; }
                    ;

expStmt             : exp SEMI
                    { $$ = $1; }
                    | SEMI
                    { $$ = nullptr; }
                    ;

compoundStmt        : BGN localDecls stmtList END
                    {
                        $$ = new AST_node(Type::Statement::Compound);
                        $$->add_child($2);
                        $$->add_child($3);
                    }
                    ;

localDecls          :
                    { $$ = nullptr; }
                    | localDecls scopedVarDecl
                    {
                        $$ = $1;
                        $$->add_sibling($2);
                    }
                    ;

stmtList            :
                    { $$ = nullptr; }
                    | stmtList stmt
                    {
                        $$ = $1;
                        $$->add_sibling($2);
                    }
                    ;

closedStmt          : selectStmtClosed
                    { $$ = $1; }
                    | iterStmtClosed
                    { $$ = $1; }
                    | expStmt
                    { $$ = $1; }
                    | compoundStmt
                    { $$ = $1; }
                    | returnStmt 
                    { $$ = $1; }
                    | breakStmt
                    { $$ = $1; }
                    ;

openStmt            : selectStmtOpen
                    { $$ = $1; }
                    | iterStmtOpen
                    { $$ = $1; }
                    ;

selectStmtOpen      : IF simpleExp THEN closedStmt
                    {
                        $$ = new AST_node(Type::Statement::Select);
                        $$->add_child($2);
                        $$->add_child($4);
                    }
                    | IF simpleExp THEN openStmt
                    {
                        $$ = new AST_node(Type::Statement::Select);
                        $$->add_child(2);
                        $$->add_child($4);
                    }
                    | IF simpleExp THEN closedStmt ELSE openStmt
                    {
                        $$ = new AST_node(Type::Statement::Select);
                        $$->add_child(2);
                        $$->add_child($4);
                        $$->add_child($6);
                    }
                    ;

selectStmtClosed    : IF simpleExp THEN closedStmt ELSE closedStmt
                    {
                        $$ = new AST_node(Type::Statement::Select);
                        $$->add_child($2);
                        $$->add_child($4);
                        $$->add_child($6);
                    }
                    ;

iterStmtOpen        : WHILE simpleExp DO openStmt
                    {
                        $$ = new AST_node(Type::Statement::Iterative);
                        $$->add_child($2);
                        $$->add_child($4);
                    }
                    | FOR ID ASGN iterRange DO openStmt
                    {
                        $$ = new AST_node(Type::Statement::Iterative);
                        $$->add_child($4);
                        $$->add_child($6);
                    }
                    ;

iterStmtClosed      : WHILE simpleExp DO closedStmt
                    {
                        $$ = new AST_node(Type::Statement::Iterative);
                        $$->add_child($2);
                        $$->add_child($4);
                    }
                    | FOR ID ASGN iterRange DO closedStmt
                    {
                        $$ = new AST_node(Type::Statement::Iterative);
                        $$->add_child($4);
                        $$->add_child($6);
                    }
                    ;

iterRange           : simpleExp TO simpleExp
                    {
                        $$ = $1;
                        $$->add_sibling($3);
                    }
                    | simpleExp TO simpleExp BY simpleExp
                    {
                        $$ = $1;
                        $$->add_sibling($3);
                        $$->add_sibling($5);
                    }
                    ;

returnStmt          : RETURN SEMI
                    {
                        $$ = new AST_node(Type::Statement::Return);
                    }
                    | RETURN exp SEMI
                    {
                        $$ = new AST_node(Type::Statement::Return);
                        $$->add_child($2);
                    }
                    ;

breakStmt           : BREAK SEMI
                    {
                        $$ = new AST_node(Type::Statement::Break);
                    }
                    ;

exp                 : mutable assignop exp
                    {
                        $$ = new AST_node(Type::Expression::Assign);
                        $$->add_child($1);
                        $$->add_child($2);
                        $$->add_child($3);
                    }
                    | mutable INC
                    {
                        $$ = new AST_node(Type::Expression::Increment);
                        $$->add_child($1);
                    }
                    | mutable DEC
                    {
                        $$ = new AST_node(Type::Expression::Decrement);
                        $$->add_child($1); 
                    }
                    | simpleExp
                    { $$ = $1; }
                    ;

assignop            : ASGN
                    { $$ = new AST_node(Type::Expression::Assign); }
                    | ADDASGN
                    { $$ = new AST_node(Type::Expression::Assign); }
                    | SUBASGN
                    { $$ = new AST_node(Type::Expression::Assign); }
                    | DIVASGN
                    { $$ = new AST_node(Type::Expression::Assign); }
                    | MULASGN
                    { $$ = new AST_node(Type::Expression::Assign); }
                    ;

simpleExp           : simpleExp OR andExp
                    {
                        $$ = new AST_node(Type::Expression::Simple);
                        $$->add_child($1);
                        $$->add_child($3);           
                    }
                    | andExp
                    { $$ = $1; }
                    ;

andExp              : andExp AND unaryRelExp
                    {
                        $$ = new AST_node(Type::Expression::And);
                        $$->add_child($1);
                        $$->add_child($3);
                    }
                    | unaryRelExp
                    { $$ = $1; }
                    ;

unaryRelExp         : NOT unaryRelExp
                    {
                        $$ = new AST_node(Type::Expression::UnaryRelation);
                        $$->add_child($2);
                    }
                    | relExp
                    { $$ = $1; }
                    ;

relExp              : sumExp relop sumExp
                    {
                        $$ = new AST_node(Type::Expression::UnaryRelation);
                    }
                    | sumExp
                    { $$ = nullptr; }
                    ;

relop               : LT
                    { $$ = nullptr; }
                    | LEQ
                    { $$ = nullptr; }
                    | GT
                    { $$ = nullptr; }
                    | GEQ
                    { $$ = nullptr; }
                    | EQ
                    { $$ = nullptr; }
                    | NEQ
                    { $$ = nullptr; }
                    ;

sumExp              : sumExp sumop mulExp
                    { $$ = nullptr; }
                    | mulExp
                    { $$ = nullptr; }
                    ;

sumop               : ADD
                    { $$ = nullptr; }
                    | SUB
                    { $$ = nullptr; }
                    ;

mulExp              : mulExp mulop unaryExp
                    { $$ = nullptr; }
                    | unaryExp
                    { $$ = nullptr; }
                    ;

mulop               : MUL
                    { $$ = nullptr; }
                    | DIV
                    { $$ = nullptr; }
                    | MOD
                    { $$ = nullptr; }
                    ;

unaryExp            : unaryop unaryExp
                    { $$ = nullptr; }
                    | factor
                    { $$ = nullptr; }
                    ;

unaryop             : SUB
                    { $$ = nullptr; }
                    | MUL
                    { $$ = nullptr; }
                    | RAND
                    { $$ = nullptr; }
                    ;

factor              : mutable
                    { $$ = $1; }
                    | immutable
                    { $$ = $1; }
                    ;

mutable             : ID
                    { $$ = nullptr; }
                    | ID LBRACK exp RBRACK
                    {
                        std::cout << "immutable:lparen exp rparen\n";
                        $$ = nullptr;
                    }
                    ;

immutable           : LPAREN exp RPAREN
                    {
                        std::cout << "immutable:lparen exp rparen\n";
                        $$ = $2;
                    }
                    | call
                    {
                        std::cout << "immutable:call\n";
                        $$ = $1;
                    }
                    | constant
                    {
                        std::cout << "immutable:constant\n";
                        $$ = $1;
                    }
                    ;

call                : ID LPAREN argList RPAREN
                    {
                        $$ = $3;
                        std::cout << "call:id lparen arglist rparen\n";
                    }
                    | ID LPAREN RPAREN
                    {
                        std::cout << "call:id lparen rparen\n";
                        $$ = nullptr;
                    }
                    ;

argList             : argList COM exp
                    {
                        std::cout << "argList:arglist com exp\n";
                        $$ = $1;
                        $$->add_sibling($3);
                    }
                    | exp
                    {
                        std::cout << "argList:exp\n";
                        $$ = $1;
                    }
                    ;

constant            : NUMCONST
                    {
                        std::cout << "constant:numconst\n";
                        $$ = new AST_node(Type::Declaration::Variable);
                    }
                    | CHARCONST
                    {
                        std::cout << "constant:charconst\n";
                        $$ = new AST_node(Type::Declaration::Variable);
                    }
                    | STRINGCONST
                    {
                        std::cout << "constant:stringconst\n";
                        $$ = new AST_node(Type::Declaration::Variable);
                    }
                    | BOOLCONST
                    {
                        std::cout << "constant:boolconst\n";
                        $$ = new AST_node(Type::Declaration::Variable);
                    }
                    ;

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
    std::cout << "print\n";
    if (tree_root != nullptr) {
        tree_root->print();
    }

    return 0;
}
