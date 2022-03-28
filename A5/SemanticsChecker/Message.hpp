#pragma once

#include <map>
#include <string>

class Message {
  public:
    enum class Type { Error, Warning };

    /// Construct a message
    /// @param type Type of message
    /// @param content Content of message
    Message(Type type, const std::string &content);
    /// @returns Type of message
    Type type() const;
    /// @returns Content of message
    std::string content() const;
    std::string toString(int linenumber) const;

    /// Reset static counters
    static void reset();
    /// @returns Number of warnings constructed since last reset
    static unsigned numWarnings();
    /// @returns Number of errors constructed since last reset
    static unsigned numErrors();

  private:
    static const std::map<Type, std::string> s_typeToString;
    static unsigned s_numerrors;
    static unsigned s_numwarnings;

    Type m_type;
    std::string m_content;
};