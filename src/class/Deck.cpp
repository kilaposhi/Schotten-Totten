#include "Deck.h"

Deck::Deck(vector<Card> cards) : cards_(cards) {
    shuffle_deck();
}

void Deck::shuffle_deck() {
    random_device randomDevice;
    mt19937 generator(randomDevice()); // Random generator better than rand;
    shuffle(cards_.begin(), cards_.end(), generator);
}

const Card& Deck::drawCard() {
    if (cards_.empty()) {
        throw std::exception();
    }
    const Card& card = cards_.back();
    cards_.pop_back();
    return card;
}

void Deck::print() const {
    int i = 0;
    for (auto& card : cards_)
        cout <<i << '\n';
//        cout << card << '\n';
}