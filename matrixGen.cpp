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
    int sheetTotal;

    if (dimensions == 2)
        sheetTotal = 1;
    else if (dimensions == 3)
        sheetTotal = bounds;
    else
    {
        cout << "Dimensions incorrect! Must be 2 or 3!" << '\n';
        return;
    }

    // Creates/opens the first text file
    std::ofstream matrixA("matrixA.txt");

    // Fills the text file with numbers
    for (int sheets = 0; sheets < sheetTotal; sheets++)
    {
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

        if (matrixA.is_open() && sheets < sheetTotal)
            matrixA << '\n';
    }

    matrixA.close();

    // Creates/opens the second text file
    std::ofstream matrixB("matrixB.txt");

    // Fills the text file with numbers
    for (int sheets = 0; sheets < sheetTotal; sheets++)
    {
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

        if (matrixB.is_open() && sheets < sheetTotal)
            matrixB << '\n';
    }

    matrixB.close();

    return;
}