#include "Node.hpp"
#include "../strutil.hpp"
#include "TypedNode.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace AST {
#pragma region Constructors / Destructors

Node::Node() : m_sibling(nullptr) {}

Node::Node(int linenum) : m_sibling(nullptr), m_linenum(linenum) {}

Node::Node(int linenum, NodeType nodeType)
    : m_linenum(linenum), m_nodeType(nodeType) {}

Node::~Node() {
    if (m_sibling != nullptr) {
        delete m_sibling;
    }

    for (auto &child : m_children) {
        if (child != nullptr) {
            delete child;
        }
    }
}

#pragma endregion

#pragma region Tree traversal and construction

void Node::addChild(Node *node) {
    m_children.push_back(node);
    if (node != nullptr) {
        node->m_parent = this;

        Node *sibling = node->sibling();
        while (sibling != nullptr) {
            sibling->m_parent = this;
            sibling = sibling->sibling();
        }
    }
}

void Node::setChild(int index, Node *node) {
    if (node == nullptr) {
        return;
    }
    if (m_children.size() <= index) {
        throw std::runtime_error("Cannot set child, index out of bounds.");
    } else {
        if (m_children[index] != nullptr &&
            !(m_children[index] == this || m_children[index] == node)) {
            delete m_children[index];
        }

        m_children[index] = node;
        node->m_parent = this;
        Node *sibling = node->sibling();
        while (sibling != nullptr) {
            sibling->m_parent = this;
            sibling = sibling->sibling();
        }
    }
}

void Node::addSibling(Node *node) {
    if (this == nullptr) {
        return;
    }
    if (node == nullptr) {
        return;
    }

    if (m_sibling == nullptr) {
        m_sibling = node;
        m_sibling->m_parent = m_parent;
    } else {
        m_sibling->addSibling(node);
    }
}

Node *Node::sibling() const { return m_sibling; }

std::vector<Node *> Node::siblings() const {
    std::vector<Node *> v;
    Node *walker = sibling();
    while (walker != nullptr) {
        v.push_back(walker);
        walker = walker->sibling();
    }
    return v;
}

Node *Node::parent() const { return m_parent; }

const std::vector<Node *> &Node::children() const { return m_children; }

#pragma endregion

#pragma region Info

void Node::print(bool debugging, bool printSymbolInfo) const {
    static int siblingCount = 0;
    static int numIndents = 0;

    std::string printstr = toString().c_str();
    if ((debugging || printSymbolInfo) && isTyped()) {
        auto *typed = this->cast<TypedNode *>();
        if (!typed->alreadyIncludesTypeTag()) {
            printstr += " " + typed->typeTag();
        }
    }
    if (printSymbolInfo) {
        // add symbol info;
    }
    printstr += " " + lineTag();

    std::cout << printstr << std::endl;
    numIndents++;

    for (int i = 0; i < m_children.size(); i++) {
        Node *child = m_children[i];
        if (child) {
            for (int j = 0; j < numIndents; j++) {
                std::cout << s_indentString;
            }

            std::cout << strutil::format("Child: %d  ", i);
            int backup = siblingCount;
            siblingCount = 0;
            child->print(debugging, printSymbolInfo);
            siblingCount = backup;
        }
    }
    numIndents--;

    siblingCount++;
    if (m_sibling) {
        for (int i = 0; i < numIndents; i++) {
            std::cout << s_indentString;
        }

        std::cout << strutil::format("Sibling: %d  ", siblingCount);
        m_sibling->print(debugging, printSymbolInfo);
    }
    siblingCount--;
}

bool Node::hasSibling() const { return m_sibling != nullptr; }

int &Node::lineNumber() { return m_linenum; }

const NodeType &Node::nodeType() const { return m_nodeType; }

#pragma endregion

#pragma region Virtual functions
bool Node::isTyped() const { return false; }

bool Node::is(NodeType t) const { return this && nodeType() == t; }
bool Node::is(StmtType t) const { return false; }
bool Node::is(DeclType t) const { return false; }
bool Node::is(ExpType t) const { return false; }
bool Node::is(OpType t) const { return false; }
bool Node::is(BoolOpType t) const { return false; }
bool Node::is(UnaryOpType t) const { return false; }
bool Node::is(UnaryAsgnType t) const { return false; }
bool Node::is(BinaryOpType t) const { return false; }
bool Node::is(AsgnType t) const { return false; }

#pragma endregion

#pragma region Private functions

Node *Node::getChild(int index) const {
    if (m_children.size() <= index) {
        return nullptr;
    } else {
        return m_children[index];
    }
}

std::string Node::lineTag() const {
    return strutil::format("[line: %d]", m_linenum);
}

#pragma endregion
} // namespace AST