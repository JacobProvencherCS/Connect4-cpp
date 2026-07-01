//
// Created by jacpr on 2026-06-20.
//

#ifndef CONNECT4_FONCTIONSUTILITAIRES_H
#define CONNECT4_FONCTIONSUTILITAIRES_H

#include <vector>

typedef std::vector<int> Line;
typedef std::vector<Line> Grid;

bool set_token(Grid &p_matrix, const int &p_col, const int &p_player);

Grid transpose(Grid p_matrix);
Grid mirror(Grid p_matrix);

bool is_all_the_same(const Line &p_line);
bool is_grid_full(const Grid &p_matrix);

int pos_diag_check(const Grid &p_matrix);
int neg_diag_check(const Grid &p_matrix);
int horizontal_check(const Grid &p_matrix);
int vertical_check(const Grid &p_matrix);
int is_winner(const Grid &p_matrix);

void printMatrix(const Grid &p_matrix);


#endif //CONNECT4_FONCTIONSUTILITAIRES_H
