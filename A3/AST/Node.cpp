#include "Node.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace AST {
Node::Node() : m_sibling(nullptr) {}

Node::Node(unsigned linenum) : m_sibling(nullptr), m_linenum(linenum) {}

Node::Node(unsigned linenum, NodeType nodeType)
    : m_linenum(linenum), m_nodeType(nodeType) {}

Node::~Node() {
    if (m_sibling != nullptr) {
        delete m_sibling;
    }

    for (auto &child : m_children) {
        delete child;
    }
}

void Node::print(bool debugging) const {
    static int siblingCount = 0;
    static int numIndents = 0;

    std::cout << toString(debugging) << std::endl;
    numIndents++;

    for (int i = 0; i < m_children.size(); i++) {
        Node *child = m_children[i];
        if (child != nullptr) {
            for (int j = 0; j < numIndents; j++) {
                std::cout << s_indentString;
            }

            std::cout << "Child: " + std::to_string(i) << "  ";
            int backup = siblingCount;
            siblingCount = 0;
            child->print(debugging);
            siblingCount = backup;
        }
    }
    numIndents--;

    siblingCount++;
    if (m_sibling != nullptr) {
        for (int i = 0; i < numIndents; i++) {
            std::cout << s_indentString;
        }

        std::cout << "Sibling: " + std::to_string(siblingCount) << "  ";
        m_sibling->print(debugging);
    }
    siblingCount--;
}

void Node::addChild(Node *node) { m_children.push_back(node); }

void Node::addSibling(Node *node) {
    if (node == nullptr) {
        return;
    }

    if (m_sibling == nullptr) {
        m_sibling = node;
    } else {
        m_sibling->addSibling(node);
    }
}

std::string Node::toString(bool debugging) const { return lineTag(); }

std::string Node::lineTag() const {
    return " [line: " + std::to_string(m_linenum) + "]";
}

std::string Node::typeTag() const { return ""; }

unsigned &Node::lineNumber() { return m_linenum; }

const NodeType &Node::nodeType() const { return m_nodeType; }

bool Node::hasSibling() const { return m_sibling != nullptr; }

Node *Node::sibling() const { return m_sibling; }

const std::vector<Node *> &Node::children() const { return m_children; }
} // namespace AST