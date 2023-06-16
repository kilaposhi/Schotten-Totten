#include "DeckFactory.h"

Deck DeckFactory::build() {
    if (this->cards_.empty())
        throw DeckFactoryException("Building an empty Deck (cards_ is empty)");
    return {std::move(this->cards_)};
}


initializer_list<CardColor> cardColors = {
        CardColor::red,
        CardColor::green,
        CardColor::blue,
        CardColor::yellow,
        CardColor::purple,
        CardColor::brown,
        CardColor::orange
};

void DeckFactory::createValuedCards(){
    cards_.clear();
    cards_.reserve(number_cards_);

    auto color_iterator = cardColors.begin();
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
    this->createValuedCards();

    return this->build();
}

DeckInfo DeckFactory::getDeckInfo() {
    DeckInfo deckInfo{};
    deckInfo.min_card_value = min_card_value_;
    deckInfo.max_card_value = max_card_value_;
//    deckInfo.total_number_cards = compute_number_cards(min_card_value_, max_card_value_, number_colors_);
    deckInfo.number_colors = number_colors_;
    return deckInfo;
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

initializer_list<TacticType> tacticTypes = {
        TacticType::joker, // There is two joker in the Shotten-Totten
        TacticType::joker,
        TacticType::banshee,
        TacticType::shield_bearer,
        TacticType::blind_man_bluff,
        TacticType::mud_fight,
        TacticType::recruiter,
        TacticType::spy,
        TacticType::strategist,
        TacticType::traiter
};

void DeckFactory::createTacticCards() {
    cards_.clear();
    number_cards_ = tacticTypes.size();
    cards_.reserve(number_cards_);
    for (auto tacticType : tacticTypes)
        cards_.push_back(make_unique<TacticCard>(tacticType));
}

Deck DeckFactory::createTacticDeck() {
    this->createTacticCards();
    return this->build();
}

unsigned int compute_number_cards(unsigned int min_value, unsigned int max_value, unsigned int num_colors){
    unsigned int number_values = max_value - min_value + 1;
    return number_values *  num_colors;
}