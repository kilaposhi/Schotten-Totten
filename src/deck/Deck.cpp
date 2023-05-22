#include "Deck.h"

// ------------------------DeckInfo
DeckInfo::DeckInfo(int total_number_cards, int min_card_value, int max_card_value) :
        deckType_(DeckType::ValuedCard),
        total_number_cards_(total_number_cards),
        min_card_value_(min_card_value),
        max_card_value_(max_card_value) {}

inline int DeckInfo::getTotalNumberCards() const { return this->total_number_cards_;}
inline int DeckInfo::getMinCardValue() const { return this->min_card_value_;}
inline int DeckInfo::getMaxCardValue() const { return this->max_card_value_;}

// -------------------- DecK

Deck::Deck(const Deck &otherDeck) {
    this->deckInfo_ = otherDeck.deckInfo_;
    copy_vector_cards(otherDeck.cards_, this->cards_);
}

Deck::Deck(Deck &&otherDeck) : cards_(std::move(otherDeck.cards_)) , deckInfo_(std::move(otherDeck.deckInfo_))  {}

Deck &Deck::operator=(const Deck &deck) {
    this->deckInfo_ = deck.deckInfo_;
    copy_vector_cards(deck.cards_, this->cards_);
    return *this;
}


void Deck::shuffle() {
    random_device randomDevice;
    mt19937 generator(randomDevice()); // Random generator better than rand;
    std::shuffle(cards_.begin(), cards_.end(), generator);
}


bool Deck::isEmpty() const { return cards_.empty(); }


unique_ptr<Card> Deck::drawCard() {
    if (this->isEmpty()) {
        throw std::out_of_range("The deck is empty");
    }
    auto card = std::move(cards_.back());
    cards_.pop_back();
    return std::move(card);
}


void Deck::putCard(unique_ptr<Card> card) {
    cards_.insert(cards_.cbegin() , std::move(card));
}


int Deck::getNumberRemainingCards() const{ return (int)cards_.size(); }


DeckInfo Deck::getDeckInfo() const{ return this->deckInfo_;  }


void Deck::print() const {
    for (auto& card : cards_)
        cout << *card << '\n';
}

// Functions

void copy_vector_cards(
        const vector<unique_ptr<Card>>& from_cards,
        vector<unique_ptr<Card>>& to_cards
        ){

    to_cards.reserve(from_cards.size());

    for (const auto& card : from_cards)
        to_cards.emplace_back(std::move(card->clone()));
}

