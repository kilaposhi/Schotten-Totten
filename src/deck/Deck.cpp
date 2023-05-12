#include "Deck.h"

Deck::Deck(vector<const Card*> cards) : cards_(cards) {
    this->shuffle();
}

void Deck::shuffle() {
    random_device randomDevice;
    mt19937 generator(randomDevice()); // Random generator better than rand;
    std::shuffle(cards_.begin(), cards_.end(), generator);
}

const Card& Deck::drawCard() {
    if (cards_.empty()) {
        throw std::out_of_range("The deck is empty");
    }
    const Card* card = cards_.back();
    cards_.pop_back();
    return *card;
}

void Deck::print() const {
    for (auto& card : cards_)
        cout << *card << '\n';
}