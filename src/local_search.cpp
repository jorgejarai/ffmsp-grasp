#include "ffmsp/local_search.h"

#include <algorithm>
#include <future>
#include <iomanip>
#include <iostream>
#include <optional>
#include <set>

#include "ffmsp/ffmsp.h"
#include "ffmsp/greedy.h"

static std::vector<char> alphabet_without(char c) {
    switch (c) {
    case 'A':
        return {'C', 'G', 'T'};
    case 'C':
        return {'A', 'G', 'T'};
    case 'G':
        return {'A', 'C', 'T'};
    case 'T':
        return {'A', 'C', 'G'};
    default:
        throw std::invalid_argument("invalid character");
    }
}

std::string ffmsp::local_search(const std::vector<std::string>& strings,
                                const std::string& solution, double threshold) {
    const auto metric = [&strings, threshold](const std::string& candidate) {
        return ffmsp::metric(strings, candidate, threshold);
    };

    std::string ret = solution;
    bool mejora = true;
    while (mejora) {
        mejora = false;
        for (std::size_t i = 0; i < ret.size(); ++i) {
            for (const char other_c : alphabet_without(ret[i])) {
                std::string new_solution{ret};
                new_solution[i] = other_c;

                std::size_t new_metric = metric(new_solution);
                std::size_t ret_metric = metric(ret);

                if (new_metric > ret_metric) {
                    ret = new_solution;
                    mejora = true;
                }
            }
        }
    }
    return ret;
}
