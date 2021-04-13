#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>

#include "matrixGen.h"
#include "rank2TensorPlain.h"
#include "rank3TensorPlain.h"
#include "rank2TensorMultOpenMP.h"

using namespace std;

int main()
{
    // Clears any information in the log file.
    ofstream times("times.log", ofstream::trunc);

    // Generates matrices in seperate text files with specified bounds and dimensions
    int bounds, dimensions;
    bounds = 10;
    dimensions = 2;
    matrixGen(bounds, dimensions);
    //  Performs Rank 2 Tensor Contraction with multithreading by OpenMP
    rank2TensorMultOpenMP(bounds);

    bounds = 20;
    matrixGen(bounds, dimensions);
    rank2TensorMultOpenMP(bounds);

    bounds = 30;
    matrixGen(bounds, dimensions);
    rank2TensorMultOpenMP(bounds);

    return 0;
}