#pragma once

#include "Type.hpp"

#include <map>
#include <string>

class AST_node
{
public:
    AST_node();
    AST_node(bool is_root);
    AST_node(const AST_node &);
    ~AST_node();
    AST_node(Type::Declaration);
    AST_node(Type::Statement);
    AST_node(Type::Expression);
    AST_node &sibling();
    AST_node &add_sibling(AST_node);
    void add_sibling(AST_node *);
    AST_node &add_child(AST_node);
    void add_child(AST_node *);
    AST_node &parent();
    std::string to_string() const;
    void print() const;

private:
    static const std::string s_print_tab;

    std::map<Type::Node, AST_node> m_children;
    AST_node *m_sibling = nullptr;
    AST_node *m_parent = nullptr;
    unsigned m_linenum;
    Type::Node m_type;
    int m_subtype;
    bool m_is_root = false;
    Type::VariableInfo m_var_info;

    void print(unsigned, const std::string &) const;
};