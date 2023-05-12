#ifndef SCHOTTEN_TOTTEN_PLAYER_H
#define SCHOTTEN_TOTTEN_PLAYER_H

#include <iostream>
#include <vector>
#include <list>

#include "Card.h"

using std::vector, std::list;



class Player {
private:
     int id;
     int number_of_cards;
     vector<Card> hand;
     int max_cards;
     list<bool> claimed_stones;

public:

    Player()=default;
    ~Player()=default;
    Player(const Player& stone)=default;
    Player& operator=(const Player& stone)=default;

    void play_card();
    const Card& draw_card();
    void claim_stone();
    int** getClaimed_stones();
    int getNumber_of_cards() const;

};


#endif //SCHOTTEN_TOTTEN_PLAYER_H
