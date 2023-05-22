#ifndef SCHOTTEN_TOTTEN_DECKFACTORY_H
#define SCHOTTEN_TOTTEN_DECKFACTORY_H

#include <vector>
#include <memory>

#include "Deck.h"
#include "Card.h"

class Deck;
enum class DeckType;

using std::move, std::vector, std::make_unique, std::unique_ptr;

// Factory : https://refactoring.guru/fr/design-patterns/factory-method
class DeckFactory {
public:
    DeckFactory()=default;
    DeckFactory(const DeckFactory&)=delete;
    DeckFactory& operator=(const DeckFactory&)=delete;
    ~DeckFactory()=default;

    [[nodiscard]] unique_ptr<Deck> createClanDeck();
    [[nodiscard]] unique_ptr<Deck> createTacticDeck();

private: // attributes
    DeckType deckType_;
    unsigned int number_cards_{0};
    unsigned int number_colors_{1};
    unsigned int min_card_value_{0};
    unsigned int max_card_value_{1};
    vector<unique_ptr<Card>> cards_; // T <=> Valued_Card**

private: // methods
    void setTypeCards(DeckType deckType);

    // ValuedCards method
    void setNumberColors(unsigned int number_colors );
    void setRangeValueCard(unsigned int min_card_value, unsigned int max_card_value);
    void create_valued_cards();

    unique_ptr<Deck> build();

};

unsigned int compute_number_cards(unsigned int min_value, unsigned int max_value, unsigned int num_colors);

#endif //SCHOTTEN_TOTTEN_DECKFACTORY_H
