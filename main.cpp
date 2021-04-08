#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <fstream>

using std::cin;
using std::cout;
using std::invalid_argument;

void matrixGen(int bounds, int dimensions);

int main()
{
    int bounds = 20;
    int dimensions = 3;

    matrixGen(bounds, dimensions);

    return 0;
}

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
                {
                    matrices << randNo << ' ';
                }
                else
                    cout << "Unable to open file \n";

                cout << randNo << ' ';
            }

            if (matrices.is_open())
            {
                matrices << '\n';
            }
            cout << '\n';
        }

        if (matrices.is_open())
        {
            matrices << '\n';
        }
        cout << '\n';
    }

    matrices.close();

    return;
}