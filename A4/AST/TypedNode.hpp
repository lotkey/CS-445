#pragma once

#include "Node.hpp"
#include "Types.hpp"

namespace AST {
class TypedNode : public Node {
  public:
    TypedNode();
    TypedNode(unsigned linenum);
    TypedNode(unsigned linenum, NodeType nodeType);

    bool isConst() const;
    bool &isConst();
    bool isArray() const;
    bool &isArray();
    bool isStatic() const;
    bool &isStatic();
    bool hasType() const;
    Type type() const;
    void setType(Type);
    TypeInfo getTypeInfo() const;
    void setTypeInfo(TypeInfo);

  private:
    TypeInfo m_typeInfo;
};
} // namespace AST