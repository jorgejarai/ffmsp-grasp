#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "argumentum/argparse.h"
#include "ffmsp.h"

#define STRING_COUNT 10

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
    auto parser = argumentum::argument_parser{};
    auto params = parser.params();

    parser.config().program(argv[0]);

    std::string instance;
    double alpha;
    double threshold;
    std::size_t initial_pop;
    int timeout;
    int crossover;
    int mutation;
    int selection;
    double crossover_rate;
    double mutation_rate;
    bool tuning;

    params.add_parameter(instance, "-i").nargs(1);
    params.add_parameter(alpha, "-a").nargs(1);
    params.add_parameter(threshold, "--th").nargs(1);
    params.add_parameter(initial_pop, "--pop").nargs(1);
    params.add_parameter(timeout, "-t").nargs(1);
    params.add_parameter(crossover, "--crossover").nargs(1);
    params.add_parameter(mutation, "--mutation").nargs(1);
    params.add_parameter(selection, "--selection").nargs(1);
    params.add_parameter(crossover_rate, "--replace-rate").nargs(1);
    params.add_parameter(mutation_rate, "--mut-rate").nargs(1);
    params.add_parameter(tuning, "--tuning").nargs(0);

    if (!parser.parse_args(argc, argv, 1)) {
        return 1;
    }

    const auto strings = read_file(instance);

    if (strings.empty()) {
        return 1;
    }

    ffmsp::genetic(strings, initial_pop, threshold, alpha, timeout,
                   crossover_rate, mutation_rate,
                   static_cast<ffmsp::crossover_type>(crossover),
                   static_cast<ffmsp::mutation_type>(mutation),
                   static_cast<ffmsp::selection_type>(selection), tuning);

    return 0;
}
