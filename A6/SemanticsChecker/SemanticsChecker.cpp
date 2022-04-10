#include "SemanticsChecker.hpp"
#include "../AST/AST.hpp"
#include "../SymbolTable/SymbolTable.hpp"
#include "Message.hpp"

#include <iostream>

SemanticsChecker::SemanticsChecker() : m_mainIsDefined(false) {}

SemanticsChecker::SemanticsChecker(bool debug)
    : m_mainIsDefined(false), m_debug(debug) {}

const SymbolTable &SemanticsChecker::symbolTable() const {
    return m_symbolTable;
}

int SemanticsChecker::numErrors() const {
    return 0;
    // return Message::numErrors() + (!m_mainIsDefined - !m_analyzed);
}

int SemanticsChecker::numWarnings() const {
    // return Message::numWarnings();
    return 0;
}

void SemanticsChecker::enterScope() {
    /// Use function name as name for the scope
    if (m_scopeName.has_value()) {
        enterScope(m_scopeName.value());
        m_scopeName.reset();
    } else {
        enterScope({});
    }
}

void SemanticsChecker::enterScope(const std::optional<std::string> &name) {
    if (name.has_value()) {
        m_symbolTable.enter(name.value());
    } else {
        m_symbolTable.enter();
    }

    /// Add any saved function parameters to the scope
    /// Parameters are declared before the scope begins, but exist inside of the
    /// scope
    for (auto *parm = m_parms->cast<AST::Decl::Decl *>(); parm != nullptr;
         parm = parm->sibling()->cast<AST::Decl::Decl *>()) {

        if (m_symbolTable.containsImmediately(parm->id()) &&
            m_symbolTable[parm->id()].isDeclared()) {
            auto *originalSymbol = m_symbolTable[parm->id()].decl();

            Message::add(parm->lineNumber(), Message::Type::Error,
                         "Symbol '%s' is already declared at line %d.",
                         parm->id().c_str(), originalSymbol->lineNumber());

        } else {
            m_symbolTable.declare(parm->id(), parm);
        }
    }
    m_parms = nullptr;
}

void SemanticsChecker::checkTopScope() {
    auto symbols = m_symbolTable.getImmediateSymbols();

    for (const auto &[id, symbol] : symbols) {

        if (!symbol.isDeclared()) {
            continue;
        } else if (symbol.decl()->lineNumber() == AST::libraryLineNumber) {
            // library symbol
            continue;
        }

        if (!symbol.isUsed()) {

            std::string warning = "The ";

            if (symbol.decl()->is(AST::DeclType::Parm)) {
                warning += "parameter ";
            } else if (symbol.decl()->is(AST::DeclType::Func)) {
                if (symbol.decl()->cast<AST::Decl::Func *>()->id() == "main") {
                    continue;
                }
                warning += "function ";
            } else if (symbol.decl()->is(AST::DeclType::Var)) {
                warning += "variable ";
            }

            warning += "'" + id + "' seems not to be used.";
            Message::add(symbol.decl()->lineNumber(), Message::Type::Warning,
                         warning);
        }

        if (symbol.decl()->declType() == AST::DeclType::Var &&
            !symbol.decl()->isStatic() && m_symbolTable.depth() > 1) {

            if (!symbol.linesUsedBeforeDefined().empty()) {

                auto linenumber = symbol.linesUsedBeforeDefined().front();
                if (!symbol.isDefined() || linenumber <= symbol.lineDefined()) {
                    Message::add(
                        linenumber, Message::Type::Warning,
                        "Variable '%s' may be uninitialized when used here.",
                        id.c_str());
                }
            }
        }
    }
}

void SemanticsChecker::leaveScope() {
    checkTopScope();
    m_symbolTable.leave();
}

void SemanticsChecker::deduceTypeFromTable(AST::Node *node) {
    if (node == nullptr) {
        return;
    }

    if (node->is(AST::ExpType::Id)) {
        auto *id = node->cast<AST::Exp::Id *>();
        if (m_symbolTable[id->id()].isDeclared() &&
            m_symbolTable[id->id()].decl()->declType() != AST::DeclType::Func) {
            id->setIdOf(m_symbolTable[id->id()].decl());
            // id->setTypeInfo(m_symbolTable[id->id()].decl()->getTypeInfo());
        }

    } else if (node->is(AST::ExpType::Call)) {
        auto *call = node->cast<AST::Exp::Call *>();

        for (const auto &arg : call->argsVector()) {
            deduceTypeFromTable(arg);
        }

        if (m_symbolTable[call->id()].isDeclared() &&
            m_symbolTable[call->id()].decl()->declType() ==
                AST::DeclType::Func) {
            call->setTypeInfo(m_symbolTable[call->id()].decl()->getTypeInfo());
        }
    }
}

void SemanticsChecker::analyze(AST::Node *tree) {
    m_analyzed = true;
    m_mainIsDefined = false;
    m_symbolTable = SymbolTable(m_debug);

    auto *ioLibrary = AST::ioLibraryTree();
    analyzeTree(ioLibrary);

    analyzeTree(tree);
    // Check global scope
    checkTopScope();
    if (!m_mainIsDefined) {
        Message::addStringMessageBefore(
            "LINKER", Message::Type::Error,
            "A function named 'main' with no parameters must be defined.");
    }
    delete ioLibrary;
}

void SemanticsChecker::analyzeTree(AST::Node *tree) {
    if (tree == nullptr) {
        return;
    }

    /// This is where nodes should be analyzed if they are declarations,
    /// uses, or definitions. They will be analyzed before their children.
    /// Set nodeWasAnalyzed to make sure they do not get analyzed twice.
    bool nodeWasAnalyzed = true;
    if (tree->is(AST::NodeType::Decl)) {
        auto *decl = tree->cast<AST::Decl::Decl *>();
        if (decl->is(AST::DeclType::Var) &&
            decl->cast<AST::Decl::Var *>()->isInitialized()) {
            auto *var = decl->cast<AST::Decl::Var *>();
            deduceTypeFromTable(var->initValue());
        }

        analyzeNode(tree->cast<AST::Decl::Decl *>());
    } else {
        nodeWasAnalyzed = false;
    }

    deduceTypeFromTable(tree);

    if (tree->is(AST::AsgnType::Asgn)) {
        analyzeDefinitions(tree->cast<AST::Exp::Op::Asgn *>());
    }

    /// Entering scopes
    /// Compound statements define scopes, but they can share the same scope
    /// as a for scope.
    if (tree->is(AST::StmtType::Compound) &&
        !(tree->parent() != nullptr &&
          tree->parent()->is(AST::StmtType::For))) {
        if (m_scopeName.has_value()) {
            enterScope(m_scopeName.value());
            m_scopeName.reset();
        } else {
            enterScope("compound");
        }
    } else if (tree->is(AST::StmtType::For)) {
        enterScope("for");
    }

    /// Analyze children of the node
    for (auto &child : tree->children()) {
        if (child) {
            analyzeTree(child);
        }
    }

    /// If the node wasn't analyzed, then the children were analyzed first
    if (!nodeWasAnalyzed) {
        switch (tree->nodeType()) {
        case AST::NodeType::Decl: {
            break;
        }
        case AST::NodeType::Stmt: {
            auto *stmt = tree->cast<AST::Stmt::Stmt *>();
            analyzeNode(stmt);
            break;
        }
        case AST::NodeType::Exp: {
            auto *exp = tree->cast<AST::Exp::Exp *>();
            analyzeNode(exp);
            break;
        }
        default:
            break;
        }
    }

    /// Handle exiting scopes
    if (tree->is(AST::StmtType::Compound) &&
        !(tree->parent() != nullptr &&
          tree->parent()->is(AST::StmtType::For))) {
        leaveScope();
    } else if (tree->is(AST::StmtType::For)) {
        leaveScope();
    }

    /// Analyze siblings
    if (tree->hasSibling()) {
        analyzeTree(tree->sibling());
    }
}

void SemanticsChecker::analyzeDefinitions(AST::Exp::Op::Asgn *op) {
    if (op->exp1()->is(AST::ExpType::Id)) {
        auto *id1 = op->exp1()->cast<AST::Exp::Id *>();

        bool shouldDefine = true;

        auto isSameId = [id1](AST::Node *node) {
            return node && node->is(AST::ExpType::Id) &&
                   node->cast<AST::Exp::Id *>()->id() == id1->id();
        };

        if (isSameId(op->exp2())) {
            m_symbolTable[id1->id()].use(op->lineNumber());
        } else if (op->exp2()->hasDescendantWhere(isSameId)) {
            m_symbolTable[id1->id()].use(op->lineNumber());
        }

        bool b1 =
            m_symbolTable[id1->id()].isDeclared() &&
            m_symbolTable[id1->id()].decl()->declType() == AST::DeclType::Func;

        if (m_symbolTable[id1->id()].isDeclared() &&
            m_symbolTable[id1->id()].decl()->declType() ==
                AST::DeclType::Func) {
            shouldDefine = false;
        } else if (op->exp2() && op->exp2()->cast<AST::Node *>()->is(
                                     AST::BinaryOpType::Index)) {
            auto *indexOp = op->exp2()->cast<AST::Exp::Op::Binary *>();
            if (indexOp->exp1()->is(AST::ExpType::Id) &&
                indexOp->exp1()->cast<AST::Exp::Id *>()->id() == id1->id()) {
                shouldDefine = false;
            }
        }

        if (shouldDefine) {
            m_symbolTable[id1->id()].define(op->lineNumber());
        }

    } else if (op->exp1()->cast<AST::Node *>()->is(AST::BinaryOpType::Index)) {

        auto *indexOp = op->exp1()->cast<AST::Exp::Op::Binary *>();
        if (indexOp->exp1()->is(AST::ExpType::Id)) {
            bool shouldDefine = true;

            auto *id1 = indexOp->exp1()->cast<AST::Exp::Id *>();
            if (m_symbolTable[id1->id()].isDeclared() &&
                m_symbolTable[id1->id()].decl()->declType() ==
                    AST::DeclType::Func) {
                shouldDefine = false;
            } else if (op->exp2()->is(AST::ExpType::Id) &&
                       op->exp2()->cast<AST::Exp::Id *>()->id() == id1->id()) {
                shouldDefine = false;
            } else if (op->exp2()->cast<AST::Node *>()->is(
                           AST::BinaryOpType::Index)) {
                auto *indexOp = op->exp2()->cast<AST::Exp::Op::Binary *>();
                if (indexOp->exp1()->is(AST::ExpType::Id) &&
                    indexOp->exp1()->cast<AST::Exp::Id *>()->id() ==
                        id1->id()) {
                    shouldDefine = false;
                }
            }

            if (shouldDefine) {
                m_symbolTable[id1->id()].define(op->lineNumber());
            }
        }
    }
}