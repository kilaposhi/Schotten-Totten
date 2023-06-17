#include "Deck.h"

// -------------------- DecK

Deck::Deck(vector<unique_ptr<Card>>&& cards): cards_(std::move(cards)){}

Deck::Deck(Deck &&otherDeck) noexcept :
        cards_(std::move(otherDeck.cards_))
{ }

Deck &Deck::operator=(Deck &&otherDeck) noexcept {
    if (this == &otherDeck){
        return *this;
    }
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

void Deck::clear(){
    cards_.clear();
}

void Deck::str() const {
    for (auto& card : cards_)
        cout << *card << '\n';
}

ostream& operator<<(ostream& stream, const Deck& deck){
    stream  << "Remaining cards : " << deck.getNumberRemainingCards();
    return stream;
}

unique_ptr<Card> Deck::drawCardByIndex(int index){
    return std::move(cards_[index]);
}
