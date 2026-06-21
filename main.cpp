#include <iostream>
#include <vector>

#include "fonctionsUtilitaires.h"


int main()
{
    std::vector<std::vector<int> > matrix = {
        {1, 2, 1, 1},
        {2, 1, 2, 2},
        {1, 2},
        {1, 1, 2},
        {1, 1, 1, 2},
        {1, 1},
        {1, 1, 1, 2},
    };

    printMatrix(transpose(matrix));


    return 0;
}
