#include "ffmsp.h"

std::size_t ffmsp::hamming(const std::string& str1, const std::string& str2) {
    const std::size_t min_size = std::min(str1.size(), str2.size());

    std::size_t distance = 0;
    for (std::size_t i = 0; i < min_size; ++i) {
        if (str1[i] != str2[i]) {
            ++distance;
        }
    }

    return distance;
}

std::size_t ffmsp::metric(const std::vector<std::string>& strings,
                          const std::string& candidate, double threshold) {
    const auto threshold_count =
        static_cast<std::size_t>(threshold * strings[0].size());

    std::size_t metric = 0;

    for (const auto& str : strings) {
        if (hamming(str, candidate) >= threshold_count) {
            ++metric;
        }
    }

    return metric;
}
