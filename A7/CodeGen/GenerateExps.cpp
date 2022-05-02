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
    case AST::OpType::Unary: {
        generateCode(op->cast<AST::Exp::Op::Unary*>(), AC);
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
        generateCodeIndexOp(op, AC);
        break;
    }
    case AST::BinaryOpType::Bool: {
        generateCode(op->cast<AST::Exp::Op::Bool*>(), AC);
        break;
    }
    default: {
        generateCodeBinaryMathop(op, AC);
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

    bool lhsIsArray =
        lhs->is(AST::ExpType::Op) &&
        lhs->cast<AST::Exp::Op::Op*>()->is(AST::OpType::Binary) &&
        lhs->cast<AST::Exp::Op::Binary*>()->is(AST::BinaryOpType::Index);

    if (lhsIsArray) {
        auto* indexOp = lhs->cast<AST::Exp::Op::Binary*>();
        auto* array = indexOp->exp1()->cast<AST::Exp::Id*>();
        auto* index = indexOp->exp2()->cast<AST::Exp::Exp*>();
        int PTR = (array->memInfo().isInGlobalMemory()) ? GP : FP;

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
        int PTR = (id->memInfo().isInGlobalMemory()) ? GP : FP;
        generateCode(rhs, AC0);
        m_instructions.push_back(Instruction::ST(AC0,
                                                 lhs->memInfo().getLocation(),
                                                 PTR,
                                                 "Store variable " + id->id()));
    }
}

void CodeGen::generateCode(AST::Exp::Op::Unary* op, int AC)
{
    switch (op->unaryOpType()) {
    case AST::UnaryOpType::Asgn: {
        generateCode(op->cast<AST::Exp::Op::UnaryAsgn*>(), AC);
        break;
    }
    case AST::UnaryOpType::Not: {
        auto* boolexp = op->operand();
        generateCode(boolexp, AC0);
        m_instructions.push_back(Instruction::LDC(AC1, "1", "Load 1"));
        m_instructions.push_back(
            Instruction::XOR(AC0, AC0, AC1, "Op XOR to get logical not"));
        break;
    }
    case AST::UnaryOpType::Random: {
        generateCode(op->operand(), AC0);
        m_instructions.push_back(Instruction::RND(AC0, AC0, "Op ?"));
        break;
    }
    case AST::UnaryOpType::Sizeof: {
        auto* array = op->operand()->cast<AST::Exp::Id*>();
        int PTR = (array->memInfo().isInGlobalMemory()) ? GP : FP;
        m_instructions.push_back(
            Instruction::LDA(AC0,
                             array->memInfo().getLocation(),
                             PTR,
                             "Load address of base of array " + array->id()));
        m_instructions.push_back(
            Instruction::LD(AC0, 1, AC0, "Load array size (op sizeof)"));
        break;
    }
    case AST::UnaryOpType::Chsign: {
        generateCode(op->operand(), AC0);
        m_instructions.push_back(Instruction::NEG(AC0, AC0, "Op unary -"));
        break;
    }
    default: {
        m_instructions.push_back(
            Instruction::Comment("Undefined unary operator"));
        break;
    }
    }
}

void CodeGen::generateCode(AST::Exp::Op::UnaryAsgn* op, int AC)
{
    auto* exp = op->mutableExp();
    bool isArray =
        exp->is(AST::ExpType::Op) &&
        exp->cast<AST::Exp::Op::Op*>()->is(AST::OpType::Binary) &&
        exp->cast<AST::Exp::Op::Binary*>()->is(AST::BinaryOpType::Index);

    if (isArray) {
        auto* indexOp = exp->cast<AST::Exp::Op::Binary*>();
        auto* array = indexOp->exp1()->cast<AST::Exp::Id*>();
        auto* index = indexOp->exp2();

        generateCode(indexOp, AC0);

        if (op->unaryAsgnType() == AST::UnaryAsgnType::Dec) {
            m_instructions.push_back(Instruction::LDA(
                AC0, -1, AC0, "Decrement value of " + array->id()));
        } else {
            m_instructions.push_back(Instruction::LDA(
                AC0, 1, AC0, "Increment value of " + array->id()));
        }

        m_instructions.push_back(Instruction::ST(AC0, 0, 5));

    } else {
        auto* id = exp->cast<AST::Exp::Id*>();
        int PTR = (id->memInfo().isInGlobalMemory()) ? GP : FP;

        generateCode(id, AC0);

        if (op->unaryAsgnType() == AST::UnaryAsgnType::Dec) {
            m_instructions.push_back(Instruction::LDA(
                AC0, -1, AC0, "Decrement value of " + id->id()));
        } else {
            m_instructions.push_back(Instruction::LDA(
                AC0, 1, AC0, "Increment value of " + id->id()));
        }

        m_instructions.push_back(Instruction::ST(AC0,
                                                 id->memInfo().getLocation(),
                                                 PTR,
                                                 "Store variable " + id->id()));
    }
}

void CodeGen::generateCodeModifyAsgn(AST::Exp::Op::Asgn* op, int AC)
{
    auto* rhs = op->exp();
    auto* lhs = op->mutableExp();

    bool lhsIsArrayElement =
        lhs->is(AST::ExpType::Op) &&
        lhs->cast<AST::Exp::Op::Op*>()->is(AST::OpType::Binary) &&
        lhs->cast<AST::Exp::Op::Binary*>()->is(AST::BinaryOpType::Index);
    bool lhsIsArray =
        lhs->is(AST::ExpType::Id) && lhs->cast<AST::Exp::Id*>()->isArray();

    if (lhsIsArrayElement) {
        auto* indexOp = lhs->cast<AST::Exp::Op::Binary*>();
        auto* array = indexOp->exp1()->cast<AST::Exp::Id*>();
        auto* index = indexOp->exp2()->cast<AST::Exp::Exp*>();
        int PTR = (array->memInfo().isInGlobalMemory()) ? GP : FP;

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
    } else if (lhsIsArray) {
        auto* lhs_array = lhs->cast<AST::Exp::Id*>();
        auto* rhs_array = rhs->cast<AST::Exp::Id*>();
        int PTR1 = (lhs_array->memInfo().isInGlobalMemory()) ? GP : FP;
        int PTR2 = (rhs_array->memInfo().isInGlobalMemory()) ? GP : FP;
        m_instructions.push_back(Instruction::LDA(
            AC0,
            rhs_array->memInfo().getLocation(),
            PTR2,
            "Load address of base of array " + rhs_array->id()));
        m_instructions.push_back(
            Instruction::LDA(AC1,
                             lhs_array->memInfo().getLocation(),
                             PTR1,
                             "Load address of lhs"));
        m_instructions.push_back(Instruction::LD(AC2, 1, AC0, "Size of rhs"));
        m_instructions.push_back(Instruction::LD(AC3, 1, AC1, "Size of lhs"));
        m_instructions.push_back(
            Instruction::SWP(AC2, AC3, "Pick smallest size"));
        m_instructions.push_back(
            Instruction::MOV(AC1, AC0, AC2, "Array op <-"));

    } else {
        auto* id = lhs->cast<AST::Exp::Id*>();
        int PTR = (id->memInfo().isInGlobalMemory()) ? GP : FP;
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

void CodeGen::generateCode(AST::Exp::Op::Bool* op, int AC)
{
    if (op->exp1()->isArray()) { return generateCodeArrayBool(op, AC); }

    int PTR1 = (op->exp1()->memInfo().isInGlobalMemory()) ? GP : FP;
    int PTR2 = (op->exp2()->memInfo().isInGlobalMemory()) ? GP : FP;
    generateCode(op->exp1(), AC0);
    m_instructions.push_back(
        Instruction::ST(AC0, toffBack(), PTR1, "Push left side"));
    toffDec();
    generateCode(op->exp2(), AC0);
    toffInc();
    m_instructions.push_back(
        Instruction::LD(AC1, toffBack(), PTR1, "Pop left into AC1"));

    switch (op->boolOpType()) {
    case AST::BoolOpType::And: {
        m_instructions.push_back(Instruction::AND(AC0, AC1, AC0, "Op AND"));
        break;
    }
    case AST::BoolOpType::Or: {
        m_instructions.push_back(Instruction::OR(AC0, AC1, AC0, "Op OR"));
        break;
    }
    case AST::BoolOpType::EQ: {
        m_instructions.push_back(Instruction::TEQ(AC0, AC1, AC0, "Op ="));
        break;
    }
    case AST::BoolOpType::GEQ: {
        m_instructions.push_back(Instruction::TGE(AC0, AC1, AC0, "Op >="));
        break;
    }
    case AST::BoolOpType::GT: {
        m_instructions.push_back(Instruction::TGT(AC0, AC1, AC0, "Op >"));
        break;
    }
    case AST::BoolOpType::LEQ: {
        m_instructions.push_back(Instruction::TLE(AC0, AC1, AC0, "Op <="));
        break;
    }
    case AST::BoolOpType::LT: {
        m_instructions.push_back(Instruction::TLT(AC0, AC1, AC0, "Op <"));
        break;
    }
    case AST::BoolOpType::NEQ: {
        m_instructions.push_back(Instruction::TNE(AC0, AC1, AC0, "Op !="));
        break;
    }
    }
}

void CodeGen::generateCodeBinaryMathop(AST::Exp::Op::Binary* op, int AC)
{
    generateCode(op->exp1(), AC0);
    int PTR1 = (op->exp1()->memInfo().isInGlobalMemory()) ? GP : FP;
    m_instructions.push_back(Instruction::ST(
        AC0, op->exp1()->memInfo().getLocation(), PTR1, "Push left side"));
    toffDec();
    generateCode(op->exp2(), AC0);
    toffInc();
    m_instructions.push_back(Instruction::LD(
        AC1, op->exp1()->memInfo().getLocation(), PTR1, "Pop left into AC1"));

    switch (op->binaryOpType()) {
    case AST::BinaryOpType::Add: {
        m_instructions.push_back(Instruction::ADD(AC0, AC1, AC0, "Op +"));
        break;
    }
    case AST::BinaryOpType::Div: {
        m_instructions.push_back(Instruction::DIV(AC0, AC1, AC0, "Op /"));
        break;
    }
    case AST::BinaryOpType::Mod: {
        m_instructions.push_back(Instruction::MOD(AC0, AC1, AC0, "Op %"));
        break;
    }
    case AST::BinaryOpType::Mul: {
        m_instructions.push_back(Instruction::MUL(AC0, AC1, AC0, "Op *"));
        break;
    }
    case AST::BinaryOpType::Subtract: {
        m_instructions.push_back(Instruction::SUB(AC0, AC1, AC0, "Op -"));
        break;
    }
    }
}

void CodeGen::generateCodeArrayBool(AST::Exp::Op::Bool* op, int AC)
{
    auto* lhs = op->exp1()->cast<AST::Exp::Id*>();
    auto* rhs = op->exp2()->cast<AST::Exp::Id*>();
    int PTR1 = (lhs->memInfo().isInGlobalMemory()) ? GP : FP;
    int PTR2 = (rhs->memInfo().isInGlobalMemory()) ? GP : FP;

    m_instructions.push_back(
        Instruction::LDA(AC0,
                         lhs->memInfo().getLocation(),
                         PTR1,
                         "Load address of base of array " + lhs->id()));
    m_instructions.push_back(
        Instruction::ST(AC0, toffBack(), FP, "Push left side"));
    toffDec();
    m_instructions.push_back(
        Instruction::LDA(AC0,
                         rhs->memInfo().getLocation(),
                         PTR2,
                         "Load address of base of array " + rhs->id()));
    toffInc();
    m_instructions.push_back(
        Instruction::LD(AC1, toffBack(), FP, "Pop left into AC1"));
    m_instructions.push_back(Instruction::LD(AC2, 1, AC0, "AC2 <- |RHS|"));
    m_instructions.push_back(Instruction::LD(AC3, 1, AC1, "AC3 <- |LHS|"));
    m_instructions.push_back(Instruction::LDA(RT, 0, AC2, "R2 <- |RHS|"));
    m_instructions.push_back(Instruction::SWP(AC2, AC3, "Pick smallest size"));
    m_instructions.push_back(Instruction::LD(AC3, 1, AC1, "AC3 <- |LHS|"));
    m_instructions.push_back(
        Instruction::CO(AC1, AC0, AC2, "Set up array compare LHS vs RHS"));
    m_instructions.push_back(
        Instruction::TNE(AC2, AC1, AC0, "If not equal then test (AC1, AC0)"));
    m_instructions.push_back(Instruction::JNZ(AC2, RT, PC, "Jump not equal"));
    m_instructions.push_back(Instruction::LDA(AC0, 0, RT, "AC1 <- |RHS|"));
    m_instructions.push_back(Instruction::LDA(AC1, 0, AC3, "AC0 <- |LHS|"));

    switch (op->boolOpType()) {
    case AST::BoolOpType::EQ: {
        m_instructions.push_back(Instruction::TEQ(AC0, AC1, AC0, "Op ="));
        break;
    }
    case AST::BoolOpType::NEQ: {
        m_instructions.push_back(Instruction::TNE(AC0, AC1, AC0, "Op !="));
        break;
    }
    case AST::BoolOpType::GT: {
        m_instructions.push_back(Instruction::TGT(AC0, AC1, AC0, "Op >"));
        break;
    }
    case AST::BoolOpType::LT: {
        m_instructions.push_back(Instruction::TLT(AC0, AC1, AC0, "Op <"));
        break;
    }
    case AST::BoolOpType::GEQ: {
        m_instructions.push_back(Instruction::TGE(AC0, AC1, AC0, "Op >="));
        break;
    }
    case AST::BoolOpType::LEQ: {
        m_instructions.push_back(Instruction::TLE(AC0, AC1, AC0, "Op <="));
        break;
    }
    }
}