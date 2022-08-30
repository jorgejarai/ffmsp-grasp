#ifndef ARGS_H
#define ARGS_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

class Arguments {
private:
    std::vector<char> m_def;
    std::map<char, int> m_args;

    std::string gen_getopt();

public:
    Arguments(const std::vector<char>& args, int argc, char* argv[]);

    int operator[](char arg) const;
    int get(char arg) const;
};

#endif  // ARGS_H