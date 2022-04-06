#pragma once

#include <memory>
#include <string>
#include <vector>

class strutil {
  public:
    /// @returns string with a quotation mark removed from the beginning and the
    /// end.
    static std::string remove_quotes(std::string);
    /// @returns a string with escaped characters.
    /// ie, make_str("tab\\t") returns a string with an actual '\\t' character
    /// in it.
    static std::string make_str(const std::string &);
    /// @returns a character from the string, following escaping rules.
    static char make_char(const std::string &);
    /// @returns the length of the string following escaping rules.
    /// ie, str_len("text\\t") would return 5 instead of 6.
    static int str_len(const std::string &);
    /// printf-style formatting
    /// @param fmt Format
    /// @param args Optional arguments for formatting
    template <typename... Args>
    static std::string format(const std::string &fmt, Args... args);
    /// Splits a string on whitespace
    /// @returns Vector of strings that the string was split into
    static std::vector<std::string> split(std::string);
    /// @returns the index of the first match in the string, std::string::npos
    /// if none.
    static size_t find_first_of_any(const std::string &,
                                    const std::vector<std::string> &);

  private:
    /// Makes a char starting from the provided index. This could be a normal
    /// char, or an escaped char. Once done, index is updated to the starting
    /// index of the next character.
    /// @param s String to make a character from
    /// @param index The starting index of the character
    /// @returns The char made
    static char get_char(const std::string &s, int &index);
};

template <typename... Args>
std::string strutil::format(const std::string &fmt, Args... args) {
    int size_s = std::snprintf(nullptr, 0, fmt.c_str(), args...) + 1;
    if (size_s <= 0) {
        throw std::runtime_error("Error during formatting.");
    }
    auto size = static_cast<size_t>(size_s);
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, fmt.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1);
}