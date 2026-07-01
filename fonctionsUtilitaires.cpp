#include <iostream>
#include <algorithm>
#include <ranges>
#include <functional>

#include "fonctionsUtilitaires.h"


bool set_token(Grid &p_matrix, const int &p_col, const int &p_player)
{
    bool valid_move = false;
    if (p_matrix[p_col].size() != 7)
    {
        p_matrix[p_col - 1].push_back(p_player);
        valid_move = true;
    }
    return valid_move;
}

Grid transpose(Grid p_matrix)
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

bool is_all_the_same(const Line &p_line)
{
    return std::ranges::adjacent_find(p_line, std::not_equal_to{}) == p_line.end() && p_line.front() != 0;
}

Grid mirror(Grid p_matrix)
{
    std::ranges::reverse(p_matrix);
    return p_matrix;
}

bool is_grid_full(const Grid &p_matrix)
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


int pos_diag_check(const Grid &p_matrix)
{
    int winner_found = 0;
    for (int j = 0; j < 4 && !winner_found; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            const Line diag_values = {
                p_matrix[j][i],
                p_matrix[j + 1][i + 1],
                p_matrix[j + 2][i + 2],
                p_matrix[j + 3][i + 3]
            };
            if (is_all_the_same(diag_values))
            {
                winner_found = diag_values[0];
            }
        }
    }
    return winner_found;
}

int neg_diag_check(const Grid &p_matrix)
{
    const Grid mirrored_matrix = mirror(p_matrix);
    return pos_diag_check(mirrored_matrix);
}

int horizontal_check(const Grid &p_matrix)
{
    int winner_found = 0;
    Grid new_matrix = transpose(p_matrix);

    for (auto lineIt = new_matrix.begin(); lineIt != new_matrix.end() && !winner_found; ++lineIt)
    {
        for (int i = 0; i < 4; i++)
        {
            if (const std::vector sub_line(lineIt->begin() + i, lineIt->begin() + i + 4); is_all_the_same(sub_line))
            {
                winner_found = sub_line[0];
            }
        }
    }
    return winner_found;
}


int vertical_check(const Grid &p_matrix)
{
    int winner_found = 0;
    for (auto colIt = p_matrix.begin(); colIt != p_matrix.end() && !winner_found; ++colIt)
    {
        for (int i = 0; i < 4; i++)
        {
            if (const std::vector sub_col(colIt->begin() + i, colIt->begin() + i + 4); is_all_the_same(sub_col))
            {
                winner_found = sub_col[0];
            }
        }
    }
    return winner_found;
}

int is_winner(const Grid &p_matrix)
{
    constexpr int winner_found = 0; // no winner found yet

    size_t total_tokens_played = 0;
    for (auto &col: p_matrix)
    {
        total_tokens_played += col.size();
    }

    if (total_tokens_played < 4) return 0;

    const std::vector<std::function<int(const Grid &)> > verifications = {
        horizontal_check,
        vertical_check,
        pos_diag_check,
        neg_diag_check
    };

    for (auto &verif: verifications)
    {
        if (const int winner = verif(p_matrix); winner != 0) return winner;
    }

    if (is_grid_full(p_matrix)) return 3; // it's a draw.

    return winner_found;
}

void printMatrix(const Grid &p_matrix)
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
