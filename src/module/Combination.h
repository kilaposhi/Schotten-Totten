#ifndef SHOTTEN_TOTTEN_COMBINATION_H
#define SHOTTEN_TOTTEN_COMBINATION_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <memory>

#include "deck/Card.h"
#include "player/Player.h"
#include "board/Border.h"

using std::vector;

class Combination {
private:
    std::vector<std::unique_ptr<ValuedCard>> value_cards;
    std::vector<std::unique_ptr<Tactic_card>> tactic_cards;
    int sumValues;
    Player* player;

public:
    int getSum() const;
    Player* getPlayer();
    void push_back(std::unique_ptr<ValuedCard> card);
    void push_back(std::unique_ptr<Tactic_card> card);
    void pop_back();

};

int compute_combination(vector<Card> combination);

bool is_color_run(vector<Card> combination);
bool is_three_of_a_kind(vector<Card> combination);
bool is_color(vector<Card> combination);
bool is_run(vector<Card> combination);

int compute_sum(vector<Card> combination);
int compute_sum(vector<Card> combination); // because of the Tactic card

// compute_all_combinations()


#endif //SHOTTEN_TOTTEN_COMBINATION_H