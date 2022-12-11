#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "argumentum/argparse.h"
#include "ffmsp/ils.h"

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
    double determinism;
    double perturbation_rate;
    double threshold;
    int timeout;
    bool tuning;

    params.add_parameter(instance, "-i").nargs(1);
    params.add_parameter(determinism, "-d").nargs(1);
    params.add_parameter(perturbation_rate, "-p").nargs(1);
    params.add_parameter(threshold, "--th").nargs(1);
    params.add_parameter(timeout, "-t").nargs(1);
    params.add_parameter(tuning, "--tuning").nargs(0);

    if (!parser.parse_args(argc, argv, 1)) {
        return 1;
    }

    const auto strings = read_file(instance);

    if (strings.empty()) {
        return 1;
    }

    ffmsp::ils(strings, threshold, determinism, perturbation_rate, timeout,
               tuning);

    return 0;
}
