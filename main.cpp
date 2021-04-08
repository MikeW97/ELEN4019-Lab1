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

/// 2D Multiplication

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

///3D Multiplication 

    int sheet = 3;
    int row = 3;
    int col = 3;
    
    vector< vector< vector<int> > > matA(sheet, vector< vector<int> >(row, vector<int>(col)));
    vector< vector< vector<int> > > matB(sheet, vector< vector<int> >(row, vector<int>(col)));
 
    // Adding values into matrices 
    for(int i=0;i<sheet;++i){
        for(int j=0;j<row;++j){
            for(int k=0;k<col;++k){
                matA[i][j][k] = i*row*col+ j*row + k;
                matB[i][j][k] = i*row*col+ j*row + k;
            }
        }    
    }

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

    vector<vector<int>> matC ( sheet_A , vector<int> (col_B));

    // Check if the 2 matrices are compatible 
    if (row_A==row_B && col_A==sheet_B)
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