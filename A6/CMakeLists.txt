cmake_minimum_required(VERSION 3.12)
project(cm)

add_library(cm
    ### AST
    ${PROJECT_SOURCE_DIR}/AST/AST.cpp
    ${PROJECT_SOURCE_DIR}/AST/MemoryInfo.cpp
    ${PROJECT_SOURCE_DIR}/AST/Node.cpp
    ${PROJECT_SOURCE_DIR}/AST/TypedNode.cpp
    ${PROJECT_SOURCE_DIR}/AST/Types.cpp

    ${PROJECT_SOURCE_DIR}/AST/Decl/Decl.cpp
    ${PROJECT_SOURCE_DIR}/AST/Decl/Func.cpp
    ${PROJECT_SOURCE_DIR}/AST/Decl/Parm.cpp
    ${PROJECT_SOURCE_DIR}/AST/Decl/Var.cpp

    ${PROJECT_SOURCE_DIR}/AST/Exp/Call.cpp
    ${PROJECT_SOURCE_DIR}/AST/Exp/Const.cpp
    ${PROJECT_SOURCE_DIR}/AST/Exp/Exp.cpp
    ${PROJECT_SOURCE_DIR}/AST/Exp/Id.cpp
    ${PROJECT_SOURCE_DIR}/AST/Exp/Op/Asgn.cpp
    ${PROJECT_SOURCE_DIR}/AST/Exp/Op/Binary.cpp
    ${PROJECT_SOURCE_DIR}/AST/Exp/Op/Bool.cpp
    ${PROJECT_SOURCE_DIR}/AST/Exp/Op/Op.cpp
    ${PROJECT_SOURCE_DIR}/AST/Exp/Op/Unary.cpp
    ${PROJECT_SOURCE_DIR}/AST/Exp/Op/UnaryAsgn.cpp
    
    ${PROJECT_SOURCE_DIR}/AST/Stmt/Break.cpp
    ${PROJECT_SOURCE_DIR}/AST/Stmt/Compound.cpp
    ${PROJECT_SOURCE_DIR}/AST/Stmt/For.cpp
    ${PROJECT_SOURCE_DIR}/AST/Stmt/Range.cpp
    ${PROJECT_SOURCE_DIR}/AST/Stmt/Return.cpp
    ${PROJECT_SOURCE_DIR}/AST/Stmt/Select.cpp
    ${PROJECT_SOURCE_DIR}/AST/Stmt/Stmt.cpp
    ${PROJECT_SOURCE_DIR}/AST/Stmt/While.cpp
    
    ### Options
    ${PROJECT_SOURCE_DIR}/Options/Options.cpp
    ${PROJECT_SOURCE_DIR}/Options/ourgetopt/ourgetopt.cpp

    ### SemanticsChecker
    ${PROJECT_SOURCE_DIR}/SemanticsChecker/AnalyzeDecls.cpp
    ${PROJECT_SOURCE_DIR}/SemanticsChecker/AnalyzeExps.cpp
    ${PROJECT_SOURCE_DIR}/SemanticsChecker/AnalyzeStmts.cpp
    ${PROJECT_SOURCE_DIR}/SemanticsChecker/Message.cpp
    ${PROJECT_SOURCE_DIR}/SemanticsChecker/SemanticsChecker.cpp

    ### SymbolTable
    ${PROJECT_SOURCE_DIR}/SymbolTable/Scope.cpp
    ${PROJECT_SOURCE_DIR}/SymbolTable/Symbol.cpp
    ${PROJECT_SOURCE_DIR}/SymbolTable/SymbolTable.cpp

    ### strutil
    ${PROJECT_SOURCE_DIR}/strutil.cpp
)

set_target_properties(cm PROPERTIES
    CXX_STANDARD 17
)