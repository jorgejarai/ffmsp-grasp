#ifndef FFMSP_ILS_H
#define FFMSP_ILS_H

#include "ffmsp/ffmsp.h"

namespace ffmsp {

result ils(const std::vector<std::string>& strings, double threshold,
           double determinism, double perturbation_rate, int max_time,
           bool tuning);

}  // namespace ffmsp

#endif  // FFMSP_ILS_H
