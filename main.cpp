#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>

#include "matrixGen.h"
#include "rank2TensorMultOpenMP.h"
#include "rank2TensorMultPThread.h"
#include "rank3TensorMultOpenMP.h"
#include "rank3TensorMultPThread.h"

using namespace std;

int main()
{
    // Clears any information in the log file.
    ofstream times("times.log", ofstream::trunc);

    // Generates matrices in seperate text files with specified bounds and dimensions
    int bounds, dimensions;
    

    //  Performs Rank 2 Tensor Contraction with multithreading by OpenMP and then PThread and 3 different bounds
    dimensions = 2;
    
    bounds = 10;
    matrixGen(bounds, dimensions); 
    rank2TensorMultOpenMP(bounds);
    rank2TensorMultPThread(bounds);

    bounds = 20;
    matrixGen(bounds, dimensions);
    rank2TensorMultOpenMP(bounds);
    rank2TensorMultPThread(bounds);

    bounds = 30;
    matrixGen(bounds, dimensions);
    rank2TensorMultOpenMP(bounds);
    rank2TensorMultPThread(bounds);
    
    //  Performs Rank 3 Tensor Contraction with multithreading by OpenMP and then PThread and 3 different bounds
    dimensions = 3;
    
    bounds = 10;
    matrixGen(bounds, dimensions);
    rank3TensorMultOpenMP(bounds);
    rank3TensorMultPThread(bounds);

    bounds = 20;
    matrixGen(bounds, dimensions);
    rank3TensorMultOpenMP(bounds);
    rank3TensorMultPThread(bounds);

    bounds = 30;
    matrixGen(bounds, dimensions);
    rank3TensorMultOpenMP(bounds);
    rank3TensorMultPThread(bounds);

    return 0;
}