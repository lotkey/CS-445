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
            std::string warning = "Expecting to return type " +
                                  AST::Types::toString(func->type()) +
                                  " but function '" + func->id() +
                                  "' has no return statement.";

            m_messages[func->lineNumber()].push_back(
                {Message::Type::Warning, warning});
        }
    }

    // If it's a parameter declaration, that is handled by enterScope()
    if (!decl->is(AST::DeclType::Parm)) {

        if (m_symbolTable.containsImmediately(decl->id())) {
            if (m_symbolTable[decl->id()].isDeclared()) {

                auto *originalSymbol = m_symbolTable[decl->id()].decl();
                std::string error =
                    "Symbol '" + decl->id() + "' is already declared at line " +
                    std::to_string(originalSymbol->lineNumber()) + ".";

                m_messages[decl->lineNumber()].push_back(
                    {Message::Type::Error, error});
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
                                std::string error = "Symbol '" + var->id() +
                                                    "' is not declared.";
                                m_messages[var->initValue()->lineNumber()]
                                    .push_back({Message::Type::Error, error});
                            } else if (var->initValue()->hasDescendantWhere(
                                           isSameVar)) {
                                auto descendants =
                                    var->initValue()->getDescendantsWhere(
                                        isSameVar);
                                std::string error = "Symbol '" + var->id() +
                                                    "' is not declared.";
                                m_messages[descendants.front()->lineNumber()]
                                    .push_back({Message::Type::Error, error});
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
                            std::string error =
                                "Symbol '" + var->id() + "' is not declared.";
                            m_messages[var->initValue()->lineNumber()]
                                .push_back({Message::Type::Error, error});
                        } else if (var->initValue()->hasDescendantWhere(
                                       isSameVar)) {
                            auto descendants =
                                var->initValue()->getDescendantsWhere(
                                    isSameVar);
                            std::string error =
                                "Symbol '" + var->id() + "' is not declared.";
                            m_messages[descendants.front()->lineNumber()]
                                .push_back({Message::Type::Error, error});
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
                std::string error = "Initializer for variable '" + var->id() +
                                    "' is not a constant expression.";
                m_messages[var->lineNumber()].push_back(
                    {Message::Type::Error, error});
            }

            if (var->initValue()->hasType() && var->hasType() &&
                var->initValue()->type() != var->type()) {
                std::string error =
                    "Initializer for variable '" + var->id() + "' of type " +
                    AST::Types::toString(var->type()) + " is of type " +
                    AST::Types::toString(var->initValue()->type());
                m_messages[var->lineNumber()].push_back(
                    {Message::Type::Error, error});
            }

            if (var->initValue()->isArray() != var->isArray()) {
                auto isArrayToString = [](bool b) {
                    if (b) {
                        return std::string(" is an array");
                    } else {
                        return std::string(" is not an array");
                    }
                };

                std::string error =
                    "Initializer for variable '" + var->id() +
                    "' requires both operands be arrays or not but variable" +
                    isArrayToString(var->isArray()) + " and rhs" +
                    isArrayToString(var->initValue()->isArray()) + ".";
                m_messages[var->lineNumber()].push_back(
                    {Message::Type::Error, error});
            }

            m_symbolTable[decl->id()].define(var->initValue()->lineNumber());
        } else if (decl->parent() != nullptr &&
                   decl->parent()->is(AST::StmtType::For)) {

            auto *forParent = var->parent()->cast<AST::Stmt::For *>();
            m_symbolTable[decl->id()].define(
                forParent->range()->from()->lineNumber());
            m_symbolTable[decl->id()].setIterator(true);
        }
    }
}