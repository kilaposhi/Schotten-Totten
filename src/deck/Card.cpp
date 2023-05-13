#include "Card.h"

initializer_list<CardColor> CardColors = {CardColor::red,
                                          CardColor::green,
                                          CardColor::blue,
                                          CardColor::purple,
                                          CardColor::brown,
                                          CardColor::orange};

Valued_Card::Valued_Card(int Value, CardColor Color) : value_(Value), color_(Color) {}

CardColor Valued_Card::getColor() const {
    return color_;
}

int Valued_Card::getValue() const {
    return value_;
}


//----- Displayers :

string Valued_Card::cardColorToString() const {
    switch (color_) {
        case CardColor::red: return "red";
        case CardColor::green : return "green";
        case CardColor::blue : return "blue";
        case CardColor::purple : return "purple";
        case CardColor::orange : return "orange";
        case CardColor::brown : return "brown";
        default:
            throw CardException("Trying to convert unknown CardColor to string");
    }
}


unique_ptr<Card> Card::clone() {
    throw CardException("Cloning an empty Card");
}


string Card::print() const {
    throw CardException("Printing an empty Card");
}

string Valued_Card::print() const {
    std::stringstream card("");
    card << "|" << value_ << "_" << this->cardColorToString() << "|";
    return card.str();
}


unique_ptr<Card> Valued_Card::clone() {
    return std::make_unique<Valued_Card>(*this);
}


ostream& operator<<(ostream& stream, const Card& card){
    stream << card.print();
    return stream;
}
// cout << Valued_Card;  Example : |3_orange|
ostream& operator<<(ostream& stream, const Valued_Card& valued_card){
    stream << valued_card.print();
    return stream;
}




