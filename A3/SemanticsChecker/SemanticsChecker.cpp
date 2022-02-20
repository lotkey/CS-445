#include "SemanticsChecker.hpp"
#include "../AST/AST.hpp"
#include "../SymbolTable/SymbolTable.hpp"

SemanticsChecker::SemanticsChecker()
    : m_symbolTable(SymbolTable()), m_mainIsDefined(false) {}

const std::vector<std::string> &SemanticsChecker::errors() const {
    return m_errors;
}

const std::vector<std::string> &SemanticsChecker::warnings() const {
    return m_warnings;
}

const SymbolTable &SemanticsChecker::symbolTable() const {
    return m_symbolTable;
}

void SemanticsChecker::analyze(AST::Node *tree) {
    m_mainIsDefined = false;
    m_symbolTable = SymbolTable();
    m_errors.clear();
    analyzeTree(tree);

    if (!m_mainIsDefined) {
        std::string error =
            "ERROR(LINKER): A function named 'main()' must be defined.";
        m_errors.push_back(error);
    }

    for (const auto &[id, info] : m_varInfo) {
        if (!info.isUsed) {
            std::string warning =
                "WARNING(" + std::to_string(info.lineDeclared) +
                "): The variable '" + id + "' seems not to be used.\n";
            m_warnings.push_back(warning);
        } else if (info.isUsed && !info.isInitialized) {
            for (const auto &line : info.linesUsed) {
                std::string warning = "WARNING(" + std::to_string(line) +
                                      "): Variable '" + id +
                                      "' may be uninitialized when used here.";
                m_warnings.push_back(warning);
            }
        }
    }
}

void SemanticsChecker::analyzeTree(AST::Node *tree) {
    for (auto child : tree->children()) {
        analyzeTree(child);
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

        if (m_symbolTable[call->id()]->declType() != AST::DeclType::Func) {
            std::string error = "ERROR(" + std::to_string(call->lineNumber()) +
                                "): '" + call->id() +
                                "' is a simple variable and cannot be called.";
            m_errors.push_back(error);
        }

        break;
    case AST::ExpType::Id: {
        AST::Exp::Id *id = (AST::Exp::Id *)exp;

        if (!m_symbolTable.contains(id->id())) {
            std::string error = "ERROR(" + std::to_string(id->lineNumber()) +
                                "): Symbol '" + id->id() +
                                "' is not declared.\n";
            m_errors.push_back(error);
        }

        if (m_symbolTable[id->id()]->declType() == AST::DeclType::Func) {
            std::string error = "ERROR(" + std::to_string(id->lineNumber()) +
                                "): Cannot use function '" + id->id() +
                                "' as a variable.";
            m_errors.push_back(error);
        } else {
            m_varInfo[id->id()].isUsed = true;
            m_varInfo[id->id()].linesUsed.push_back(id->lineNumber());
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
        AST::Decl::Decl *originalSymbol = m_symbolTable[decl->id()];

        std::string error = "ERROR(" + std::to_string(decl->lineNumber()) +
                            "): Symbol '" + decl->id() +
                            "' is already declared at line " +
                            std::to_string(originalSymbol->lineNumber());

        m_errors.push_back(error);
    } else {
        m_symbolTable.add(decl);
    }

    switch (decl->declType()) {
    case AST::DeclType::Func: {
        if (decl->id() == "main") {
            m_mainIsDefined = true;
        }

        break;
    }
    case AST::DeclType::Parm: {
        if (m_varInfo.find(decl->id()) == m_varInfo.end()) {
            m_varInfo[decl->id()] = VarInfo();
            m_varInfo[decl->id()].lineDeclared = decl->lineNumber();
        }

        break;
    }
    case AST::DeclType::Var: {
        if (m_varInfo.find(decl->id()) == m_varInfo.end()) {
            m_varInfo[decl->id()] = VarInfo();
            m_varInfo[decl->id()].lineDeclared = decl->lineNumber();
        }

        break;
    }
    }
}

void SemanticsChecker::analyzeNode(AST::Stmt::Stmt *stmt) {}