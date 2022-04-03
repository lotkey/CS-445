#include "Message.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

const std::map<Message::Type, std::string> Message::s_typeToString = {
    {Type::Error, "ERROR"}, {Type::Warning, "WARNING"}};
std::map<int, std::vector<std::string>> Message::s_messages;
std::map<std::string, std::vector<std::string>> Message::s_stringMessagesBefore;
std::map<std::string, std::vector<std::string>> Message::s_stringMessagesAfter;
std::map<int, std::vector<std::string>> Message::s_syntaxMessages;
std::map<Message::Type, int> Message::s_counts = {{Type::Error, 0},
                                                  {Type::Warning, 0}};
std::map<Message::Type, int> Message::s_syntaxCounts = {{Type::Error, 0},
                                                        {Type::Warning, 0}};

void Message::print(bool verbose) {
    std::cout << toString(verbose) << std::endl;
}

int Message::numberOf(Type type) {
    if (s_syntaxCounts[type] > 0) {
        return s_syntaxCounts[type];
    } else {
        return s_counts[type];
    }
}

std::string Message::toString(bool verbose) {
    std::string str;
    if (s_syntaxMessages.empty()) {
        if (verbose) {
            for (const auto &[label, bucket] : s_stringMessagesBefore) {
                for (auto it = bucket.rbegin(); it != bucket.rend(); it++) {
                    str += *it;
                    str += "\n";
                }
            }

            for (const auto &[lineNumber, bucket] : s_messages) {
                for (auto it = bucket.rbegin(); it != bucket.rend(); it++) {
                    str += *it;
                    str += "\n";
                }
            }

            for (const auto &[lineNumber, bucket] : s_stringMessagesAfter) {
                for (auto it = bucket.rbegin(); it != bucket.rend(); it++) {
                    str += *it;
                    str += "\n";
                }
            }
        }
        str += strutil::format("Number of warnings: %d\n",
                               s_counts[Type::Warning]);
        str += strutil::format("Number of errors: %d", s_counts[Type::Error]);
    } else {
        for (const auto &[lineNumber, bucket] : s_syntaxMessages) {
            for (auto it = bucket.rbegin(); it != bucket.rend(); it++) {
                str += *it;
                str += "\n";
            }
        }

        str += strutil::format("Number of warnings: %d\n",
                               s_syntaxCounts[Type::Warning]);
        str += strutil::format("Number of errors: %d",
                               s_syntaxCounts[Type::Error]);
    }
    return str;
}

void Message::reset() {
    s_messages.clear();
    s_stringMessagesBefore.clear();
    s_stringMessagesAfter.clear();
    s_syntaxMessages.clear();
    s_counts = {{Type::Error, 0}, {Type::Warning, 0}};
    s_syntaxCounts = {{Type::Error, 0}, {Type::Warning, 0}};
}