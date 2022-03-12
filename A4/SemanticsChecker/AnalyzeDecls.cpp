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
            if (!func->hasParms() &&
                (func->typeInfo().type.value() == AST::Type::Void ||
                 func->typeInfo().type.value() == AST::Type::Int)) {
                m_mainIsDefined = true;
            } else {
                m_mainIsDefined = false;
            }
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
            }
        } else {
            m_symbolTable.declare(decl->id(), decl);
        }
    }

    if (decl->is(AST::DeclType::Var)) {
        auto *var = decl->cast<AST::Decl::Var *>();

        if (var->isInitialized()) {
            if (var->initValue() != nullptr &&
                var->initValue()->is(AST::ExpType::Op)) {
                var->initValue()->cast<AST::Exp::Op::Op *>()->deduceType();
            }

            if (!var->initValue()->typeInfo().isConst) {
                std::string error = "Initializer for variable '" + var->id() +
                                    "' is not a constant expression.";
                m_messages[var->lineNumber()].push_back(
                    {Message::Type::Error, error});
            }

            if (var->initValue()->typeInfo().type.has_value() &&
                var->typeInfo().type.has_value() &&
                var->initValue()->typeInfo().type.value() !=
                    var->typeInfo().type.value()) {
                std::string error =
                    "Initializer for variable '" + var->id() + "' of type " +
                    AST::Types::toString(var->typeInfo().type) +
                    " is of type " +
                    AST::Types::toString(var->initValue()->typeInfo().type);
                m_messages[var->lineNumber()].push_back(
                    {Message::Type::Error, error});
            }

            if (var->initValue()->typeInfo().isArray !=
                var->typeInfo().isArray) {
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
                    isArrayToString(var->typeInfo().isArray) + " and rhs" +
                    isArrayToString(var->initValue()->typeInfo().isArray) + ".";
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