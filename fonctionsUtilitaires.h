//
// Created by jacpr on 2026-06-20.
//

#ifndef CONNECT4_FONCTIONSUTILITAIRES_H
#define CONNECT4_FONCTIONSUTILITAIRES_H

#include <vector>

bool set_token(std::vector<std::vector<int> > &p_matrix, const int &p_col, const int &p_player);

std::vector<std::vector<int> > transpose(std::vector<std::vector<int> > p_matrix);
std::vector<std::vector<int> > mirror(std::vector<std::vector<int> > p_matrix);

bool is_all_the_same(std::vector<int> p_line);
bool is_grid_full(const std::vector<std::vector<int> > &p_matrix);

int pos_diag_check(const std::vector<std::vector<int> > &p_matrix);
int neg_diag_check(const std::vector<std::vector<int> > &p_matrix);
int horizontal_check(const std::vector<std::vector<int> > &p_matrix);
int vertical_check(const std::vector<std::vector<int> > &p_matrix);
int is_winner(std::vector<std::vector<int> > &p_matrix);

void printMatrix(const std::vector<std::vector<int> > &p_matrix);


#endif //CONNECT4_FONCTIONSUTILITAIRES_H
