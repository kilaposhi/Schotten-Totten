#include "Card.h"

initializer_list<CardColor> CardColors = {CardColor::red,
                                          CardColor::green,
                                          CardColor::blue,
                                          CardColor::purple,
                                          CardColor::brown,
                                          CardColor::orange};

Valued_Card::Valued_Card(int Value, CardColor Color) : value(Value), color(Color) {}

CardColor Valued_Card::getColor() const {
    return color;
}

int Valued_Card::getValue() const {
    return value;
}


//----- Displayers :

string Valued_Card::cardColorToString() const {
    switch (color) {
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

// cout << Card;  Example : |3_orange|
ostream& operator<<(ostream& stream, const Valued_Card& valued_card){
    stream << "|" << valued_card.getValue() << '_' <<
           valued_card.cardColorToString() << '|';
    return stream;
}




