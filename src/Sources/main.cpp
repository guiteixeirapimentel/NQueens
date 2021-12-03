// #include <random>
#include <iostream>
#include "NQueenBoard.hpp"

int main()
{
    try
    {
         NQueenBoard<5> nQueenBoard;
    NQueenBoard<5> nQueenBoard2;

    // nQueenBoard.drawNQueenBoard();

    nQueenBoard.pmxWith(nQueenBoard2).drawNQueenBoard();

    std::cout << "Get fitting: " << nQueenBoard.getFitting() << std::endl;

    }
    catch(const Exception& e)
    {
        std::cout << "Exceção lançada: ";
        std::cout << e.getMsg() << std::endl;
    }
   
    return 0;
}