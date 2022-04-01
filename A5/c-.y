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

static const std::map<std::string, std::string> token_to_string = {
    {"ADDASGN", "\"+=\""},              {"AND", "\"and\""},
    {"ASGN", "\"<-\""},                 {"BGN", "\"begin\""},
    {"BOOL", "\"bool\""},               {"BOOLCONST", "Boolean constant"},
    {"BREAK", "\"break\""},             {"BY", "\"by\""},
    {"CHAR", "\"char\""},               {"CHARCONST", "character constant"},
    {"DASH", "-"},                      {"DEC", "\"--\""},
    {"DIVASGN", "\"/=\""},              {"DO", "\"do\""},
    {"ELSE", "\"else\""},               {"END", "\"end\""},
    {"FOR", "\"for\""},                 {"GEQ", "\">=\""},
    {"ID", "identifier"},               {"IF", "\"if\""},
    {"INC", "\"++\""},                  {"INT", "\"int\""},
    {"LEQ", "\"<=\""},                  {"MULASGN", "\"*=\""},
    {"NEQ", "\"!=\""},                  {"NOT", "\"not\""},
    {"NUMCONST", "numeric constant"},   {"OR", "\"or\""},
    {"STATIC", "\"static\""},           {"STRINGCONST", "string constant"},
    {"SUBASGN", "\"-=\""},              {"THEN", "\"then\""},
    {"TO", "\"to\""},                   {"WHILE", "\"while\""},
    {"RETURN", "\"return\""},           {"$end", "end of input"},

    {"LPAREN", "'('"},                  {"RPAREN", "')'"}, 
    {"LBRACK", "'['"},                  {"RBRACK", "']'"}, 
    {"RAND", "'?'"},                    {"ASTERISK", "'*'"}, 
    {"DIV", "'/'"},                     {"MOD", "'%'"}, 
    {"ADD", "'+'"},                     {"DASH", "'-'"}, 
    {"SEMI", "';'"},                    {"LT", "'<'"}, 
    {"GT", "'>'"},                      {"EQ", "'='"}, 
    {"COL", "':'"},                     {"COM", "','"}
};

#define YYERROR_VERBOSE
void yyerror(const char *msg)
{
    auto words = strutil::split(msg);
    
    for (int i = 3; i < words.size(); i += 2) {
        if (!words[i].empty() && words[i][words[i].length() - 1] == ',') {
            words[i] = words[i].substr(0, words[i].length() - 1);
        }

        if (token_to_string.find(words[i]) != token_to_string.end()) {
            words[i] = token_to_string.at(words[i]);
        }
    }
    
    auto unexpected = words[3];
    std::string error_msg = strutil::format("ERROR(%d): Syntax error, unexpected %s",
                line, unexpected.c_str());

    if (words.size() > 5) {
        error_msg += ",";
        for (int i = 4; i < words.size(); i++) {
            error_msg += strutil::format(" %s", words[i].c_str());
        }
    }
    error_msg += ".";

    std::cout << error_msg << std::endl;
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
                    ;

declList            : declList decl {
                        $$ = $1;
                        if ($$) { $$->addSibling($2); }
                        yyerrok;
                    }
                    | decl { $$ = $1; yyerrok; }
                    ;

decl                : varDecl { $$ = $1; yyerrok; }
                    | funDecl { $$ = $1; yyerrok; }
                    | error { $$ = nullptr; }
                    ;

varDecl             : typeSpec varDeclList SEMI {
                        auto *var = $2->cast<AST::Decl::Var *>();
                        if (var) { var->setType($1); }
                        $$ = var;
                        yyerrok;
					}
                    | error varDeclList SEMI { $$ = nullptr; yyerrok; }
                    | typeSpec error SEMI { $$ = nullptr; yyerrok; }
                    ;

scopedVarDecl       : STATIC typeSpec varDeclList SEMI {
                        auto *var = $3->cast<AST::Decl::Var *>();
                        if (var) {
                            var->setType($2);
                            var->setIsStatic(true);
                        }
                        $$ = var;
                        yyerrok;
					}
                    | typeSpec varDeclList SEMI {
                        auto *var = $2->cast<AST::Decl::Var *>();
                        if (var) { var->setType($1); }
                        $$ = var;
                        yyerrok;
					}
                    ;

varDeclList         : varDeclList COM varDeclInit {
                        $$ = $1;
                        if ($$) { $$->addSibling($3); }
                        yyerrok;
                    }
                    | varDeclInit { $$ = $1; }
                    | varDeclList COM error { $$ = nullptr; }
                    | error { $$ = nullptr; }
                    ;

varDeclInit         : varDeclId { $$ = $1; yyerrok; }
                    | varDeclId COL simpleExp {
                        $$ = $1;
                        if ($$) { $$->addChild($3); }
                        yyerrok;
                    }
                    | varDeclId COL error {
                        $$ = nullptr;
                        yyerrok;
                    }
                    | error COL simpleExp { $$ = nullptr; yyerrok; }
                    ;
                
varDeclId           : ID {
                        if ($1) {
                            $$ = new AST::Decl::Var($1->linenum, $1->tokenstr, false);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | ID LBRACK NUMCONST RBRACK {
                        if ($1) {
                            $$ = new AST::Decl::Var($1->linenum, $1->tokenstr, true);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | error RBRACK { $$ = nullptr; }
                    | ID LBRACK error { $$ = nullptr; }
                    ;

typeSpec            : BOOL { $$ = AST::Type::Bool; yyerrok; }
                    | CHAR { $$ = AST::Type::Char; yyerrok; }
                    | INT { $$ = AST::Type::Int; yyerrok; }
                    ;

funDecl             : typeSpec ID LPAREN parms RPAREN compoundStmt {
                        if ($2) {
                            $$ = new AST::Decl::Func($2->linenum, $1, $2->tokenstr, $4, $6);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | ID LPAREN parms RPAREN compoundStmt {
                        if ($1) {
                            $$ = new AST::Decl::Func($1->linenum, $1->tokenstr, $3, $5);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | typeSpec error { $$ = nullptr; }
                    | typeSpec ID LPAREN error { $$ = nullptr; }
                    | ID LPAREN error { $$ = nullptr; }
                    | ID LPAREN parms RPAREN error { $$ = nullptr; }
                    ;

parms               : { $$ = nullptr; yyerrok; }
                    | parmList { $$ = $1; yyerrok; }
                    ;

parmList            : parmList SEMI parmTypeList {
                        $$ = $1;
                        if ($$) { $$->addSibling($3); }
                        yyerrok;
                    }
                    | parmTypeList { $$ = $1; yyerrok; }
                    | parmList SEMI error { $$ = nullptr; }
                    | error { $$ = nullptr; }
                    ;

parmTypeList        : typeSpec parmIdList {
                        auto *parms = $2->cast<AST::Decl::Parm *>();
                        if (parms) { parms->setType($1); }
                        $$ = parms;
                        yyerrok;
					}
                    | typeSpec error { $$ = nullptr; }
                    ;

parmIdList          : parmIdList COM parmId {
                        $$ = $1;
                        if ($$) { $$->addSibling($3); }
                        yyerrok;
                    }
                    | parmId { $$ = $1; yyerrok; }
                    | parmIdList COM error { $$ = nullptr; }
                    ;

parmId              : ID {
                        if ($1) {
                            $$ = new AST::Decl::Parm($1->linenum, $1->tokenstr, false);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    | ID LBRACK RBRACK {
                        if ($1) {
                            $$ = new AST::Decl::Parm($1->linenum, $1->tokenstr, true);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    ;

stmt                : closedStmt { $$ = $1; yyerrok; }
                    | openStmt { $$ = $1; yyerrok; }
                    ;

expStmt             : exp SEMI { $$ = $1; yyerrok; }
                    | SEMI { $$ = nullptr; yyerrok; }
                    | error SEMI { $$ = nullptr; yyerrok; }
                    ;

compoundStmt        : BGN localDecls stmtList END {
                        if ($1) {
                            $$ = new AST::Stmt::Compound($1->linenum, $2, $3);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    ;

localDecls          : { $$ = nullptr; yyerrok; }
                    | localDecls scopedVarDecl {
                        if ($1) {
                            $$ = $1;
                            $$->addSibling($2);
                        } else {
                            $$ = $2;
                        }
                        yyerrok;
                    }
                    ;

stmtList            : { $$ = nullptr; yyerrok; }
                    | stmtList stmt {
                        if ($1) {
                            $$ = $1;
                            $$->addSibling($2);
                        } else {
                            $$ = $2;
                        }
                        yyerrok;
                    }
                    ;

closedStmt          : selectStmtClosed { $$ = $1; yyerrok; }
                    | iterStmtClosed { $$ = $1; yyerrok; }
                    | expStmt { $$ = $1; yyerrok; }
                    | compoundStmt { $$ = $1; yyerrok; }
                    | returnStmt  { $$ = $1; yyerrok; }
                    | breakStmt { $$ = $1; yyerrok; }
                    ;

openStmt            : selectStmtOpen { $$ = $1; yyerrok; }
                    | iterStmtOpen { $$ = $1; yyerrok; }
                    ;

selectStmtOpen      : IF simpleExp THEN stmt {
                        if ($1) {
                            $$ = new AST::Stmt::Select($1->linenum, $2, $4);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | IF simpleExp THEN closedStmt ELSE openStmt {
                        if ($1) {
                            $$ = new AST::Stmt::Select($1->linenum, $2, $4, $6);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | IF error THEN stmt { $$ = nullptr; yyerrok; } 
                    | IF error THEN closedStmt ELSE openStmt { $$ = nullptr; yyerrok; }
                    ;

selectStmtClosed    : IF simpleExp THEN closedStmt ELSE closedStmt {
                        if ($1) {
                            $$ = new AST::Stmt::Select($1->linenum, $2, $4, $6);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | IF error { $$ = nullptr; }
                    | IF error ELSE closedStmt { $$ = nullptr; yyerrok; }
                    | IF error THEN closedStmt ELSE closedStmt { $$ = nullptr; yyerrok; } 
                    ;

iterStmtOpen        : WHILE simpleExp DO openStmt {
                        if ($1) {
                            $$ = new AST::Stmt::While($1->linenum, $2, $4);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | FOR ID ASGN iterRange DO openStmt {
                        if ($1 && $2) {
                            auto *iterator = new AST::Decl::Var($1->linenum, $2->tokenstr, false);
                            iterator->setType(AST::Type::Int);
                            $$ = new AST::Stmt::For($1->linenum, iterator, $4, $6);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | FOR ID ASGN error DO closedStmt { $$ = nullptr; yyerrok; }
                    | FOR error { $$ = nullptr; }
                    | WHILE error DO closedStmt { $$ = nullptr; yyerrok; }
                    | WHILE error { $$ = nullptr; }
                    ;

iterStmtClosed      : WHILE simpleExp DO closedStmt {
                        if ($1) {
                            $$ = new AST::Stmt::While($1->linenum, $2, $4);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | FOR ID ASGN iterRange DO closedStmt {
                        if ($1 && $2) {
                            auto *iterator = new AST::Decl::Var($1->linenum, $2->tokenstr, false);
                            iterator->setType(AST::Type::Int);
                            $$ = new AST::Stmt::For($1->linenum, iterator, $4, $6);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | WHILE error DO closedStmt { $$ = nullptr; yyerrok; }
                    | WHILE error { $$ = nullptr; yyerrok; }
                    | FOR ID ASGN error DO closedStmt { $$ = nullptr; yyerrok; }
                    | FOR error { $$ = nullptr; yyerrok; }
                    ;

iterRange           : simpleExp TO simpleExp {
                        if ($1) {
                            $$ = new AST::Stmt::Range($1->lineNumber(), $1, $3);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | simpleExp TO simpleExp BY simpleExp {
                        if ($1) {
                            $$ = new AST::Stmt::Range($1->lineNumber(), $1, $3, $5);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | simpleExp TO error { $$ = nullptr; }
                    | error BY error { $$ = nullptr; yyerrok; }
                    | simpleExp TO simpleExp BY error { $$ = nullptr; }
                    ;

returnStmt          : RETURN SEMI {
                        if ($1) {
                            $$ = new AST::Stmt::Return($1->linenum, nullptr);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | RETURN exp SEMI {
                        if ($1) {
                            $$ = new AST::Stmt::Return($1->linenum, $2);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | RETURN error SEMI { $$ = nullptr; yyerrok; }
                    ;

breakStmt           : BREAK SEMI {
                        if ($1) {
                            $$ = new AST::Stmt::Break($1->linenum);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    ;

exp                 : mutable assignop exp {
                        auto *op = $2->cast<AST::Exp::Op::Asgn *>();
                        if (op) { op->addChildren($1, $3); }
                        $$ = op;
                        yyerrok;
                    }
                    | mutable INC {
                        if ($1) {
                            $$ = new AST::Exp::Op::UnaryAsgn($1->lineNumber(), AST::UnaryAsgnType::Inc, $1);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | mutable DEC {
                        if ($1) {
                            $$ = new AST::Exp::Op::UnaryAsgn($1->lineNumber(), AST::UnaryAsgnType::Dec, $1);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | simpleExp {
                        $$ = $1;
                        yyerrok;
					}
                    | error assignop exp { $$ = nullptr; yyerrok; }
                    | mutable assignop error { $$ = nullptr; }
                    | error INC { $$ = nullptr; yyerrok; }
                    | error DEC { $$ = nullptr; yyerrok; }
                    ;

assignop            : ASGN {
                        if ($1) {
                            $$ = new AST::Exp::Op::Asgn($1->linenum, AST::AsgnType::Asgn);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    | ADDASGN {
                        if ($1) {
                            $$ = new AST::Exp::Op::Asgn($1->linenum, AST::AsgnType::AddAsgn);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    | SUBASGN {
                        if ($1) {
                            $$ = new AST::Exp::Op::Asgn($1->linenum, AST::AsgnType::SubAsgn);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    | DIVASGN {
                        if ($1) {
                            $$ = new AST::Exp::Op::Asgn($1->linenum, AST::AsgnType::DivAsgn);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    | MULASGN {
                        if ($1) {
                            $$ = new AST::Exp::Op::Asgn($1->linenum, AST::AsgnType::MulAsgn);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    ;

simpleExp           : simpleExp OR andExp {
                        if ($1) {
                            auto *boolop = new AST::Exp::Op::Bool($1->lineNumber(), AST::BoolOpType::Or);
                            boolop->addChildren($1, $3);
                            $$ = boolop;
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | andExp { $$ = $1; yyerrok; }
                    | simpleExp OR error { $$ = nullptr; }
                    ;

andExp              : andExp AND unaryRelExp {
                        if ($1) {
                            auto *boolop = new AST::Exp::Op::Bool($1->lineNumber(), AST::BoolOpType::And);
                            boolop->addChildren($1, $3);
                            $$ = boolop;
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | unaryRelExp { $$ = $1; yyerrok; }
                    | andExp AND error { $$ = nullptr; }
                    ;

unaryRelExp         : NOT unaryRelExp {
                        $$ = new AST::Exp::Op::Unary($1->linenum, AST::UnaryOpType::Not, $2);
                        yyerrok;
                    }
                    | relExp { $$ = $1; yyerrok; }
                    | NOT error { $$ = nullptr; }
                    ;

relExp              : sumExp relop sumExp {
                        auto *op = $2->cast<AST::Exp::Op::Binary *>();
                        if (op) { op->addChildren($1, $3); }
                        $$ = op;
                        yyerrok;
                    }
                    | sumExp { $$ = $1; yyerrok; }
                    ;

relop               : LT {
                        if ($1) {
                            $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::LT);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    | LEQ {
                        if ($1) {
                            $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::LEQ);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    | GT {
                        if ($1) {
                            $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::GT);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    | GEQ {
                        if ($1) {
                            $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::GEQ);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    | EQ {
                        if ($1) {
                            $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::EQ);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    | NEQ {
                        if ($1) {
                            $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::NEQ);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    ;

sumExp              : sumExp sumop mulExp {
                        auto *op = $2->cast<AST::Exp::Op::Binary *>();
                        if (op) { op->addChildren($1, $3); }
                        $$ = op;
                        yyerrok;
					}
                    | mulExp { $$ = $1; yyerrok; }
                    | sumExp sumop error { $$ = nullptr; }
                    ;

sumop               : ADD {
                        if ($1) {
                            $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Add);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    | DASH {
                        if ($1) {
                            $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Subtract);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    ;

mulExp              : mulExp mulop unaryExp {
                        auto *op = $2->cast<AST::Exp::Op::Binary *>();
                        if (op) { op->addChildren($1, $3); }
                        $$ = op;
                        yyerrok;
					}
                    | unaryExp { $$ = $1; yyerrok; }
                    | mulExp mulop error { $$ = nullptr; }
                    ;

mulop               : ASTERISK {
                        if ($1) {
                            $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Mul);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    | DIV {
                        if ($1) {
                            $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Div);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    | MOD {
                        if ($1) {
                            $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Mod);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    ;

unaryExp            : unaryop unaryExp {
                        auto *op = $1->cast<AST::Exp::Op::Unary *>();
                        if (op) { op->addExp($2); }
                        $$ = op;
                        yyerrok;
					}
                    | factor { $$ = $1; yyerrok; }
                    | unaryop error { $$ = nullptr; }
                    ;

unaryop             : DASH {
                        if ($1) {
                            $$ = new AST::Exp::Op::Unary($1->linenum, AST::UnaryOpType::Chsign);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    | ASTERISK {
                        if ($1) {
                            $$ = new AST::Exp::Op::Unary($1->linenum, AST::UnaryOpType::Sizeof);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    | RAND {
                        if ($1) {
                            $$ = new AST::Exp::Op::Unary($1->linenum, AST::UnaryOpType::Random);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    ;

factor              : mutable { $$ = $1; yyerrok; }
                    | immutable { $$ = $1; yyerrok; }
                    ;

mutable             : ID {
                        if ($1) {
                            $$ = new AST::Exp::Id($1->linenum, $1->tokenstr);
                        } else { $$ = nullptr; }
                        yyerrok;
					}
                    | ID LBRACK exp RBRACK {
                        if ($1) {
                            $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Index, new AST::Exp::Id($1->linenum, $1->tokenstr), $3);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    ;

immutable           : LPAREN exp RPAREN { $$ = $2; yyerrok; }
                    | call { $$ = $1; yyerrok; }
                    | constant { $$ = $1; yyerrok; }
                    | LPAREN error { $$ = nullptr; }
                    ;

call                : ID LPAREN argList RPAREN {
                        if ($1) {
                            $$ = new AST::Exp::Call($1->linenum, $1->tokenstr, $3);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | ID LPAREN RPAREN {
                        if ($1) {
                            $$ = new AST::Exp::Call($1->linenum, $1->tokenstr);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | error LPAREN { $$ = nullptr; }
                    ;

argList             : argList COM exp {
                        if ($1) {
                            $$ = $1;
                        } else { $$ = nullptr; }
                        $$->addSibling($3);
                        yyerrok;
                    }
                    | exp { $$ = $1; yyerrok; }
                    | argList COM error { $$ = nullptr; }
                    ;

constant            : NUMCONST {
                        AST::TypeInfo type = {AST::Type::Int, false, false};
                        if ($1) {
                            $$ = new AST::Exp::Const($1->linenum, type, $1->tokenstr);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | CHARCONST {
                        AST::TypeInfo type = {AST::Type::Char, false, false};
                        if ($1) {
                            $$ = new AST::Exp::Const($1->linenum, type, $1->tokenstr);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | STRINGCONST {
                        AST::TypeInfo type = {AST::Type::Char, true, false};
                        if ($1) {
                            $$ = new AST::Exp::Const($1->linenum, type, $1->tokenstr);
                        } else { $$ = nullptr; }
                        yyerrok;
                    }
                    | BOOLCONST {
                        AST::TypeInfo type = {AST::Type::Bool, false, false};
                        if ($1) {
                            $$ = new AST::Exp::Const($1->linenum, type, $1->tokenstr);
                        } else { $$ = nullptr; }
                        yyerrok;
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
            if (tree_root ) {
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