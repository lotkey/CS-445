#include "AST.hpp"

namespace AST {
[[nodiscard]] Node *ioLibraryTree() {
    auto *output_parm = new Decl::Parm(0, "i", false);
    output_parm->setType(Type::Int);
    auto *output = new Decl::Func(0, "output", output_parm, nullptr);
    output->setType(Type::Void);

    auto *outputb_parm = new Decl::Parm(0, "b", false);
    outputb_parm->setType(Type::Bool);
    auto *outputb = new Decl::Func(0, "outputb", outputb_parm, nullptr);
    outputb->setType(Type::Void);

    auto *outputc_parm = new Decl::Parm(0, "c", false);
    outputc_parm->setType(Type::Char);
    auto *outputc = new Decl::Func(0, "outputc", outputc_parm, nullptr);
    outputc->setType(Type::Void);

    auto *input = new Decl::Func(0, "input", nullptr, nullptr);
    input->setType(Type::Int);

    auto *inputb = new Decl::Func(0, "inputb", nullptr, nullptr);
    input->setType(Type::Bool);

    auto *inputc = new Decl::Func(0, "inputc", nullptr, nullptr);
    input->setType(Type::Char);

    auto *outnl = new Decl::Func(0, "outnl", nullptr, nullptr);
    outnl->setType(Type::Void);

    input->addSibling(inputb);
    input->addSibling(inputc);
    input->addSibling(output);
    input->addSibling(outputb);
    input->addSibling(outputc);
    input->addSibling(outnl);
    return input;
}
} // namespace AST