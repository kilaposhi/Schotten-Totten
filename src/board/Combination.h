#ifndef PROJET_COMBINATION_H
#define PROJET_COMBINATION_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "deck/Card.h"
#include "player/Player.h"

class Combination {
public:
    std::vector<int> cards;
    int sumValues;
};

#endif //PROJET_COMBINATION_H
