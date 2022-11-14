#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <utility>

#include "ffmsp.h"
#include "genetic/crossover.h"
#include "genetic/mutation.h"
#include "genetic/selection.h"
#include "rng.h"

template <typename T>
static std::pair<std::string, std::size_t> calculate_best(const T& pop) {
    const auto best = std::max_element(pop.begin(), pop.end(),
                                       [](const auto& str1, const auto& str2) {
                                           return str1.second < str2.second;
                                       });

    return {best->first, best->second};
}

std::string crossover_fn(ffmsp::crossover_type type, std::string& str1,
                         const std::string& str2) {
    switch (type) {
    case ffmsp::SINGLE_POINT:
        return genetic::crossover::one_point(str1, str2);
    case ffmsp::TWO_POINT:
        return genetic::crossover::two_point(str1, str2);
    case ffmsp::UNIFORM:
    default:
        return genetic::crossover::uniform(str1, str2);
    }
}

std::string selection_fn(
    ffmsp::selection_type type,
    const std::vector<std::pair<std::string, std::size_t>>& pop) {
    switch (type) {
    case ffmsp::ROULETTE:
        return genetic::selection::roulette(pop);
    case ffmsp::RANDOM:
        return genetic::selection::random(pop);
    case ffmsp::TOURNAMENT:
    default:
        return genetic::selection::tournament(pop, 3);
    }

    return "";
}

std::string mutation_fn(ffmsp::mutation_type type, const std::string& str) {
    switch (type) {
    case ffmsp::FLIP:
        return genetic::mutation::bit_flip(str);
    case ffmsp::SWAP:
        return genetic::mutation::swap_mutation(str);
    case ffmsp::SCRAMBLE:
    default:
        return genetic::mutation::scramble_mutation(str);
    }

    return "";
}

ffmsp::result ffmsp::genetic(const std::vector<std::string>& strings,
                             std::size_t initial_pop, double threshold,
                             double alpha, int max_time, double crossover_rate,
                             double mutation_rate,
                             ffmsp::crossover_type crossover,
                             ffmsp::mutation_type mutation,
                             ffmsp::selection_type selection, bool tuning) {
    using std::chrono::duration;
    using std::chrono::high_resolution_clock;
    using std::chrono::seconds;

    std::cout << std::fixed << std::setprecision(3);

    const auto metric = [&strings, threshold](const std::string& candidate) {
        return ffmsp::metric(strings, candidate, threshold);
    };

    // Crear población inicial con greedy
    std::vector<std::string> population;
    std::map<std::string, std::size_t> metrics;

    for (std::size_t i = 0; i < initial_pop; ++i) {
        const auto res = ffmsp::random_greedy(strings, threshold, alpha);

        population.push_back(res.str);
        metrics[res.str] = res.metric;

        if (!tuning) {
            std::cout << "\rSeeding initial population (" << i + 1 << "/"
                      << initial_pop << ")" << std::flush;
        }
    }

    if (!tuning) {
        std::cout << '\n';
    }

    const auto first_best = calculate_best(metrics);

    std::string best_solution = first_best.first;
    std::size_t best_metric = first_best.second;

    if (!tuning) {
        std::cout << "Best greedy fitness: " << best_metric << "\n";
    }

    const auto start = high_resolution_clock::now();
    do {
        std::vector<std::string> new_population;

        // Calcular cantidad de crossovers
        size_t crossover_count =
            std::floor(population.size() * crossover_rate / 100 / 2);

        std::vector<std::pair<std::string, size_t>> pop;
        pop.reserve(population.size());
        for (const auto& str : population) {
            pop.push_back({str, metrics[str]});
        }

        // Hacer crossovers
        for (std::size_t i = 0; i < crossover_count; i++) {
            std::string parent1 = selection_fn(selection, pop);
            std::string parent2 = selection_fn(selection, pop);

            new_population.push_back(crossover_fn(crossover, parent1, parent2));
            new_population.push_back(crossover_fn(crossover, parent2, parent1));
        }

        // Clonar al resto de la población
        for (std::size_t i = 0; i < population.size() - crossover_count * 2;
             ++i) {
            std::string clone = selection_fn(selection, pop);

            new_population.push_back(clone);
        }

        // Matar a la generación anterior (std::move)
        population.clear();
        population.reserve(new_population.size());
        std::move(new_population.begin(), new_population.end(),
                  std::back_inserter(population));

        // Mutar a las nuevas soluciones
        for (auto& str : population) {
            if (RNG::get_instance().rand_real(0, 1) > mutation_rate) {
                continue;
            }

            str = mutation_fn(mutation, str);
        }

        // Calcular las métricas de las nuevas soluciones
        metrics.clear();
        for (auto& str : population) {
            metrics[str] = metric(str);
        }

        // Tomar mejor solución e imprimir por pantalla
        const auto cur_best = calculate_best(pop);
        if (cur_best.second > best_metric) {
            best_metric = cur_best.second;
            best_solution = cur_best.first;
        }

        const duration<double> elapsed = high_resolution_clock::now() - start;
        if (!tuning) {
            std::cout << "\r[" << elapsed.count()
                      << "] Fitness: " << best_metric << std::flush;
        }
    } while (high_resolution_clock::now() - start < seconds(max_time));

    const duration<double> elapsed = high_resolution_clock::now() - start;
    if (!tuning) {
        std::cout << "\r[" << elapsed.count()
                  << "] Best fitness: " << best_metric << "\n";
        std::cout << "Best solution: " << best_solution << "\n";
    } else {
        std::cout << "-" << best_metric << "\n";
    }

    return {best_solution, best_metric};
}
