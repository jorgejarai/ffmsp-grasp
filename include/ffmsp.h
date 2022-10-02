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

std::size_t hamming(const std::string& a, const std::string& b);
std::size_t metric(const std::vector<std::string>& strings,
                   const std::string& candidate, double threshold);

}  // namespace ffmsp

#endif