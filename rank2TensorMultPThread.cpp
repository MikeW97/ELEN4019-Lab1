#include "rank2TensorMultPThread.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <pthread.h>
#include <time.h>

using namespace std;

struct thread_data
{
    vector<vector<int>> matrixA;
    vector<vector<int>> matrixB;
    vector<vector<int>> matrixC;
    int bounds;
    int iteration;
};

pthread_mutex_t myMutex;

void *multiplyThread(void *threadarg)
{
    struct thread_data *my_data;
    my_data = (struct thread_data *)threadarg;

    int N = my_data->bounds;
    int i = my_data->iteration;
    auto matrixA = my_data->matrixA;
    auto matrixB = my_data->matrixB;

    pthread_mutex_lock(&myMutex);

    int M = (2 * i + (N / 5));
    for (2 * i; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            my_data->matrixC[i][j] = 0;
            for (int k = 0; k < N; k++)
            {
                my_data->matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    pthread_mutex_unlock(&myMutex);
    pthread_exit(NULL);
}

void rank2TensorMultPThread(int bounds)
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

    // Sets up a timer to track elapsed time of multiplication process
    clock_t startTime;
    clock_t endTime;
    startTime = clock();

    pthread_t threads[5];
    struct thread_data data[5];
    int rc;

    pthread_mutex_init(&myMutex, 0);

    int counter = 0;

    if (colA == rowB)
    {

        for (int i = 0; i < 5; i++)
        {

            data[i].bounds = bounds;
            data[i].iteration = i;
            data[i].matrixA = matrixA;
            data[i].matrixB = matrixB;
            data[i].matrixC = matrixC;

            rc = pthread_create(&threads[i], NULL, multiplyThread, (void *)&data[i]);
            counter++;
        }
    }
    else
    {
        cout << "ERROR IN RANK 2 TENSOR CONTRACTION \n";
        
    }
    
    endTime = clock();

    clock_t runTime;
    runTime = endTime - startTime;

    ofstream times("times.log", ofstream::app);

    times << "rank2TensorMultPThread: \n Bounds: " << bounds << "\n Start: " << startTime << " clock cycles, " << (double)startTime / CLOCKS_PER_SEC << " seconds." << '\n';
    times << "End: " << endTime << " clock cycles, " << (double)endTime / CLOCKS_PER_SEC << " seconds." << '\n';
    times << "Total runtime: " << runTime << " clock cycles, " << (double)runTime / CLOCKS_PER_SEC << "seconds." << '\n'
          << '\n';


    for(int i = 0; i < counter; i++) {
        pthread_join(threads[i], NULL);
    }


    pthread_mutex_destroy(&myMutex);

    return;
}