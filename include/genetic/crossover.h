#ifndef GENETIC_CROSSOVER_H
#define GENETIC_CROSSOVER_H

#include <string>

namespace genetic {

namespace crossover {

std::string one_point(const std::string& parent1, const std::string& parent2);
std::string two_point(const std::string& parent1, const std::string& parent2);
std::string uniform(const std::string& parent1, const std::string& parent2);

}  // namespace crossover

}  // namespace genetic

#endif  // GENETIC_CROSSOVER_H
