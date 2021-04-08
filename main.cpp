#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>

#include "matrixGen.h"

using namespace std;

int main()
{
    int bounds = 10;
    int dimensions = 2;

    matrixGen(bounds, dimensions);

    ifstream firstMat("matrixA.txt");
    vector<vector<int>> matrixA;
    string line;
    while (getline(firstMat, line))
    {
        istringstream is(line);
        matrixA.push_back(
            vector<int>(istream_iterator<int>(is),
                        istream_iterator<int>()));
    }

    firstMat.close();

    ifstream secondMat("matrixB.txt");
    vector<vector<int>> matrixB;
    while (getline(secondMat, line))
    {
        istringstream is(line);
        matrixB.push_back(
            vector<int>(istream_iterator<int>(is),
                        istream_iterator<int>()));
    }

    //First Check if columns of A = rows of B
    int colA = matrixA[0].size();
    int rowB = matrixB.size();

    //set the resultant vector dimensions and do the multiplication
    int rowC = matrixA.size();
    int colC = matrixB[0].size();
    vector<vector<int>> matrixC(rowC, vector<int>(colC));

    if (colA == rowB)
    {
        int i, j, k;
        int N = colA;

        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                matrixC[i][j] = 0;

                for (k = 0; k < N; k++)
                {
                    matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
    }
    else
    {
        //can implement some sort of error once function is set using throw and catch.
    }

    // Just checking the results of the multiplication.
    cout << "Result matrix is \n";
    for (int i = 0; i < rowC; i++)
    {
        for (int j = 0; j < colC; j++)
            cout << matrixC[i][j] << " ";
        cout << "\n";
    }

    return 0;
}