#include "deck/Card.h"
#include "Combination.h"
#include <memory>

int Combination::getSum() const {
    return sumValues;
}

void Combination::push_back(std::unique_ptr<ValuedCard> card) {
    cards.push_back(std::move(card));
    sumValues += cards.back()->getValue();
}

Player *Combination::getPlayer() {
    return player;
}


int compute_combination(array<Card,3> combination){
    int strength;
    if (is_color_run(combination)) return strength = 4;
    if (is_three_of_a_kind(combination)) return strength = 3;
    if (is_color(combination)) return strength = 2;
    if (is_run(combination)) return strength = 1;

    return strength = 0; // need to compute the Sum
}

bool is_color_run(array<Card,3> combination){
    if (is_color(combination) && is_run(combination))
        return true;
    return false;
}