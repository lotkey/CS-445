#pragma once

#include "ourgetopt/ourgetopt.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

class Options
{
public:
    Options(int argc, char **argv);
    bool print() const;
    bool debug() const;
    const std::vector<std::string> &files() const;

private:
    std::vector<std::string> m_files;
    bool m_print = false;
    bool m_debug = false;
};