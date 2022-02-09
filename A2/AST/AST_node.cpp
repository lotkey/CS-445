#include "AST_node.hpp"
#include "Type.hpp"

#include <iostream>
#include <string>

const std::string AST_node::s_print_tab = ".   ";

AST_node::AST_node() {}

AST_node::AST_node(bool is_root)
    : m_is_root(is_root)
{
    std::cout << "Construct" << std::endl;
}

AST_node::AST_node(const AST_node &node)
    : m_linenum(node.m_linenum),
      m_type(node.m_type),
      m_subtype(node.m_subtype)
{
    std::cout << "Copy construct" << std::endl;
    for (const auto &[_, child] : node.m_children)
    {
        add_child(AST_node(child));
    }

    AST_node *walker = node.m_sibling;
    while (walker != nullptr)
    {
        add_sibling(AST_node(*walker));
        walker = walker->m_sibling;
    }
}

AST_node::~AST_node()
{
    std::cout << "Destruct" << std::endl;
    if (m_sibling != nullptr)
    {
        delete m_sibling;
    }
}

AST_node::AST_node(Type::Declaration subtype)
    : m_type(Type::Node::Declaration),
      m_subtype((int)subtype)
{
    std::cout << "Construct delcaration" << std::endl;
}

AST_node::AST_node(Type::Statement subtype)
    : m_type(Type::Node::Statement),
      m_subtype((int)subtype)
{
    std::cout << "Construct statement" << std::endl;
}

AST_node::AST_node(Type::Expression subtype)
    : m_type(Type::Node::Expression),
      m_subtype((int)subtype)
{
    std::cout << "Construct expression" << std::endl;
}

AST_node &AST_node::add_child(AST_node node)
{
    std::cout << "add child" << std::endl;
    if (m_children.find(node.m_type) != m_children.end())
    {
        return m_children[node.m_type].add_sibling(node);
    }
    else
    {
        m_children[node.m_type] = node;
        return m_children[node.m_type];
    }
}

void AST_node::add_child(AST_node *node)
{
    std::cout << "add child" << std::endl;
    if (node == nullptr)
    {
        return;
    }

    if (m_children.find(node->m_type) != m_children.end())
    {
        m_children[node->m_type].add_sibling(node);
    }
    else
    {
        m_children[node->m_type] = *node;
    }
}

AST_node &AST_node::add_sibling(AST_node node)
{
    if (m_sibling != nullptr)
    {
        return m_sibling->add_sibling(node);
    }
    else
    {
        m_sibling = new AST_node(node);
        return *m_sibling;
    }
}

void AST_node::add_sibling(AST_node *node)
{
    if (m_sibling != nullptr)
    {
        m_sibling->add_sibling(node);
    }
    else
    {
        m_sibling = node;
    }
}

AST_node &AST_node::sibling()
{
    std::cout << "get sibling" << std::endl;
    if (m_is_root)
    {
        throw std::runtime_error("Adding sibling to root is illegal");
    }
    return *m_sibling;
}

AST_node &AST_node::parent()
{
    std::cout << "get parent" << std::endl;
    return *m_parent;
}

std::string AST_node::to_string() const
{
    std::cout << "to string" << std::endl;
    switch (m_type)
    {
    case Type::Node::Declaration:
        switch (static_cast<Type::Declaration>(m_subtype))
        {
        case Type::Declaration::Function:
            return "Function";
        case Type::Declaration::Parameter:
            return "Parameter";
        case Type::Declaration::Variable:
            return "Variable";
        default:
            return "Declaration";
        };
    case Type::Node::Expression:
        switch (static_cast<Type::Expression>(m_subtype))
        {
        case Type::Expression::And:
            return "And";
        case Type::Expression::Assign:
            return "Assign";
        case Type::Expression::Decrement:
            return "Decrement";
        case Type::Expression::Increment:
            return "Increment";
        case Type::Expression::Simple:
            return "Simple";
        case Type::Expression::UnaryRelation:
            return "UnaryRelation";
        default:
            return "Expression";
        };
    case Type::Node::Statement:
        switch (static_cast<Type::Statement>(m_subtype))
        {
        case Type::Statement::Break:
            return "Break";
        case Type::Statement::Compound:
            return "Compound";
        case Type::Statement::Expression:
            return "Expression";
        case Type::Statement::Iterative:
            return "Iterative";
        case Type::Statement::Return:
            return "Return";
        case Type::Statement::Select:
            return "Select";
        default:
            return "Statement";
        };
    default:
        return "No type";
    };
}

void AST_node::print() const
{
    std::cout << "print" << std::endl;
    if (!m_is_root)
    {
        std::cout << to_string() << std::endl;

        for (const auto &[_, child] : m_children)
        {
            child.print(1, "Child: ");
        }

        if (m_sibling != nullptr)
        {
            std::cout << "Sibling: ";
            m_sibling->print();
        }
    }
    else
    {
        for (const auto &[_, child] : m_children)
        {
            child.print();
        }
    }
}

void AST_node::print(unsigned num_indents, const std::string &prefix) const
{
    std::cout << "print with indent" << std::endl;
    if (m_is_root)
    {
        throw std::runtime_error("Cannot print root as if it is a child/sibling");
    }

    for (unsigned i = 0; i < num_indents; i++)
    {
        std::cout << s_print_tab;
    }

    std::cout << prefix << to_string() << std::endl;

    for (const auto &[_, child] : m_children)
    {
        child.print(num_indents + 1, "Child: ");
    }

    if (m_sibling != nullptr)
    {
        m_sibling->print(num_indents, "Sibling: ");
    }
}