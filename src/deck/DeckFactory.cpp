#include "DeckFactory.h"

Deck DeckFactory::build() {
    if (this->cards_.empty())
        throw DeckFactoryException("Building an empty Deck (cards_ is empty)");

    return {std::move(this->cards_)};
}


void DeckFactory::create_valued_cards(){
    cards_.reserve(number_cards_);

    auto color_iterator = CardColors.begin();
    for (size_t color_index = 0; color_index < number_colors_ ; color_index++) {
        CardColor color = *color_iterator++;
        for (int value = min_card_value_; value <= max_card_value_; value++)
            cards_.push_back(make_unique<ValuedCard>(value, color));
    }
}


Deck DeckFactory::createClanDeck() {
    const int MAX_CLAN_CARD_VALUE = 9;
    const int MIN_CLAN_CARD_VALUE = 1;
    this->setRangeValueCard(MIN_CLAN_CARD_VALUE, MAX_CLAN_CARD_VALUE);
    this->setNumberColors(6);
    this->create_valued_cards();

    return this->build();
}


void DeckFactory::setRangeValueCard(unsigned int min_card_value, unsigned int max_card_value) {
    this->min_card_value_ = min_card_value;
    this->max_card_value_ = max_card_value;
    this->number_cards_ = compute_number_cards(min_card_value, max_card_value, number_colors_);
}


void DeckFactory::setNumberColors(unsigned int number_colors) {
    if (number_colors > 7)
        throw DeckFactoryException("There is only 7 colors implemented in the enum class `CardColor`, see 'Card.h'");
    this->number_colors_ = number_colors;
    this->number_cards_ = compute_number_cards(min_card_value_, max_card_value_, number_colors_);
}


unsigned int compute_number_cards(unsigned int min_value, unsigned int max_value, unsigned int num_colors){
    unsigned int number_values = max_value - min_value + 1;
    return number_values *  num_colors;
}
