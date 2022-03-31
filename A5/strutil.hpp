#pragma once

#include <memory>
#include <string>
#include <vector>

class strutil {
  public:
    static std::string remove_quotes(std::string);
    static std::string make_str(const std::string &);
    static char make_char(const std::string &);
    static char make_char(const std::string &, int linenumber);
    static int str_len(const std::string &);
    template <typename... Args>
    static std::string format(const std::string &fmt, Args... args);
    static std::vector<std::string> split(std::string);
    static size_t find_first_of_any(const std::string&, const std::vector<std::string>&);

  private:
    static char get_char(const std::string &, int &);
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