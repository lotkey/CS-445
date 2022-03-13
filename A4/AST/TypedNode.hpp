#pragma once

#include "Node.hpp"
#include "Types.hpp"

#include <optional>

namespace AST {
class TypedNode : public Node {
  public:
    TypedNode();
    TypedNode(int linenum);
    TypedNode(int linenum, NodeType nodeType);

    bool isConst() const;
    void setIsConst(bool);
    bool isArray() const;
    void setIsArray(bool);
    bool isStatic() const;
    void setIsStatic(bool);
    bool hasType() const;
    Type type() const;
    std::optional<Type> typeOptional() const;
    virtual void setType(Type);
    TypeInfo getTypeInfo() const;
    void setTypeInfo(TypeInfo);

  private:
    TypeInfo m_typeInfo;
};
} // namespace AST