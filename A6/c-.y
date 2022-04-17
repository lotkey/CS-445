%{
#include "AST/AST.hpp"
#include "scanType.hpp"  // TokenData Type
#include "strutil.hpp"
#include "Options/Options.hpp"
#include "SemanticsChecker/SemanticsChecker.hpp"
#include "SemanticsChecker/Message.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <set>

extern int yylex();
extern FILE *yyin;
extern int line;         // ERR line number from the scanner!!
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
    {"DIV", "'/'"},                     {"MOD", "'%%'"}, 
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
    std::string error_msg = "Syntax error, unexpected " + unexpected;
    if (unexpected == "identifier") {
        error_msg += " \"" + std::string(yytext) + "\"";
    } else if (unexpected == "numeric constant" || unexpected == "Boolean constant") {
        error_msg += " \"" + std::string(yytext) + "\"";
    } else if (unexpected == "character constant" || unexpected == "string constant") {
        error_msg += " " + std::string(yytext);

        if (unexpected == "character constant") {
            int strlen = strutil::str_len(strutil::remove_quotes(yytext));
            if (strlen == 0) {
                Message::addSyntaxMessage(
                    line, Message::Type::Error,
                    "Empty character ''. Characters ignored.");
            } else if (strlen > 1) {
                Message::addSyntaxMessage(
                    line, Message::Type::Warning,
                    "character is %d characters long and not a single "
                    "character: '%s'. The first char will be used.",
                    strlen, yytext);
            }
        }
    }


    if (words.size() > 5) {
        error_msg += ", expecting";
        std::vector<std::string> expected;
        for (int i = 5; i < words.size(); i += 2) {
            expected.push_back(words[i]);
        }
        std::sort(expected.begin(), expected.end());

        for (int i = 0; i < expected.size() - 1; i++) {
            error_msg += " " + expected[i] + " or";
        }
        error_msg += " " + expected.back();
    }
    error_msg += ".";
    Message::addSyntaxMessage(line, Message::Type::Error, error_msg);
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
                    }
                    ;

declList            : declList decl {
                        $$ = $1;
                        if ($$) { $$->addSibling($2); }
                    }
                    | decl { $$ = $1; }
                    ;

decl                : varDecl { $$ = $1; }
                    | funDecl { $$ = $1; }
                    | error { $$ = nullptr; }
                    ;

varDecl             : typeSpec varDeclList SEMI {
                        auto *var = $2->cast<AST::Decl::Var *>();
                        if (var) {
                            var->setType($1);
                            var->setGlobal(true);     
                            var->calculateMemory();                   
                        }
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
                            var->calculateMemory();                   
                        }
                        $$ = var;
                        yyerrok;
					}
                    | typeSpec varDeclList SEMI {
                        auto *var = $2->cast<AST::Decl::Var *>();
                        if (var) { 
                            var->setType($1);
                            // var->calculateLocation();
                        }
                        $$ = var;
                        yyerrok;
					}
                    ;

varDeclList         : varDeclList COM varDeclInit {
                        $$ = $1;
                        if ($$) { $$->addSibling($3); }
                    }
                    | varDeclInit { $$ = $1; }
                    | varDeclList COM error { $$ = nullptr; }
                    | error { $$ = nullptr; }
                    ;

varDeclInit         : varDeclId { $$ = $1; }
                    | varDeclId COL simpleExp {
                        $$ = $1;
                        if ($$) { $$->addChild($3); }
                    }
                    | error COL simpleExp { $$ = nullptr; yyerrok; }
                    ;
                
varDeclId           : ID {
                        if ($1) {
                            $$ = new AST::Decl::Var($1->linenum, $1->tokenstr);
                        } else { $$ = nullptr; }
                    }
                    | ID LBRACK NUMCONST RBRACK {
                        if ($1) {
                            $$ = new AST::Decl::Var($1->linenum, $1->tokenstr, std::atoi($3->tokenstr.c_str()));
                        } else { $$ = nullptr; }
                    }
                    | ID LBRACK error { $$ = nullptr; }
                    | error RBRACK { $$ = nullptr; yyerrok; }
                    ;

typeSpec            : BOOL { $$ = AST::Type::Bool; }
                    | CHAR { $$ = AST::Type::Char; }
                    | INT { $$ = AST::Type::Int; }
                    ;

funDecl             : typeSpec ID LPAREN parms RPAREN compoundStmt {
                        if ($2) {
                            auto *func = new AST::Decl::Func($2->linenum, $1, $2->tokenstr, $4, $6);
                            func->calculateMemory();
                            $$ = func;
                        } else { $$ = nullptr; }
                    }
                    | ID LPAREN parms RPAREN compoundStmt {
                        if ($1) {
                            auto *func = new AST::Decl::Func($1->linenum, $1->tokenstr, $3, $5);
                            func->calculateMemory();
                            $$ = func;
                        } else { $$ = nullptr; }
                    }
                    | typeSpec error { $$ = nullptr; }
                    | typeSpec ID LPAREN error { $$ = nullptr; }
                    | ID LPAREN error { $$ = nullptr; }
                    | ID LPAREN parms RPAREN error { $$ = nullptr; }
                    ;

parms               : { $$ = nullptr; }
                    | parmList { $$ = $1; }
                    ;

parmList            : parmList SEMI parmTypeList {
                        $$ = $1;
                        if ($$) { $$->addSibling($3); }
                    }
                    | parmTypeList { $$ = $1; }
                    | parmList SEMI error { $$ = nullptr; }
                    | error { $$ = nullptr; }
                    ;

parmTypeList        : typeSpec parmIdList {
                        auto *parms = $2->cast<AST::Decl::Parm *>();
                        if (parms) { parms->setType($1); }
                        $$ = parms;
					}
                    | typeSpec error { $$ = nullptr; }
                    ;

parmIdList          : parmIdList COM parmId {
                        $$ = $1;
                        if ($$) { $$->addSibling($3); }
                    }
                    | parmId { $$ = $1; }
                    | parmIdList COM error { $$ = nullptr; }
                    | error { $$ = nullptr; }
                    ;

parmId              : ID {
                        if ($1) {
                            $$ = new AST::Decl::Parm($1->linenum, $1->tokenstr, false);
                        } else { $$ = nullptr; }
					}
                    | ID LBRACK RBRACK {
                        if ($1) {
                            $$ = new AST::Decl::Parm($1->linenum, $1->tokenstr, true);
                        } else { $$ = nullptr; }
					}
                    ;

stmt                : closedStmt { $$ = $1; }
                    | openStmt { $$ = $1; }
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

localDecls          : { $$ = nullptr; }
                    | localDecls scopedVarDecl {
                        if ($1) {
                            $$ = $1;
                            $$->addSibling($2);
                        } else {
                            $$ = $2;
                        }
                    }
                    ;

stmtList            : { $$ = nullptr; }
                    | stmtList stmt {
                        if ($1) {
                            $$ = $1;
                            $$->addSibling($2);
                        } else {
                            $$ = $2;
                        }
                    }
                    ;

closedStmt          : selectStmtClosed { $$ = $1; }
                    | iterStmtClosed { $$ = $1; }
                    | expStmt { $$ = $1; }
                    | compoundStmt { $$ = $1; }
                    | returnStmt  { $$ = $1; }
                    | breakStmt { $$ = $1; }
                    ;

openStmt            : selectStmtOpen { $$ = $1; }
                    | iterStmtOpen { $$ = $1; }
                    ;

selectStmtOpen      : IF simpleExp THEN stmt {
                        if ($1) {
                            $$ = new AST::Stmt::Select($1->linenum, $2, $4);
                        } else { $$ = nullptr; }
                    }
                    | IF simpleExp THEN closedStmt ELSE openStmt {
                        if ($1) {
                            $$ = new AST::Stmt::Select($1->linenum, $2, $4, $6);
                        } else { $$ = nullptr; }
                    }
                    | IF error THEN stmt { $$ = nullptr; yyerrok; } 
                    | IF error THEN closedStmt ELSE openStmt { $$ = nullptr; yyerrok; }
                    ;

selectStmtClosed    : IF simpleExp THEN closedStmt ELSE closedStmt {
                        if ($1) {
                            $$ = new AST::Stmt::Select($1->linenum, $2, $4, $6);
                        } else { $$ = nullptr; }
                    }
                    | IF error { $$ = nullptr; }
                    | IF error ELSE closedStmt { $$ = nullptr; yyerrok; }
                    | IF error THEN closedStmt ELSE closedStmt { $$ = nullptr; yyerrok; } 
                    ;

iterStmtOpen        : WHILE simpleExp DO openStmt {
                        if ($1) {
                            $$ = new AST::Stmt::While($1->linenum, $2, $4);
                        } else { $$ = nullptr; }
                    }
                    | FOR ID ASGN iterRange DO openStmt {
                        if ($1 && $2) {
                            auto *iterator = new AST::Decl::Var($1->linenum, $2->tokenstr);
                            iterator->setType(AST::Type::Int);
                            $$ = new AST::Stmt::For($1->linenum, iterator, $4, $6);
                        } else { $$ = nullptr; }
                    }
                    | FOR ID ASGN error DO openStmt { $$ = nullptr; yyerrok; }
                    | FOR error { $$ = nullptr; }
                    | WHILE error DO openStmt { $$ = nullptr; yyerrok; }
                    | WHILE error { $$ = nullptr; }
                    ;

iterStmtClosed      : WHILE simpleExp DO closedStmt {
                        if ($1) {
                            $$ = new AST::Stmt::While($1->linenum, $2, $4);
                        } else { $$ = nullptr; }
                    }
                    | FOR ID ASGN iterRange DO closedStmt {
                        if ($1 && $2) {
                            auto *iterator = new AST::Decl::Var($1->linenum, $2->tokenstr);
                            iterator->setType(AST::Type::Int);
                            $$ = new AST::Stmt::For($1->linenum, iterator, $4, $6);
                        } else { $$ = nullptr; }
                    }
                    | WHILE error DO closedStmt { $$ = nullptr; yyerrok; }
                    | WHILE error { $$ = nullptr; }
                    | FOR ID ASGN error DO closedStmt { $$ = nullptr; yyerrok; }
                    | FOR error { $$ = nullptr; }
                    ;

iterRange           : simpleExp TO simpleExp {
                        if ($1) {
                            $$ = new AST::Stmt::Range($1->lineNumber(), $1, $3);
                        } else { $$ = nullptr; }
                    }
                    | simpleExp TO simpleExp BY simpleExp {
                        if ($1) {
                            $$ = new AST::Stmt::Range($1->lineNumber(), $1, $3, $5);
                        } else { $$ = nullptr; }
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
                    }
                    | mutable INC {
                        if ($1) {
                            $$ = new AST::Exp::Op::UnaryAsgn($1->lineNumber(), AST::UnaryAsgnType::Inc, $1);
                        } else { $$ = nullptr; }
                    }
                    | mutable DEC {
                        if ($1) {
                            $$ = new AST::Exp::Op::UnaryAsgn($1->lineNumber(), AST::UnaryAsgnType::Dec, $1);
                        } else { $$ = nullptr; }
                    }
                    | simpleExp { $$ = $1; }
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
					}
                    | SUBASGN {
                        if ($1) {
                            $$ = new AST::Exp::Op::Asgn($1->linenum, AST::AsgnType::SubAsgn);
                        } else { $$ = nullptr; }
					}
                    | DIVASGN {
                        if ($1) {
                            $$ = new AST::Exp::Op::Asgn($1->linenum, AST::AsgnType::DivAsgn);
                        } else { $$ = nullptr; }
					}
                    | MULASGN {
                        if ($1) {
                            $$ = new AST::Exp::Op::Asgn($1->linenum, AST::AsgnType::MulAsgn);
                        } else { $$ = nullptr; }
					}
                    ;

simpleExp           : simpleExp OR andExp {
                        if ($1) {
                            auto *boolop = new AST::Exp::Op::Bool($1->lineNumber(), AST::BoolOpType::Or);
                            boolop->addChildren($1, $3);
                            $$ = boolop;
                        } else { $$ = nullptr; }
                    }
                    | andExp { $$ = $1; }
                    | simpleExp OR error { $$ = nullptr; }
                    ;

andExp              : andExp AND unaryRelExp {
                        if ($1) {
                            auto *boolop = new AST::Exp::Op::Bool($1->lineNumber(), AST::BoolOpType::And);
                            boolop->addChildren($1, $3);
                            $$ = boolop;
                        } else { $$ = nullptr; }
                    }
                    | unaryRelExp { $$ = $1; }
                    | andExp AND error { $$ = nullptr; }
                    ;

unaryRelExp         : NOT unaryRelExp {
                        $$ = new AST::Exp::Op::Unary($1->linenum, AST::UnaryOpType::Not, $2);
                    }
                    | relExp { $$ = $1; }
                    | NOT error { $$ = nullptr; }
                    ;

relExp              : sumExp relop sumExp {
                        auto *op = $2->cast<AST::Exp::Op::Binary *>();
                        if (op) { op->addChildren($1, $3); }
                        $$ = op;
                    }
                    | sumExp { $$ = $1; }
                    ;

relop               : LT {
                        if ($1) {
                            $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::LT);
                        } else { $$ = nullptr; }
					}
                    | LEQ {
                        if ($1) {
                            $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::LEQ);
                        } else { $$ = nullptr; }
					}
                    | GT {
                        if ($1) {
                            $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::GT);
                        } else { $$ = nullptr; }
					}
                    | GEQ {
                        if ($1) {
                            $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::GEQ);
                        } else { $$ = nullptr; }
					}
                    | EQ {
                        if ($1) {
                            $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::EQ);
                        } else { $$ = nullptr; }
					}
                    | NEQ {
                        if ($1) {
                            $$ = new AST::Exp::Op::Bool($1->linenum, AST::BoolOpType::NEQ);
                        } else { $$ = nullptr; }
					}
                    ;

sumExp              : sumExp sumop mulExp {
                        auto *op = $2->cast<AST::Exp::Op::Binary *>();
                        if (op) { op->addChildren($1, $3); }
                        $$ = op;
					}
                    | mulExp { $$ = $1; }
                    | sumExp sumop error { $$ = nullptr; }
                    ;

sumop               : ADD {
                        if ($1) {
                            $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Add);
                        } else { $$ = nullptr; }
					}
                    | DASH {
                        if ($1) {
                            $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Subtract);
                        } else { $$ = nullptr; }
					}
                    ;

mulExp              : mulExp mulop unaryExp {
                        auto *op = $2->cast<AST::Exp::Op::Binary *>();
                        if (op) { op->addChildren($1, $3); }
                        $$ = op;
					}
                    | unaryExp { $$ = $1; }
                    | mulExp mulop error { $$ = nullptr; }
                    ;

mulop               : ASTERISK {
                        if ($1) {
                            $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Mul);
                        } else { $$ = nullptr; }
					}
                    | DIV {
                        if ($1) {
                            $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Div);
                        } else { $$ = nullptr; }
					}
                    | MOD {
                        if ($1) {
                            $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Mod);
                        } else { $$ = nullptr; }
					}
                    ;

unaryExp            : unaryop unaryExp {
                        auto *op = $1->cast<AST::Exp::Op::Unary *>();
                        if (op) { op->addExp($2); }
                        $$ = op;
					}
                    | factor { $$ = $1; }
                    | unaryop error { $$ = nullptr; }
                    ;

unaryop             : DASH {
                        if ($1) {
                            $$ = new AST::Exp::Op::Unary($1->linenum, AST::UnaryOpType::Chsign);
                        } else { $$ = nullptr; }
					}
                    | ASTERISK {
                        if ($1) {
                            $$ = new AST::Exp::Op::Unary($1->linenum, AST::UnaryOpType::Sizeof);
                        } else { $$ = nullptr; }
					}
                    | RAND {
                        if ($1) {
                            $$ = new AST::Exp::Op::Unary($1->linenum, AST::UnaryOpType::Random);
                        } else { $$ = nullptr; }
					}
                    ;

factor              : mutable { $$ = $1; }
                    | immutable { $$ = $1; }
                    ;

mutable             : ID {
                        if ($1) {
                            $$ = new AST::Exp::Id($1->linenum, $1->tokenstr);
                        } else { $$ = nullptr; }
					}
                    | ID LBRACK exp RBRACK {
                        if ($1) {
                            auto *id = new AST::Exp::Id($1->linenum, $1->tokenstr);
                            $$ = new AST::Exp::Op::Binary($1->linenum, AST::BinaryOpType::Index, id, $3);
                        } else { $$ = nullptr; }
                    }
                    ;

immutable           : LPAREN exp RPAREN { $$ = $2; yyerrok; }
                    | call { $$ = $1; }
                    | constant { $$ = $1; }
                    | LPAREN error { $$ = nullptr; }
                    ;

call                : ID LPAREN argList RPAREN {
                        if ($1) {
                            $$ = new AST::Exp::Call($1->linenum, $1->tokenstr, $3);
                        } else { $$ = nullptr; }
                    }
                    | ID LPAREN RPAREN {
                        if ($1) {
                            $$ = new AST::Exp::Call($1->linenum, $1->tokenstr);
                        } else { $$ = nullptr; }
                    }
                    | error LPAREN { $$ = nullptr; yyerrok; }
                    ;

argList             : argList COM exp {
                        if ($1) {
                            $$ = $1;
                            $$->addSibling($3);
                        } else { $$ = nullptr; }
                    }
                    | exp { $$ = $1; }
                    | argList COM error { $$ = nullptr; }
                    ;

constant            : NUMCONST {
                        AST::TypeInfo type = {AST::Type::Int, false, false};
                        if ($1) {
                            $$ = new AST::Exp::Const($1->linenum, type, $1->tokenstr);
                        } else { $$ = nullptr; }
                    }
                    | CHARCONST {
                        AST::TypeInfo type = {AST::Type::Char, false, false};
                        if ($1) {
                            $$ = new AST::Exp::Const($1->linenum, type, $1->tokenstr);
                        } else { $$ = nullptr; }
                    }
                    | STRINGCONST {
                        AST::TypeInfo type = {AST::Type::Char, true, false};
                        if ($1) {
                            $$ = new AST::Exp::Const($1->linenum, type, $1->tokenstr);
                        } else { $$ = nullptr; }
                    }
                    | BOOLCONST {
                        AST::TypeInfo type = {AST::Type::Bool, false, false};
                        if ($1) {
                            $$ = new AST::Exp::Const($1->linenum, type, $1->tokenstr);
                        } else { $$ = nullptr; }
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
            yyparse();

            semantics.analyze(tree_root);

            Message::print(options.print() || options.printTypeInfo() || options.printSymbolInfo());

            if (tree_root && Message::numberOf(Message::Type::Error) == 0) {
                if (options.print() || options.printTypeInfo() || options.printSymbolInfo()) {
                    tree_root->print(options.printTypeInfo(), options.printSymbolInfo());
                }
            }
            if (options.printSymbolInfo()) {
                std::cout << "Offset for end of global space: " 
                          << AST::MemoryInfo::globalOffset() << std::endl;
            }
            Message::printCounts();

            // Free memory
            if (tree_root) {
                delete tree_root;
            }
            tokens.clear();
        }
        else {
            std::cout << "ERROR(ARGLIST): source file \"" + file.value() + "\" could not be opened." << std::endl;
            std::cout << "Number of warnings: 0" << std::endl;
            std::cout << "Number of errors: 1" << std::endl;
            fileExists = false;
        }
    } else {
        yyparse();
    }
    
    return 0;
}