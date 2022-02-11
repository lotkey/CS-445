#pragma once

#include "../Node.hpp"

#include <string>

namespace AST::Exp
{
    class Id : public Node
    {
    public:
        Id();
        Id(unsigned);
        Id(unsigned, const std::string &);
        virtual std::string toString() const override;

    protected:
        std::string m_id;
    };
}