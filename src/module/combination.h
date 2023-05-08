#ifndef SHOTTEN_TOTTEN_COMBINATION_H
#define SHOTTEN_TOTTEN_COMBINATION_H

#include <iostream>
#include <vector>

#include "../class/Card.h"

using std::vector;



int compute_combination(vector<Card> combination);

bool is_color_run(vector<Card> combination);
bool is_three_of_a_kind(vector<Card> combination);
bool is_color(vector<Card> combination);
bool is_run(vector<Card> combination);

int compute_sum(vector<Card> combination);
int compute_sum(vector<Card> combination); // because of the Tactic card

// compute_all_combinations()


#endif //SHOTTEN_TOTTEN_COMBINATION_H
