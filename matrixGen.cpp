#include "matrixGen.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using std::cout;

void matrixGen(int bounds, int dimensions)
{
    srand((unsigned)time(0));

    std::ofstream matrices("matrices.txt");

    int randNo;

    for (int dim = 0; dim < dimensions; dim++)
    {
        for (int col = 0; col < bounds; col++)
        {
            for (int row = 0; row < bounds; row++)
            {
                randNo = (rand() % 21);

                if (matrices.is_open())
                    matrices << randNo << ' ';
                else
                    cout << "Unable to open file \n";
            }

            if (matrices.is_open())
                matrices << '\n';
            else
                cout << "Unable to open file \n";
        }

        if (matrices.is_open())
            matrices << '\n';
        else
            cout << "Unable to open file \n";
    }

    matrices.close();

    return;
}