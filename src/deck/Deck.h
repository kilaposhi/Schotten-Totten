#ifndef SCHOTTEN_TOTTEN_DECK_H
#define SCHOTTEN_TOTTEN_DECK_H

#include <algorithm>
#include <random>
#include <memory>
#include <vector>

#include "DeckFactory.h"
#include "Card.h"


using std::shuffle, std::random_device, std::mt19937, std::vector, std::cout;
using std::move, std::make_unique, std::unique_ptr;


class Deck {
public:

    Deck()=default;
    Deck(vector<unique_ptr<Card>>&& cards); // constructor used by 'DeckFactory'
    ~Deck()=default;
    Deck(const Deck&) = delete;
    Deck& operator=(const Deck &) = delete;
    Deck(Deck&&) noexcept ;
    Deck& operator=(Deck &&otherDeck) noexcept;

public:
    void shuffle();
    [[nodiscard]] bool isEmpty() const;
    unique_ptr<Card> drawCard();
    void removeCard(const Card* card);
    void putCard(unique_ptr<Card> card);
    void pushCardTop(unique_ptr<Card> card);
    [[nodiscard]] int getNumberRemainingCards() const;
    void str() const;
    void clear();
    unique_ptr<Card> drawCardByIndex(int index);
private:
    vector<unique_ptr<Card>> cards_;
};

ostream& operator<<(ostream& stream, const Deck& deck);

#endif //SCHOTTEN_TOTTEN_DECK_H
