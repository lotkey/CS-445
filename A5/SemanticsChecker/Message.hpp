#pragma once

#include "../strutil.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

class Message {
  public:
    enum class Type { Error, Warning };

    template <typename... Args>
    static void add(int lineNumber, Type type, const std::string &format,
                    Args... args);
    template <typename... Args>
    static void addStringMessageBefore(std::string label, Type type,
                                       const std::string &format, Args... args);
    template <typename... Args>
    static void addStringMessageAfter(std::string label, Type type,
                                      const std::string &format, Args... args);
    template <typename... Args>
    static void addSyntaxMessage(int lineNumber, Type type,
                                 const std::string &format, Args... args);

    static int numberOf(Type);
    static void print(bool verbose = false);
    static std::string toString(bool verbose = false);
    static void reset();

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