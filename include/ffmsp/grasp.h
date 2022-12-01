#ifndef FFMSP_GRASP_H
#define FFMSP_GRASP_H

#include "ffmsp/ffmsp.h"

namespace ffmsp {

result grasp(const std::vector<std::string>& strings, double threshold,
             double alpha, int max_time);

}  // namespace ffmsp

#endif  // FFMSP_GRASP_H
