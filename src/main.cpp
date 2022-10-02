#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "args.h"
#include "ffmsp.h"
#include "rng.h"
#include "timer.h"

#define STRING_COUNT 10

const std::vector<Arguments::ArgDefinition> args_list{
    {'i', Arguments::ArgDefinition::STRING, false},
    {'t', Arguments::ArgDefinition::DOUBLE, false},
    {'a', Arguments::ArgDefinition::DOUBLE, true},
    {
        'm',
        Arguments::ArgDefinition::INT,
        true,
    }};

void check_args(const Arguments& args) {
    const auto instance_arg = args.get<std::string>('i');
    const auto threshold_arg = args.get<double>('t');
    const auto alpha_arg = args.get<double>('a');
    const auto max_time_arg = args.get<int>('m');

    if (!instance_arg || !threshold_arg) {
        std::exit(1);
    }

    const auto threshold = threshold_arg.value();
    const auto alpha = alpha_arg.value_or(0.9);
    const auto max_time = max_time_arg.value_or(30);

    if (threshold < 0 || threshold > 1 || alpha < 0 || alpha > 1 ||
        max_time < 0) {
        std::exit(1);
    }
}

std::vector<std::string> read_file(const std::string& path) {
    std::ifstream instance_file;
    instance_file.open(path);

    if (!instance_file.is_open()) {
        std::exit(1);
    }

    std::vector<std::string> ret;

    while (!instance_file.eof()) {
        std::string line;
        getline(instance_file, line);

        if (line.empty()) {
            continue;
        }

        ret.push_back(line);
    }

    instance_file.close();

    return ret;
}

int main(int argc, char* argv[]) {
    const Arguments args(args_list, argc, argv);
    check_args(args);

    const auto instance = args.get<std::string>('i').value();
    const auto threshold = args.get<double>('t').value();
    const auto alpha = args.get<double>('a').value_or(0.9);
    const auto max_time = args.get<int>('m').value_or(30);

    const auto strings = read_file(instance);

    ffmsp::grasp(strings, threshold, alpha, max_time);

    return 0;
}
