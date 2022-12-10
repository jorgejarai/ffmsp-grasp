#include "ffmsp/ils.h"

#include <chrono>

#include "ffmsp/ffmsp.h"
#include "ffmsp/grasp.h"
#include "ffmsp/greedy.h"
#include "rng.h"

std::string perturbate(const std::string& solution, double alpha) {
    std::string ret = solution;

    std::size_t n = solution.size();
    std::size_t k = static_cast<std::size_t>(alpha * n);

    for (std::size_t i = 0; i < k; ++i) {
        std::size_t j = RNG::get_instance().rand_int(0, n - 1);
        ret[j] = RNG::get_instance().rand_choose(ffmsp::ALPHABET);
    }

    return ret;
}

ffmsp::result ffmsp::ils(const std::vector<std::string>& strings,
                         double threshold, double alpha, int max_time) {
    using std::chrono::duration;
    using std::chrono::high_resolution_clock;
    using std::chrono::seconds;

    const auto metric = [&strings, threshold](const std::string& candidate) {
        return ffmsp::metric(strings, candidate, threshold);
    };

    std::string best_solution =
        ffmsp::random_greedy(strings, threshold, alpha).str;
    best_solution = ffmsp::local_search(strings, best_solution, threshold);
    std::size_t best_metric = metric(best_solution);

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

    return {"", 0};
}
