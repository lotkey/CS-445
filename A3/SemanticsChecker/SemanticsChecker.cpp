#include "SemanticsChecker.hpp"
#include "../AST/AST.hpp"
#include "../SymbolTable/SymbolTable.hpp"

#include <iostream>

SemanticsChecker::SemanticsChecker()
    : m_symbolTable(SymbolTable()), m_mainIsDefined(false) {}

SemanticsChecker::SemanticsChecker(bool debug)
    : m_symbolTable(SymbolTable(debug)), m_mainIsDefined(false) {}

const SymbolTable &SemanticsChecker::symbolTable() const {
    return m_symbolTable;
}

int SemanticsChecker::numErrors() const {
    return Message::numErrors() + (!m_mainIsDefined - !m_analyzed);
}

int SemanticsChecker::numWarnings() const { return Message::numWarnings(); }

void SemanticsChecker::print() const {
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
}

void SemanticsChecker::enterScope() {
    if (m_scopeName.has_value()) {
        m_symbolTable.enter(m_scopeName.value());
        m_scopeName = {};
    } else {
        m_symbolTable.enter();
    }
}

void SemanticsChecker::leaveScope() {
    auto symbols = m_symbolTable.getImmediateSymbols();

    for (const auto &[id, symbol] : symbols) {

        if (!symbol.isUsed()) {
            std::string warning =
                "The variable '" + id + "' seems not to be used.";

            if (symbol.isDeclared()) {
                m_messages[symbol.decl()->lineNumber()].push_back(
                    {Message::Type::Warning, warning});
            }

        } else if (symbol.isUsed() && !symbol.isDefined()) {
            for (const auto &line : symbol.linesUsed()) {
                if (!m_symbolTable.isGlobal(id)) {
                    std::string warning =
                        "Variable '" + id +
                        "' may be uninitialized when used here.";

                    if (symbol.isDeclared()) {
                        m_messages[symbol.decl()->lineNumber()].push_back(
                            {Message::Type::Warning, warning});
                    }
                }
            }
        }
    }

    m_symbolTable.leave();
}

void SemanticsChecker::analyze(AST::Node *tree) {
    m_analyzed = true;
    m_mainIsDefined = false;
    m_symbolTable = SymbolTable();
    m_messages.clear();
    m_numErrors = 0;
    m_numWarnings = 0;
    analyzeTree(tree);
}

void SemanticsChecker::analyzeTree(AST::Node *tree) {
    bool isFunction = false;
    if (tree->nodeType() == AST::NodeType::Decl) {
        auto *decl = (AST::Decl::Decl *)tree;
        if (decl->declType() == AST::DeclType::Func) {
            m_scopeName = decl->id();
        }
    }

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

    for (auto &child : tree->children()) {
        if (child != nullptr) {
            analyzeTree(child);
        }
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

    if (isCompoundStmt) {
        leaveScope();
    }

    if (tree->hasSibling()) {
        analyzeTree(tree->sibling());
    }
}

void SemanticsChecker::analyzeNode(AST::Exp::Exp *exp) {
    switch (exp->expType()) {
    case AST::ExpType::Call: {
        AST::Exp::Call *call = (AST::Exp::Call *)exp;

        if (!m_symbolTable.contains(call->id())) {

            std::string error = "Symbol '" + call->id() + "' is not declared.";
            m_messages[call->lineNumber()].push_back(
                {Message::Type::Error, error});
        } else if (m_symbolTable[call->id()].isDeclared() &&
                   m_symbolTable[call->id()].decl()->declType() !=
                       AST::DeclType::Func) {

            std::string error = "'" + call->id() +
                                "' is a simple variable and cannot be called.";
            m_messages[call->lineNumber()].push_back(
                {Message::Type::Error, error});
        } else {
            if (m_symbolTable[call->id()].isDeclared()) {
                call->typeInfo() = m_symbolTable[call->id()].decl()->typeInfo();
            }
        }

        break;
    }
    case AST::ExpType::Id: {
        AST::Exp::Id *id = (AST::Exp::Id *)exp;

        if (m_symbolTable.contains(id->id())) {
            if (m_symbolTable[id->id()].isDeclared()) {
                id->typeInfo() = m_symbolTable[id->id()].decl()->typeInfo();

                if (m_symbolTable[id->id()].decl()->declType() ==
                    AST::DeclType::Func) {

                    std::string error =
                        "Cannot use function '" + id->id() + "' as a variable.";
                    m_messages[id->lineNumber()].push_back(
                        {Message::Type::Error, error});
                } else {
                }

            } else {
            }

        } else {
            std::string error = "Symbol '" + id->id() + "' is not declared.";
            m_messages[id->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        m_symbolTable[id->id()].use(id->lineNumber());

        break;
    }
    case AST::ExpType::Op: {
        AST::Exp::Op::Op *op = (AST::Exp::Op::Op *)exp;
        analyzeNode(op);
        break;
    }
    default: {
        break;
    }
    }
}

void SemanticsChecker::analyzeNode(AST::Exp::Op::Op *op) {
    op->deduceType();

    switch (op->opType()) {
    case AST::OpType::Binary: {
        auto *binary = (AST::Exp::Op::Binary *)op;

        if (binary->binaryOpType() == AST::BinaryOpType::Add ||
            binary->binaryOpType() == AST::BinaryOpType::Div ||
            binary->binaryOpType() == AST::BinaryOpType::Mod ||
            binary->binaryOpType() == AST::BinaryOpType::Mul ||
            binary->binaryOpType() == AST::BinaryOpType::Subtract) {
            if (binary->typeInfo().isArray) {
                std::string error =
                    "The operation '" +
                    AST::Types::toString(binary->binaryOpType()) +
                    "' does not work with arrays.";

                m_messages[binary->lineNumber()].push_back(
                    {Message::Type::Error, error});
            }
        }

        else {
            switch (binary->binaryOpType()) {
            case AST::BinaryOpType::Asgn: {
                analyzeNode((AST::Exp::Op::Asgn *)binary);
                break;
            }
            case AST::BinaryOpType::Add: {
                break;
            }
            case AST::BinaryOpType::Bool: {
                break;
            }
            case AST::BinaryOpType::Div: {
                break;
            }
            case AST::BinaryOpType::Index: {
                AST::Exp::Id *id = (AST::Exp::Id *)binary->exp1();

                if (!id->typeInfo().isArray) {
                    std::string error =
                        "Cannot index nonarray '" + id->id() + "'.";
                    m_messages[id->lineNumber()].push_back(
                        {Message::Type::Error, error});
                } else {
                    op->typeInfo() = id->typeInfo();
                    op->typeInfo().isArray = false;

                    if (binary->exp2()->typeInfo().type != AST::Type::Int) {
                        std::string error =
                            "Array '" + id->id() +
                            "' should be indexed by type int but got " +
                            AST::Types::toString(
                                binary->exp2()->typeInfo().type) +
                            ".";
                        m_messages[binary->lineNumber()].push_back(
                            {Message::Type::Error, error});
                    }
                }
                break;
            }
            case AST::BinaryOpType::Mod: {
                break;
            }
            case AST::BinaryOpType::Mul: {
                break;
            }
            case AST::BinaryOpType::Subtract: {
                break;
            }
            }
        }

        break;
    }
    case AST::OpType::Unary: {

        break;
    }
    default: {
        break;
    }
    }
}

void SemanticsChecker::analyzeNode(AST::Exp::Op::Unary *op) {
    switch (op->unaryOpType()) {
    case AST::UnaryOpType::Asgn: {
        break;
    }
    case AST::UnaryOpType::Chsign: {
        break;
    }
    case AST::UnaryOpType::Not: {
        break;
    }
    case AST::UnaryOpType::Random: {
        if (op->typeInfo().isArray) {
            std::string error = "The operation '?' does not work with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
        break;
    }
    case AST::UnaryOpType::Sizeof: {
        if (!op->typeInfo().isArray) {
            std::string error =
                "The operation 'sizeof' only works with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
        break;
    }
    }
}

void SemanticsChecker::analyzeNode(AST::Exp::Op::Asgn *op) {
    switch (op->asgnType()) {
    case AST::AsgnType::Asgn: {
        auto *mut = op->exp1();
        if (mut->expType() == AST::ExpType::Id) {
            AST::Exp::Id *id = (AST::Exp::Id *)op->exp1();

            m_symbolTable[id->id()].define(op->lineNumber());
        } else if (mut->expType() == AST::ExpType::Op) {
            auto *op = (AST::Exp::Op::Op *)mut;
            if (op->opType() == AST::OpType::Binary) {
                auto *id = (AST::Exp::Id *)((AST::Exp::Op::Binary *)op)->exp1();
                m_symbolTable[id->id()].define(op->lineNumber());
            }
            // if
            // if (mut->expType())
        }
        // m_symbolTable[op->getMutable()->id()].define(op->lineNumber()); //
        // could be id[], not just id! if (id != nullptr) {
        // }
        break;
    }
    }
}

void SemanticsChecker::analyzeNode(AST::Decl::Decl *decl) {
    if (m_symbolTable.containsImmediately(decl->id()) &&
        m_symbolTable[decl->id()].isDeclared()) {
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
        break;
    }
    case AST::DeclType::Var: {
        break;
    }
    default: {
        break;
    }
    }
}

void SemanticsChecker::analyzeNode(AST::Stmt::Stmt *stmt) {
    switch (stmt->stmtType()) {
    case AST::StmtType::Compound: {
        break;
    }
    case AST::StmtType::For: {
        auto *forNode = (AST::Stmt::For *)stmt;
        auto *id = (AST::Exp::Id *)forNode->id();
        m_symbolTable.removeImmediately(id->id());
        break;
    }
    }
}