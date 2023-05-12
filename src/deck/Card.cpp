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


string Card::print() const {
    return "";
}

string Valued_Card::print() const {
    std::stringstream card("");
    card << "|" << value_ << "_" << this->cardColorToString() << "|";
    return card.str();
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




