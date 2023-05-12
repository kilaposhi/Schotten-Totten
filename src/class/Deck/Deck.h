#ifndef SCHOTTEN_TOTTEN_DECK_H
#define SCHOTTEN_TOTTEN_DECK_H

#include <algorithm>
#include <random>

#include "Card_game.h"
#include "DeckCreator.h"



using std::shuffle, std::random_device, std::mt19937, std::vector;
using std::cout;


class Deck {
private:

    friend class DeckCreator;

    DeckType deckType;
    vector<unique_ptr<Card>> cards_;
public:

    Deck();
    ~Deck()=default;
    Deck(const Deck& )=default;
    Deck& operator=(const Deck& )=default;

    void shuffle();
    bool isEmpty() const;
    const unique_ptr<Card> drawCard();
    int getNumberCardsRemaining() const;
    void print() const;
};


#endif
