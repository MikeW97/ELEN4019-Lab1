#include "rank2TensorMultPThread.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <pthread.h>
#include <time.h>

using namespace std;

const int NUM_THREADS = 5;
pthread_mutex_t myMutex;
vector<vector<int>> matrixC; // A shared variable

struct thread_data
{
    vector<vector<int>> matrixA;
    vector<vector<int>> matrixB;
    int bounds;
    int iteration;
};

void *multiplyThread(void *threadarg)
{

    struct thread_data *my_data;
    my_data = (struct thread_data *)threadarg;

    int N = my_data->bounds;
    int i = my_data->iteration;
    auto matrixA = my_data->matrixA;
    auto matrixB = my_data->matrixB;

    pthread_mutex_lock(&myMutex);

    for (2 * i; i < (2 * i + (N / NUM_THREADS)); i++)
    {
        for (int j = 0; j < N; j++)
        {
            //pthread_mutex_lock(&myMutex);
            matrixC[i][j] = 0;
            //pthread_mutex_unlock(&myMutex);

            for (int k = 0; k < N; k++)
            {
                //pthread_mutex_lock(&myMutex);
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
                //pthread_mutex_unlock(&myMutex);
            }
        }
    }

    // cout << "This is thread: " << threadarg << '\n';
    pthread_mutex_unlock(&myMutex);

    //pthread_exit(NULL);
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

    pthread_t threads[NUM_THREADS];
    struct thread_data data[NUM_THREADS];
    // pthread_attr_t attr;
    // pthread_attr_init(&attr);
    // pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    cout << "Here is test 1" << '\n';
    // pthread_mutex_init(&myMutex, NULL);
    void *status;

    if (colA == rowB)
    {
        cout << "Here is test 2" << '\n';
        for (int i = 0; i < NUM_THREADS; i++)
        {
            //pthread_mutex_lock(&myMutex);
            cout << "This should be thread " << i << '\n';

            data[i].bounds = bounds;
            data[i].iteration = i;
            data[i].matrixA = matrixA;
            data[i].matrixB = matrixB;

            pthread_create(&threads[i], NULL, multiplyThread, (void *)&data[i]);
            //pthread_mutex_unlock(&myMutex);
        }
    }
    else
    {
        cout << "ERROR IN RANK 2 TENSOR CONTRACTION \n";
        //can implement some sort of error once function is set using throw and catch.
    }

    //pthread_attr_destroy(&attr);
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], &status);
    }

    endTime = clock();

    clock_t runTime;
    runTime = endTime - startTime;

    ofstream times("times.log", ofstream::app);

    times << "rank2TensorMultPThread: \n Bounds: " << bounds << "\n Start: " << startTime << " clock cycles, " << (double)startTime / CLOCKS_PER_SEC << " seconds." << '\n';
    times << "End: " << endTime << " clock cycles, " << (double)endTime / CLOCKS_PER_SEC << " seconds." << '\n';
    times << "Total runtime: " << runTime << " clock cycles, " << (double)runTime / CLOCKS_PER_SEC << "seconds." << '\n'
          << '\n';

    // Just checking the results of the multiplication.
    /*cout << "Result matrix is \n";
    for (int i = 0; i < rowC; i++)
    {
        for (int j = 0; j < colC; j++)
            cout << matrixC[i][j] << " ";
        cout << "\n";
    }*/

    // pthread_mutex_destroy(&myMutex);
    pthread_exit(NULL);

    return;
}