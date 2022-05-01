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
    const int toff_pre_args = toffBack();

    m_instructions.push_back(Instruction::Comment("CALL " + call->id()));
    m_instructions.push_back(Instruction::ST(
        FP, toffBack(), FP, "Store FP in ghost frame for output"));
    toffDec();
    m_instructions.push_back(Instruction::Comment("START Params"));
    int argCounter = 1;
    for (auto* arg = call->arglist(); arg != nullptr;
         arg = arg->sibling()->cast<AST::Exp::Exp*>()) {
        toffDec();
        m_instructions.push_back(
            Instruction::Comment("Param " + std::to_string(argCounter)));
        generateCode(arg, AC);
        m_instructions.push_back(
            Instruction::ST(AC0, toffBack(), FP, "Push parameter"));
        argCounter++;
    }
    m_instructions.push_back(Instruction::Comment("END Params"));

    toffSet(toff_pre_args);
    m_instructions.push_back(Instruction::LDA(
        FP, toffBack(), FP, "Ghost frame becomes new active frame"));
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
    int PTR = (id->memInfo().isInGlobalMemory()) ? GP : FP;

    if (id->decl()->is(AST::DeclType::Parm)) {
        auto* parm = id->decl()->cast<AST::Decl::Parm*>();
        if (parm->isArray()) {
            m_instructions.push_back(
                Instruction::LD(AC,
                                parm->memInfo().getLocation(),
                                PTR,
                                "Load address of base of array " + parm->id()));
        } else {
            m_instructions.push_back(
                Instruction::LD(AC,
                                parm->memInfo().getLocation(),
                                PTR,
                                "Load variable " + parm->id()));
        }
    } else {
        auto* var = id->decl()->cast<AST::Decl::Var*>();
        int ptr;

        if (var->isArray()) {
            m_instructions.push_back(
                Instruction::LDA(AC,
                                 id->decl()->memInfo().getLocation(),
                                 PTR,
                                 "Load address of base of array " + id->id()));
        } else {
            m_instructions.push_back(
                Instruction::LD(AC,
                                id->decl()->memInfo().getLocation(),
                                PTR,
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
    if (op->asgnType() != AST::AsgnType::Asgn) {
        generateCodeModifyAsgn(op, AC);
    }

    auto* rhs = op->exp();
    auto* lhs = op->mutableExp();
    int PTR = (lhs->memInfo().isInGlobalMemory()) ? GP : FP;

    bool lhsIsArray =
        lhs->is(AST::ExpType::Op) &&
        lhs->cast<AST::Exp::Op::Op*>()->is(AST::OpType::Binary) &&
        lhs->cast<AST::Exp::Op::Binary*>()->is(AST::BinaryOpType::Index);

    if (lhsIsArray) {
        auto* indexOp = lhs->cast<AST::Exp::Op::Binary*>();
        auto* array = indexOp->exp1()->cast<AST::Exp::Id*>();
        auto* index = indexOp->exp2()->cast<AST::Exp::Exp*>();

        generateCode(index, AC0);
        m_instructions.push_back(
            Instruction::ST(AC0, toffBack(), FP, "Push index"));
        toffDec();
        generateCode(rhs, AC0);
        toffInc();
        m_instructions.push_back(
            Instruction::LD(AC1, toffBack(), FP, "Pop index"));
        m_instructions.push_back(
            Instruction::LDA(AC2,
                             array->memInfo().getLocation(),
                             PTR,
                             "Load address of base of array " + array->id()));
        m_instructions.push_back(
            Instruction::SUB(AC2, AC2, AC1, "Compute offset of value"));
        m_instructions.push_back(
            Instruction::ST(AC0, 0, AC2, "Store variable " + array->id()));
    } else {
        auto* id = lhs->cast<AST::Exp::Id*>();
        generateCode(rhs, AC0);
        m_instructions.push_back(Instruction::ST(AC0,
                                                 lhs->memInfo().getLocation(),
                                                 PTR,
                                                 "Store variable " + id->id()));
    }
}

void CodeGen::generateCodeModifyAsgn(AST::Exp::Op::Asgn* op, int AC)
{
    auto* rhs = op->exp();
    auto* lhs = op->mutableExp();
    int PTR = (lhs->memInfo().isInGlobalMemory()) ? GP : FP;

    bool lhsIsArray =
        lhs->is(AST::ExpType::Op) &&
        lhs->cast<AST::Exp::Op::Op*>()->is(AST::OpType::Binary) &&
        lhs->cast<AST::Exp::Op::Binary*>()->is(AST::BinaryOpType::Index);

    if (lhsIsArray) {
        auto* indexOp = lhs->cast<AST::Exp::Op::Binary*>();
        auto* array = indexOp->exp1()->cast<AST::Exp::Id*>();
        auto* index = indexOp->exp2()->cast<AST::Exp::Exp*>();

        // Generate the index and push it onto the stack
        generateCode(index, AC0);
        m_instructions.push_back(
            Instruction::ST(AC0, toffBack(), FP, "Push index"));
        toffDec();

        // Generate the rhs, AKA the amount to add/subtract/multiply/etc
        generateCode(rhs, AC0);
        toffInc();

        m_instructions.push_back(
            Instruction::LD(AC1, toffBack(), FP, "Pop index"));
        m_instructions.push_back(
            Instruction::LDA(AC2,
                             array->memInfo().getLocation(),
                             PTR,
                             "Load address of base of array " + array->id()));
        m_instructions.push_back(
            Instruction::SUB(AC2, AC2, AC1, "Compute offset of value"));

        m_instructions.push_back(
            Instruction::LD(AC1, 0, AC2, "Load lhs variable " + array->id()));

        switch (op->asgnType()) {
        case AST::AsgnType::AddAsgn: {
            m_instructions.push_back(Instruction::ADD(AC0, AC1, AC0, "Op +="));
            break;
        }
        case AST::AsgnType::DivAsgn: {
            m_instructions.push_back(Instruction::SUB(AC0, AC1, AC0, "Op -="));
            break;
        }
        case AST::AsgnType::MulAsgn: {
            m_instructions.push_back(Instruction::MUL(AC0, AC1, AC0, "Op *="));
            break;
        }
        case AST::AsgnType::SubAsgn: {
            m_instructions.push_back(Instruction::DIV(AC0, AC1, AC0, "Op /="));
            break;
        }
        }

        m_instructions.push_back(
            Instruction::ST(AC0, 0, AC2, "Store variable " + array->id()));
    } else {
        auto* id = lhs->cast<AST::Exp::Id*>();
        generateCode(rhs, AC0);
        generateCode(lhs, AC1);

        switch (op->asgnType()) {
        case AST::AsgnType::AddAsgn: {
            m_instructions.push_back(Instruction::ADD(AC0, AC1, AC0, "Op +="));
            break;
        }
        case AST::AsgnType::DivAsgn: {
            m_instructions.push_back(Instruction::SUB(AC0, AC1, AC0, "Op -="));
            break;
        }
        case AST::AsgnType::MulAsgn: {
            m_instructions.push_back(Instruction::MUL(AC0, AC1, AC0, "Op *="));
            break;
        }
        case AST::AsgnType::SubAsgn: {
            m_instructions.push_back(Instruction::DIV(AC0, AC1, AC0, "Op /="));
            break;
        }
        }

        m_instructions.push_back(Instruction::ST(AC0,
                                                 lhs->memInfo().getLocation(),
                                                 PTR,
                                                 "Store variable " + id->id()));
    }
}

void CodeGen::generateCodeIndexOp(AST::Exp::Op::Binary* op, int AC)
{
    auto* array = op->exp1()->cast<AST::Exp::Id*>();
    auto* index = op->exp2();
    int PTR = (array->decl()->memInfo().isInGlobalMemory()) ? GP : FP;
    m_instructions.push_back(
        Instruction::LDA(AC0,
                         array->memInfo().getLocation(),
                         PTR,
                         "Load address of base of array " + array->id()));
    m_instructions.push_back(
        Instruction::ST(AC0, toffBack(), FP, "Push left side"));
    toffDec();
    generateCode(index);
    toffInc();
    m_instructions.push_back(
        Instruction::LD(AC1, toffBack(), FP, "Pop left into AC1"));
    m_instructions.push_back(
        Instruction::SUB(AC0, AC1, AC0, "Compute location from index"));
    m_instructions.push_back(
        Instruction::LD(AC0, 0, AC0, "Load array element"));
}