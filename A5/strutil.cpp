#include <iostream>
#include <string>

#include "strutil.hpp"

std::string strutil::remove_quotes(std::string s) {
    return s.erase(0, 1).erase(s.length() - 1, s.length());
}

int strutil::str_len(const std::string &s) {
    int counter = 0;
    for (unsigned i = 0; i < s.length(); i++) {
        if (s[i] == '\\') {
            if (i == s.length() - 1) {
                return counter;
            } else {
                i++;
            }
        }
        counter++;
    }

    return counter;
}

char strutil::get_char(const std::string &s, int &index) {
    if (index >= s.length()) {
        throw std::runtime_error("getChar(): index out of bounds");
    }

    char c = '\0';

    if (s[index] == '\\') {
        if (s.length() - index > 1) {
            switch (s[index + 1]) {
            case 'n':
                c = '\n';
                break;
            case '0':
                c = '\0';
                break;
            default:
                c = s[index + 1];
                break;
            }
        }
        index += 2;
    } else {
        c = s[index];
        index++;
    }
    return c;
}

std::string strutil::make_str(const std::string &str) {
    std::string str2;
    for (int i = 0; i < str.length();) {
        str2 += get_char(str, i);
    }
    return str2;
}

char strutil::make_char(const std::string &str) {
    int index = 0;
    return get_char(str, index);
}

std::vector<std::string> strutil::split(std::string s) {
    std::vector<std::string> words;
    std::vector<std::string> delimiters = {" ", "\r", "\n", "\t", "\v", "\f"};

    size_t pos;
    while ((pos = find_first_of_any(s, delimiters)) != std::string::npos) {
        std::string word = s.substr(0, pos);
        if (!word.empty()) {
            words.push_back(word);
        }
        s.erase(0, pos + 1);
    }
    if (!s.empty()) {
        words.push_back(s);
    }

    return words;
}

size_t strutil::find_first_of_any(const std::string &text,
                                  const std::vector<std::string> &delimiters) {
    size_t first = std::string::npos;
    for (const auto &delimiter : delimiters) {
        size_t index = text.find_first_of(delimiter);
        if (index < first) {
            first = index;
        }
    }

    return first;
}