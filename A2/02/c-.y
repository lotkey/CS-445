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
extern std::vector<TokenData*> tokens;
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
    Type::ExpressionType type;
    AST_node *node;
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
                        $$->add_sibling($2);
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
                        $$ = $2;
					}
                    ;

scopedVarDecl       : STATIC typeSpec varDeclList SEMI
                    {
                        $$ = $3;
					}
                    | typeSpec varDeclList SEMI
                    {
                        $$ = $2;
					}
                    ;

varDeclList         : varDeclList COM varDeclInit
                    {
                        $$ = $1;
                        $$->add_sibling($3);
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
                        $$->add_child($3);
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

typeSpec            : BOOL
                    {
                        $$ = Type::ExpressionType::Boolean;
                    }
                    | CHAR
                    {
                        $$ = Type::ExpressionType::Char;
                    }
                    | INT
                    {
                        $$ = Type::ExpressionType::Integer;
                    }
                    ;

funDecl             : typeSpec ID LPAREN parms RPAREN compoundStmt
                    {
                        $$ = new AST_node(Type::Declaration::Function);
                        $$->add_child($4);
                        $$->add_child($6);
                    }
                    | ID LPAREN parms RPAREN compoundStmt
                    {
                        $$ = new AST_node(Type::Declaration::Function);
                        $$->add_child($3);
                        $$->add_child($5);
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
                        $$->add_sibling($3);
                    }
                    | parmTypeList
                    {
                        $$ = $1;
					}
                    ;

parmTypeList        : typeSpec parmIdList
                    {
                        $$ = $2;
					}
                    ;

parmIdList          : parmIdList COM parmId
                    {
                        $$ = $1;
                        $$->add_sibling($3);
                    }
                    | parmId
                    {
                        $$ = $1;
					}
                    ;

parmId              : ID
                    {
                        $$ = new AST_node(Type::Declaration::Parameter);
					}
                    | ID LBRACK RBRACK
                    {
                        $$ = new AST_node(Type::Declaration::Parameter);
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
                        $$ = new AST_node(Type::Statement::Compound);
                        $$->add_child($2);
                        $$->add_child($3);
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
                            $$->add_sibling($2);
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
                            $$->add_sibling($2);
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

selectStmtOpen      : IF simpleExp THEN closedStmt
                    {
                        $$ = new AST_node(Type::Statement::Select);
                        $$->add_child($2);
                        $$->add_child($4);
                    }
                    | IF simpleExp THEN openStmt
                    {
                        $$ = new AST_node(Type::Statement::Select);
                        $$->add_child($2);
                        $$->add_child($4);
                    }
                    | IF simpleExp THEN closedStmt ELSE openStmt
                    {
                        $$ = new AST_node(Type::Statement::Select);
                        $$->add_child($2);
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
                        $$ = new AST_node(Type::Statement::While);
                        $$->add_child(new AST_node(Type::Expression::Id));
                        $$->add_child($4);
                    }
                    | FOR ID ASGN iterRange DO openStmt
                    {
                        $$ = new AST_node(Type::Statement::Iterative);
                        $$->add_child(new AST_node(Type::Expression::Id));
                        $$->add_child($4);
                        $$->add_child($6);
                    }
                    ;

iterStmtClosed      : WHILE simpleExp DO closedStmt
                    {
                        $$ = new AST_node(Type::Statement::While);
                        $$->add_child(new AST_node(Type::Expression::Id));
                        $$->add_child($4);
                    }
                    | FOR ID ASGN iterRange DO closedStmt
                    {
                        $$ = new AST_node(Type::Statement::Iterative);
                        $$->add_child(new AST_node(Type::Expression::Id));
                        $$->add_child($4);
                        $$->add_child($6);
                    }
                    ;

iterRange           : simpleExp TO simpleExp
                    {
                        $$ = new AST_node(Type::Expression::Range);
                        $$->add_child($1);
                        $$->add_child($3);
                    }
                    | simpleExp TO simpleExp BY simpleExp
                    {
                        $$ = new AST_node(Type::Expression::Range);
                        $$->add_child($1);
                        $$->add_child($3);
                        $$->add_child($5);
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
                        $$ = $2;
                        $$->add_child($1);
                        $$->add_child($3);
                    }
                    | mutable INC
                    {
                        $$ = new AST_node(Type::Statement::Assign);
                        $$ = $1;
                    }
                    | mutable DEC
                    {
                        $$ = new AST_node(Type::Statement::Assign);
                        $$ = $1;
                    }
                    | simpleExp
                    {
                        $$ = $1;
					}
                    ;

assignop            : ASGN
                    {
                        $$ = new AST_node(Type::Statement::Assign);
					}
                    | ADDASGN
                    {
                        $$ = new AST_node(Type::Statement::Assign);
					}
                    | SUBASGN
                    {
                        $$ = new AST_node(Type::Statement::Assign);
					}
                    | DIVASGN
                    {
                        $$ = new AST_node(Type::Statement::Assign);
					}
                    | MULASGN
                    {
                        $$ = new AST_node(Type::Statement::Assign);
					}
                    ;

simpleExp           : simpleExp OR andExp
                    {
                        $$ = new AST_node(Type::Expression::Or);
                        $$->add_child($1);
                        $$->add_child($3);
                    }
                    | andExp
                    {
                        $$ = $1;
					}
                    ;

andExp              : andExp AND unaryRelExp
                    {
                        $$ = new AST_node(Type::Expression::And);
                        $$->add_child($1);
                        $$->add_child($3);
                    }
                    | unaryRelExp
                    {
                        $$ = $1;
					}
                    ;

unaryRelExp         : NOT unaryRelExp
                    {
                        $$ = new AST_node(Type::Expression::UnaryOperator);
                        $$->add_child($2);
                    }
                    | relExp
                    {
                        $$ = $1;
					}
                    ;

relExp              : sumExp relop sumExp
                    {
                        $$ = $2;
                        $$->add_child($1);
                        $$->add_child($3);
                    }
                    | sumExp
                    {
                        $$ = $1;
					}
                    ;

relop               : LT
                    {
                        $$ = new AST_node(Type::Expression::RelationalOperator);
					}
                    | LEQ
                    {
                        $$ = new AST_node(Type::Expression::RelationalOperator);
					}
                    | GT
                    {
                        $$ = new AST_node(Type::Expression::RelationalOperator);
					}
                    | GEQ
                    {
                        $$ = new AST_node(Type::Expression::RelationalOperator);
					}
                    | EQ
                    {
                        $$ = new AST_node(Type::Expression::RelationalOperator);
					}
                    | NEQ
                    {
                        $$ = new AST_node(Type::Expression::RelationalOperator);
					}
                    ;

sumExp              : sumExp sumop mulExp
                    {
                        $$ = $2;
                        $$->add_child($1);
                        $$->add_child($3);
					}
                    | mulExp
                    {
                        $$ = $1;
					}
                    ;

sumop               : ADD
                    {
                        $$ = new AST_node(Type::Expression::Operator);
					}
                    | SUB
                    {
                        $$ = new AST_node(Type::Expression::Operator);
					}
                    ;

mulExp              : mulExp mulop unaryExp
                    {
                        $$ = $2;
                        $$->add_child($1);
                        $$->add_child($3);
					}
                    | unaryExp
                    {
                        $$ = $1;
					}
                    ;

mulop               : MUL
                    {
                        $$ = new AST_node(Type::Expression::Operator);
					}
                    | DIV
                    {
                        $$ = new AST_node(Type::Expression::Operator);
					}
                    | MOD
                    {
                        $$ = new AST_node(Type::Expression::Operator);
					}
                    ;

unaryExp            : unaryop unaryExp
                    {
                        $$ = $1;
                        $$->add_child($2);
					}
                    | factor
                    {
                        $$ = $1;
					}
                    ;

unaryop             : SUB
                    {
                        $$ = new AST_node(Type::Expression::UnaryOperator);
					}
                    | MUL
                    {
                        $$ = new AST_node(Type::Expression::UnaryOperator);
					}
                    | RAND
                    {
                        $$ = new AST_node(Type::Expression::UnaryOperator);
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
                        $$ = new AST_node(Type::Expression::Id);
					}
                    | ID LBRACK exp RBRACK
                    {
                        $$ = new AST_node(Type::Expression::Operator);
                        $$->add_child(new AST_node(Type::Expression::Id));
                        $$->add_child($3);
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
                        $$ = new AST_node(Type::Statement::Call);
                        $$->add_child($3);
                    }
                    | ID LPAREN RPAREN
                    {
                        $$ = new AST_node(Type::Statement::Call);
                    }
                    ;

argList             : argList COM exp
                    {
                        $$ = $1;
                        $$->add_sibling($3);
                    }
                    | exp
                    {
                        $$ = $1;
                    }
                    ;

constant            : NUMCONST
                    {
                        $$ = new AST_node(Type::Expression::Constant);
                    }
                    | CHARCONST
                    {
                        $$ = new AST_node(Type::Expression::Constant);
                    }
                    | STRINGCONST
                    {
                        $$ = new AST_node(Type::Expression::Constant);
                    }
                    | BOOLCONST
                    {
                        $$ = new AST_node(Type::Expression::Constant);
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
