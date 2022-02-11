#pragma once

#include <string>
#include <vector>

namespace AST
{
    static const std::string s_indentString = ".   ";

    class Node
    {
    public:
        Node();
        Node(unsigned);
        virtual ~Node();
        void print() const;
        virtual std::string toString() const;
        void addChild(Node *);
        void addSibling(Node *);
        unsigned &lineNumber();

    private:
    protected:
        std::vector<Node *> m_children;
        Node *m_sibling = nullptr;
        unsigned m_linenum;

        std::string lineTag() const;
    };
}