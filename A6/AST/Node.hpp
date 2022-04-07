#pragma once

#include "Types.hpp"

#include <functional>
#include <iostream>
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
#pragma region Constructors / Destructors
    /// Default constructor
    Node();
    /// @param linenum Line number the node appears on
    Node(int linenum);
    /// @param linenum Line number the node appears on
    /// @param nodeType Type of node
    Node(int linenum, NodeType nodeType);
    /// Virtual destructor, release all dynamically allocated memory
    virtual ~Node();
#pragma endregion

#pragma region Tree traversal and construction
    /// Adds a child node
    void addChild(Node *node);
    /// Sets the child at the index to the node
    /// If there is already a node at the index, it is freed
    /// @param index Child index
    /// @param node Node to set the child at the index
    void setChild(int index, Node *node);
    /// Adds a sibling node
    void addSibling(Node *node);
    /// @returns The address of the sibling, nullptr if none
    Node *sibling() const;
    std::vector<Node *> siblings() const;
    /// @returns The address of the parent, nullptr if none
    Node *parent() const;
    /// @returns The vector of children nodes
    const std::vector<Node *> &children() const;
#pragma endregion

#pragma region Info
    /// Recursively prints the tree
    void print(bool debugging = false, bool printSymbolInfo = false) const;
    /// @returns True if the node has a sibling
    bool hasSibling() const;
    /// Gets reference to the line number member
    int &lineNumber();
    /// @returns Type of node
    const NodeType &nodeType() const;
#pragma endregion

#pragma region Virtual functions
    virtual bool isTyped() const;
    /// Get a string representation of the node
    virtual std::string toString() const = 0;

    /// Functions to determine node type from base Node pointer
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
#pragma endregion

#pragma region Templated functions
    /// Casts the address of the Node to some type
    /// @returns The casted address
    template <typename T> T cast() const { return (T)this; }

    bool hasAncestorWhere(const std::function<bool(Node *)> &predicate) const {

        for (Node *walker = parent(); walker != nullptr;
             walker = walker->parent()) {
            if (predicate(walker)) {
                return true;
            }
        }
        return false;
    }

    /// @param t Node type (enum)
    /// @returns True if the node has an ancestor of type t
    template <typename T> bool hasAncestorOfType(T t) const {
        return hasAncestorWhere([t](Node *node) { return node->is(t); });
    }

    Node *getClosestAncestorWhere(
        const std::function<bool(Node *)> &predicate) const {

        for (Node *walker = parent(); walker != nullptr;
             walker = walker->parent()) {
            if (predicate(walker)) {
                return walker;
            }
        }
        return nullptr;
    }

    /// @param t Node type (enum)
    /// @returns Address of the closest ancestor that is the provided type
    template <typename T> Node *getClosestAncestorOfType(T t) const {
        return getClosestAncestorWhere([t](Node *node) { return node->is(t); });
    }

    std::vector<Node *> getDescendants() const {
        std::vector<Node *> descendants;
        for (const auto &child : children()) {
            if (child != nullptr) {
                descendants.push_back(child);
                std::vector<Node *> v = child->getDescendants();
                descendants.insert(descendants.end(), v.begin(), v.end());
            }
        }
        return descendants;
    }

    bool
    hasDescendantWhere(const std::function<bool(Node *)> &predicate) const {
        if (!this) {
            return false;
        }
        for (const auto &child : children()) {
            if (child) {
                if (predicate(child)) {
                    return true;
                } else if (child->hasDescendantWhere(predicate)) {
                    return true;
                } else {
                    for (const auto &sibling : child->siblings()) {
                        if (sibling && predicate(sibling)) {
                            return true;
                        }

                        if (child->hasDescendantWhere(predicate)) {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    template <typename T> bool hasDescendantOfType(T t) const {
        return hasDescendantWhere([t](Node *node) { return node->is(t); });
    }

    std::vector<Node *>
    getDescendantsWhere(const std::function<bool(Node *)> &predicate) const {
        auto descendants = getDescendants();
        std::vector<Node *> v;
        for (const auto &descendant : descendants) {
            if (predicate(descendant)) {
                v.push_back(descendant);
            }
        }
        return v;
    }
#pragma endregion

  private:
  protected:
    NodeType m_nodeType;
    std::vector<Node *> m_children;
    Node *m_sibling = nullptr;
    Node *m_parent = nullptr;
    int m_linenum;
    std::optional<ReferenceType> m_referenceType;
    int m_size = 0;
    int m_loc = 0;

    /// @param index Returns the child at the specified index, nullptr if none
    /// exists
    Node *getChild(int index) const;
    std::string lineTag() const;
};
} // namespace AST