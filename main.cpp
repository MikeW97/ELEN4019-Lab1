#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>

#include "matrixGen.h"
#include "rank2TensorPlain.h"

using namespace std;

int main()
{
    int bounds = 10;
    int dimensions = 2;

    // Generates matrices in seperate text files with specified bounds and dimensions
    matrixGen(bounds, dimensions);

    // Performs Rank 2 Tensor Contraction without threading
    rank2TensorPlain();

    ///3D Multiplication

    bounds = 10;
    dimensions = 3;

    matrixGen(bounds, dimensions);

    int sheet = bounds;
    int row = bounds;
    int col = bounds;

    vector<vector<vector<int>>> matA(sheet, vector<vector<int>>(row, vector<int>(col)));
    vector<vector<vector<int>>> matB(sheet, vector<vector<int>>(row, vector<int>(col)));

    ifstream firstMat("matrixA.txt");
    vector<vector<int>> tempMat;
    string line;
    while (getline(firstMat, line))
    {
        if (line.size() == 0)
        {
            matA.push_back(tempMat);
            tempMat.clear();
        }
        else
        {
            istringstream is(line);
            tempMat.push_back(
                vector<int>(istream_iterator<int>(is),
                            istream_iterator<int>()));
        }
    }

    firstMat.close();

    ifstream secondMat("matrixB.txt");
    tempMat.clear();
    while (getline(secondMat, line))
    {
        if (line.size() == 0)
        {
            matB.push_back(tempMat);
            tempMat.clear();
            cout << line << '\n';
        }
        else
        {
            cout << line << '\n';
            istringstream is(line);
            tempMat.push_back(
                vector<int>(istream_iterator<int>(is),
                            istream_iterator<int>()));
        }
    }

    secondMat.close();

    // Check -2 of the 3 indices have to be equal to perform a contraction

    //Dimensions A
    int sheet_A = matA.size();
    int row_A = matA[0].size();
    int col_A = matA[0][0].size();

    //Dimensions B
    int sheet_B = matB.size();
    int row_B = matB[0].size();
    int col_B = matB[0][0].size();

    //Resultant Vector
    vector<vector<int>> matC(sheet_A, vector<int>(col_B));

    // Check if the 2 matrices are compatible
    if (row_A == row_B && col_A == sheet_B)
    {
        //Multiplication route
        for (int i = 0; i < sheet_A; i++)
        {
            for (int j = 0; j < col_B; j++)
            {
                for (int k = 0; k < row_A; k++)
                {
                    for (int l = 0; l < col_A; l++)
                    {
                        matC[i][j] += matA[i][k][l] * matB[k][l][j];
                    }
                }
            }
        }
    }
    else
    {
        //error check
    }

    return 0;
}