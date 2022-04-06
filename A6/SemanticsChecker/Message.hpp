#pragma once

#include "../strutil.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

class Message {
  public:
    enum class Type { Error, Warning };

    /// Adds a message
    /// @param lineNumber Line the message is related to
    /// @param type Type of message (error, warning)
    /// @param format Format for printf-style formatting
    /// @param args Optional args for printf-style formatting
    template <typename... Args>
    static void add(int lineNumber, Type type, const std::string &format,
                    Args... args);
    /// Adds a string message to be printed out before the numbered messages
    /// @param label String label for the message
    /// @param type Type of message (error, warning)
    /// @param format Format for printf-style formatting
    /// @param args Optional args for printf-style formatting
    template <typename... Args>
    static void addStringMessageBefore(std::string label, Type type,
                                       const std::string &format, Args... args);
    /// Adds a string message to be printed out before the after messages
    /// @param label String label for the message
    /// @param type Type of message (error, warning)
    /// @param format Format for printf-style formatting
    /// @param args Optional args for printf-style formatting
    template <typename... Args>
    static void addStringMessageAfter(std::string label, Type type,
                                      const std::string &format, Args... args);
    /// Adds a syntax message
    /// @param lineNumber Line the message is related to
    /// @param type Type of message (error, warning)
    /// @param format Format for printf-style formatting
    /// @param args Optional args for printf-style formatting
    template <typename... Args>
    static void addSyntaxMessage(int lineNumber, Type type,
                                 const std::string &format, Args... args);
    /// @param type The type of message to count
    /// @returns The number of a certain type of message
    static int numberOf(Type type);
    /// Prints if verbose. If there are syntax messages, these are printed and
    /// any other type of message is not printed.
    /// @param verbose Whether or not to print messages
    static void print(bool verbose = false);
    /// Clears any messages and resets all counts
    static void reset();
    /// Prints the number of errors and warnings
    static void printCounts();

  private:
    static const std::map<Type, std::string> s_typeToString;
    static std::map<int, std::vector<std::string>> s_messages;
    static std::map<std::string, std::vector<std::string>>
        s_stringMessagesBefore;
    static std::map<std::string, std::vector<std::string>>
        s_stringMessagesAfter;
    static std::map<int, std::vector<std::string>> s_syntaxMessages;
    static std::map<Type, int> s_counts;
    static std::map<Type, int> s_syntaxCounts;

    static std::string toString(bool verbose = false);
    static std::string counts();
};

template <typename... Args>
void Message::add(int lineNumber, Type type, const std::string &format,
                  Args... args) {
    if (lineNumber < 1) {
        return;
    }
    std::string message = strutil::format(format, args...);
    message = strutil::format("%s(%d): %s", s_typeToString.at(type).c_str(),
                              lineNumber, message.c_str());
    s_messages[lineNumber].push_back(message);
    s_counts[type]++;
}

template <typename... Args>
void Message::addStringMessageBefore(std::string label, Type type,
                                     const std::string &format, Args... args) {
    std::string message = strutil::format(format, args...);
    message = strutil::format("%s(%s): %s", s_typeToString.at(type).c_str(),
                              label.c_str(), message.c_str());
    s_stringMessagesBefore[label].push_back(message);
    s_counts[type]++;
}

template <typename... Args>
void Message::addStringMessageAfter(std::string label, Type type,
                                    const std::string &format, Args... args) {
    std::string message = strutil::format(format, args...);
    message = strutil::format("%s(%s): %s", s_typeToString.at(type).c_str(),
                              label.c_str(), message.c_str());
    s_stringMessagesAfter[label].push_back(message);
    s_counts[type]++;
}

template <typename... Args>
void Message::addSyntaxMessage(int lineNumber, Type type,
                               const std::string &format, Args... args) {
    std::string message = strutil::format(format, args...);
    message = strutil::format("%s(%d): %s", s_typeToString.at(type).c_str(),
                              lineNumber, message.c_str());
    s_syntaxMessages[lineNumber].push_back(message);
    s_syntaxCounts[type]++;
}