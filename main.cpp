#include <algorithm>
#include <iostream>
#include <vector>
#include <ranges>
#include <functional>


bool set_token(std::vector<std::vector<int> > &p_matrix, const int col, const int player)
{
    bool valid = false;
    if (p_matrix[col].size() != 7)
    {
        p_matrix[col - 1].push_back(player);
        valid = true;
    }
    return valid;
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

bool is_all_the_same(std::vector<int> p_line)
{
    return std::ranges::adjacent_find(p_line, std::not_equal_to{}) == p_line.end() && p_line.front() != 0;
}

std::vector<std::vector<int> > mirror(std::vector<std::vector<int> > &p_matrix)
{
    std::vector<std::vector<int> > result = transpose(p_matrix);
    std::ranges::reverse(result);
    return result;
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


bool pos_diag_check(std::vector<std::vector<int> > &p_matrix)
{
    bool winner_found = false;
    for (int j = 0; j < 4 && !winner_found; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            const std::vector diag_values = {
                p_matrix[j][i],
                p_matrix[j + 1][i + 1],
                p_matrix[j + 2][i + 2],
                p_matrix[j + 3][i + 3]
            };
            if (is_all_the_same(diag_values))
            {
                winner_found = true;
            }
        }
    }
    return winner_found;
}

bool neg_diag_check(std::vector<std::vector<int> > &p_matrix)
{
    return pos_diag_check(mirror(p_matrix));
}

bool horizontal_check(std::vector<std::vector<int> > &p_matrix)
{
    bool winner_found = false;
    std::vector<std::vector<int> > new_matrix = transpose(p_matrix);

    for (auto lineIt = new_matrix.begin(); lineIt != new_matrix.end() && !winner_found; ++lineIt)
    {
        for (int i = 0; i < 4; i++)
        {
            if (const std::vector sub_line(lineIt->begin() + i, lineIt->begin() + i + 4); is_all_the_same(sub_line))
            {
                winner_found = true;
            }
        }
    }
    return winner_found;
}


bool vertical_check(std::vector<std::vector<int> > &p_matrix)
{
    bool winner_found = false;
    for (auto colIt = p_matrix.begin(); colIt != p_matrix.end() && !winner_found; ++colIt)
    {
        for (int i = 0; i < 4; i++)
        {
            if (const std::vector sub_col(colIt->begin() + i, colIt->begin() + i + 4); is_all_the_same(sub_col))
            {
                winner_found = true;
            }
        }
    }
    return winner_found;
}

int is_winner(const std::vector<std::vector<int> > &p_matrix)
{
    int outcome = 0;

    std::vector<std::function<bool(std::vector<std::vector<int> > &)> > verifications = {
        horizontal_check,
        vertical_check,
        pos_diag_check,
        neg_diag_check
    };

    for (int i = 1; i < 3 && outcome; i++) // for each player (1 and 2)
    {
        for (auto &verif: verifications)
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
        {1, 2, 1, 1},
        {2, 1, 2, 2},
        {1, 2},
        {1, 1, 2},
        {1, 1, 1, 2},
        {1, 1},
        {1, 1, 1, 2},
    };

    std::cout << is_winner(matrix) << std::endl;

    printMatrix(transpose(matrix));


    return 0;
}
