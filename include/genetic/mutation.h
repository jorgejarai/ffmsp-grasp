#ifndef GENETIC_MUTATION_H
#define GENETIC_MUTATION_H

#include <string>
#include <utility>
#include <vector>

namespace genetic {

namespace mutation {

std::string bit_flip(const std::string& str);
std::string swap_mutation(const std::string& str);
std::string scramble_mutation(const std::string& str);

}  // namespace mutation

}  // namespace genetic

#endif  // GENETIC_MUTATION_H
