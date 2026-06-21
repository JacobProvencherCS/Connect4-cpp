//
// Created by jacpr on 2026-06-20.
//

#ifndef CONNECT4_FONCTIONSUTILITAIRES_H
#define CONNECT4_FONCTIONSUTILITAIRES_H

#include <vector>

bool set_token(std::vector<std::vector<int> > &p_matrix, const int &p_col, const int &p_player);
std::vector<std::vector<int> > transpose(std::vector<std::vector<int> > &p_matrix);
bool is_all_the_same(std::vector<int> p_line);
bool is_grid_full(const std::vector<std::vector<int> > &p_matrix);
bool pos_diag_check(std::vector<std::vector<int> > &p_matrix);
bool neg_diag_check(std::vector<std::vector<int> > &p_matrix);
bool horizontal_check(std::vector<std::vector<int> > &p_matrix);
bool vertical_check(std::vector<std::vector<int> > &p_matrix);
int is_winner(const std::vector<std::vector<int> > &p_matrix);
void printMatrix(const std::vector<std::vector<int> > &p_matrix);


#endif //CONNECT4_FONCTIONSUTILITAIRES_H
