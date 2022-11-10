#include "genetic/selection.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "rng.h"

std::string genetic::selection::tournament(
    const std::vector<std::pair<std::string, size_t>>& pop, size_t best_n) {
    std::vector<std::size_t> best_indices;
    best_indices.reserve(best_n);
    for (std::size_t i = 0; i < best_n; i++) {
        best_indices.push_back(RNG::get_instance().rand_int(0, pop.size() - 1));
    }

    std::vector<std::pair<std::string, size_t>> best;
    best.reserve(best_n);
    for (const auto& i : best_indices) {
        best.push_back(pop.at(i));
    }

    std::sort(best.begin(), best.end(),
              [](const std::pair<std::string, size_t>& a,
                 const std::pair<std::string, size_t>& b) {
                  return a.second > b.second;
              });

    return best.at(0).first;
}

std::string genetic::selection::roulette(
    const std::vector<std::pair<std::string, size_t>>& pop) {
    std::vector<std::pair<double, double>> probabilities;

    size_t total_fitness = 0;
    for (const auto& p : pop) {
        total_fitness += p.second;
    }

    double cur_prob = 0.0;
    for (const auto& p : pop) {
        double prob =
            static_cast<double>(p.second) / static_cast<double>(total_fitness);
        probabilities.push_back({cur_prob, prob});

        cur_prob += prob;
    }

    double selected = RNG::get_instance().rand_real(0.0, 1.0);
    std::string ret;

    for (std::size_t i = 0; i < probabilities.size(); i++) {
        if (selected >= probabilities.at(i).first &&
            selected < probabilities.at(i).first + probabilities.at(i).second) {
            ret = pop.at(i).first;
        }
    }

    return ret;
}

std::string genetic::selection::random(
    const std::vector<std::pair<std::string, size_t>>& pop) {
    const std::size_t index = RNG::get_instance().rand_int(0, pop.size() - 1);

    return pop.at(index).first;
}
