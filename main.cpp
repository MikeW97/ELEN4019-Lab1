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

using namespace std;

int main()
{    
    // Generates matrices in seperate text files with specified bounds and dimensions
    int bounds = 10;
    int dimensions = 2;
    matrixGen(bounds, dimensions);

    // Performs Rank 2 Tensor Contraction without threading
    rank2TensorPlain(bounds);

    // Generates 3D matrices with specified bounds
    bounds = 10;
    dimensions = 3;
    matrixGen(bounds, dimensions);

    // Performs Rank 3 Tensor Contraction without threading
    rank3TensorPlain(bounds);

    return 0;
}