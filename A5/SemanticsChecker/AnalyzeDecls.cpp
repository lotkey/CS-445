#include "../AST/AST.hpp"
#include "../SymbolTable/SymbolTable.hpp"
#include "SemanticsChecker.hpp"

#include <iostream>

void SemanticsChecker::analyzeNode(AST::Decl::Decl *decl) {
    // Check to see if it's defining main()
    if (decl->is(AST::DeclType::Func)) {
        m_scopeName = decl->id();
        auto *func = decl->cast<AST::Decl::Func *>();

        m_parms = func->parms();

        if (func->id() == "main") {
            if (!func->hasParms() && func->hasType() &&
                (func->type() == AST::Type::Void ||
                 func->type() == AST::Type::Int) &&
                !m_symbolTable["main"].isDeclared()) {
                m_mainIsDefined = true;
            }
        }

        if (func->hasType() && func->type() != AST::Type::Void &&
            !func->hasDescendantOfType(AST::StmtType::Return)) {

            Message::add(func->lineNumber(), Message::Type::Warning,
                         "Expecting to return type %s but function '%s' has no "
                         "return statement.",
                         AST::Types::toString(func->type()).c_str(),
                         func->id().c_str());
        }
    }

    // If it's a parameter declaration, that is handled by enterScope()
    if (!decl->is(AST::DeclType::Parm)) {

        if (m_symbolTable.containsImmediately(decl->id())) {
            if (m_symbolTable[decl->id()].isDeclared()) {

                auto *originalSymbol = m_symbolTable[decl->id()].decl();

                Message::add(decl->lineNumber(), Message::Type::Error,
                             "Symbol '%s' is already declared at line %d.",
                             decl->id().c_str(), originalSymbol->lineNumber());
            } else {

                if (decl->is(AST::DeclType::Var)) {
                    auto *var = decl->cast<AST::Decl::Var *>();
                    if (var->isInitialized()) {
                        auto isSameVar = [var](AST::Node *node) {
                            return node->is(AST::ExpType::Id) &&
                                   node->cast<AST::Exp::Id *>()->id() ==
                                       var->id();
                        };

                        if (!m_symbolTable[var->id()].isDeclared()) {
                            if (isSameVar(var->initValue())) {

                                Message::add(var->initValue()->lineNumber(),
                                             Message::Type::Error,
                                             "Symbol '%s' is not declared.",
                                             var->id().c_str());
                            } else if (var->initValue()->hasDescendantWhere(
                                           isSameVar)) {
                                auto descendants =
                                    var->initValue()->getDescendantsWhere(
                                        isSameVar);

                                Message::add(descendants.front()->lineNumber(),
                                             Message::Type::Error,
                                             "Symbol '%s' is not declared.",
                                             var->id().c_str());
                            }
                        }
                    }
                }

                m_symbolTable.declare(decl->id(), decl);
            }
        } else {
            if (decl->is(AST::DeclType::Var)) {
                auto *var = decl->cast<AST::Decl::Var *>();
                if (var->isInitialized()) {
                    auto isSameVar = [var](AST::Node *node) {
                        return node->is(AST::ExpType::Id) &&
                               node->cast<AST::Exp::Id *>()->id() == var->id();
                    };

                    if (!m_symbolTable[var->id()].isDeclared()) {
                        if (isSameVar(var->initValue())) {

                            Message::add(var->initValue()->lineNumber(),
                                         Message::Type::Error,
                                         "Symbol '%s' is not declared.",
                                         var->id().c_str());
                        } else if (var->initValue()->hasDescendantWhere(
                                       isSameVar)) {

                            auto descendants =
                                var->initValue()->getDescendantsWhere(
                                    isSameVar);

                            Message::add(descendants.front()->lineNumber(),
                                         Message::Type::Error,
                                         "Symbol '%s' is not declared.",
                                         var->id().c_str());
                        }
                    }
                }
            }
            m_symbolTable.declare(decl->id(), decl);
        }
    }

    if (decl->is(AST::DeclType::Var)) {
        auto *var = decl->cast<AST::Decl::Var *>();

        if (var->isInitialized()) {
            if (var->initValue()->is(AST::ExpType::Op)) {
                var->initValue()->cast<AST::Exp::Op::Op *>()->deduceType();
            }

            if (!var->initValue()->isConst()) {

                Message::add(var->lineNumber(), Message::Type::Error,
                             "Initializer for variable '%s' is not a constant "
                             "expression.",
                             var->id().c_str());
            }

            if (var->initValue()->hasType() && var->hasType() &&
                var->initValue()->type() != var->type()) {

                Message::add(
                    var->lineNumber(), Message::Type::Error,
                    "Initializer for variable '%s' of type %s is of type %s.",
                    var->id().c_str(),
                    AST::Types::toString(var->type()).c_str(),
                    AST::Types::toString(var->initValue()->type()).c_str());
            }

            if (var->initValue()->isArray() != var->isArray()) {
                auto isArrayToString = [](bool b) {
                    if (b) {
                        return std::string("is an array");
                    } else {
                        return std::string("is not an array");
                    }
                };

                Message::add(
                    var->lineNumber(), Message::Type::Error,
                    "Initializer for variable '%s' requires both operands be "
                    "arrays or not but variable %s and rhs %s.",
                    var->id().c_str(), isArrayToString(var->isArray()).c_str(),
                    isArrayToString(var->initValue()->isArray()).c_str());
            }

            m_symbolTable[decl->id()].define(var->initValue()->lineNumber());
        } else if (decl->parent() != nullptr &&
                   decl->parent()->is(AST::StmtType::For)) {

            auto *forParent = var->parent()->cast<AST::Stmt::For *>();
            auto *range = forParent->range();
            if (range) {
                m_symbolTable[decl->id()].define(
                    forParent->range()->from()->lineNumber());
                m_symbolTable[decl->id()].setIterator(true);
            }
        }
    }
}