#ifndef SCHOTTEN_TOTTEN_STONE_H
#define SCHOTTEN_TOTTEN_STONE_H


#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "deck/Card.h"
#include "player/Player.h"

using std::string, std::exception, std::vector ;


class Player;
class Stone {
private:
    int stone_number;
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
    void claim(int id_player_);
    int getNbStone() const;
    void addCard(unique_ptr<Card> card_) const;

};


#endif //SCHOTTEN_TOTTEN_STONE_H
