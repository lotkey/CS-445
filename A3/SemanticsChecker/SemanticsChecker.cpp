#include "SemanticsChecker.hpp"
#include "../AST/AST.hpp"
#include "../SymbolTable/SymbolTable.hpp"

#include <iostream>

SemanticsChecker::SemanticsChecker() : m_mainIsDefined(false) {}

SemanticsChecker::SemanticsChecker(bool debug)
    : m_mainIsDefined(false), m_debug(debug) {}

const SymbolTable &SemanticsChecker::symbolTable() const {
    return m_symbolTable;
}

int SemanticsChecker::numErrors() const {
    return Message::numErrors() + (!m_mainIsDefined - !m_analyzed);
}

int SemanticsChecker::numWarnings() const { return Message::numWarnings(); }

void SemanticsChecker::print() const {
    if (!m_mainIsDefined) {
        std::cout << "ERROR(LINKER): A function named 'main()' must be defined."
                  << std::endl;
    }

    for (const auto &[lineNumber, bucket] : m_messages) {
        for (int i = bucket.size() - 1; i >= 0; i--) {
            auto message = bucket[i];
            std::string tag;

            if (message.type() == Message::Type::Error) {
                tag = "ERROR(" + std::to_string(lineNumber) + "): ";
            } else {
                tag = "WARNING(" + std::to_string(lineNumber) + "): ";
            }
            std::cout << tag + message.content() << std::endl;
        }
    }
}

void SemanticsChecker::enterScope() {
    if (m_scopeName.has_value()) {
        m_symbolTable.enter(m_scopeName.value());
        m_scopeName = {};
    } else {
        m_symbolTable.enter();
    }

    auto *parm = (AST::Decl::Decl *)m_parms;
    while (parm != nullptr) {

        if (m_symbolTable.containsImmediately(parm->id()) &&
            m_symbolTable[parm->id()].isDeclared()) {
            auto *originalSymbol = m_symbolTable[parm->id()].decl();
            std::string error =
                "Symbol '" + parm->id() + "' is already declared at line " +
                std::to_string(originalSymbol->lineNumber()) + ".";

            m_messages[parm->lineNumber()].push_back(
                {Message::Type::Error, error});

        } else {
            m_symbolTable.declare(parm->id(), parm);
        }

        parm = (AST::Decl::Decl *)parm->sibling();
    }
    m_parms = nullptr;
}

void SemanticsChecker::leaveScope() {
    auto symbols = m_symbolTable.getImmediateSymbols();

    for (const auto &[id, symbol] : symbols) {

        if (!symbol.isUsed()) {
            std::string warning =
                "The variable '" + id + "' seems not to be used.";

            if (symbol.isDeclared()) {
                m_messages[symbol.decl()->lineNumber()].insert(
                    m_messages[symbol.decl()->lineNumber()].begin(),
                    {Message::Type::Warning, warning});
            }
        }

        if (symbol.isDeclared() &&
            symbol.decl()->declType() != AST::DeclType::Parm &&
            !symbol.decl()->typeInfo().isStatic) {

            if (symbol.isUsed()) {

                auto linenumber = symbol.linesUsed()[0];
                if (!symbol.isDefined() || linenumber < symbol.lineDefined()) {
                    std::string warning =
                        "Variable '" + id +
                        "' may be uninitialized when used here.";

                    m_messages[linenumber].insert(
                        m_messages[linenumber].begin(),
                        {Message::Type::Warning, warning});
                }
            }
        }
    }

    m_symbolTable.leave();
}

void SemanticsChecker::analyze(AST::Node *tree) {
    m_analyzed = true;
    m_mainIsDefined = false;
    m_symbolTable = SymbolTable(m_debug);
    m_messages.clear();
    m_numErrors = 0;
    m_numWarnings = 0;
    analyzeTree(tree);
}

void SemanticsChecker::analyzeTree(AST::Node *tree) {
    bool isCompoundStmt = false;
    bool isFunction = false;

    if (tree->nodeType() == AST::NodeType::Decl) {
        auto *decl = (AST::Decl::Decl *)tree;

        // Check to see if it's defining main()
        if (decl->declType() == AST::DeclType::Func) {
            isFunction = true;
            m_scopeName = decl->id();
            auto *func = (AST::Decl::Func *)decl;

            m_parms = func->parms();

            if (func->id() == "main") {
                if (!(func->hasParms() &&
                      func->typeInfo().type.value() == AST::Type::Void)) {
                    m_mainIsDefined = true;
                } else {
                    m_mainIsDefined = false;
                }
            }
        }

        // If it's a parameter declaration, that is handled by enterScope()
        if (decl->declType() != AST::DeclType::Parm) {
            if (m_symbolTable.containsImmediately(decl->id()) &&
                m_symbolTable[decl->id()].isDeclared()) {
                auto *originalSymbol = m_symbolTable[decl->id()].decl();
                std::string error =
                    "Symbol '" + decl->id() + "' is already declared at line " +
                    std::to_string(originalSymbol->lineNumber()) + ".";

                m_messages[decl->lineNumber()].push_back(
                    {Message::Type::Error, error});

            } else {
                m_symbolTable.declare(decl->id(), decl);
            }
        }

        if (decl->declType() == AST::DeclType::Var) {
            auto *var = (AST::Decl::Var *)decl;
            if (var->isInitialized()) {
                m_symbolTable[decl->id()].define(
                    var->initValue()->lineNumber());
            }
        }

    } else if (tree->nodeType() == AST::NodeType::Stmt) {
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
        // AST::Decl::Decl *decl = (AST::Decl::Decl *)tree;
        // if (decl->declType() != AST::DeclType::Parm) {
        //     analyzeNode(decl);
        // }
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
        } else if (m_symbolTable[call->id()].isDeclared()) {

            m_symbolTable[call->id()].use(call->lineNumber());

            if (m_symbolTable[call->id()].decl()->declType() !=
                AST::DeclType::Func) {

                std::string error =
                    "'" + call->id() +
                    "' is a simple variable and cannot be called.";
                m_messages[call->lineNumber()].push_back(
                    {Message::Type::Error, error});
            } else {
                call->typeInfo() = m_symbolTable[call->id()].decl()->typeInfo();
            }
        }

        break;
    }
    case AST::ExpType::Id: {
        AST::Exp::Id *id = (AST::Exp::Id *)exp;

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

            if (binary->exp1()->typeInfo().isArray ||
                binary->exp2()->typeInfo().isArray &&
                    binary->exp1()->typeInfo().type.has_value() &&
                    binary->exp2()->typeInfo().type.has_value()) {
                std::string error =
                    "The operation '" +
                    AST::Types::toString(binary->binaryOpType()) +
                    "' does not work with arrays.";

                m_messages[binary->lineNumber()].push_back(
                    {Message::Type::Error, error});
            }

            if (binary->exp1()->typeInfo().type != AST::Type::Int &&
                binary->exp1()->typeInfo().type.has_value()) {
                std::string error =
                    "'" + AST::Types::toString(binary->binaryOpType()) +
                    "' requires operands of type int but lhs is of type " +
                    AST::Types::toString(binary->exp1()->typeInfo().type) + ".";
                m_messages[binary->lineNumber()].push_back(
                    {Message::Type::Error, error});
            }

            if (binary->exp2()->typeInfo().type != AST::Type::Int &&
                binary->exp2()->typeInfo().type.has_value()) {
                std::string error =
                    "'" + AST::Types::toString(binary->binaryOpType()) +
                    "' requires operands of type int but rhs is of type " +
                    AST::Types::toString(binary->exp2()->typeInfo().type) + ".";
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
                analyzeNode((AST::Exp::Op::Bool::Bool *)binary);
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
                }

                auto *index = (AST::Exp::Exp *)binary->exp2();
                if (index->expType() == AST::ExpType::Id) {
                    auto *indexId = (AST::Exp::Id *)index;

                    if (m_symbolTable[indexId->id()].isDeclared() &&
                        m_symbolTable[indexId->id()]
                            .decl()
                            ->typeInfo()
                            .isArray) {
                        std::string error =
                            "Array index is the unindexed array '" +
                            indexId->id() + "'.";
                        m_messages[binary->lineNumber()].push_back(
                            {Message::Type::Error, error});
                    }
                }

                op->typeInfo() = id->typeInfo();
                op->typeInfo().isArray = false;

                if (binary->exp2()->typeInfo().type != AST::Type::Int &&
                    binary->exp2()->typeInfo().type.has_value()) {
                    std::string error =
                        "Array '" + id->id() +
                        "' should be indexed by type int but got type " +
                        AST::Types::toString(binary->exp2()->typeInfo().type) +
                        ".";
                    m_messages[binary->lineNumber()].push_back(
                        {Message::Type::Error, error});
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
        auto *unaryop = (AST::Exp::Op::Unary *)op;
        analyzeNode(unaryop);
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
        auto *unaryasgn = (AST::Exp::Op::UnaryAsgn *)op;

        if (unaryasgn->operand()->typeInfo().isArray &&
            unaryasgn->operand()->typeInfo().type.has_value()) {
            std::string error =
                "The operation '" +
                AST::Types::toString(unaryasgn->unaryAsgnType()) +
                "' does not work with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        if (unaryasgn->operand()->typeInfo().type != AST::Type::Int &&
            unaryasgn->operand()->typeInfo().type.has_value()) {
            std::string error =
                "Unary '" + AST::Types::toString(unaryasgn->unaryAsgnType()) +
                "' requires an operand of type int but was given type " +
                AST::Types::toString(unaryasgn->operand()->typeInfo().type) +
                ".";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        break;
    }
    case AST::UnaryOpType::Chsign: {
        if (op->operand()->typeInfo().isArray &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error = "The operation '" +
                                AST::Types::toString(op->unaryOpType()) +
                                "' does not work with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        if (op->operand()->typeInfo().type != AST::Type::Int &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error =
                "Unary '" + AST::Types::toString(op->unaryOpType()) +
                "' requires an operand of type int but was given type " +
                AST::Types::toString(op->operand()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
        break;
    }
    case AST::UnaryOpType::Not: {
        if (op->operand()->typeInfo().isArray &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error = "The operation '" +
                                AST::Types::toString(op->unaryOpType()) +
                                "' does not work with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        if (op->operand()->typeInfo().type != AST::Type::Bool &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error =
                "Unary '" + AST::Types::toString(op->unaryOpType()) +
                "' requires an operand of type bool but was given type " +
                AST::Types::toString(op->operand()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
        break;
    }
    case AST::UnaryOpType::Random: {
        if (op->typeInfo().isArray && op->typeInfo().type.has_value()) {
            std::string error = "The operation '?' does not work with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        if (op->typeInfo().type != AST::Type::Int &&
            op->typeInfo().type.has_value()) {
            std::string error = "Unary '?' requires an operand of type int but "
                                "was given type " +
                                AST::Types::toString(op->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
        break;
    }
    case AST::UnaryOpType::Sizeof: {
        if (!op->operand()->typeInfo().isArray &&
            op->operand()->typeInfo().type.has_value()) {
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
            if (m_symbolTable[id->id()].isDeclared() &&
                m_symbolTable[id->id()].decl()->declType() ==
                    AST::DeclType::Func) {
                return;
            }

            m_symbolTable[id->id()].define(op->lineNumber());
        } else if (mut->expType() == AST::ExpType::Op) {
            auto *op = (AST::Exp::Op::Op *)mut;
            if (op->opType() == AST::OpType::Binary) {
                auto *id = (AST::Exp::Id *)((AST::Exp::Op::Binary *)op)->exp1();
                m_symbolTable[id->id()].define(op->lineNumber());
            }
        }

        if (op->exp1()->typeInfo().isArray != op->exp2()->typeInfo().isArray) {
            auto isArrayToString = [](bool b) {
                if (b) {
                    return std::string(" is an array");
                } else {
                    return std::string(" is not an array");
                }
            };

            std::string error =
                "'<-' requires both operands be arrays or not but lhs" +
                isArrayToString(op->exp1()->typeInfo().isArray) + " and rhs" +
                isArrayToString(op->exp2()->typeInfo().isArray) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        if (op->exp1()->typeInfo().type != op->exp2()->typeInfo().type &&
            op->exp1()->typeInfo().type.has_value() &&
            op->exp2()->typeInfo().type.has_value()) {
            std::string error =
                "'<-' requires operands of the same type but lhs is type " +
                AST::Types::toString(op->exp1()->typeInfo().type) +
                " and rhs is type " +
                AST::Types::toString(op->exp2()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
        break;
    }
    }
}

void SemanticsChecker::analyzeNode(AST::Exp::Op::Bool::Bool *op) {
    if (op->boolOpType() == AST::BoolOpType::And ||
        op->boolOpType() == AST::BoolOpType::Or) {

        if (op->exp1()->typeInfo().isArray ||
            op->exp2()->typeInfo().isArray &&
                op->exp1()->typeInfo().type.has_value() &&
                op->exp2()->typeInfo().type.has_value()) {
            std::string error = "The operation '" +
                                AST::Types::toString(op->boolOpType()) +
                                "' does not work with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        if (op->exp1()->typeInfo().type != AST::Type::Bool &&
            op->exp1()->typeInfo().type.has_value()) {
            std::string error =
                "'" + AST::Types::toString(op->boolOpType()) +
                "' requires operands of type bool but lhs is of type " +
                AST::Types::toString(op->exp1()->typeInfo().type) + ".";

            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        if (op->exp2()->typeInfo().type != AST::Type::Bool) {
            std::string error =
                "'" + AST::Types::toString(op->boolOpType()) +
                "' requires operands of type bool but rhs is of type " +
                AST::Types::toString(op->exp2()->typeInfo().type) + ".";

            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
    } else {
        if (op->exp1()->typeInfo().type != op->exp2()->typeInfo().type &&
            op->exp1()->typeInfo().type.has_value() &&
            op->exp2()->typeInfo().type.has_value()) {
            std::string error =
                "'" + AST::Types::toString(op->boolOpType()) +
                "' requires operands of the same type but lhs is "
                "type " +
                AST::Types::toString(op->exp1()->typeInfo().type) +
                " and rhs is type " +
                AST::Types::toString(op->exp2()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
    }
}

void SemanticsChecker::analyzeNode(AST::Stmt::Stmt *stmt) {
    switch (stmt->stmtType()) {
    case AST::StmtType::Compound: {
        break;
    }
    case AST::StmtType::For: {
        // auto *forNode = (AST::Stmt::For *)stmt;
        // auto *id = (AST::Exp::Id *)forNode->id();
        // m_symbolTable.removeImmediately(id->id());
        break;
    }
    case AST::StmtType::Return: {
        auto *returnNode = (AST::Stmt::Return *)stmt;
        if (!returnNode->children().empty()) {
            auto *returnExp = (AST::Exp::Exp *)returnNode->children().front();
            if (returnExp != nullptr && returnExp->typeInfo().isArray) {
                std::string error = "Cannot return an array.";
                m_messages[returnNode->lineNumber()].push_back(
                    {Message::Type::Error, error});
            }
        }
        break;
    }
    }
}