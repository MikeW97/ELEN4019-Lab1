#include "matrixGen.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using std::cout;

void matrixGen(int bounds, int dimensions)
{
    srand((unsigned)time(0));
    int randNo;

    std::ofstream matrixA("matrixA.txt");

    for (int col = 0; col < bounds; col++)
    {
        for (int row = 0; row < bounds; row++)
        {
            randNo = (rand() % 21);

            if (matrixA.is_open())
                matrixA << randNo << ' ';
            else
                cout << "Unable to open file \n";
        }

        if (matrixA.is_open())
            matrixA << '\n';
        else
            cout << "Unable to open file \n";
    }

    matrixA.close();
    std::ofstream matrixB("matrixB.txt");

    for (int col = 0; col < bounds; col++)
    {
        for (int row = 0; row < bounds; row++)
        {
            randNo = (rand() % 21);

            if (matrixB.is_open())
                matrixB << randNo << ' ';
            else
                cout << "Unable to open file \n";
        }

        if (matrixB.is_open())
            matrixB << '\n';
        else
            cout << "Unable to open file \n";
    }

    matrixB.close();
    if (dimensions == 3)
    {
        std::ofstream matrixC("matrixC.txt");

        for (int col = 0; col < bounds; col++)
        {
            for (int row = 0; row < bounds; row++)
            {
                randNo = (rand() % 21);

                if (matrixC.is_open())
                    matrixC << randNo << ' ';
                else
                    cout << "Unable to open file \n";
            }

            if (matrixC.is_open())
                matrixC << '\n';
            else
                cout << "Unable to open file \n";
        }

        matrixC.close();
    }
    else
        return;

    return;
}