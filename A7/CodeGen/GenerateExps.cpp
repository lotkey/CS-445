#include "CodeGen.hpp"
#include "Instruction.hpp"

#include <string>

void CodeGen::generateCode(AST::Exp::Exp* exp, int AC)
{
    switch (exp->expType()) {
    case AST::ExpType::Const: {
        generateCode(exp->cast<AST::Exp::Const*>(), AC);
        break;
    }
    case AST::ExpType::Call: {
        generateCode(exp->cast<AST::Exp::Call*>(), AC);
        break;
    }
    case AST::ExpType::Id: {
        generateCode(exp->cast<AST::Exp::Id*>(), AC);
        break;
    }
    case AST::ExpType::Op: {
        generateCode(exp->cast<AST::Exp::Op::Op*>(), AC);
        break;
    }
    default: {
        break;
    }
    }
}

void CodeGen::generateCode(AST::Exp::Const* constant, int AC)
{
    if (constant->isArray()) {
        m_instructions.push_back(Instruction::LIT(
            constant->getTmString(), "Load string into data memory"));
    } else {
        std::string comment = "Load constant";
        if (constant->getTmString() == "666") { comment += " ⸸"; }
        m_instructions.push_back(
            Instruction::LDC(AC, constant->getTmString(), comment));
    }
}

void CodeGen::generateCode(AST::Exp::Call* call, int AC)
{
    auto* func = call->getFunc();
    auto* parent = call->getClosestAncestorWhere([](AST::Node* node) {
        return node->hasMemoryInfo() && node->memInfo().sizeSet() &&
               node->memInfo().getSize() < 0;
    });
    int toff = parent->memInfo().getSize();
    const int og_toff = toff;

    m_instructions.push_back(Instruction::Comment("CALL " + call->id()));
    m_instructions.push_back(
        Instruction::ST(FP, toff, FP, "Store FP in ghost frame for output"));
    toff--;
    m_instructions.push_back(Instruction::Comment("START Params"));
    int argCounter = 1;
    for (auto* arg = call->arglist(); arg != nullptr;
         arg = arg->sibling()->cast<AST::Exp::Exp*>()) {
        toff--;
        m_instructions.push_back(
            Instruction::Comment("Param " + std::to_string(argCounter)));
        generateCode(arg, AC);
        m_instructions.push_back(
            Instruction::ST(AC0, toff, FP, "Push parameter"));
        argCounter++;
    }
    m_instructions.push_back(Instruction::Comment("END Params"));

    m_instructions.push_back(Instruction::LDA(
        FP, og_toff, FP, "Ghost frame becomes new active frame"));
    m_instructions.push_back(
        Instruction::LDA(AC0, 1, PC, "Return address in AC"));

    int jmp_loc = (m_functionLocs.at(func->id()) - Instruction::whereAmI()) - 1;
    m_instructions.push_back(
        Instruction::JMP(jmp_loc, PC, "CALL " + func->id()));
    m_instructions.push_back(
        Instruction::LDA(AC0, 0, RT, "Save the result in AC"));
    m_instructions.push_back(Instruction::Comment("CALL END " + call->id()));
}

void CodeGen::generateCode(AST::Exp::Id* id, int AC)
{
    if (id->decl()->is(AST::DeclType::Parm)) {
        auto* parm = id->decl()->cast<AST::Decl::Parm*>();
        if (parm->isArray()) {
            m_instructions.push_back(
                Instruction::LD(AC,
                                parm->memInfo().getLocation(),
                                FP,
                                "Load address of base of array " + parm->id()));
        } else {
            m_instructions.push_back(
                Instruction::LD(AC,
                                parm->memInfo().getLocation(),
                                FP,
                                "Load variable " + parm->id()));
        }
    } else {
        auto* var = id->decl()->cast<AST::Decl::Var*>();
        int ptr;
        if (id->parent()->is(AST::ExpType::Call)) {
            ptr = FP;
        } else {
            ptr = GP;
        }

        if (var->isArray()) {
            m_instructions.push_back(
                Instruction::LDA(AC,
                                 id->decl()->memInfo().getLocation(),
                                 ptr,
                                 "Load address of base of array " + id->id()));
        } else {
            m_instructions.push_back(
                Instruction::LD(AC,
                                id->decl()->memInfo().getLocation(),
                                ptr,
                                "Load variable " + id->id()));
        }
    }
}

void CodeGen::generateCode(AST::Exp::Op::Op* op, int AC)
{
    switch (op->opType()) {
    case AST::OpType::Binary: {
        generateCode(op->cast<AST::Exp::Op::Binary*>(), AC);
        break;
    }
    }
}

void CodeGen::generateCode(AST::Exp::Op::Binary* op, int AC)
{
    switch (op->binaryOpType()) {
    case AST::BinaryOpType::Asgn: {
        generateCode(op->cast<AST::Exp::Op::Asgn*>(), AC);
        break;
    }
    case AST::BinaryOpType::Index: {
        generateCodeIndexOp(op);
        break;
    }
    }
}

void CodeGen::generateCode(AST::Exp::Op::Asgn* op, int AC)
{
    auto* rhs = op->exp();
    auto* lhs = op->mutableExp();

    bool lhsIsArray =
        lhs->is(AST::ExpType::Op) &&
        lhs->cast<AST::Exp::Op::Op*>()->is(AST::OpType::Binary) &&
        lhs->cast<AST::Exp::Op::Binary*>()->is(AST::BinaryOpType::Index);

    if (lhsIsArray) {
        auto* indexOp = lhs->cast<AST::Exp::Op::Binary*>();
        auto* array = indexOp->exp1()->cast<AST::Exp::Id*>();
        auto* index = indexOp->exp2()->cast<AST::Exp::Exp*>();
        auto* toffParent =
            indexOp->getClosestAncestorWhere([](AST::Node* node) {
                return node->hasMemoryInfo() && node->memInfo().sizeSet() &&
                       node->memInfo().getSize() < 0;
            });
        int toff = toffParent->memInfo().getSize();

        generateCode(index, AC0);
        m_instructions.push_back(Instruction::ST(AC0, toff, FP, "Push index"));
        generateCode(rhs, AC0);
        m_instructions.push_back(Instruction::LD(AC1, toff, FP, "Pop index"));
        m_instructions.push_back(
            Instruction::LDA(AC2,
                             array->memInfo().getLocation(),
                             FP,
                             "Load address of base of array " + array->id()));
        m_instructions.push_back(
            Instruction::SUB(AC2, AC2, AC1, "Compute offset of value"));
        m_instructions.push_back(
            Instruction::ST(AC0, 0, AC2, "Store variable " + array->id()));
    } else {
        auto* id = rhs->cast<AST::Exp::Id*>();
        generateCode(rhs, AC0);
        m_instructions.push_back(Instruction::ST(AC0,
                                                 lhs->memInfo().getLocation(),
                                                 GP,
                                                 "Store variable " + id->id()));
    }
}

void CodeGen::generateCodeIndexOp(AST::Exp::Op::Binary* op, int AC) {}