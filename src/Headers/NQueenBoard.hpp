#pragma once
#include <iostream>
#include <array>
#include <stdint.h>
#include <algorithm>
#include <functional>
#include <ranges>
#include <random>

#include <cassert>

#include "Exception.hpp"

template <int N>
class NQueenBoard
{
public:
    NQueenBoard()
        : cGenotype({}),
          cFenotype({})
    {
        for (int val = 0; val < N; val++)
        {
            cGenotype[val] = val;
        }
    }

    NQueenBoard(const std::array<int, N> &genotype)
        : cGenotype(genotype),
          cFenotype({})
    {
    }

    ~NQueenBoard() {}

    NQueenBoard pmxWith(const NQueenBoard &mate) const
    {
        const auto randomNumber1 = getRandNumber();
        const auto randomNumber2 = getRandNumber(N - randomNumber1) + randomNumber1 + 1;

        std::array<int, N> newGenotype = {-1};

        // copy random piece of genotype from first parent
        for (auto i = randomNumber1; i != randomNumber2; i++)
            newGenotype[i] = cGenotype[i];

        for (auto i = randomNumber1; i != N; i++)
        {
            const auto genotype = mate.cGenotype[i];

            const auto indexGenotype = getIndexByGenotypeValue(genotype);

            if (indexGenotype == -1)
            {
                const auto indexGenotypeMate =  mate.getIndexByGenotypeValue(cGenotype[i]);
                if(newGenotype[indexGenotypeMate] == -1)
                    newGenotype[indexGenotypeMate] = mate.cGenotype[indexGenotypeMate];
            }
        }

        for (auto i = 0; i != randomNumber1; i++)
        {
        }

        mate.drawNQueenBoard();

        return NQueenBoard<N>(newGenotype);
    }

    void drawNQueenBoard()
    {
        calculateFenotype();

        for (auto i = 0u; i < N; i++)
        {
            for (auto j = 0u; j < N; j++)
            {
                std::cout << "|" << (cFenotype[j + i * N] ? "Q" : " ");
            }
            std::cout << "|\n";
        }
    }

    auto getGenotype() const
    {
        return cGenotype;
    }

    auto getFitting()
    {
        calculateFenotype();

        const auto getNumberOfCaptures = [this](const auto row, const auto col)
        {
            auto result = 0u;

            for (auto ij = std::max(row, col); ij != N; ij++)
            {
                result += cFenotype[(ij) + (ij)*N] ? 1 : 0;
            }

            for (auto ij = std::min(row, col); ij != 0; ij--)
            {
                result += cFenotype[(ij) + (ij)*N] ? 1 : 0;
            }

            return result;
        };

        auto total = 0.0f;

        for (auto ii = 0; ii != int(cGenotype.size()); ii++)
        {
            total += getNumberOfCaptures(cGenotype[ii], ii);
        }

        return 1 / total;
    }

    constexpr uint32_t getBoardSize() const
    {
        return N;
    }

private:
    void calculateFenotype()
    {
        for (auto j = 0; j != N; j++)
        {
            const auto &genotype = cGenotype[j];
            if (genotype < 0)
                throw Exception("Genótipo inválido!");

            cFenotype[genotype * N + j] = true;
        }
    }

private:
    inline auto getRandNumber(const int maxValue = N) const
    {
        return rand() % maxValue;
    };

    auto getIndexByGenotypeValue(const int value)
    {
        for (auto i = 0; i < N; i++)
        {
            if (cGenotype[i] == value)
                return i;
        }

        return -1;
    }

private:
    std::array<int, N> cGenotype;
    std::array<bool, N * N> cFenotype;
};