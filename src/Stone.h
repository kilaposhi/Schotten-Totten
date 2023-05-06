#ifndef SHOTTEN_TOTTEN_STONE_H
#define SHOTTEN_TOTTEN_STONE_H


#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "Card.h"
#include "Player.h"

using std::string, std::exception, std::vector ;

class Stone {
private:
    bool claimed;
    Player& winner;
    unsigned int slot_number;
    vector<Card> cardSlotsAvailable;
    Card* tactic_slot;
    Card** player_1_combination;
    Card** player_2_combination;

public:
    Stone()=default;
    ~Stone()=default;
    Stone(const Stone& stone)=default;
    Stone& operator=(const Stone& stone) =default;

    int getNbStone() const;
    void addCard() const;

};


#endif //SHOTTEN_TOTTEN_STONE_H
