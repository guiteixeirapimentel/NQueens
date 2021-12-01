#pragma once
#include <iostream>
#include <array>
#include <stdint.h>
#include <algorithm>
#include <functional>
#include <ranges>
#include <random>

template <typename T, uint32_t N>
class NQueenBoard
{
public:
    NQueenBoard()
        : cGenotype({}),
          cFenotype({})
    {
        for(T val = 0; val < N; val++)
        {
            cGenotype[val] = val;
        }

        calculateFenotype();
    }

    ~NQueenBoard() {}

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

    auto getGenotype() const
    {
        return cGenotype;
    }

    auto getFitting() const
    {
        const auto getNumberOfCaptures = [this](const auto row, const auto col) {
            auto result = 0u;

            for(auto ij = std::max(row, col); ij != N; ij++)
            {
                // std::cout << "1Olhando " << ij << ":" << ij << std::endl;
                result += cFenotype[(ij) + (ij)*N] ? 1 : 0;
            }

            for(auto ij = std::min(row, col); ij != 0; ij--)
            {
                // std::cout << "2Olhando " << ij << ":" << ij << std::endl;
                result += cFenotype[(ij) + (ij)*N] ? 1 : 0;
            }

            return result;
        };

        auto total = 0u;

        for(auto ii = 0u; ii != cGenotype.size(); ii++)
        {
            total += getNumberOfCaptures(cGenotype[ii], ii);
        }

        return total;
    }

private:
    void calculateFenotype()
    {
        for(auto j = 0u; j < N; j++)
        {
            const auto& genotype = cGenotype[j];
            cFenotype[genotype * N + j] = true;
        }
    }

    private:
    inline static std::default_random_engine cGenerator;
    inline static auto cDistribution = std::uniform_int_distribution<T>(0, N);

private:
    std::array<T, N> cGenotype;
    std::array<bool, N*N> cFenotype;
};