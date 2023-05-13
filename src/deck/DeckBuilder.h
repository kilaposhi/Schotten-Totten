#ifndef SCHOTTEN_TOTTEN_DECKBUILDER_H
#define SCHOTTEN_TOTTEN_DECKBUILDER_H

#include <vector>
#include <memory>

#include "Deck.h"
#include "Card.h"

class Deck;
enum class DeckType;

using std::move, std::vector, std::make_unique, std::unique_ptr;


class DeckBuilder {
private:
    DeckType deckType;
    int number_cards_ = 0;
    int min_card_value_;
    int max_card_value_;
    vector<unique_ptr<Card>> cards_; // T <=> Valued_Card**

    void setTypeCards(DeckType deckType);

    // ValuedCards method
    void setNumberColors(int number_colors );
    void setRangeValueCard(int min_card_value, int max_card_value);

    void create_valued_cards();

public:
    DeckBuilder(DeckType deckType);
    DeckBuilder()=default;
    DeckBuilder(const DeckBuilder&)=delete;
    DeckBuilder& operator=(const DeckBuilder&)=delete;
    ~DeckBuilder()=default;

    DeckBuilder& createClanDeck();
    DeckBuilder& createTacticDeck();
    Deck build();
};

unsigned int compute_number_cards(unsigned int min_value, unsigned int max_value );

#endif //SCHOTTEN_TOTTEN_DECKBUILDER_H
