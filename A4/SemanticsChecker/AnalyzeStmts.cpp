#include "../AST/AST.hpp"
#include "../SymbolTable/SymbolTable.hpp"
#include "SemanticsChecker.hpp"

#include <iostream>

void SemanticsChecker::analyzeNode(AST::Stmt::Stmt *stmt) {
    switch (stmt->stmtType()) {
    case AST::StmtType::Compound: {
        break;
    }
    case AST::StmtType::For: {
        break;
    }
    case AST::StmtType::Return: {
        auto *returnNode = stmt->cast<AST::Stmt::Return *>();
        if (returnNode->exp() != nullptr && returnNode->exp()->isArray()) {
            std::string error = "Cannot return an array.";
            m_messages[returnNode->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        auto *functionParent =
            returnNode->getClosestAncestor(AST::DeclType::Func)
                ->cast<AST::Decl::Func *>();

        if (functionParent != nullptr && functionParent->hasType()) {
            if (functionParent->type() == AST::Type::Void &&
                returnNode->exp() != nullptr) {

                std::string error =
                    "Function '" + functionParent->id() + "' at line " +
                    std::to_string(functionParent->lineNumber()) +
                    " is expecting no return value, but return has a "
                    "value.";

                m_messages[returnNode->lineNumber()].push_back(
                    {Message::Type::Error, error});

            } else if (functionParent->type() != AST::Type::Void &&
                       returnNode->exp() == nullptr) {

                std::string error =
                    "Function '" + functionParent->id() + "' at line " +
                    std::to_string(functionParent->lineNumber()) +
                    " is expecting to return type " +
                    AST::Types::toString(functionParent->type()) +
                    " but return has no value.";

                m_messages[returnNode->lineNumber()].push_back(
                    {Message::Type::Error, error});

            } else if (returnNode->exp() != nullptr &&
                       returnNode->exp()->hasType() &&
                       functionParent->type() != returnNode->exp()->type()) {

                std::string error =
                    "Function '" + functionParent->id() + "' at line " +
                    std::to_string(functionParent->lineNumber()) +
                    " is expecting to return type " +
                    AST::Types::toString(functionParent->type()) +
                    " but returns type " +
                    AST::Types::toString(returnNode->exp()->type()) + ".";

                m_messages[returnNode->lineNumber()].push_back(
                    {Message::Type::Error, error});
            }
        }

        break;
    }
    case AST::StmtType::Range: {
        auto *range = stmt->cast<AST::Stmt::Range *>();
        std::vector<AST::Exp::Exp *> rangeChildren = {range->from(),
                                                      range->to(), range->by()};

        for (int i = 0; i < rangeChildren.size(); i++) {
            if (rangeChildren[i] != nullptr) {
                if (rangeChildren[i]->isArray()) {
                    std::string error = "Cannot use array in position " +
                                        std::to_string(i + 1) +
                                        " in range of for statement.";
                    m_messages[range->lineNumber()].push_back(
                        {Message::Type::Error, error});
                }

                if (rangeChildren[i]->hasType() &&
                    rangeChildren[i]->type() != AST::Type::Int) {
                    std::string error =
                        "Expecting type int in position " +
                        std::to_string(i + 1) +
                        " in range of for statement but got type " +
                        AST::Types::toString(rangeChildren[i]->type()) + ".";
                    m_messages[range->lineNumber()].push_back(
                        {Message::Type::Error, error});
                }
            }
        }

        break;
    }
    case AST::StmtType::Break: {
        if (!(stmt->hasAncestor(AST::StmtType::For) ||
              stmt->hasAncestor(AST::StmtType::While))) {
            std::string error =
                "Cannot have a break statement outside of loop.";
            m_messages[stmt->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
        break;
    }
    case AST::StmtType::While: {
        auto *whilestmt = stmt->cast<AST::Stmt::While *>();

        if (whilestmt->exp()->isArray()) {
            std::string error =
                "Cannot use array as test condition in while statement.";
            m_messages[whilestmt->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        if (whilestmt->exp()->hasType() &&
            whilestmt->exp()->type() != AST::Type::Bool) {
            std::string error =
                "Expecting Boolean test condition in while statement but got "
                "type " +
                AST::Types::toString(whilestmt->exp()->type()) + ".";

            m_messages[whilestmt->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
        break;
    }
    case AST::StmtType::Select: {
        auto *ifstmt = stmt->cast<AST::Stmt::Select *>();

        if (ifstmt->exp()->isArray()) {
            std::string error =
                "Cannot use array as test condition in if statement.";
            m_messages[ifstmt->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        if (ifstmt->exp()->hasType() &&
            ifstmt->exp()->type() != AST::Type::Bool) {
            std::string error =
                "Expecting Boolean test condition in if statement but got "
                "type " +
                AST::Types::toString(ifstmt->exp()->type()) + ".";

            m_messages[ifstmt->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
        break;
    }
    }
}