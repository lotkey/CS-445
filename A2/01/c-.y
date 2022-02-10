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

%token <node> ID NUMCONST CHARCONST STRINGCONST BOOLCONST
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
                        std::cout << "program:declList\n";
                        $$ = $1;
                        tree_root = $$;
                    }
                    ;

declList            : declList decl
                    {
                        std::cout << "declList:declList decl\n";
                        if ($1 != nullptr) {
                            $$ = $1;
                            $$->add_sibling($2);
                        } else {
                            $$ = $2;
                        }
                    }
                    | decl
                    {
                        std::cout << "declList:decl\n";
                        $$ = $1;
                    }
                    ;

decl                : varDecl
                    {
						std::cout << "decl:varDecl\n"; 
						$$ = $1;
					}
                    | funDecl
                    {
						std::cout << "decl:funDecl\n"; 
						$$ = $1;
					}
                    ;

varDecl             : typeSpec varDeclList SEMI
                    {
						std::cout << "varDecl:typeSpec varDeclList SEMI\n"; 
						$$ = $2;
					}
                    ;

scopedVarDecl       : STATIC typeSpec varDeclList SEMI
                    {
						std::cout << "scopedVarDecl:STATIC typeSpec varDeclList SEMI\n"; 
						$$ = $3;
					}
                    | typeSpec varDeclList SEMI
                    {
						std::cout << "scopedVarDecl:typeSpec varDeclList SEMI\n"; 
						$$ = $2;
					}
                    ;

varDeclList         : varDeclList COM varDeclInit
                    {
						std::cout << "varDeclList:varDeclList COM varDeclInit\n";
                        if ($1 != nullptr) {
                            $$ = $1;
                            $$->add_sibling($3);
                        } else {
                            $$ = $3;
                        }
                    }
                    | varDeclInit
                    {
						std::cout << "varDeclList:varDeclInit\n"; 
						$$ = $1;
					}
                    ;

varDeclInit         : varDeclId
                    {
						std::cout << "varDeclInit:varDeclId\n"; 
						$$ = $1;
					}
                    | varDeclId COL simpleExp
                    {
						std::cout << "varDeclInit:varDeclId COL simpleExp\n";
                        if ($1 != nullptr) {
                            $$ = $1;
                            $$->add_sibling($3);
                        }
                    }
                    ;
                
varDeclId           : ID
                    {
						std::cout << "varDeclId:ID\n";
                        $$ = new AST_node(Type::Declaration::Variable);
                    }
                    | ID LBRACK NUMCONST RBRACK
                    {
						std::cout << "varDeclId:ID LBRACK NUMCONST RBRACK\n";
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
						std::cout << "typeSpec ID LPAREN parms RPAREN compoundStmt\n";
                        $$ = new AST_node(Type::Declaration::Function);
                        $$->add_child($2);
                        if ($4 != nullptr) {
                            $$->add_child($4);
                        }
                        $$->add_child($6);
                    }
                    | ID LPAREN parms RPAREN compoundStmt
                    {
						std::cout << "ID LPAREN parms RPAREN compoundStmt\n";
                        $$ = new AST_node(Type::Declaration::Function);
                        $$->add_child($1);
                        if ($3 != nullptr) {
                            $$->add_child($3);
                        }
                        $$->add_child($5);
                    }
                    ;

parms               :
                    {
                        std::cout << "parms:\n";
						$$ = nullptr;
					}
                    | parmList
                    {
						std::cout << "parms:parmList\n";
						$$ = $1;
					}
                    ;

parmList            : parmList SEMI parmTypeList
                    {
						std::cout << "parmList:parmList SEMI parmTypeList\n";
                        if ($1 != nullptr) {
                            $$ = $1;
                            $$->add_sibling($3);
                        } else {
                            $$ = $3;
                        }
                    }
                    | parmTypeList
                    {
						std::cout << "parmList:parmTypeList\n"; 
						$$ = $1;
					}
                    ;

parmTypeList        : typeSpec parmIdList
                    {
						std::cout << "parmTypeList:typeSpec parmIdList\n"; 
						$$ = $2;
					}
                    ;

parmIdList          : parmIdList COM parmId
                    {
						std::cout << "parmIdList:parmIdList COM parmId\n";
                        if ($1 != nullptr) {
                            $$ = $1;
                            $$->add_sibling($3);
                        } else {
                            $$ = $3;
                        }
                    }
                    | parmId
                    {
						std::cout << "parmIdList:parmId\n"; 
						$$ = $1;
					}
                    ;

parmId              : ID
                    {
						std::cout << "parmId:ID\n"; 
						$$ = new AST_node(Type::Expression::Id);
					}
                    | ID LBRACK RBRACK
                    {
						std::cout << "parmId:ID LBRACK RBRACK\n"; 
						$$ = new AST_node(Type::Expression::Id);
					}
                    ;

stmt                : closedStmt
                    {
						std::cout << "stmt:closedStmt\n"; 
						$$ = $1;
					}
                    | openStmt
                    {
						std::cout << "stmt:openStmt\n"; 
						$$ = $1;
					}
                    ;

expStmt             : exp SEMI
                    {
						std::cout << "expStmt:exp SEMI\n"; 
						$$ = $1;
					}
                    | SEMI
                    {
						std::cout << "expStmt:SEMI\n"; 
						$$ = nullptr;
					}
                    ;

compoundStmt        : BGN localDecls stmtList END
                    {
						std::cout << "compoundStmt:BGN localDecls stmtList END\n";
                        $$ = new AST_node(Type::Statement::Compound);
                        $$->add_child($2);
                        $$->add_child($3);
                    }
                    ;

localDecls          :
                    {
                        std::cout << "localDecls:\n";
						$$ = nullptr;
					}
                    | localDecls scopedVarDecl
                    {
						std::cout << "localDecls:localDecls scopedVarDecl\n";
                        if ($1 != nullptr) {
                            $$ = $1;
                            $$->add_sibling($2);
                        } else {
                            $$ = $2;
                        }
                    }
                    ;

stmtList            :
                    { 
                        std::cout << "stmtList:\n";
						$$ = nullptr;
					}
                    | stmtList stmt
                    {
						std::cout << "stmtList:stmtList stmt\n";
                        if ($$ != nullptr) {
                            $$ = $1;
                            $$->add_sibling($2);
                        } else {
                            $$ = $2;
                        }
                    }
                    ;

closedStmt          : selectStmtClosed
                    {
						std::cout << "closedStmt:selectStmtClosed\n"; 
						$$ = $1;
					}
                    | iterStmtClosed
                    {
						std::cout << "closedStmt:iterStmtClosed\n"; 
						$$ = $1;
					}
                    | expStmt
                    {
						std::cout << "closedStmt:expStmt\n"; 
						$$ = $1;
					}
                    | compoundStmt
                    {
						std::cout << "closedStmt:compoundStmt\n"; 
						$$ = $1;
					}
                    | returnStmt 
                    {
						std::cout << "closedStmt:returnStmt \n"; 
						$$ = $1;
					}
                    | breakStmt
                    {
						std::cout << "closedStmt:breakStmt\n"; 
						$$ = $1;
					}
                    ;

openStmt            : selectStmtOpen
                    {
						std::cout << "openStmt:selectStmtOpen\n"; 
						$$ = $1;
					}
                    | iterStmtOpen
                    {
						std::cout << "openStmt:iterStmtOpen\n"; 
						$$ = $1;
					}
                    ;

selectStmtOpen      : IF simpleExp THEN closedStmt
                    {
						std::cout << "selectStmtOpen:IF simpleExp THEN closedStmt\n";
                        $$ = new AST_node(Type::Statement::Select);
                        $$->add_child($2);
                        $$->add_child($4);
                    }
                    | IF simpleExp THEN openStmt
                    {
						std::cout << "selectStmtOpen:IF simpleExp THEN openStmt\n";
                        $$ = new AST_node(Type::Statement::Select);
                        $$->add_child($2);
                        $$->add_child($4);
                    }
                    | IF simpleExp THEN closedStmt ELSE openStmt
                    {
						std::cout << "IF simpleExp THEN closedStmt ELSE openStmt\n";
                        $$ = new AST_node(Type::Statement::Select);
                        $$->add_child($2);
                        $$->add_child($4);
                        $$->add_child($6);
                    }
                    ;

selectStmtClosed    : IF simpleExp THEN closedStmt ELSE closedStmt
                    {
						std::cout << "IF simpleExp THEN closedStmt ELSE closedStmt\n";
                        $$ = new AST_node(Type::Statement::Select);
                        $$->add_child($2);
                        $$->add_child($4);
                        $$->add_child($6);
                    }
                    ;

iterStmtOpen        : WHILE simpleExp DO openStmt
                    {
						std::cout << "WHILE simpleExp DO openStmt\n";
                        $$ = new AST_node(Type::Statement::Iterative);
                        $$->add_child($2);
                        $$->add_child($4);
                    }
                    | FOR ID ASGN iterRange DO openStmt
                    {
						std::cout << "FOR ID ASGN iterRange DO openStmt\n";
                        $$ = new AST_node(Type::Statement::Iterative);
                        $$->add_child($4);
                        $$->add_child($6);
                    }
                    ;

iterStmtClosed      : WHILE simpleExp DO closedStmt
                    {
						std::cout << "WHILE simpleExp DO closedStmt\n";
                        $$ = new AST_node(Type::Statement::Iterative);
                        $$->add_child($2);
                        $$->add_child($4);
                    }
                    | FOR ID ASGN iterRange DO closedStmt
                    {
						std::cout << "FOR ID ASGN iterRange DO closedStmt\n";
                        $$ = new AST_node(Type::Statement::Iterative);
                        $$->add_child($4);
                        $$->add_child($6);
                    }
                    ;

iterRange           : simpleExp TO simpleExp
                    {
						std::cout << "simpleExp TO simpleExp\n";
                        $$ = new AST_node(Type::Expression::Range);
                        $$->add_child($1);
                        $$->add_child($3);
                    }
                    | simpleExp TO simpleExp BY simpleExp
                    {
						std::cout << "simpleExp TO simpleExp\n";
                        $$ = new AST_node(Type::Expression::Range);
                        $$->add_child($1);
                        $$->add_child($3);
                        $$->add_child($5);
                    }
                    ;

returnStmt          : RETURN SEMI
                    {
						std::cout << "RETURN SEMI\n";
                        $$ = new AST_node(Type::Statement::Return);
                    }
                    | RETURN exp SEMI
                    {
						std::cout << "RETURN exp SEMI\n";
                        $$ = new AST_node(Type::Statement::Return);
                        $$->add_child($2);
                    }
                    ;

breakStmt           : BREAK SEMI
                    {
						std::cout << "BREAK SEMI\n";
                        $$ = new AST_node(Type::Statement::Break);
                    }
                    ;

exp                 : mutable assignop exp
                    {
						std::cout << "mutable assignop exp\n";
                        $$ = new AST_node(Type::Statement::Assign);
                        $$->add_child($1);
                        $$->add_child($2);
                        $$->add_child($3);
                    }
                    | mutable INC
                    {
						std::cout << "mutable INC\n";
                        $$ = new AST_node(Type::Statement::Assign);
                        $$->add_child($1);
                    }
                    | mutable DEC
                    {
						std::cout << "mutable DEC\n";
                        $$ = new AST_node(Type::Statement::Assign);
                        $$->add_child($1); 
                    }
                    | simpleExp
                    {
						std::cout << "simpleExp\n"; 
						$$ = $1;
					}
                    ;

assignop            : ASGN
                    {
						std::cout << "ASGN\n"; 
						$$ = new AST_node(Type::Statement::Assign);
					}
                    | ADDASGN
                    {
						std::cout << "ADDASGN\n"; 
						$$ = new AST_node(Type::Statement::Assign);
					}
                    | SUBASGN
                    {
						std::cout << "SUBASGN\n"; 
						$$ = new AST_node(Type::Statement::Assign);
					}
                    | DIVASGN
                    {
						std::cout << "DIVASGN\n"; 
						$$ = new AST_node(Type::Statement::Assign);
					}
                    | MULASGN
                    {
						std::cout << "MULASGN\n"; 
						$$ = new AST_node(Type::Statement::Assign);
					}
                    ;

simpleExp           : simpleExp OR andExp
                    {
						std::cout << "simpleExp OR andExp\n";
                        $$ = new AST_node(Type::Expression::Simple);
                        $$->add_child($1);
                        $$->add_child($3);           
                    }
                    | andExp
                    {
						std::cout << "andExp\n"; 
						$$ = $1;
					}
                    ;

andExp              : andExp AND unaryRelExp
                    {
						std::cout << "andExp AND unaryRelExp\n";
                        $$ = new AST_node(Type::Expression::And);
                        $$->add_child($1);
                        $$->add_child($3);
                    }
                    | unaryRelExp
                    {
						std::cout << "unaryRelExp\n"; 
						$$ = $1;
					}
                    ;

unaryRelExp         : NOT unaryRelExp
                    {
						std::cout << "NOT unaryRelExp\n";
                        $$ = new AST_node(Type::Expression::UnaryRelation);
                        $$->add_child($2);
                    }
                    | relExp
                    {
						std::cout << "relExp\n"; 
						$$ = $1;
					}
                    ;

relExp              : sumExp relop sumExp
                    {
						std::cout << "sumExp relop sumExp\n";
                        $$ = new AST_node(Type::Expression::Operator);
                        $$->add_child($1);
                        $$->add_child($3);
                    }
                    | sumExp
                    {
						std::cout << "sumExp\n"; 
						$$ = $1;
					}
                    ;

relop               : LT
                    {
						std::cout << "LT\n"; 
                        std::cout << "relop:lt\n";
						$$ = nullptr;
					}
                    | LEQ
                    {
						std::cout << "LEQ\n"; 
                        std::cout << "relop:leq\n";
						$$ = nullptr;
					}
                    | GT
                    {
						std::cout << "GT\n"; 
                        std::cout << "relop:gt\n";
						$$ = nullptr;
					}
                    | GEQ
                    {
						std::cout << "GEQ\n"; 
                        std::cout << "relop:geq\n";
						$$ = nullptr;
					}
                    | EQ
                    {
						std::cout << "EQ\n"; 
                        std::cout << "relop:eq\n";
						$$ = nullptr;
					}
                    | NEQ
                    {
						std::cout << "NEQ\n"; 
                        std::cout << "relop:neq\n";
						$$ = nullptr;
					}
                    ;

sumExp              : sumExp sumop mulExp
                    {
                        std::cout << "sumexp:sumexp sumop mulexp\n";
						$$ = new AST_node(Type::Expression::Operator);
                        $$->add_child($1);
                        $$->add_child($3);
					}
                    | mulExp
                    {
                        std::cout << "sumexp:mulexp\n";
                        $$ = $1;
					}
                    ;

sumop               : ADD
                    {
						std::cout << "ADD\n"; 
                        std::cout << "sumop:add\n";
						$$ = nullptr;
					}
                    | SUB
                    {
						std::cout << "SUB\n"; 
                        std::cout << "sumop:sub\n";
						$$ = nullptr;
					}
                    ;

mulExp              : mulExp mulop unaryExp
                    {
                        std::cout << "mulop:mulexp mulop unaryexp\n";
						$$ = new AST_node(Type::Expression::Operator);
                        $$->add_child($1);
                        $$->add_child($3);
					}
                    | unaryExp
                    {
                        std::cout << "mulop:mulexp\n";
						$$ = $1;
					}
                    ;

mulop               : MUL
                    {
						std::cout << "MUL\n"; 
                        std::cout << "mulop:mul\n";
						$$ = nullptr;
					}
                    | DIV
                    {
						std::cout << "DIV\n"; 
                        std::cout << "mulop:div\n";
						$$ = nullptr;
					}
                    | MOD
                    {
						std::cout << "MOD\n"; 
                        std::cout << "mulop:mod\n";
						$$ = nullptr;
					}
                    ;

unaryExp            : unaryop unaryExp
                    {
						std::cout << "unaryop unaryExp\n"; 
                        std::cout << "unaryexp:unaryop unaryexp\n";
						$$ = new AST_node(Type::Expression::Operator);
                        $$->add_child($2);
					}
                    | factor
                    {
						std::cout << "factor\n"; 
                        std::cout << "unaryexp:factor\n";
						$$ = $1;
					}
                    ;

unaryop             : SUB
                    {
						std::cout << "SUB\n"; 
                        std::cout << "unaryop:sub\n";
						$$ = nullptr;
					}
                    | MUL
                    {
						std::cout << "MUL\n"; 
                        std::cout << "unaryop:mul\n";
						$$ = nullptr;
					}
                    | RAND
                    {
						std::cout << "RAND\n"; 
                        std::cout << "unaryop:rand\n";
						$$ = nullptr;
					}
                    ;

factor              : mutable
                    {
						std::cout << "mutable\n"; 
                        std::cout << "factor:mutable\n";
						$$ = $1;
					}
                    | immutable
                    {
						std::cout << "immutable\n"; 
                        std::cout << "factor:immutable\n";
						$$ = $1;
					}
                    ;

mutable             : ID
                    {
						std::cout << "ID\n"; 
                        std::cout << "immutable:id\n";
						$$ = new AST_node(Type::Expression::Id);
					}
                    | ID LBRACK exp RBRACK
                    {
						std::cout << "ID LBRACK exp RBRACK\n";
                        std::cout << "immutable:lparen exp rparen\n";
                        $$ = new AST_node(Type::Expression::Operator);
                        $$->add_sibling($3);
                    }
                    ;

immutable           : LPAREN exp RPAREN
                    {
						std::cout << "LPAREN exp RPAREN\n";
                        std::cout << "immutable:lparen exp rparen\n";
                        $$ = $2;
                    }
                    | call
                    {
						std::cout << "call\n";
                        std::cout << "immutable:call\n";
                        $$ = $1;
                    }
                    | constant
                    {
						std::cout << "constant\n";
                        std::cout << "immutable:constant\n";
                        $$ = $1;
                    }
                    ;

call                : ID LPAREN argList RPAREN
                    {
                        std::cout << "call:id lparen arglist rparen\n";
                        $$ = new AST_node(Type::Statement::Call);
                        $$->add_child(new AST_node(Type::Expression::Id));
                        $$->add_child($3);
                    }
                    | ID LPAREN RPAREN
                    {
						std::cout << "ID LPAREN RPAREN\n";
                        std::cout << "call:id lparen rparen\n";
                        $$ = new AST_node(Type::Statement::Call);
                        $$->add_child(new AST_node(Type::Expression::Id));
                    }
                    ;

argList             : argList COM exp
                    {
                        std::cout << "argList:arglist com exp\n";
                        if ($1 != nullptr) {
                            $$ = $1;
                            $$->add_sibling($3);
                        } else {
                            $$ = $3;
                        }
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
