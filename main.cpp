#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

using std::cin;
using std::cout;
using std::invalid_argument;

int main()
{
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

    return 0;
}