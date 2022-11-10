#ifndef GENETIC_SELECTION_H
#define GENETIC_SELECTION_H

#include <string>
#include <utility>
#include <vector>

namespace genetic {

namespace selection {

std::string tournament(const std::vector<std::pair<std::string, size_t>>& pop,
                       size_t best_n);
std::string roulette(const std::vector<std::pair<std::string, size_t>>& pop);
std::string random(const std::vector<std::pair<std::string, size_t>>& pop);

}  // namespace selection

}  // namespace genetic

#endif  // GENETIC_SELECTION_H
