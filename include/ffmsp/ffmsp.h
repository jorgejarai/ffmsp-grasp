#ifndef FFMSP_FFMSP_H
#define FFMSP_FFMSP_H

#include <optional>
#include <string>
#include <vector>

namespace ffmsp {

struct result {
    std::string str;
    std::size_t metric;
};

std::size_t hamming(const std::string& a, const std::string& b);
std::size_t metric(const std::vector<std::string>& strings,
                   const std::string& candidate, double threshold);

}  // namespace ffmsp

#endif  // FFMSP_FFMSP_H
