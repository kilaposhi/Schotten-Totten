#ifndef SCHOTTEN_TOTTEN_DECK_H
#define SCHOTTEN_TOTTEN_DECK_H

#include <algorithm>
#include <random>
#include <memory>

#include "DeckCreator.h"
#include "Card.h"


using std::shuffle, std::random_device, std::mt19937, std::vector, std::cout;
using std::move, std::make_unique, std::unique_ptr;

enum class DeckType{
    ValuedCard,
    TacticCard,
    DiscardDeck
};

class DeckInfo{
private:
    DeckType deckType_;
    int total_number_cards_;
    int min_card_value_, max_card_value_;
public:
    DeckInfo()=default;
    DeckInfo( int total_number_cards,
             int min_card_value,
             int max_card_value);
    DeckInfo(const DeckInfo&)=default;
    DeckInfo& operator=(const DeckInfo&)=default;
    ~DeckInfo()=default;

    inline int getTotalNumberCards() const;
    inline int getMinCardValue() const;
    inline int getMaxCardValue() const;
};


class Deck {
private:
    friend class DeckCreator;
    DeckInfo deckInfo_;
    vector<unique_ptr<Card>> cards_;
public:

    Deck()=default;
    ~Deck()=default;
    Deck(const Deck& );
    Deck& operator=(const Deck&);

    void shuffle();
    bool isEmpty() const;
    unique_ptr<Card> drawCard();
    void putCard(unique_ptr<Card> card);
    int getNumberRemainingCards() const;
    DeckInfo getDeckInfo() const;
    void print() const;
};


void copy_vector_cards(
        const vector<unique_ptr<Card>>& from_cards,
        vector<unique_ptr<Card>>& to_cards
);


#endif //SCHOTTEN_TOTTEN_DECK_H
