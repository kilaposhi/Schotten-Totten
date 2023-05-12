#include "Deck.h"

Deck::Deck(vector<const Card*> cards) : cards_(cards) {
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

Card Deck::drawCard() {
    if (this->isEmpty()) {
        throw std::out_of_range("The deck is empty");
    }
    const Card* card = cards_.back();
    cards_.pop_back();
    return *card;
}

void Deck::putCard(const Card& card) {
    cards_.insert(cards_.cbegin() , *card);
}

int Deck::getNumberRemainingCards() const{
    return cards_.size();
}

void Deck::print() const {
    for (auto& card : cards_)
        cout << *card << '\n';
}