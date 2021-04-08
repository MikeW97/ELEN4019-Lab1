#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

using std::cin;
using std::cout;
using std::invalid_argument;
using namespace std; 

int main()
{   
    //Random Number generator 
    srand((unsigned)time(0));

    int bounds;
    int dimensions;
    int randNo;

    cout << "Please enter the bounds of the arrays: " << '\n';
    cin >> bounds;

    if ((bounds % 10 != 0) || bounds > 30)
        throw invalid_argument("Input must be 10, 20 or 30!");

    cout << "Please enter the dimensions of the arrays: " << '\n';
    cin >> dimensions;

    if (dimensions != 2 && dimensions != 3)
        throw invalid_argument("Dimensions must be either 2 or 3!");

    for (int dim = 0; dim < dimensions; dim++)
    {
        for (int col = 0; col < bounds; col++)
        {
            for (int row = 0; row < bounds; row++)
            {
                randNo = (rand() % 21);
                cout << randNo << ' ';
            }

            cout << '\n';
        }

        cout << '\n';
    }

    // 2D Multiplication 
        vector<vector<int>> matrixA
    {
        {1, 2, 3, 5, 4},
        {5, 1, 3, 2, 6},
        {2, 4, 1, 6, 2},
        {5, 1, 3, 2, 6},
        {2, 4, 1, 6, 2},
    };
        vector<vector<int>> matrixB
    {
        {1, 4 ,1, 4, 6},
        {2, 3 ,2, 2, 3},
        {1, 2 ,3, 5, 4},
        {2, 3 ,2, 3, 1},
        {1, 2 ,3, 2, 4},
    };

    //First Check if columns of A = rows of B
    int colA = matrixA[0].size();
    int rowB = matrixB.size();

    //set the resultant vector dimensions and do the multiplication 
    int rowC = matrixA.size();
    int colC = matrixB[0].size() ;
    vector<vector<int>> matrixC ( rowC , vector<int> (colC));

    if (colA==rowB) 
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
    for (int i = 0; i < rowC; i++) {
        for (int j = 0; j < colC; j++)
            cout << matrixC[i][j] << " ";
        cout << "\n";
    }

    return 0;
}