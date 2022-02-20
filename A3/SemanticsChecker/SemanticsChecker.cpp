#include "SemanticsChecker.hpp"
#include "../AST/AST.hpp"
#include "../SymbolTable/SymbolTable.hpp"

#include <iostream>

SemanticsChecker::SemanticsChecker()
    : m_symbolTable(SymbolTable()), m_mainIsDefined(false) {}

const SymbolTable &SemanticsChecker::symbolTable() const {
    return m_symbolTable;
}

void SemanticsChecker::enterScope() {
    if (m_scopeName.has_value()) {
        m_symbolTable.enter(m_scopeName.value());
        m_scopeName = {};
    } else {
        m_symbolTable.enter();
    }

    for (auto &parm : m_parms) {
        AST::Decl::Parm *p = parm;
        while (p != nullptr) {
            m_symbolTable.declare(p->id(), p);
            p = (AST::Decl::Parm *)p->sibling();
        }
    }
    m_parms.clear();
}

void SemanticsChecker::leaveScope() {
    auto symbols = m_symbolTable.getImmediateSymbols();

    for (const auto &[id, symbol] : symbols) {
        if (!symbol.isUsed()) {
            std::string warning =
                "The variable '" + id + "' seems not to be used.";

            m_messages[symbol.decl()->lineNumber()].push_back(
                {Message::Type::Warning, warning});

        } else if (symbol.isUsed() && !symbol.isDefined()) {
            for (const auto &line : symbol.linesUsed()) {
                std::string warning = "Variable '" + id +
                                      "' may be uninitialized when used here.";

                m_messages[symbol.decl()->lineNumber()].push_back(
                    {Message::Type::Warning, warning});
            }
        }
    }

    m_symbolTable.leave();
}

void SemanticsChecker::analyze(AST::Node *tree) {
    m_mainIsDefined = false;
    m_symbolTable = SymbolTable();
    m_messages.clear();
    m_numErrors = 0;
    m_numWarnings = 0;
    analyzeTree(tree);

    for (const auto &[lineNumber, bucket] : m_messages) {
        for (const auto &message : bucket) {
            std::string tag;

            if (message.type() == Message::Type::Error) {
                tag = "ERROR(" + std::to_string(lineNumber) + "): ";
            } else {
                tag = "WARNING(" + std::to_string(lineNumber) + "): ";
            }
            std::cout << tag + message.content() << std::endl;
        }
    }

    if (!m_mainIsDefined) {
        std::cout << "ERROR(LINKER): A function named 'main()' must be defined."
                  << std::endl;
    }
    std::cout << "Number of errors: " << Message::numErrors() << std::endl;
    std::cout << "Number of warnings: " << Message::numWarnings() << std::endl;
}

void SemanticsChecker::analyzeTree(AST::Node *tree) {

    bool isCompoundStmt = false;
    if (tree->nodeType() == AST::NodeType::Stmt) {
        auto *stmt = (AST::Stmt::Stmt *)tree;
        if (stmt->stmtType() == AST::StmtType::Compound) {
            isCompoundStmt = true;
        }
    }

    if (isCompoundStmt) {
        enterScope();
    }

    for (auto child : tree->children()) {
        analyzeTree(child);
    }

    if (isCompoundStmt) {
        leaveScope();
    }

    if (tree->hasSibling()) {
        analyzeTree(tree->sibling());
    }

    switch (tree->nodeType()) {
    case AST::NodeType::Decl: {
        AST::Decl::Decl *decl = (AST::Decl::Decl *)tree;
        analyzeNode(decl);
        break;
    }
    case AST::NodeType::Stmt: {
        AST::Stmt::Stmt *stmt = (AST::Stmt::Stmt *)tree;
        analyzeNode(stmt);
        break;
    }
    case AST::NodeType::Exp: {
        AST::Exp::Exp *exp = (AST::Exp::Exp *)tree;
        analyzeNode(exp);
        break;
    }
    default:
        break;
    }
}

void SemanticsChecker::analyzeNode(AST::Exp::Exp *exp) {
    switch (exp->expType()) {
    case AST::ExpType::Call: {
        AST::Exp::Call *call = (AST::Exp::Call *)exp;

        if (m_symbolTable[call->id()].decl()->declType() !=
            AST::DeclType::Func) {
            std::string error = "'" + call->id() +
                                "' is a simple variable and cannot be called.";
            m_messages[call->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        break;
    }
    case AST::ExpType::Id: {
        AST::Exp::Id *id = (AST::Exp::Id *)exp;

        if (!m_symbolTable.contains(id->id())) {
            std::string error = "Symbol '" + id->id() + "' is not declared.\n";
            m_messages[id->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        if (m_symbolTable[id->id()].decl()->declType() == AST::DeclType::Func) {
            std::string error =
                "Cannot use function '" + id->id() + "' as a variable.";
            m_messages[id->lineNumber()].push_back(
                {Message::Type::Error, error});
        } else {
            m_symbolTable[id->id()].use(id->lineNumber());
        }

        break;
    }
    case AST::ExpType::Op: {
        AST::Exp::Op::Op *op = (AST::Exp::Op::Op *)exp;
        analyzeNode(op);
        break;
    }
    }
}

void SemanticsChecker::analyzeNode(AST::Exp::Op::Op *op) {
    switch (op->opType()) {
    case AST::OpType::Binary: {
        auto *binary = (AST::Exp::Op::Binary *)op;

        switch (binary->binaryOpType()) {
        case AST::BinaryOpType::Asgn: {
            break;
        }
        }

        break;
    }
    case AST::OpType::Unary: {

        break;
    }
    }
}

void SemanticsChecker::analyzeNode(AST::Decl::Decl *decl) {
    if (m_symbolTable.containsImmediately(decl->id())) {
        AST::Decl::Decl *originalSymbol = m_symbolTable[decl->id()].decl();

        std::string error = "Symbol '" + decl->id() +
                            "' is already declared at line " +
                            std::to_string(originalSymbol->lineNumber());

        m_messages[decl->lineNumber()].push_back({Message::Type::Error, error});
    } else {
        m_symbolTable.declare(decl->id(), decl);
    }

    switch (decl->declType()) {
    case AST::DeclType::Func: {
        m_scopeName = decl->id();

        if (decl->id() == "main") {
            m_mainIsDefined = true;
        }

        break;
    }
    case AST::DeclType::Parm: {
        /// Store the parms
        /// They are not in the current scope, but in the following scope for
        /// the compound stmt
        m_parms.push_back((AST::Decl::Parm *)decl);
        break;
    }
    case AST::DeclType::Var: {
        break;
    }
    }
}

void SemanticsChecker::analyzeNode(AST::Stmt::Stmt *stmt) {
    switch (stmt->stmtType()) {
    case AST::StmtType::Compound: {
    }
    }
}