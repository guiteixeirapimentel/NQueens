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

void showInfo(const auto currentGeneration, const auto maxFitting, const auto& population)
{
    std::cout << "---------------------------------------\n";
    std::cout << "Current gen: " << currentGeneration << std::endl;
    std::cout << "Max fitting: " << maxFitting << std::endl;
    population.front().writeGenotype();

    population.front().drawNQueenBoard();
    std::cout << "---------------------------------------\n";
}

void simulateGenerations()
{
    std::vector<NQueenBoard<boardSize>> population;

    population.resize(populationSize);

    auto nextPopulation = population;

    const auto sortDescByFitting = [](auto &iterable) -> void
    {
        std::sort(iterable.begin(), iterable.end(), [](const auto &p1, const auto &p2) -> bool
                  { return p1.getFitting() > p2.getFitting(); });
    };

    sortDescByFitting(nextPopulation);
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
        sortDescByFitting(population);

        const auto maxFitting = population.front().getFitting();

        if (showOutputPerGeneration)
        {
            showInfo(currentGeneration, maxFitting, population);
        }

        if (maxFitting == 1.0f)
            break;
    }

    if (!showOutputPerGeneration)
    {
        const auto maxFitting = population.front().getFitting();
        showInfo(currentGeneration, maxFitting, population);
    }
}