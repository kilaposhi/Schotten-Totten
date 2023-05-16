#include "DeckFactory.h"

Deck DeckFactory::build() {
    DeckInfo newDeckInfo(
            number_cards_,
            min_card_value_,
            max_card_value_
            );
    Deck newDeck;
    newDeck.deckInfo_ = newDeckInfo;
    copy_vector_cards(this->cards_, newDeck.cards_);
    return newDeck;
}

void DeckFactory::create_valued_cards(){
    cards_.reserve(number_cards_);
    for (auto color : CardColors)
        for (int value = min_card_value_; value <= max_card_value_; value++)
            cards_.push_back(make_unique<ValuedCard>(value, color));
}

Deck DeckFactory::createClanDeck() {
    const int MAX_CLAN_CARD_VALUE = 9;
    const int MIN_CLAN_CARD_VALUE = 1;
    this->setRangeValueCard(MIN_CLAN_CARD_VALUE, MAX_CLAN_CARD_VALUE);
    this->create_valued_cards();

    return this->build();
}

void DeckFactory::setRangeValueCard(int min_card_value, int max_card_value) {
    this->min_card_value_ = min_card_value;
    this->max_card_value_ = max_card_value;
    this->number_cards_ = compute_number_cards(min_card_value, max_card_value);
}

unsigned int compute_number_cards(unsigned int min_value, unsigned int max_value ){
    unsigned int number_values = max_value - min_value + 1;
    unsigned int number_colors = 6; // EnumClass in .src\Card.h

    return number_values *  number_colors;;
}
