#ifndef FFMSP_GREEDY_H
#define FFMSP_GREEDY_H

#include "ffmsp/ffmsp.h"

namespace ffmsp {

result greedy(const std::vector<std::string>& strings, double threshold);
result random_greedy(const std::vector<std::string>& strings, double threshold,
                     double alpha);

}  // namespace ffmsp

#endif  // FFMSP_GREEDY_H
