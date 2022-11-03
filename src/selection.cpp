#include "genetic/selection.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "rng.h"

std::vector<std::pair<std::string, size_t>> genetic::selection::tournament(
    const std::vector<std::pair<std::string, size_t>>& pop, size_t best_n) {
    std::vector<std::pair<std::string, size_t>> temp;
    std::vector<std::pair<std::string, size_t>> tournament;
    size_t k = 3;
    for (size_t i = 0; i < best_n; i++) {
        int selected = RNG::get_instance().rand_int(0, pop.size());
        for (size_t j = 0; j < k; j++) {
            if (std::find(tournament.begin(), tournament.end(),
                          pop.at(selected)) != tournament.end() &&
                std::find(temp.begin(), temp.end(), pop.at(selected)) !=
                    tournament.end()) {
                tournament.push_back(pop.at(selected));
            } else {
                int selected = RNG::get_instance().rand_int(0, pop.size());
                while (std::find(tournament.begin(), tournament.end(),
                                 pop.at(selected)) != tournament.end() &&
                       std::find(temp.begin(), temp.end(), pop.at(selected)) !=
                           tournament.end()) {
                    int selected = RNG::get_instance().rand_int(0, pop.size());
                }
                tournament.push_back(pop.at(selected));
            }
        }
        std::sort(tournament.begin(), tournament.end(),
                  [](const std::pair<std::string, size_t>& a,
                     const std::pair<std::string, size_t>& b) {
                      return a.second < b.second;
                  });
        temp.push_back(tournament.back());
    }
    return temp;
}

std::vector<std::pair<std::string, size_t>> genetic::selection::roulette(
    const std::vector<std::pair<std::string, size_t>>& pop, size_t best_n) {
    std::vector<std::pair<std::string, size_t>> temp;
    std::vector<size_t> selected;

    size_t sum = 0;
    for (size_t i = 0; i < pop.size(); i++) {
        sum += pop.at(i).second;
    }

    for (size_t i = 0; i < best_n; i++) {
        size_t temp_selected;
        temp_selected = RNG::get_instance().rand_int(0, sum);
        selected.push_back(temp_selected);
    }

    int currentSum = 0;
    for (size_t i = 0; i < pop.size(); i++) {
        currentSum += pop.at(i).second;
        if (temp.size() < best_n) {
            for (size_t j = 0; j < selected.size(); j++) {
                if (selected.at(i) < currentSum &&
                    selected.at(i) > currentSum - pop.at(i).second) {
                    temp.push_back(pop.at(i));
                }
            }
        }
    }

    return temp;
}

std::vector<std::pair<std::string, size_t>> genetic::selection::random(
    const std::vector<std::pair<std::string, size_t>>& pop, size_t best_n) {
    std::vector<std::pair<std::string, size_t>> temp;
    for (size_t i = 0; i < best_n; i++) {
        int selected = RNG::get_instance().rand_int(0, pop.size());
        if (std::find(temp.begin(), temp.end(), pop.at(selected)) !=
            temp.end()) {
            temp.push_back(pop.at(selected));
        } else {
            int selected = RNG::get_instance().rand_int(0, pop.size());
            while (std::find(temp.begin(), temp.end(), pop.at(selected)) !=
                   temp.end()) {
                selected = RNG::get_instance().rand_int(0, pop.size());
            }
            temp.push_back(pop.at(selected));
        }
    }
    return temp;
}
