#ifndef SCHOTTEN_TOTTEN_DECK_H
#define SCHOTTEN_TOTTEN_DECK_H

#include <algorithm>
#include <random>

#include "Card_game.h"



using std::shuffle, std::random_device, std::mt19937, std::vector;
using std::cout;


class Deck {
private:
    vector<const Card*> cards_;
public:

    Deck(vector<const Card*>);
    ~Deck()=default;
    Deck(const Deck& )=default;
    Deck& operator=(const Deck& )=default;

    void shuffle();
    const Card& drawCard();
    void print() const;
};


#endif SCHOTTEN_TOTTEN_DECK_H
