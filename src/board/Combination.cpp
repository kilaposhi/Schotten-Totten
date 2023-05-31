#include "Combination.h"

int Combination::getSum() const {
    return sumValues;
}

void Combination::push_back(const ValuedCard& card) {
    cards.push_back(card);
    sumValues += card.getValue();
}



