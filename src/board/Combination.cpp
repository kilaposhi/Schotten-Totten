//
// Created by Lilian Valin on 18/05/2023.
//

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



