#include <iostream>
#include "NQueenBoard.hpp"
#include <vector>
#include <algorithm>

constexpr auto populationSize = 6;
constexpr auto boardSize = 5;

constexpr auto totalOfGenerations = 100;

void simulateGenerations();

int main()
{
    try
    {
        simulateGenerations();
    }
    catch (const Exception &e)
    {
        std::cout << "Exceção lançada: ";
        std::cout << e.getMsg() << std::endl;
    }

    return 0;
}

void simulateGenerations()
{
    std::vector<NQueenBoard<boardSize>> population;

    population.resize(populationSize);

    auto nextPopulation = population;

    const auto sortAscByFitting = [](auto &iterable) -> void
    {
        std::sort(iterable.begin(), iterable.end(), [](const auto &p1, const auto &p2) -> bool
                  { return p1.getFitting() < p2.getFitting(); });
    };

    sortAscByFitting(nextPopulation);

    for (auto currentGeneration = 0; currentGeneration != totalOfGenerations; currentGeneration++)
    {
        for (auto pair = 0; pair < populationSize; pair += 2)
        {
            nextPopulation[pair] = population[pair].oxWith(population[pair + 1]);

            nextPopulation[pair + 1] = population[pair + 1].oxWith(population[pair]);
        }

        for (const auto pop : population)
        {
            std::cout << "fit: " << pop.getFitting() << std::endl;
        }
        population = nextPopulation;
        sortAscByFitting(population);
        {
            std::cout << "fit: " << pop.getFitting() << std::endl;
        }
        std::cout << "---------------------------------------\n";
        std::cout << "Current gen: " << currentGeneration << std::endl;
        std::cout << "Max fitting: " << population.front().getFitting() << std::endl;
        population.front().writeGenotype();

        population.front().drawNQueenBoard();
        std::cout << "---------------------------------------\n";
    }
}