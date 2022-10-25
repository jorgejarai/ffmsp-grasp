#include "genetic/mutation.h"

#include "rng.h"

std::string genetic::mutation::bit_flip(const std::string& str) {
    auto bit_flip_position = RNG::get_instance().rand_int(0, str.size() - 1);
    auto new_value = RNG::get_instance().rand_choose(
        std::vector<char>({'A', 'C', 'G', 'T'}));

    char n = new_value;
    std::string ret{str};
    ret[bit_flip_position] = n;
    return ret;
}