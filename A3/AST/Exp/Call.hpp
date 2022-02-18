#pragma once

#include "../Node.hpp"
#include "Exp.hpp"

#include <string>

namespace AST::Exp
{
    /// Function call node
    class Call : public Exp
    {
    public:
        Call();
        /// @param linenum Line number the node appears on
        Call(unsigned linenum);
        /// @param linenum Line number the node appears on
        /// @param id String identifier of the function
        /// @param arglist Optional, argument list for function call
        Call(unsigned linenum, const std::string &id, Node *arglist = nullptr);
        virtual std::string toString() const override;

    protected:
        std::string m_id;
        Exp *m_arglist;
    };
}