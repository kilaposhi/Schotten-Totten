#ifndef SCHOTTEN_TOTTEN_DECK_H
#define SCHOTTEN_TOTTEN_DECK_H

#include <algorithm>
#include <random>

#include "Card_game.h"



using std::shuffle, std::random_device, std::mt19937, std::vector, std::cout;


class Deck {
private:
    vector<const Card*> cards_;
public:

    Deck(vector<const Card*>);
    Deck()=default;
    ~Deck()=default;
    Deck(const Deck& )=default;
    Deck& operator=(const Deck& )=default;

    void shuffle();
    bool isEmpty() const;
    Card drawCard();
    void putCard(const Card card);
    int getNumberRemainingCards() const;
    void print() const;
};


#endif //SCHOTTEN_TOTTEN_DECK_H
