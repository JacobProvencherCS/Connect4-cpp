#include <algorithm>
#include <iostream>
#include <vector>
#include <ranges>
#include <functional>

std::vector<std::vector<int> > grid;
std::vector<std::function<bool> > verifs = {
    horizontal_check,
    vertical_check,
    pos_diag_check,
    neg_diag_check
};

bool set_token(int col, int player)
{
    bool valid = false;
    if (grid[col].size() != 7)
    {
        grid[col].push_back(player);
        valid = true;
    }
    return valid;
}

int is_winner(const std::vector<std::vector<int> > &p_matrix)
{
    int outcome = 0;

    for (int i = 1; i < 3 && outcome; i++)
    {
        for (auto &verif: verifs)
        {
            if (verif(i))
            {
                outcome = i;
            }
        }
    }

    if (!outcome && is_grid_full(p_matrix))
    {
        outcome = 3;
    }
    return outcome;
}

bool pos_diag_check(std::vector<std::vector<int> > p_matrix)
{
    bool winner_found = false;
    for (int j = 0; j < 4 && !winner_found; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            std::vector<int> diag_values = {
                grid[j][i],
                grid[j+1][i+1],
                grid[j+2][i+2],
                grid[j+3][i+3]
            };
            if (is_all_the_same(diag_values))
            {
                winner_found = true;
            }
        }
    }
    return winner_found;
}

bool neg_diag_check(std::vector<std::vector<int>> p_matrix)
{
    return pos_diag_check(mirror(p_matrix));
}

bool horizontal_check(std::vector<std::vector<int>> p_matrix)
{
    bool winner_found = false;
    for (auto& line : transpose(p_matrix))
    {
        if (!winner_found)
        {
            for (int i = 0; i < 4; i++)
            {
                if (is_all_the_same(line[i:i+4])) // can't do that in C++... todo : fix here please...
                {
                    winner_found = true;
                }
            }
        }
    }
    return winner_found;
}

bool vertical_check(std::vector<std::vector<int>> p_matrix)
{
    bool winner_found = false;
    for (auto& col : p_matrix)
    {
        if (!winner_found)
        {
            for (int i = 0; i < 4; i++)
            {
                if (is_all_the_same(col[i:i+4])) // can't do that in C++... todo : fix here please...
                {
                    winner_found = true;
                }
            }
        }
    }
    return winner_found;
}

std::vector<std::vector<int> > transpose(std::vector<std::vector<int> > &p_matrix)
{
    if (p_matrix.empty()) return {};

    // Get ROWS X COLS, where ROWS is always 7 and COLS is the column with the most token in it.
    const size_t n_rows = p_matrix.size();
    constexpr size_t n_cols = 6;

    for (auto &col: p_matrix) col.resize(n_cols, 0);      // fill columns with zeros to ensure matrix is rectangle
    std::vector result(n_cols, std::vector<int>(n_rows)); // allocate memory for new array `result`

    for (size_t i = 0; i < n_rows; ++i)
    {
        for (size_t j = 0; j < n_cols; ++j)
        {
            result[j][i] = p_matrix[i][j];
        }
    }
    return result;
}

std::vector<std::vector<int> > mirror(std::vector<std::vector<int> > &p_matrix)
{
    std::vector<std::vector<int> > result = transpose(p_matrix);
    std::ranges::reverse(result);
    return result;
}

bool is_all_the_same(std::vector<int> p_line)
{
    return std::ranges::adjacent_find(p_line, std::not_equal_to{}) == p_line.end();
}

bool is_grid_full(const std::vector<std::vector<int> > &p_matrix)
{
    bool is_full = true;

    for (auto lineIt = p_matrix.begin(); lineIt != p_matrix.end() && is_full; ++lineIt)
    {
        if (lineIt->size() != 6)
        {
            is_full = false;
        }
    }
    return is_full;
}

void printMatrix(const std::vector<std::vector<int> > &p_matrix)
{
    for (auto &line: p_matrix | std::views::reverse)
    {
        for (auto &col: line)
        {
            std::cout << col;
        }
        std::cout << std::endl;
    }
}


int main()
{
    std::vector<std::vector<int> > matrix = {
        {1},
        {2, 1},
        {2, 2, 1},
        {3, 3, 3, 1},
        {},
        {},
        {4, 4, 4}
    };

    return 0;
}
