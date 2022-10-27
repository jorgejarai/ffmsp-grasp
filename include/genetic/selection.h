#ifndef GENETIC_SELECTION_H
#define GENETIC_SELECTION_H

#include <string>
#include <utility>
#include <vector>

namespace genetic {

namespace selection {

std::vector<std::pair<std::string, size_t>> tournament(
    const std::vector<std::pair<std::string, size_t>>& pop, size_t best_n);
std::vector<std::pair<std::string, size_t>> roulette(
    const std::vector<std::pair<std::string, size_t>>& pop, size_t best_n);
std::vector<std::pair<std::string, size_t>> random(
    const std::vector<std::pair<std::string, size_t>>& pop, size_t best_n);

}  // namespace selection

}  // namespace genetic

#endif  // GENETIC_SELECTION_H
