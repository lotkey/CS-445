#pragma once

#include "../Node.hpp"
#include "Decl.hpp"

#include <map>
#include <string>

namespace AST::Decl
{
    class Var : public Decl
    {
    public:
        Var();
        Var(unsigned);
        Var(unsigned, const std::string &, bool);
        virtual std::string toString() const override;
        void setStatic();

    protected:
        bool m_isArray = false;
        bool m_isStatic = false;
    };
}