#include "Deck.h"

Deck::Deck() : cards_() {
    this->shuffle();
}

void Deck::shuffle() {
    random_device randomDevice;
    mt19937 generator(randomDevice()); // Random generator better than rand;
    std::shuffle(cards_.begin(), cards_.end(), generator);
}

bool Deck::isEmpty() const {
    return cards_.empty();
}

const unique_ptr<Card> Deck::drawCard() {
    if (isEmpty()) {
        throw std::out_of_range("The deck is empty");
    }
    unique_ptr<Card> card = std::move(cards_.back() );
    cards_.pop_back();
    return card;
}

int Deck::getNumberCardsRemaining() const{
    return cards_.size();
}

void Deck::print() const {
    for (auto& card : cards_)
        cout << *card << '\n';
}