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

Deck::Deck(DeckInfo deckInfo, vector<unique_ptr<Card>>&& cards)
            : deckInfo_(deckInfo), cards_(std::move(cards)) {};

Deck::Deck(Deck &&otherDeck) noexcept :
            cards_(std::move(otherDeck.cards_)) ,
            deckInfo_(otherDeck.deckInfo_)
            { }

Deck &Deck::operator=(Deck &&otherDeck) noexcept {
    if (this == &otherDeck){
        return *this;
    }
    this->deckInfo_ = otherDeck.deckInfo_;
    this->cards_ = std::move(otherDeck.cards_);
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


