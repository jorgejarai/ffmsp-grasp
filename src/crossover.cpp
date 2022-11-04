#include "genetic/crossover.h"

#include "rng.h"

std::string genetic::crossover::one_point(const std::string& parent1,
                                          const std::string& parent2) {
    const auto crossover_point =
        RNG::get_instance().rand_int(0, parent1.size() - 1);

    std::string ret;

    for (auto i = 0; i < crossover_point; ++i) {
        ret += parent1[i];
    }

    for (auto i = crossover_point; i < parent2.size(); ++i) {
        ret += parent2[i];
    }

    return ret;
}

std::string genetic::crossover::two_point(const std::string& parent1,
                                          const std::string& parent2) {
    const auto crossover_point1 =
        RNG::get_instance().rand_int(0, parent1.size() - 1);

    const auto crossover_point2 =
        RNG::get_instance().rand_int(0, parent1.size() - 1);

    const auto min_point = std::min(crossover_point1, crossover_point2);
    const auto max_point = std::max(crossover_point1, crossover_point2);

    std::string ret;

    for (auto i = 0; i < min_point; ++i) {
        ret += parent1[i];
    }

    for (auto i = min_point; i < max_point; ++i) {
        ret += parent2[i];
    }

    for (auto i = max_point; i < parent2.size(); ++i) {
        ret += parent1[i];
    }

    return ret;
}

std::string genetic::crossover::uniform(const std::string& parent1,
                                        const std::string& parent2) {
    std::string ret;

    for (auto i = 0; i < parent1.size(); ++i) {
        if (RNG::get_instance().rand_bool()) {
            ret += parent1[i];
        } else {
            ret += parent2[i];
        }
    }

    return ret;
}
