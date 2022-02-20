#pragma once

#include "Types.hpp"

#include <optional>
#include <string>
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
    void print() const;
    virtual std::string toString() const;
    /// Adds a child node
    void addChild(Node *);
    /// Adds a sibling node
    void addSibling(Node *);
    /// Gets reference to the line number member
    unsigned &lineNumber();
    /// @returns Type of node
    const NodeType &nodeType() const;
    bool hasSibling() const;
    Node *sibling() const;
    const std::vector<Node *> &children() const;

  private:
  protected:
    NodeType m_nodeType;
    std::vector<Node *> m_children;
    Node *m_sibling = nullptr;
    unsigned m_linenum;

    /// @returns The line tag at the end of every node's print statement
    std::string lineTag() const;
};
} // namespace AST