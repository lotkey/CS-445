#pragma once

#include <string>

namespace strutil
{
    std::string remove_quotes(const std::string &);
    int str_len(const std::string &);
    char get_char(const std::string &, int &);
    std::string make_str(const std::string &);
}