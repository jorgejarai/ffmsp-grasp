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

#define POPULATION_SIZE 100

ffmsp::result ffmsp::genetic(const std::vector<std::string>& strings,
                             double threshold, double alpha, int max_time,
                             double crossover_rate, double mutation_rate,
                             crossover_type crossover, mutation_type mutation,
                             selection_type selection, bool tuning) {
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

    for (std::size_t i = 0; i < POPULATION_SIZE; ++i) {
        const auto res = ffmsp::random_greedy(strings, threshold, alpha);

        population.push_back(res.str);
        metrics[res.str] = res.metric;
    }

    const auto best = std::max_element(
        metrics.begin(), metrics.end(),
        [](const auto& a, const auto& b) { return a.second < b.second; });

    std::string best_solution = best->first;
    std::size_t best_metric = best->second;

    const auto start = high_resolution_clock::now();
    do {
        std::vector<std::string> new_population;

        // Calcular cantidad de crossovers
        size_t crossover_count =
            std::floor(population.size() * crossover_rate / (100 / 2));

        std::vector<std::pair<std::string, size_t>> pop;
        for (const auto& s : population) {
            pop.push_back({s, metrics[s]});
        }

        // Hacer crossovers
        for (std::size_t i = 0; i < crossover_count; i++) {
            std::string parent1, parent2;

            std::vector<std::pair<std::string, std::size_t>> temp;
            switch (selection) {
            case selection_type::TOURNAMENT:
                temp = genetic::selection::tournament(pop, 2);
                parent1 = temp.at(0).first;
                parent2 = temp.at(1).first;
                break;
            case selection_type::ROULETTE:
                temp = genetic::selection::roulette(pop, 2);
                parent1 = temp.at(0).first;
                parent2 = temp.at(1).first;
                break;
            case selection_type::RANK:
                temp = genetic::selection::random(pop, 2);
                parent1 = temp.at(0).first;
                parent2 = temp.at(1).first;
                break;
            }

            std::string child1, child2;
            switch (crossover) {
            case crossover_type::SINGLE_POINT:
                child1 = genetic::crossover::one_point(parent1, parent2);
                child2 = genetic::crossover::one_point(parent2, parent1);
                break;
            case crossover_type::TWO_POINT:
                child1 = genetic::crossover::two_point(parent1, parent2);
                child2 = genetic::crossover::two_point(parent2, parent1);
                break;
            case crossover_type::UNIFORM:
                child1 = genetic::crossover::uniform(parent1, parent2);
                child2 = genetic::crossover::uniform(parent2, parent1);
            }
            new_population.push_back(child1);
            new_population.push_back(child2);
        }

        // Clonar al resto de la población
        std::vector<std::pair<std::string, std::size_t>> temp;
        switch (selection) {
        case selection_type::TOURNAMENT:
            temp = genetic::selection::tournament(
                pop, population.size() - crossover_count * 2);
            break;
        case selection_type::ROULETTE:
            temp = genetic::selection::roulette(
                pop, population.size() - crossover_count * 2);
            break;
        case selection_type::RANK:
            temp = genetic::selection::random(
                pop, population.size() - crossover_count * 2);
            break;
        }

        for (std::size_t i = 0; i < temp.size(); i++) {
            new_population.push_back(temp.at(i).first);
        }

        // Matar a los boomers (std::move)
        population = std::move(new_population);

        // Mutar a las nuevas soluciones
        for (auto& str : population) {
            switch (mutation) {
            case mutation_type::FLIP:
                str = genetic::mutation::bit_flip(str);
                break;
            case mutation_type::SWAP:
                str = genetic::mutation::swap_mutation(str);
                break;
            case mutation_type::SCRAMBLE:
                str = genetic::mutation::scramble_mutation(str);
                break;
            }
        }

        // Calcular las métricas de las nuevas soluciones
        metrics.clear();
        for (auto& str : population) {
            metrics[str] = metric(str);
        }

        // Tomar mejor solución e imprimir por pantalla
        const auto best = std::max_element(
            metrics.begin(), metrics.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; });

        if (best->second > best_metric) {
            best_metric = best->second;
            best_solution = best->first;
        }

        const duration<double> elapsed = high_resolution_clock::now() - start;
        if (!tuning) {
            std::cout << "[" << elapsed.count() << "] Fitness: " << best_metric
                      << "\n";
        }

        // std::cout << best_solution << std::endl;
    } while (high_resolution_clock::now() - start < seconds(max_time));

    const duration<double> elapsed = high_resolution_clock::now() - start;
    if (!tuning) {
        std::cout << "[" << elapsed.count() << "] Fitness: " << best_metric
                  << "\n";
    } else {
        std::cout << -best_metric << "\n";
    }

    return {best_solution, best_metric};

    return {"", 0};

    return {"", 0};

    return {"", 0};

    return {"", 0};

    return {"", 0};

    return {"", 0};
}
