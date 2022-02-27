#pragma once

#include "Types.hpp"

#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace AST {

/// String to print for indentations
static const std::string s_indentString = ".   ";

/// Base AST Node class
class Node {
  public:
    /// Default constructor
    Node();
    /// @param linenum Line number the node appears on
    Node(unsigned linenum);
    Node(unsigned linenum, NodeType nodeType);
    virtual ~Node();
    /// Recursively prints the tree
    void print(bool debugging = false) const;
    void printWithTypeDebugging() const;
    virtual std::string toString(bool debugging = false) const;
    /// Adds a child node
    void addChild(Node *);
    void setChild(int, Node *);
    /// Adds a sibling node
    void addSibling(Node *);
    /// Gets reference to the line number member
    unsigned &lineNumber();
    /// @returns Type of node
    const NodeType &nodeType() const;
    bool hasSibling() const;
    Node *sibling() const;
    Node *parent() const;
    const std::vector<Node *> &children() const;

    virtual bool is(NodeType) const;
    virtual bool is(StmtType) const;
    virtual bool is(DeclType) const;
    virtual bool is(ExpType) const;
    virtual bool is(OpType) const;
    virtual bool is(BoolOpType) const;
    virtual bool is(UnaryOpType) const;
    virtual bool is(UnaryAsgnType) const;
    virtual bool is(BinaryOpType) const;
    virtual bool is(AsgnType) const;

    template <typename T> bool hasAncestor(T t) const {
        Node *walker = parent();
        while (walker != nullptr) {
            if (walker->is(t)) {
                return true;
            }

            walker = walker->parent();
        }
        return false;
    }

    template <typename T> T cast() const { return (T)this; }

  private:
  protected:
    NodeType m_nodeType;
    std::vector<Node *> m_children;
    Node *m_sibling = nullptr;
    Node *m_parent = nullptr;
    unsigned m_linenum;

    /// @returns The line tag at the end of every node's print statement
    std::string lineTag() const;
    virtual std::string typeTag() const;
    Node *getChild(int index) const;
};
} // namespace AST