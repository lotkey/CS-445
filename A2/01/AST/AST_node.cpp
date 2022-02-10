#include "AST_node.hpp"
#include "Type.hpp"

#include <iostream>
#include <string>

const std::string AST_node::s_print_tab = ".   ";

AST_node::AST_node()
    : m_sibling(nullptr) {}

AST_node::AST_node(bool is_root)
    : m_sibling(nullptr)
{
    // std::cout << "Construct" << std::endl;
}

AST_node::AST_node(const AST_node &node)
    : m_linenum(node.m_linenum),
      m_type(node.m_type),
      m_subtype(node.m_subtype),
      m_sibling(nullptr)
{
    std::cout << "Copy construct" << std::endl;
    for (const auto child : node.m_children)
    {
        add_child(new AST_node(child));
    }

    AST_node *walker = node.m_sibling;
    while (walker != NULL)
    {
        add_sibling(new AST_node(*walker));
        walker = walker->m_sibling;
    }
}

AST_node::~AST_node()
{
    std::cout << "\nDestruct\n" << std::endl;
    if (m_sibling != nullptr)
    {
        delete m_sibling;
    }

    for (auto &child : m_children)
    {
        delete child;
    }
}

AST_node::AST_node(Type::Declaration subtype)
    : m_type(Type::Node::Declaration),
      m_subtype((int)subtype),
      m_sibling(nullptr)
{
    // std::cout << "Construct delcaration" << std::endl;
}

AST_node::AST_node(Type::Statement subtype)
    : m_type(Type::Node::Statement),
      m_subtype((int)subtype),
      m_sibling(nullptr)
{
    // std::cout << "Construct statement" << std::endl;
}

AST_node::AST_node(Type::Expression subtype)
    : m_type(Type::Node::Expression),
      m_subtype((int)subtype),
      m_sibling(nullptr)
{
    // std::cout << "Construct expression" << std::endl;
}

void AST_node::add_child(AST_node *node)
{
    // std::cout << "add child" << std::endl;
    if (node == nullptr)
    {
        std::cout << "\nnot adding null as child\n\n";
        return;
    }

    static int count = 1;
    std::cout << "add child: " << count << std::endl;
    count++;
    m_children.push_back(node);
}

void AST_node::add_sibling(AST_node *node)
{
    // std::cout << "add sibling" << std::endl;
    if (node == nullptr)
    {
        std::cout << "\nnot adding null as sibling\n\n";
        return;
    }

    static int count = 1;
    if (m_sibling != nullptr)
    {
        m_sibling->add_sibling(node);
    }
    else
    {
        std::cout << "add sibling: " << count << std::endl;
        count++;
        m_sibling = node;
    }
}

std::string AST_node::to_string() const
{
    // std::cout << "to string" << std::endl;
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
        case Type::Statement::Assign:
            return "Assign";
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
    // std::cout << "print" << std::endl;
    std::cout << to_string() << std::endl;

    for (const auto child : m_children)
    {
        child->print(1, "Child: ");
    }

    if (m_sibling != nullptr)
    {
        std::cout << "Sibling: ";
        m_sibling->print();
    }
}

void AST_node::print(unsigned num_indents, const std::string &prefix) const
{
    // std::cout << "print with indent" << std::endl;
    for (unsigned i = 0; i < num_indents; i++)
    {
        std::cout << s_print_tab;
    }

    std::cout << prefix << to_string() << std::endl;

    for (const auto child : m_children)
    {
        child->print(num_indents + 1, "Child: ");
    }

    if (m_sibling != nullptr)
    {
        m_sibling->print(num_indents, "Sibling: ");
    }
}

int AST_node::number_of_nodes() const
{
    int sum = 0;

    if (m_sibling == nullptr)
    {
        sum += 1;
    }
    else
    {
        sum += 1 + m_sibling->number_of_nodes();
    }

    for (const auto &child : m_children)
    {
        sum += child->number_of_nodes();
    }

    return sum;
}