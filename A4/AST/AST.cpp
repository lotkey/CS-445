#include "AST.hpp"

namespace AST {
[[nodiscard]] Node *ioLibraryTree() {
    auto *output_parm = new Decl::Parm(libraryLineNumber, "i", false);
    output_parm->setType(Type::Int);
    auto *output = new Decl::Func(libraryLineNumber, Type::Void, "output",
                                  output_parm, nullptr);

    auto *outputb_parm = new Decl::Parm(libraryLineNumber, "b", false);
    outputb_parm->setType(Type::Bool);
    auto *outputb = new Decl::Func(libraryLineNumber, Type::Void, "outputb",
                                   outputb_parm, nullptr);

    auto *outputc_parm = new Decl::Parm(libraryLineNumber, "c", false);
    outputc_parm->setType(Type::Char);
    auto *outputc = new Decl::Func(libraryLineNumber, Type::Void, "outputc",
                                   outputc_parm, nullptr);

    auto *input =
        new Decl::Func(libraryLineNumber, Type::Int, "input", nullptr, nullptr);

    auto *inputb = new Decl::Func(libraryLineNumber, Type::Bool, "inputb",
                                  nullptr, nullptr);

    auto *inputc = new Decl::Func(libraryLineNumber, Type::Char, "inputc",
                                  nullptr, nullptr);

    auto *outnl = new Decl::Func(libraryLineNumber, Type::Void, "outnl",
                                 nullptr, nullptr);

    input->addSibling(inputb);
    input->addSibling(inputc);
    input->addSibling(output);
    input->addSibling(outputb);
    input->addSibling(outputc);
    input->addSibling(outnl);
    return input;
}
} // namespace AST