#ifndef PROJET_COMBINATION_H
#define PROJET_COMBINATION_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "deck/Card.h"
#include "player/Player.h"

class Combination {
private:
    std::vector<Card> cards;
    int sumValues;

public:
    int getSum() const;

    void push_back(const ValuedCard &card);

    friend class Border;
};

#endif //PROJET_COMBINATION_H
