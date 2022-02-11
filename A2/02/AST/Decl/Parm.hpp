#pragma once

#include "../Node.hpp"
#include "Decl.hpp"

#include <map>
#include <string>

namespace AST::Decl
{
    class Parm : public Decl
    {
    public:
        Parm();
        Parm(unsigned);
        Parm(unsigned, const std::string &, bool);
        virtual std::string toString() const override;

    protected:
        bool m_isArray;
    };
}