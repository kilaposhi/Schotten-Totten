#ifndef SHOTTEN_TOTTEN_STONE_H
#define SHOTTEN_TOTTEN_STONE_H


#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "Card.h"

using std::string, std::exception, std::vector ;

class Stone {
private:
    bool claimed;
//    Player& winner;
    unsigned int slot_number;
    vector<Card> cardSlotsAvailable;
    Card* tactic_slot;
    Card** player_1_combination;
    Card** player_2_combination;

    int getNbStoneTiles();
    void addCard();

};


#endif //SHOTTEN_TOTTEN_STONE_H
