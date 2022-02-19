#pragma once

#include "../Node.hpp"

#include <map>
#include <string>

namespace AST::Stmt {
/// Base statement node
class Stmt : public Node {
  public:
    Stmt();
    /// @param linenum Line number the node appears on
    Stmt(unsigned linenum);
    virtual std::string toString() const override;

  protected:
    /// Statement type (for printing)
    enum class Type { Break, Compound, For, Return, Select, While };

    static const std::map<Type, std::string> s_typeToString;

    Type m_type;
};
} // namespace AST::Stmt