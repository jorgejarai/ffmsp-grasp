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

std::string genetic::mutation::swap_mutation(const std::string& str) {
    std::size_t swap_position1 =
        RNG::get_instance().rand_int(0, str.size() - 1);
    std::size_t swap_position2 =
        RNG::get_instance().rand_int(0, str.size() - 1);
    std::string ret{str};
    auto aux = ret[swap_position1];
    ret[swap_position1] = ret[swap_position2];
    ret[swap_position2] = aux;
    return ret;
}

std::string genetic::mutation::scramble_mutation(const std::string& str) {
    std::size_t scramble_position_start =
        RNG::get_instance().rand_int(0, str.size() - 1);
    std::size_t scramble_position_end =
        RNG::get_instance().rand_int(0, str.size() - 1);
    if (scramble_position_end < scramble_position_start) {
        auto aux = scramble_position_start;
        scramble_position_start = scramble_position_end;
        scramble_position_end = aux;
    }
    std::string ret{str};
    for (size_t i = scramble_position_start; i < scramble_position_end; i++) {
        auto new_value = RNG::get_instance().rand_choose(
            std::vector<char>({'A', 'C', 'G', 'T'}));
        char n = new_value;
        ret[i] = n;
    }
    return ret;
}
