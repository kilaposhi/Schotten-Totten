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

Deck::Deck(const Deck &deck) {
    this->deckInfo_ = deck.deckInfo_;
    copy_vector_cards(deck.cards_, this->cards_);
}


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
    auto card = move(cards_.back());
    cards_.pop_back();
    return move(card);
}


void Deck::putCard(unique_ptr<Card> card) {
    cards_.insert(cards_.cbegin() , move(card));
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
    size_t vector_cards_size = from_cards.size();
    to_cards.reserve(vector_cards_size);

    for (const auto& card : from_cards)
        to_cards.push_back(card->clone());
}
