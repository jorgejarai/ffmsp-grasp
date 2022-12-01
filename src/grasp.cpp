#include "ffmsp/grasp.h"

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

static std::string local_search(const std::vector<std::string>& strings,
                                const std::string& solution, double threshold) {
    const auto metric = [&strings, threshold](const std::string& candidate) {
        return ffmsp::metric(strings, candidate, threshold);
    };

    std::string ret = solution;

    for (std::size_t i = 0; i < ret.size(); ++i) {
        for (const char other_c : alphabet_without(ret[i])) {
            std::string new_solution{ret};
            new_solution[i] = other_c;

            std::size_t new_metric = metric(new_solution);
            std::size_t ret_metric = metric(ret);

            if (new_metric > ret_metric) {
                ret = new_solution;
            }
        }
    }

    return ret;
}

ffmsp::result ffmsp::grasp(const std::vector<std::string>& strings,
                           double threshold, double alpha, int max_time) {
    using std::chrono::duration;
    using std::chrono::high_resolution_clock;
    using std::chrono::seconds;

    std::cout << std::fixed << std::setprecision(3);

    const auto metric = [&strings, threshold](const std::string& candidate) {
        return ffmsp::metric(strings, candidate, threshold);
    };

    std::string best_solution;
    std::size_t best_metric = 0;

    const auto start = high_resolution_clock::now();
    do {
        const auto result = ffmsp::random_greedy(strings, threshold, alpha);

        auto candidate{result.str};
        candidate = local_search(strings, candidate, threshold);

        const auto candidate_metric = metric(candidate);

        if (candidate_metric > best_metric) {
            best_solution = candidate;
            best_metric = candidate_metric;
        }
    } while (high_resolution_clock::now() - start < seconds(max_time));

    std::cout << -static_cast<int>(best_metric) << "\n";

    return {best_solution, best_metric};
}
