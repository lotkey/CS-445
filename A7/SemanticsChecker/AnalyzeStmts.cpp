#include "../AST/AST.hpp"
#include "../SymbolTable/SymbolTable.hpp"
#include "SemanticsChecker.hpp"

#include <iostream>

void SemanticsChecker::analyzeNode(AST::Stmt::Stmt *stmt) {
    if (!stmt) {
        return;
    }

    switch (stmt->stmtType()) {
    case AST::StmtType::Compound: {
        break;
    }
    case AST::StmtType::For: {
        break;
    }
    case AST::StmtType::Return: {
        auto *returnNode = stmt->cast<AST::Stmt::Return *>();
        if (returnNode->exp() && returnNode->exp()->isArray()) {
            Message::add(returnNode->lineNumber(), Message::Type::Error,
                         "Cannot return an array.");
        }

        auto *functionParent =
            returnNode->getClosestAncestorOfType(AST::DeclType::Func)
                ->cast<AST::Decl::Func *>();

        if (functionParent && functionParent->hasType()) {
            if (functionParent->type() == AST::Type::Void &&
                returnNode->exp() != nullptr) {

                Message::add(returnNode->lineNumber(), Message::Type::Error,
                             "Function '%s' at line %d is expecting no return "
                             "value, but return has a value.",
                             functionParent->id().c_str(),
                             functionParent->lineNumber());

            } else if (functionParent->type() != AST::Type::Void &&
                       returnNode->exp() == nullptr) {

                Message::add(
                    returnNode->lineNumber(), Message::Type::Error,
                    "Function '%s' at line %d is expecting to return "
                    "type %s but return has no value.",
                    functionParent->id().c_str(), functionParent->lineNumber(),
                    AST::Types::toString(functionParent->type()).c_str());

            } else if (returnNode->exp() && returnNode->exp()->hasType() &&
                       functionParent->type() != returnNode->exp()->type()) {

                Message::add(
                    returnNode->lineNumber(), Message::Type::Error,
                    "Function '%s' at line %d is expecting to return "
                    "type %s but returns type %s.",
                    functionParent->id().c_str(), functionParent->lineNumber(),
                    AST::Types::toString(functionParent->type()).c_str(),
                    AST::Types::toString(returnNode->exp()->type()).c_str());
            }
        }

        break;
    }
    case AST::StmtType::Range: {
        auto *range = stmt->cast<AST::Stmt::Range *>();
        std::vector<AST::Exp::Exp *> rangeChildren = {range->from(),
                                                      range->to(), range->by()};

        for (int i = 0; i < rangeChildren.size(); i++) {
            if (rangeChildren[i]) {
                if (rangeChildren[i]->isArray()) {

                    Message::add(range->lineNumber(), Message::Type::Error,
                                 "Cannot use array in position %d in range of "
                                 "for statement.",
                                 i + 1);
                }

                if (rangeChildren[i]->hasType() &&
                    rangeChildren[i]->type() != AST::Type::Int) {

                    Message::add(
                        range->lineNumber(), Message::Type::Error,
                        "Expecting type int in position %d in range of for "
                        "statement but got type %s.",
                        i + 1,
                        AST::Types::toString(rangeChildren[i]->type()).c_str());
                }
            }
        }

        break;
    }
    case AST::StmtType::Break: {
        if (!(stmt->hasAncestorOfType(AST::StmtType::For) ||
              stmt->hasAncestorOfType(AST::StmtType::While))) {

            Message::add(stmt->lineNumber(), Message::Type::Error,
                         "Cannot have a break statement outside of loop.");
        }
        break;
    }
    case AST::StmtType::While: {
        auto *whilestmt = stmt->cast<AST::Stmt::While *>();

        if (whilestmt->exp() && whilestmt->exp()->isArray()) {

            Message::add(
                whilestmt->lineNumber(), Message::Type::Error,
                "Cannot use array as test condition in while statement.");
        }

        if (whilestmt->exp() && whilestmt->exp()->hasType() &&
            whilestmt->exp()->type() != AST::Type::Bool) {

            Message::add(
                whilestmt->lineNumber(), Message::Type::Error,
                "Expecting Boolean test condition in while statement "
                "but got type %s.",
                AST::Types::toString(whilestmt->exp()->type()).c_str());
        }
        break;
    }
    case AST::StmtType::Select: {
        auto *ifstmt = stmt->cast<AST::Stmt::Select *>();

        if (ifstmt->exp() && ifstmt->exp()->isArray()) {

            Message::add(ifstmt->lineNumber(), Message::Type::Error,
                         "Cannot use array as test condition in if statement.");
        }

        if (ifstmt->exp() && ifstmt->exp()->hasType() &&
            ifstmt->exp()->type() != AST::Type::Bool) {

            Message::add(ifstmt->lineNumber(), Message::Type::Error,
                         "Expecting Boolean test condition in if statement but "
                         "got type %s.",
                         AST::Types::toString(ifstmt->exp()->type()).c_str());
        }
        break;
    }
    }
}