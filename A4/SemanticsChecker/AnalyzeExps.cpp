#include "../AST/AST.hpp"
#include "../SymbolTable/SymbolTable.hpp"
#include "SemanticsChecker.hpp"

#include <iostream>

void SemanticsChecker::analyzeNode(AST::Exp::Exp *exp) {

    switch (exp->expType()) {
    case AST::ExpType::Call: {
        auto *call = exp->cast<AST::Exp::Call *>();

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

            auto *decl =
                m_symbolTable[call->id()].decl()->cast<AST::Decl::Func *>();
            if (decl->numParms() > call->numArgs()) {
                std::string error = "Too few parameters passed for function '" +
                                    call->id() + "' declared on line " +
                                    std::to_string(decl->lineNumber()) + ".";

                m_messages[call->lineNumber()].push_back(
                    {Message::Type::Error, error});
            } else if (decl->numParms() < call->numArgs()) {
                std::string error =
                    "Too many parameters passed for function '" + call->id() +
                    "' declared on line " + std::to_string(decl->lineNumber()) +
                    ".";

                m_messages[call->lineNumber()].push_back(
                    {Message::Type::Error, error});
            } else {

                auto parms = decl->parmsVector();
                auto args = call->argsVector();

                for (int i = 0; i < decl->numParms(); i++) {

                    if (parms[i]->typeInfo().isArray &&
                        !args[i]->typeInfo().isArray) {

                        std::string error =
                            "Expecting array in parameter " +
                            std::to_string(i + 1) + " of call to '" +
                            call->id() + "' declared on line " +
                            std::to_string(decl->lineNumber()) + ".";

                        m_messages[call->lineNumber()].push_back(
                            {Message::Type::Error, error});
                    } else if (!parms[i]->typeInfo().isArray &&
                               args[i]->typeInfo().isArray) {
                        std::string error =
                            "Not expecting array in parameter " +
                            std::to_string(i + 1) + " of call to '" +
                            call->id() + "' declared on line " +
                            std::to_string(decl->lineNumber()) + ".";

                        m_messages[call->lineNumber()].push_back(
                            {Message::Type::Error, error});
                    }
                }
            }
        }

        break;
    }
    case AST::ExpType::Id: {
        auto *id = exp->cast<AST::Exp::Id *>();

        if (m_symbolTable[id->id()].isDeclared()) {
            id->typeInfo() = m_symbolTable[id->id()].decl()->typeInfo();

            if (m_symbolTable[id->id()].decl()->declType() ==
                AST::DeclType::Func) {

                std::string error =
                    "Cannot use function '" + id->id() + "' as a variable.";
                m_messages[id->lineNumber()].push_back(
                    {Message::Type::Error, error});
            }

        } else {
            std::string error = "Symbol '" + id->id() + "' is not declared.";
            m_messages[id->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        bool isUsed = true;
        if (id->hasAncestor(AST::StmtType::Range)) {
            auto *range = id->getClosestAncestor(AST::StmtType::Range)
                              ->cast<AST::Stmt::Range *>();

            if (range->parent() != nullptr) {
                auto *forstmt = range->parent()->cast<AST::Stmt::For *>();

                if (forstmt->id()->id() == id->id()) {
                    isUsed = false;
                }
            }
        }

        if (isUsed) {
            m_symbolTable[id->id()].use(id->lineNumber());
        }

        break;
    }
    case AST::ExpType::Op: {
        auto *op = exp->cast<AST::Exp::Op::Op *>();
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
        auto *binary = op->cast<AST::Exp::Op::Binary *>();

        if (binary->is(AST::BinaryOpType::Add) ||
            binary->is(AST::BinaryOpType::Div) ||
            binary->is(AST::BinaryOpType::Mod) ||
            binary->is(AST::BinaryOpType::Mul) ||
            binary->is(AST::BinaryOpType::Subtract)) {

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
                analyzeNode((AST::Exp::Op::Bool *)binary);
                break;
            }
            case AST::BinaryOpType::Div: {
                break;
            }
            case AST::BinaryOpType::Index: {

                auto *id = binary->exp1()->cast<AST::Exp::Id *>();
                if (!id->typeInfo().isArray) {
                    std::string error =
                        "Cannot index nonarray '" + id->id() + "'.";
                    m_messages[id->lineNumber()].push_back(
                        {Message::Type::Error, error});
                }

                auto *index = binary->exp2();
                if (index->expType() == AST::ExpType::Id) {
                    auto *indexId = index->cast<AST::Exp::Id *>();

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
        auto *unaryop = op->cast<AST::Exp::Op::Unary *>();
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
        auto *unaryasgn = op->cast<AST::Exp::Op::UnaryAsgn *>();

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
        if (op->operand()->typeInfo().isArray &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error = "The operation '?' does not work with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        if (op->operand()->typeInfo().type != AST::Type::Int &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error =
                "Unary '?' requires an operand of type int but "
                "was given type " +
                AST::Types::toString(op->operand()->typeInfo().type) + ".";
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

    if (!op->is(AST::AsgnType::Asgn)) {
        if (op->exp1()->typeInfo().type != AST::Type::Int &&
            op->exp1()->typeInfo().type.has_value()) {
            std::string error =
                "'" + AST::Types::toString(op->asgnType()) +
                "' requires operands of type int but lhs is of type " +
                AST::Types::toString(op->exp1()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        if (op->exp2()->typeInfo().type != AST::Type::Int &&
            op->exp2()->typeInfo().type.has_value()) {
            std::string error =
                "'" + AST::Types::toString(op->asgnType()) +
                "' requires operands of type int but rhs is of type " +
                AST::Types::toString(op->exp2()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
    }

    switch (op->asgnType()) {
    case AST::AsgnType::Asgn: {

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

void SemanticsChecker::analyzeNode(AST::Exp::Op::Bool *op) {
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

        if (op->exp1()->typeInfo().isArray != op->exp2()->typeInfo().isArray) {
            auto isArrayToString = [](bool b) {
                if (b) {
                    return std::string(" is an array");
                } else {
                    return std::string(" is not an array");
                }
            };
            std::string error =
                "'" + AST::Types::toString(op->boolOpType()) +
                "' requires both operands be arrays or not but lhs" +
                isArrayToString(op->exp1()->typeInfo().isArray) + " and rhs" +
                isArrayToString(op->exp2()->typeInfo().isArray) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
    }
}