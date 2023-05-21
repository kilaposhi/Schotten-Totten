#ifndef PROJET_COMBINATION_H
#define PROJET_COMBINATION_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <memory>

#include "deck/Card.h"
#include "player/Player.h"

class Combination {
private:
    std::vector<std::unique_ptr<ValuedCard>> cards;
    int sumValues;
    Player* player;

public:
    int getSum() const;
    Player* getPlayer();
    void push_back(std::unique_ptr<ValuedCard> card);

};



#endif //PROJET_COMBINATION_H
