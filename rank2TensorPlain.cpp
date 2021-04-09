#include "rank2TensorPlain.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>

using namespace std;

void rank2TensorPlain(int bounds)
{
    // Fills the first matrix from the text file
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

    // Fills the second matrix from the text file
    ifstream secondMat("matrixB.txt");
    vector<vector<int>> matrixB;
    while (getline(secondMat, line))
    {
        istringstream is(line);
        matrixB.push_back(
            vector<int>(istream_iterator<int>(is),
                        istream_iterator<int>()));
    }

    secondMat.close();

    /// 2D Multiplication

    //First Check if columns of A = rows of B
    int colA = matrixA[0].size();
    int rowB = matrixB.size();

    //set the resultant vector dimensions and do the multiplication
    int rowC = matrixA.size();
    int colC = matrixB[0].size();
    vector<vector<int>> matrixC(rowC, vector<int>(colC));

    clock_t startTime;
    clock_t endTime;
    startTime = clock();

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

    endTime = clock();

    clock_t runTime;
    runTime = endTime - startTime;

    cout << "2D tensor contraction of matrices with bounds of " << bounds << " started at " << (float)startTime / CLOCKS_PER_SEC << " seconds." << '\n';
    cout << "2D tensor contraction of matrices with bounds of " << bounds << " ended at " << (float)endTime / CLOCKS_PER_SEC << " seconds." << '\n';
    cout << "Total process runtime is " << (float)runTime / CLOCKS_PER_SEC << "seconds." << '\n';

    // Just checking the results of the multiplication.
    /*  cout << "Result matrix is \n";
    for (int i = 0; i < rowC; i++)
    {
        for (int j = 0; j < colC; j++)
            cout << matrixC[i][j] << " ";
        cout << "\n";
    } */

    return;
}