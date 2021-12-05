#include <iostream>
#include "NQueenBoard.hpp"
#include <vector>
#include <algorithm>

constexpr auto populationSize = 20;
constexpr auto boardSize = 8;
constexpr auto totalOfGenerations = 500;

constexpr auto showOutputPerGeneration = true;

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
    auto currentGeneration = 0;

    for (; currentGeneration != totalOfGenerations; currentGeneration++)
    {
        nextPopulation[0] = population[0];
        nextPopulation[0 + 1] = population[0 + 1];

        for (auto pair = 2; pair < populationSize / 2; pair += 2)
        {
            nextPopulation[pair] = population[pair].oxWith(population[pair + 1]);
            nextPopulation[pair + 1] = population[pair + 1].oxWith(population[pair]);
        }

        for (auto index = (populationSize / 2) - 1; index < populationSize; index++)
        {
            const auto mateIndex = rand() % populationSize;
            nextPopulation[index] = population[index].oxWith(population[mateIndex]);
        }
        population = nextPopulation;
        sortAscByFitting(population);

        const auto minFitting = population.front().getFitting();

        if (showOutputPerGeneration)
        {
            std::cout << "---------------------------------------\n";
            std::cout << "Current gen: " << currentGeneration << std::endl;
            std::cout << "Min fitting: " << minFitting << std::endl;
            population.front().writeGenotype();

            population.front().drawNQueenBoard();
            std::cout << "---------------------------------------\n";
        }

        if (minFitting == 0)
            break;
    }

    if (!showOutputPerGeneration)
    {
        const auto minFitting = population.front().getFitting();
        std::cout << "---------------------------------------\n";
        std::cout << "Current gen: " << currentGeneration << std::endl;
        std::cout << "Min fitting: " << minFitting << std::endl;
        population.front().writeGenotype();

        population.front().drawNQueenBoard();
        std::cout << "---------------------------------------\n";
    }
}