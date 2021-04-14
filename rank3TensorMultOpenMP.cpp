#include "rank3TensorMultOpenMP.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <time.h>
#include <omp.h>

using namespace std;

void rank3TensorMultOpenMP(int bounds)
{
    int sheet = bounds;
    int row = bounds;
    int col = bounds;

    vector<vector<vector<int>>> matA;
    vector<vector<vector<int>>> matB;

    ifstream firstMat("matrixA.txt");
    vector<vector<int>> tempMat;
    string line;
    while (getline(firstMat, line))
    {
        if (line.size() != 0)
        {
            istringstream is(line);
            tempMat.push_back(
                vector<int>(istream_iterator<int>(is),
                            istream_iterator<int>()));
        }
        else
        {
            matA.push_back(tempMat);
            tempMat.clear();
        }
    }

    firstMat.close();

    ifstream secondMat("matrixB.txt");
    tempMat.clear();
    while (getline(secondMat, line))
    {
        if (line.size() != 0)
        {
            istringstream is(line);
            tempMat.push_back(
                vector<int>(istream_iterator<int>(is),
                            istream_iterator<int>()));
        }
        else
        {
            matB.push_back(tempMat);
            tempMat.clear();
        }
    }

    secondMat.close();


    //Dimensions A
    int sheet_A = matA.size();
    int row_A = matA[0].size();
    int col_A = matA[0][0].size();

    //Dimensions B
    int sheet_B = matB.size();
    int row_B = matB[0].size();
    int col_B = matB[0][0].size();


    clock_t startTime;
    clock_t endTime;
    startTime = clock();

    //Resultant Vector
    vector<vector<vector<int>>> matC(sheet, vector<vector<int>>(row, vector<int>(col)));

    // Sets up OpenMP parallelisation parameters
    omp_set_num_threads(5);

    // For the vectors to be compatible, the number of planes in A should equal to the number of columns in B
    if (sheet_A == row_B)
    {
        int m, i, j, k;

        //Multiplication route
        #pragma omp parallel for private(m, i, j, k) shared(matA, matB, matC)
        for (m = 0; m < sheet_A; m++)
        {
            for (i = 0; i < col_B; i++)
            {
                for (j = 0; j < row_A; j++)
                {
                    for (k = 0; k < col_A; k++)
                    {
                        matC[j][m][i] += matA[k][i][j] * matB[j][k][i];
                    }
                }
            }
        }
    }
    else
    {
        //error check
        cout << "ERROR: Incompatible Matrices!" << '\n';
    }

    endTime = clock();

    clock_t runTime;
    runTime = endTime - startTime;

    ofstream times("times.log", ofstream::app);

    times << "rank3TensorMultOpenMP: \n Bounds: " << bounds << "\n Start: " << startTime << " clock cycles, " << (double)startTime / CLOCKS_PER_SEC << " seconds." << '\n';
    times << "End: " << endTime << " clock cycles, " << (double)endTime / CLOCKS_PER_SEC << " seconds." << '\n';
    times << "Total runtime: " << runTime << " clock cycles, " << (double)runTime / CLOCKS_PER_SEC << "seconds." << '\n'
          << '\n';

    return;
}