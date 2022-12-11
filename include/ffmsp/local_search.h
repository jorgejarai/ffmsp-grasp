#ifndef FFMSP_LOCAL_SEARCH_H
#define FFMSP_LOCAL_SEARCH_H

#include "ffmsp/ffmsp.h"

namespace ffmsp {

std::string local_search(const std::vector<std::string>& strings,
                         const std::string& solution, double threshold);

}  // namespace ffmsp

#endif  // FFMSP_LOCAL_SEARCH_H
