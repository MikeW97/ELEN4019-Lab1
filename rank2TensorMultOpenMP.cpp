#include "rank2TensorPlain.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <omp.h>

using namespace std;

void rank2TensorMultOpenMP(int bounds)
{
    // Fills the first matrix from the text file
    ifstream firstMat("matrixA.txt");
    vector<vector<int>> matrixA;
    string line;
    while (getline(firstMat, line))
    {
        if (line.size() != 0)
        {
            istringstream is(line);
            matrixA.push_back(
                vector<int>(istream_iterator<int>(is),
                            istream_iterator<int>()));
        }
    }

    firstMat.close();

    // Fills the second matrix from the text file
    ifstream secondMat("matrixB.txt");
    vector<vector<int>> matrixB;
    while (getline(secondMat, line))
    {
        if (line.size() != 0)
        {
            istringstream is(line);
            matrixB.push_back(
                vector<int>(istream_iterator<int>(is),
                            istream_iterator<int>()));
        }
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

    // Sets up OpenMP parallelisation parameters
    omp_set_num_threads(omp_get_num_procs());

    // Sets up a timer to track elapsed time of multiplication process
    clock_t startTime;
    clock_t endTime;
    startTime = clock();

    cout << colA << ' ' << rowB << '\n';

    if (colA == rowB)
    {
        int i, j, k;
        int N = colA;

#pragma omp parallel for private(i, j, k) shared(matrixA, matrixB, matrixC)
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
        cout << "ERROR IN RANK 2 TENSOR CONTRACTION \n";
        //can implement some sort of error once function is set using throw and catch.
    }

    endTime = clock();

    clock_t runTime;
    runTime = endTime - startTime;

    cout << "2D tensor contraction of matrices, with multithreading, with bounds of " << bounds << " started at " << (double)startTime / CLOCKS_PER_SEC << " seconds." << '\n';
    cout << "2D tensor contraction of matrices, with multithreading, with bounds of " << bounds << " ended at " << (double)endTime / CLOCKS_PER_SEC << " seconds." << '\n';
    cout << "Total process runtime is " << runTime << " clock ticks which is " << (double)runTime / CLOCKS_PER_SEC << "seconds." << '\n';

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