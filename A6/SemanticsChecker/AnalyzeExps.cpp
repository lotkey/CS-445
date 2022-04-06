#include "../AST/AST.hpp"
#include "../SymbolTable/SymbolTable.hpp"
#include "SemanticsChecker.hpp"

#include <iostream>

void SemanticsChecker::analyzeNode(AST::Exp::Exp *exp) {

    switch (exp->expType()) {
    case AST::ExpType::Call: {
        auto *call = exp->cast<AST::Exp::Call *>();

        if (!m_symbolTable[call->id()].isDeclared()) {

            Message::add(call->lineNumber(), Message::Type::Error,
                         "Symbol '%s' is not declared.", call->id().c_str());
        } else {

            m_symbolTable[call->id()].use(call->lineNumber());

            if (m_symbolTable[call->id()].decl()->declType() !=
                AST::DeclType::Func) {

                Message::add(call->lineNumber(), Message::Type::Error,
                             "'%s' is a simple variable and cannot be called.",
                             call->id().c_str());
            } else {
                call->setTypeInfo(
                    m_symbolTable[call->id()].decl()->getTypeInfo());

                auto *decl =
                    m_symbolTable[call->id()].decl()->cast<AST::Decl::Func *>();
                if (decl->numParms() > call->numArgs()) {

                    Message::add(call->lineNumber(), Message::Type::Error,
                                 "Too few parameters passed for function '%s' "
                                 "declared on line %d.",
                                 call->id().c_str(), decl->lineNumber());
                } else if (decl->numParms() < call->numArgs()) {

                    Message::add(call->lineNumber(), Message::Type::Error,
                                 "Too many parameters passed for function '%s' "
                                 "declared on line %d.",
                                 call->id().c_str(), decl->lineNumber());
                }

                auto parms = decl->parmsVector();
                auto args = call->argsVector();

                for (int i = 0; i < decl->numParms() && i < call->numArgs();
                     i++) {

                    if (parms[i]->isArray() && !args[i]->isArray()) {

                        Message::add(call->lineNumber(), Message::Type::Error,
                                     "Expecting array in parameter %d of call "
                                     "to '%s' declared on line %d.",
                                     i + 1, call->id().c_str(),
                                     decl->lineNumber());
                    } else if (!parms[i]->isArray() && args[i]->isArray()) {

                        Message::add(call->lineNumber(), Message::Type::Error,
                                     "Not expecting array in parameter %d of "
                                     "call to '%s' declared on line %d.",
                                     i + 1, call->id().c_str(),
                                     decl->lineNumber());
                    }

                    if (parms[i]->hasType() && args[i]->hasType() &&
                        parms[i]->type() != args[i]->type()) {

                        Message::add(
                            call->lineNumber(), Message::Type::Error,
                            "Expecting type %s in parameter %d of call to '%s' "
                            "declared on line %d but got type %s.",
                            AST::Types::toString(parms[i]->type()).c_str(),
                            i + 1, call->id().c_str(), decl->lineNumber(),
                            AST::Types::toString(args[i]->type()).c_str());
                    }
                }
            }
        }

        break;
    }
    case AST::ExpType::Id: {
        auto *id = exp->cast<AST::Exp::Id *>();
        bool isUsed = true;

        if (id->hasAncestorOfType(AST::DeclType::Var)) {
            auto *decl = id->getClosestAncestorOfType(AST::DeclType::Var)
                             ->cast<AST::Decl::Var *>();
            if (decl->id() == id->id()) {
                isUsed = false;
            }
        }

        if (m_symbolTable[id->id()].isDeclared()) {

            if (m_symbolTable[id->id()].decl()->declType() ==
                AST::DeclType::Func) {

                Message::add(id->lineNumber(), Message::Type::Error,
                             "Cannot use function '%s' as a variable.",
                             id->id().c_str());
            } else {
                id->setTypeInfo(m_symbolTable[id->id()].decl()->getTypeInfo());
            }

        } else {

            Message::add(id->lineNumber(), Message::Type::Error,
                         "Symbol '%s' is not declared.", id->id().c_str());
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

    if (op == nullptr) {
        return;
    }

    op->deduceType();

    switch (op->opType()) {
    case AST::OpType::Binary: {
        auto *binary = op->cast<AST::Exp::Op::Binary *>();

        if (!(binary->exp1() && binary->exp2())) {
            return;
        }

        if (binary->is(AST::BinaryOpType::Add) ||
            binary->is(AST::BinaryOpType::Div) ||
            binary->is(AST::BinaryOpType::Mod) ||
            binary->is(AST::BinaryOpType::Mul) ||
            binary->is(AST::BinaryOpType::Subtract)) {

            if (binary->exp1()->isArray() || binary->exp2()->isArray() &&
                                                 binary->exp1()->hasType() &&
                                                 binary->exp2()->hasType()) {

                Message::add(
                    binary->lineNumber(), Message::Type::Error,
                    "The operation '%s' does not work with arrays.",
                    AST::Types::toString(binary->binaryOpType()).c_str());
            }

            if (binary->exp1()->hasType() &&
                binary->exp1()->type() != AST::Type::Int) {

                Message::add(
                    binary->lineNumber(), Message::Type::Error,
                    "'%s' requires operands of type int but lhs is of type %s.",
                    AST::Types::toString(binary->binaryOpType()).c_str(),
                    AST::Types::toString(binary->exp1()->type()).c_str());
            }

            if (binary->exp2()->hasType() &&
                binary->exp2()->type() != AST::Type::Int) {

                Message::add(
                    binary->lineNumber(), Message::Type::Error,
                    "'%s' requires operands of type int but rhs is of type %s.",
                    AST::Types::toString(binary->binaryOpType()).c_str(),
                    AST::Types::toString(binary->exp2()->type()).c_str());
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
                if (!id->isArray()) {

                    Message::add(id->lineNumber(), Message::Type::Error,
                                 "Cannot index nonarray '%s'.",
                                 id->id().c_str());
                }

                auto *index = binary->exp2();
                if (index && index->expType() == AST::ExpType::Id) {
                    auto *indexId = index->cast<AST::Exp::Id *>();

                    if (m_symbolTable[indexId->id()].isDeclared() &&
                        m_symbolTable[indexId->id()].decl()->isArray()) {

                        Message::add(binary->lineNumber(), Message::Type::Error,
                                     "Array index is the unindexed array '%s'.",
                                     indexId->id().c_str());
                    }
                }

                op->setTypeInfo(id->getTypeInfo());
                op->setIsArray(false);

                if (binary->exp2() && binary->exp2()->hasType() &&
                    binary->exp2()->type() != AST::Type::Int) {

                    Message::add(
                        binary->lineNumber(), Message::Type::Error,
                        "Array '%s' should be indexed by type int but got type "
                        "%s.",
                        id->id().c_str(),
                        AST::Types::toString(binary->exp2()->type()).c_str());
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
    if (!(op && op->operand())) {
        return;
    }

    switch (op->unaryOpType()) {
    case AST::UnaryOpType::Asgn: {
        auto *unaryasgn = op->cast<AST::Exp::Op::UnaryAsgn *>();

        if (unaryasgn->operand()->hasType() &&
            unaryasgn->operand()->isArray()) {

            Message::add(
                op->lineNumber(), Message::Type::Error,
                "The operation '%s' does not work with arrays.",
                AST::Types::toString(unaryasgn->unaryAsgnType()).c_str());
        }

        if (unaryasgn->operand()->hasType() &&
            unaryasgn->operand()->type() != AST::Type::Int) {

            Message::add(
                op->lineNumber(), Message::Type::Error,
                "Unary '%s' requires an operand of type int but was given type "
                "%s.",
                AST::Types::toString(unaryasgn->unaryAsgnType()).c_str(),
                AST::Types::toString(unaryasgn->operand()->type()).c_str());
        }

        break;
    }
    case AST::UnaryOpType::Chsign: {
        if (op->operand()->isArray() && op->operand()->hasType()) {

            Message::add(op->lineNumber(), Message::Type::Error,
                         "The operation '%s' does not work with arrays.",
                         AST::Types::toString(op->unaryOpType()).c_str());
        }

        if (op->operand()->hasType() &&
            op->operand()->type() != AST::Type::Int) {

            Message::add(op->lineNumber(), Message::Type::Error,
                         "Unary '%s' requires an operand of type int but was "
                         "given type %s.",
                         AST::Types::toString(op->unaryOpType()).c_str(),
                         AST::Types::toString(op->operand()->type()).c_str());
        }
        break;
    }
    case AST::UnaryOpType::Not: {
        if (op->operand()->hasType() && op->operand()->isArray()) {

            Message::add(op->lineNumber(), Message::Type::Error,
                         "The operation '%s' does not work with arrays.",
                         AST::Types::toString(op->unaryOpType()).c_str());
        }

        if (op->operand()->hasType() &&
            op->operand()->type() != AST::Type::Bool) {

            Message::add(op->lineNumber(), Message::Type::Error,
                         "Unary '%s' requires an operand of type bool but was "
                         "given type %s.",
                         AST::Types::toString(op->unaryOpType()).c_str(),
                         AST::Types::toString(op->operand()->type()).c_str());
        }
        break;
    }
    case AST::UnaryOpType::Random: {
        if (op->operand()->hasType() && op->operand()->isArray()) {

            Message::add(op->lineNumber(), Message::Type::Error,
                         "The operation '?' does not work with arrays.");
        }

        if (op->operand()->hasType() &&
            op->operand()->type() != AST::Type::Int) {

            Message::add(op->lineNumber(), Message::Type::Error,
                         "Unary '?' requires an operand of type int but was "
                         "given type %s.",
                         AST::Types::toString(op->operand()->type()).c_str());
        }
        break;
    }
    case AST::UnaryOpType::Sizeof: {
        if (op->operand()->hasType() && !op->operand()->isArray()) {

            Message::add(op->lineNumber(), Message::Type::Error,
                         "The operation 'sizeof' only works with arrays.");
        }
        break;
    }
    }
}

void SemanticsChecker::analyzeNode(AST::Exp::Op::Asgn *op) {
    if (!op || !(op->exp1() && op->exp2())) {
        return;
    }

    if (!op->is(AST::AsgnType::Asgn)) {
        if (op->exp1()->hasType() && op->exp1()->type() != AST::Type::Int) {

            Message::add(
                op->lineNumber(), Message::Type::Error,
                "'%s' requires operands of type int but lhs is of type %s.",
                AST::Types::toString(op->asgnType()).c_str(),
                AST::Types::toString(op->exp1()->type()).c_str());
        }

        if (op->exp2()->hasType() && op->exp2()->type() != AST::Type::Int) {

            Message::add(
                op->lineNumber(), Message::Type::Error,
                "'%s' requires operands of type int but rhs is of type %s.",
                AST::Types::toString(op->asgnType()).c_str(),
                AST::Types::toString(op->exp2()->type()).c_str());
        }
    }

    switch (op->asgnType()) {
    case AST::AsgnType::Asgn: {

        if (op->exp1()->isArray() != op->exp2()->isArray()) {
            auto isArrayToString = [](bool b) {
                if (b) {
                    return std::string("is an array");
                } else {
                    return std::string("is not an array");
                }
            };

            Message::add(op->lineNumber(), Message::Type::Error,
                         "'<-' requires both operands be arrays or not but lhs "
                         "%s and rhs %s.",
                         isArrayToString(op->exp1()->isArray()).c_str(),
                         isArrayToString(op->exp2()->isArray()).c_str());
        }

        if (op->exp1()->hasType() && op->exp2()->hasType() &&
            op->exp1()->type() != op->exp2()->type()) {

            Message::add(op->lineNumber(), Message::Type::Error,
                         "'<-' requires operands of the same type but lhs is "
                         "type %s and rhs is type %s.",
                         AST::Types::toString(op->exp1()->type()).c_str(),
                         AST::Types::toString(op->exp2()->type()).c_str());
        }
        break;
    }
    }
}

void SemanticsChecker::analyzeNode(AST::Exp::Op::Bool *op) {
    if (op->boolOpType() == AST::BoolOpType::And ||
        op->boolOpType() == AST::BoolOpType::Or) {

        if (op->exp1()->isArray() || op->exp2()->isArray() &&
                                         op->exp1()->hasType() &&
                                         op->exp2()->hasType()) {

            Message::add(op->lineNumber(), Message::Type::Error,
                         "The operation '%s' does not work with arrays.",
                         AST::Types::toString(op->boolOpType()).c_str());
        }

        if (op->exp1()->hasType() && op->exp1()->type() != AST::Type::Bool) {

            Message::add(
                op->lineNumber(), Message::Type::Error,
                "'%s' requires operands of type bool but lhs is of type %s.",
                AST::Types::toString(op->boolOpType()).c_str(),
                AST::Types::toString(op->exp1()->type()).c_str());
        }

        if (op->exp2()->hasType() && op->exp2()->type() != AST::Type::Bool) {

            Message::add(
                op->lineNumber(), Message::Type::Error,
                "'%s' requires operands of type bool but rhs is of type %s.",
                AST::Types::toString(op->boolOpType()).c_str(),
                AST::Types::toString(op->exp2()->type()).c_str());
        }
    } else {
        if (op->exp1()->hasType() && op->exp2()->hasType() &&
            op->exp1()->type() != op->exp2()->type()) {

            Message::add(op->lineNumber(), Message::Type::Error,
                         "'%s' requires operands of the same type but lhs is "
                         "type %s and rhs is type %s.",
                         AST::Types::toString(op->boolOpType()).c_str(),
                         AST::Types::toString(op->exp1()->type()).c_str(),
                         AST::Types::toString(op->exp2()->type()).c_str());
        }

        if (op->exp1()->isArray() != op->exp2()->isArray()) {
            auto isArrayToString = [](bool b) {
                if (b) {
                    return std::string("is an array");
                } else {
                    return std::string("is not an array");
                }
            };

            Message::add(op->lineNumber(), Message::Type::Error,
                         "'%s' requires both operands be arrays or not but lhs "
                         "%s and rhs %s.",
                         AST::Types::toString(op->boolOpType()).c_str(),
                         isArrayToString(op->exp1()->isArray()).c_str(),
                         isArrayToString(op->exp2()->isArray()).c_str());
        }
    }
}