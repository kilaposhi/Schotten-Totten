#ifndef SCHOTTEN_TOTTEN_DECKFACTORY_H
#define SCHOTTEN_TOTTEN_DECKFACTORY_H

#include <vector>
#include <memory>
#include <string>

#include "Deck.h"
#include "Card.h"

class Deck;

using std::move, std::vector, std::make_unique, std::unique_ptr, std::string;

// Factory : https://refactoring.guru/fr/design-patterns/factory-method
class DeckFactory {
public:
    DeckFactory()=default;
    DeckFactory(const DeckFactory&)=delete;
    DeckFactory& operator=(const DeckFactory&)=delete;
    ~DeckFactory()=default;

    [[nodiscard]] Deck createClanDeck();
    [[nodiscard]] Deck createTacticDeck();

private: // attributes
    unsigned int number_cards_{0};
    unsigned int number_colors_{1};
    unsigned int min_card_value_{0};
    unsigned int max_card_value_{1};
    vector<unique_ptr<Card>> cards_; // T <=> Valued_Card**
private:
    // ValuedCards method
    void setNumberColors(unsigned int number_colors );
    void setRangeValueCard(unsigned int min_card_value, unsigned int max_card_value);
    void createValuedCards();

    void createTacticCards();
    Deck build();
};

unsigned int compute_number_cards(unsigned int min_value, unsigned int max_value, unsigned int num_colors);

class DeckFactoryException{
public:
    DeckFactoryException(string&& message) : message_(std::move(message)) { }
    string what() const noexcept { return message_; }
private:
    string message_;
};

#endif //SCHOTTEN_TOTTEN_DECKFACTORY_H
