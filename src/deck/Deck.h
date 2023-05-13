#ifndef SCHOTTEN_TOTTEN_DECK_H
#define SCHOTTEN_TOTTEN_DECK_H

#include <algorithm>
#include <random>

#include "DeckCreator.h"
#include "Card.h"


using std::shuffle, std::random_device, std::mt19937, std::vector, std::cout;
using std::move;

class Deck {
private:
    friend class DeckCreator;
    vector<unique_ptr<Card>> cards_;
public:

    Deck();
    ~Deck()=default;
    Deck(const Deck& )=default;
    Deck& operator=(const Deck&);

    void shuffle();
    bool isEmpty() const;
    unique_ptr<Card> drawCard();
    void putCard(unique_ptr<Card> card);
    int getNumberRemainingCards() const;
    void print() const;
};

void copy_vector_cards(
        const vector<unique_ptr<Card>>& from_cards,
        vector<unique_ptr<Card>>& to_cards
);


#endif //SCHOTTEN_TOTTEN_DECK_H
