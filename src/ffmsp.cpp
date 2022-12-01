#include "ffmsp.h"

#include <algorithm>

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

static std::size_t heuristic_eval(const std::vector<std::string>& strings_over,
                                  const std::vector<std::string>& strings_under,
                                  const std::string& candidate,
                                  double threshold) {
    const std::size_t hamming_sum =
        std::accumulate(std::begin(strings_over), std::end(strings_over), 0,
                        [&candidate](std::size_t sum, const std::string& str) {
                            return sum + ffmsp::hamming(str, candidate);
                        });
    const std::size_t max_under =
        std::accumulate(std::begin(strings_under), std::end(strings_under), 0,
                        [](std::size_t acc, const std::string& str) {
                            const auto hamming = ffmsp::hamming(str, candidate);

                            return std::max(acc, hamming);
                        });

    return hamming_sum + max_under;
}

std::size_t ffmsp::metric(const std::vector<std::string>& strings,
                          const std::string& candidate, double threshold) {
    const auto threshold_count =
        static_cast<std::size_t>(threshold * strings[0].size());

    std::vector<std::string> strings_over;
    std::vector<std::string> strings_under;

    for (const auto& str : strings) {
        if (hamming(str, candidate) >= threshold_count) {
            strings_over.push_back(str);
        } else {
            strings_under.push_back(str);
        }
    }

    const auto heuristic =
        heuristic_eval(strings_over, strings_under, candidate, threshold);

    return 0;
}
