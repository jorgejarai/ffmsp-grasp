#ifndef FFMSP_H
#define FFMSP_H

#include <optional>
#include <string>
#include <vector>

namespace ffmsp {

struct result {
    std::string str;
    std::size_t metric;
};

result greedy(const std::vector<std::string>& strings, double threshold);
result random_greedy(const std::vector<std::string>& strings, double threshold,
                     double alpha);

result grasp(const std::vector<std::string>& strings, double threshold,
             double alpha, int max_time);

enum crossover_type { UNIFORM, SINGLE_POINT, TWO_POINT };
enum mutation_type { FLIP, SWAP, SCRAMBLE };
enum selection_type { ROULETTE, TOURNAMENT, RANK };

result genetic(const std::vector<std::string>& strings, double threshold,
               double alpha, int max_time, double crossover_rate,
               double mutation_rate, crossover_type crossover,
               mutation_type mutation, selection_type selection, bool tuning);

std::size_t hamming(const std::string& a, const std::string& b);
std::size_t metric(const std::vector<std::string>& strings,
                   const std::string& candidate, double threshold);

}  // namespace ffmsp

#endif
