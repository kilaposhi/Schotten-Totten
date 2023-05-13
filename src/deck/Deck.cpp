#include "Deck.h"


Deck::Deck(const Deck &deck) {
    copy_vector_cards(deck.cards_, this->cards_);
}


Deck &Deck::operator=(const Deck &deck) {
    copy_vector_cards(deck.cards_, this->cards_);
    return *this;
}

void Deck::shuffle() {
    random_device randomDevice;
    mt19937 generator(randomDevice()); // Random generator better than rand;
    std::shuffle(cards_.begin(), cards_.end(), generator);
}

bool Deck::isEmpty() const {
    return cards_.empty();
}

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

int Deck::getNumberRemainingCards() const{
    return (int)cards_.size();
}

void Deck::print() const {
    for (auto& card : cards_)
        cout << *card << '\n';
}

void copy_vector_cards(
        const vector<unique_ptr<Card>>& from_cards,
        vector<unique_ptr<Card>>& to_cards
        ){
    size_t vector_cards_size = from_cards.size();
    to_cards.reserve(vector_cards_size);

    for (const auto& card : from_cards)
        to_cards.push_back(card->clone());
}
