#pragma once

#include "Type.hpp"

#include <optional>
#include <string>
#include <vector>

class AST_node
{
public:
    AST_node();
    AST_node(bool is_root);
    AST_node(const AST_node &);
    AST_node(Type::Declaration);
    AST_node(Type::Statement);
    AST_node(Type::Expression);
    ~AST_node();
    void add_sibling(AST_node *);
    void add_child(AST_node *);
    void print() const;
    int number_of_nodes() const;
    std::string to_string() const;

private:
    static const std::string s_print_tab;

    std::vector<AST_node *> m_children;
    AST_node *m_sibling = nullptr;
    unsigned m_linenum;
    Type::Node m_type;
    int m_subtype;
    Type::VariableInfo m_var_info;

    void print(unsigned, const std::string &) const;
};