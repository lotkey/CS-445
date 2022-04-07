#pragma once

#include "ourgetopt/ourgetopt.hpp"

#include <optional>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

class Options {
  public:
    /// Construct and parse the command line arguments
    Options(int argc, char **argv);
    /// @returns True if the user said to print the AST
    bool print() const;
    /// @returns True if the user said to print parser debugging information
    bool debug() const;
    /// @returns True if the user said to print symbol table debugging
    bool debugSymbolTable() const;
    /// @returns True if the user said to print type information in the AST
    bool printTypeInfo() const;
    bool printSymbolInfo() const;
    /// @returns The filename of the file the user provided, if any
    const std::optional<std::string> &file() const;

  private:
    std::optional<std::string> m_file;
    bool m_print = false;
    bool m_debug = false;
    bool m_debugSymTbl = false;
    bool m_printTypeInfo = false;
    bool m_printSymbolInfo = false;
};