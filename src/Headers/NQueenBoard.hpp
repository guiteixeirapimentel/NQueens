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
        const auto offset = getRandNumber();
        for (int val = 0; val < N; val++)
        {
            cGenotype[(val + offset) % N] = val;
        }
        calculateFenotype();
    }

    NQueenBoard(const std::array<int, N> &genotype)
        : cGenotype(genotype),
          cFenotype({})
    {
        calculateFenotype();
    }

    ~NQueenBoard() {}

    NQueenBoard oxWith(const NQueenBoard &mate) const
    {
        const auto randomNumber1 = getRandNumber();
        const auto randomNumber2 = getRandNumber(N - randomNumber1) + randomNumber1 + 1;

        auto newGenotype = std::array<int, N>();

        std::fill(newGenotype.begin(), newGenotype.end(), -1);

        auto positionSonF = randomNumber2;

        for (auto i = randomNumber1; i != randomNumber2; i++)
            newGenotype[i] = cGenotype[i];

        const auto getIndexOfValue = [](const auto value, const auto &array, const auto arrayLength) -> int
        {
            for (auto i = 0; i < arrayLength; i++)
            {
                if (array[i] == value)
                    return i;
            }

            return -1;
        };

        const auto verifyAndCopy = [&mate, &newGenotype, &positionSonF, &getIndexOfValue, this](const auto positionMate) -> void
        {
            const auto genotype = mate.cGenotype[positionMate];

            const auto indexGenotype = getIndexOfValue(genotype, newGenotype, N);
            const auto alreadyCopied = indexGenotype != -1;

            if (alreadyCopied)
            {
                return;
            }

            newGenotype[positionSonF] = genotype;
            positionSonF = (positionSonF +1) % N;
        };
        positionSonF %= N;
        for (auto positionMate = randomNumber2; positionMate != N; positionMate++)
        {
            verifyAndCopy(positionMate);
        }

        for (auto positionMate = 0; positionMate != randomNumber2; positionMate++)
        {
            verifyAndCopy(positionMate);
        }

        return NQueenBoard<N>(newGenotype);
    }

    void drawNQueenBoard() const
    {
        for (auto i = 0u; i < N; i++)
        {
            for (auto j = 0u; j < N; j++)
            {
                std::cout << "|" << (cFenotype[j + i * N] ? "Q" : " ");
            }
            std::cout << "|\n";
        }
    }

    void writeGenotype() const
    {
        for(const auto genotype : cGenotype)
            std::cout << '|' << genotype << '|';  

        std::cout << '\n';
    }

    auto getGenotype() const
    {
        return cGenotype;
    }

    auto getFitting() const
    {
        const auto getNumberOfCaptures = [this](const auto row, const auto col)
        {
            auto result = 0;

            for(auto offset = 1; offset < N; offset++)
            {
                const auto i = row + offset;
                const auto j = col + offset;

                if(i >= N || j >= N)
                    break;
                
                result += cFenotype[(j) + (i)*N] ? 1 : 0;
            }

            for(auto offset = 1; offset < N; offset++)
            {
                const auto i = row - offset;
                const auto j = col - offset;

                if(i < 0 || j < 0)
                    break;
                
                result += cFenotype[(j) + (i)*N] ? 1 : 0;
            }

            for(auto offset = 1; offset < N; offset++)
            {
                const auto i = row + offset;
                const auto j = col - offset;

                if(i >= N || j < 0)
                    break;
                
                result += cFenotype[(j) + (i)*N] ? 1 : 0;
            }

            for(auto offset = 1; offset < N; offset++)
            {
                const auto i = row - offset;
                const auto j = col + offset;

                if(i < 0 || j >= N)
                    break;
                
                result += cFenotype[(j) + (i)*N] ? 1 : 0;
            }

            return result;
        };

        auto total = 0.0f;

        for (auto ii = 0; ii != int(cGenotype.size()); ii++)
        {
            total += getNumberOfCaptures(cGenotype[ii], ii);
        }

        return total;
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

    auto getIndexByGenotypeValue(const int value) const
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