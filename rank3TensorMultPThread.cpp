#include "rank3TensorMultPThread.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <time.h>

using namespace std;

struct thread_data_3d
{
    vector<vector<vector<int>>> matrixA;
    vector<vector<vector<int>>>matrixB;
    vector<vector<vector<int>>> matrixC;
    int bounds;
    int iteration;
};

pthread_mutex_t myMutex_3d;

void *multiplyThread_3d(void *threadarg)
{
    struct thread_data_3d *my_data;
    my_data = (struct thread_data_3d *)threadarg;

    int N = my_data->bounds;
    int i = my_data->iteration;
    auto matA = my_data->matrixA;
    auto matB = my_data->matrixB;
    // auto matC = my_data->matrixC;

    //Dimensions A
    int sheet_A = matA.size();
    int row_A = matA[0].size();
    int col_A = matA[0][0].size();

    //cout << sheet_A << ' ' << row_A << ' ' << col_A << ' ' << matA.capacity() << '\n';

    //Dimensions B
    int sheet_B = matB.size();
    int row_B = matB[0].size();
    int col_B = matB[0][0].size();

    cout << "This is 3d thread: " << i << '\n';

    pthread_mutex_lock(&myMutex_3d);

        //Multiplication route
        for (int m = 0; m < sheet_A; m++)
        {
            for (int i = 0; i < col_B; i++)
            {
                for (int j = 0; j < row_A; j++)
                {
                    for (int k = 0; k < col_A; k++)
                    {
                        my_data->matrixC[j][m][i] += matA[k][i][j] * matB[j][k][i];
                    }
                }
            }
        }

    pthread_mutex_unlock(&myMutex_3d);
    pthread_exit(NULL);
}

void rank3TensorMultPThread(int bounds)
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

    clock_t startTime;
    clock_t endTime;
    startTime = clock();

    pthread_t threads[5];
    struct thread_data_3d data[5];
    int rc;

    //Resultant Vector
    vector<vector<vector<int>>> matC(sheet, vector<vector<int>>(row, vector<int>(col)));

    int counter = 0;
    // For the vectors to be compatible, the number of planes in A should equal to the number of columns in B
    if (sheet_A == row_B)
    {
                // cout << "Here is test 2" << '\n';
        for (int i = 0; i < 5; i++)
        {
            // cout << "This should be thread " << i << '\n';

            data[i].bounds = bounds;
            data[i].iteration = i;
            data[i].matrixA = matA;
            data[i].matrixB = matB;
            data[i].matrixC = matC;

            // cout << i << " iteration "<<data[i].iteration<<" "<< '\n';
            rc = pthread_create(&threads[i], NULL, multiplyThread_3d, (void *)&data[i]);
            // rc = pthread_create(&threads[i], NULL, multiplyThread, NULL);
            counter++;
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

    // cout << "3D tensor contraction of matrices with bounds of " << bounds << " started at " << (float)startTime / CLOCKS_PER_SEC << " seconds." << '\n';
    // cout << "3D tensor contraction of matrices with bounds of " << bounds << " ended at " << (float)endTime / CLOCKS_PER_SEC << " seconds." << '\n';
    // cout << "Total process runtime is " << (float)runTime / CLOCKS_PER_SEC << "seconds." << '\n';

    for(int i = 0; i < counter; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&myMutex_3d);

    return;
}