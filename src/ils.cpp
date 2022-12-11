#include "ffmsp/ils.h"

#include <chrono>
#include <iomanip>
#include <iostream>

#include "ffmsp/ffmsp.h"
#include "ffmsp/grasp.h"
#include "ffmsp/greedy.h"
#include "rng.h"

static std::string initial_solution(const std::vector<std::string>& strings,
                                    double threshold, double alpha) {
    std::string best_solution =
        ffmsp::random_greedy(strings, threshold, alpha).str;
    best_solution = ffmsp::local_search(strings, best_solution, threshold);

    return best_solution;
}

static std::string perturbate(const std::string& solution, double alpha) {
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
                         double threshold, double determinism,
                         double perturbation_rate, int max_time, bool tuning) {
    using std::chrono::duration;
    using std::chrono::high_resolution_clock;
    using std::chrono::seconds;

    const auto metric = [&strings, threshold](const std::string& candidate) {
        return ffmsp::metric(strings, candidate, threshold);
    };

    auto best_solution = initial_solution(strings, threshold, determinism);
    std::size_t best_metric = metric(best_solution);

    std::cout << std::fixed << std::setprecision(3);

    if (!tuning) {
        std::cout << "[0.000] Fitness: " << static_cast<int>(best_metric)
                  << "\n";
    }

    const auto start = high_resolution_clock::now();
    do {
        auto candidate = perturbate(best_solution, perturbation_rate);
        candidate = local_search(strings, candidate, threshold);

        if (metric(candidate) > best_metric) {
            // if (ffmsp::is_str_better(strings, candidate, best_solution,
            //                          threshold)) {
            best_solution = candidate;
            best_metric = metric(best_solution);

            if (!tuning) {
                const auto now =
                    duration<double>(high_resolution_clock::now() - start)
                        .count();

                std::cout << "[" << now
                          << "] Fitness: " << static_cast<int>(best_metric)
                          << "\n";
            }
        }
    } while (high_resolution_clock::now() - start < seconds(max_time));

    if (tuning) {
        std::cout << -static_cast<int>(best_metric) << "\n";
    } else {
        const auto now =
            duration<double>(high_resolution_clock::now() - start).count();

        std::cout << "[" << now
                  << "] Fitness: " << static_cast<int>(best_metric) << "\n";
    }

    return {best_solution, best_metric};
}
