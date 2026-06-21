#include <iostream>
#include <vector>

#include "fonctionsUtilitaires.h"


int main()
{
    std::vector<std::vector<int> > matrix = {
        {},
        {},
        {},
        {},
        {},
        {},
        {}
    };

    int player_turn = 1;
    std::cout << is_winner(matrix) << std::endl;

    while (!is_winner(matrix))
    {
        int input;
        std::cout << "Enter a column number (1-7) : " << std::endl;
        std::cin >> input;
        set_token(matrix, input, player_turn);
        player_turn = player_turn % 2 + 1;
        printMatrix(transpose(matrix));
        std::cout << std::endl;
    }

    return 0;
}
