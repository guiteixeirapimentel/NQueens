#include <iostream>
#include "NQueenBoard.hpp"

int main()
{
    NQueenBoard<uint32_t, 5> nQueenBoard;

    nQueenBoard.drawNQueenBoard();

    std::cout << "Get fitting: " << nQueenBoard.getFitting() << std::endl;

    return 0;
}