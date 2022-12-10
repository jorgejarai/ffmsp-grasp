#ifndef FFMSP_GRASP_H
#define FFMSP_GRASP_H

#include "ffmsp/ffmsp.h"

namespace ffmsp {

result grasp(const std::vector<std::string>& strings, double threshold,
             double alpha, int max_time);

std::string local_search(const std::vector<std::string>& strings,
                         const std::string& solution, double threshold);

}  // namespace ffmsp

#endif  // FFMSP_GRASP_H
