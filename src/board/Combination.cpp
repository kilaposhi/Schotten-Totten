//
// Created by Lilian Valin on 18/05/2023.
//

#include "Combination.h"

int Combination::getSum() const {
    return sumValues;
}

int Combination::size() const {
    return cards.size();
}

void Combination::push_back(const ValuedCard& card) {
    cards.push_back(card);
    sumValues += card.getValue();
}

CombinationType Combination::compute_combination() const {
    int n = size();
    if (n < 3) {
        throw CombinationException("There is not enough cards to claim the stone");
    } else if (Color(n) && Run(n)) {
        return CombinationType::ColorRun;
    } else if (Color(n)) {
        return CombinationType::Color;
    } else if (ThreeOfAKind(n)) {
        return CombinationType::ThreeOfAKind;
    } else if (Run(n)) {
        return CombinationType::Run;
    } else {
        return CombinationType::Sum;
    }
}

bool Combination::Color(int n) {
    bool color = true;
    int i = 0;
    while (i < n - 1 && color) {
        if (color = (cards[i]->getColor() != cards[i + 1]->getColor())) {
            color = false;
        }
        i++;
    }
    return color;
}

bool Combination::ThreeOfAKind(int n) {
    bool three = true;
    int i = 0;
    while (i < n - 1 && three) {
        if (cards[i]->getValue() != cards[i+1]->getValue()) {
            three = false;
        }
        i++;
    }
    return three;
}

bool Combination::Run(vector<Card*> combination, int n) {
    sort(cards.begin(), cards.end());
    bool run = true;
    int i = 0;
    while (i < n - 1 && run) {
        if (cards[i]->getValue() != cards[i+1]->getValue() - 1) {
            run = false;
        }
        i++;
    }
    return run;
}

CombinationType Combination::getType() const {
    if (!type) {
        return compute_combination();
    } else {
        return type;
    }
}

bool operator<(const Combination& LeftCombination, const Combination& RightCombination) {
    if (LeftCombination.getType() == RightCombination.getType()) {
        return (LeftCombination.getSum() < RightCombination.getSum());
    } else {
        return (LeftCombination.getType() < Right}}

#endif //SCHOTTEN_TOTTEN_STONE_H
