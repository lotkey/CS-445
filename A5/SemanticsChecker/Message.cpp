#include "Message.hpp"

unsigned Message::s_numerrors = 0;
unsigned Message::s_numwarnings = 0;

const std::map<Message::Type, std::string> Message::s_typeToString = {
    {Type::Error, "ERROR"}, {Type::Warning, "WARNING"}};

Message::Message(Type type, const std::string &content)
    : m_type(type), m_content(content) {
    if (type == Type::Error) {
        s_numerrors++;
    } else {
        s_numwarnings++;
    }
}

Message::Type Message::type() const { return m_type; }

std::string Message::content() const { return m_content; }

std::string Message::toString(int linenumber) const {
    return s_typeToString.at(m_type) + "(" + std::to_string(linenumber) +
           "): " + m_content;
}

unsigned Message::numErrors() { return s_numerrors; }

unsigned Message::numWarnings() { return s_numwarnings; }

void Message::reset() {
    s_numerrors = 0;
    s_numwarnings = 0;
}