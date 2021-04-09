#include "rank3TensorPlain.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>

using namespace std;

void rank3TensorPlain(int bounds)
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
            cout << "EMPTY LINE" << '\n';
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

    // CHECKING CONTENTS OF MATRIX A
   /* for (vector<vector<vector<int>>>::const_iterator i = matA.begin(); i != matA.end(); ++i)
    {
        for (vector<vector<int>>::const_iterator j = i->begin(); j != i->end(); ++j)
        {
            for (vector<int>::const_iterator k = j->begin(); k != j->end(); ++k)
            {
                cout << *k << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
    } */

    // Check -2 of the 3 indices have to be equal to perform a contraction

    //Dimensions A
    int sheet_A = matA.size();
    int row_A = matA[0].size();
    int col_A = matA[0][0].size();

    //cout << sheet_A << ' ' << row_A << ' ' << col_A << ' ' << matA.capacity() << '\n';

    //Dimensions B
    int sheet_B = matB.size();
    int row_B = matB[0].size();
    int col_B = matB[0][0].size();

    //cout << sheet_B << ' ' << row_B << ' ' << col_B << ' ' << matB.capacity() << '\n';

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
        cout << "ERROR: Incompatible Matrices!" << '\n';
    }

    return;
}