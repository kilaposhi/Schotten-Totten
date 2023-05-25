#include "Card.h"

initializer_list<CardColor> CardColors = {CardColor::red,
                                          CardColor::green,
                                          CardColor::blue,
                                          CardColor::purple,
                                          CardColor::brown,
                                          CardColor::orange};

// -------------------Constructors
ValuedCard::ValuedCard(int Value, CardColor Color) : value_(Value), color_(Color) {}

ValuedCard::ValuedCard(Card& valuedCard){
    if (dynamic_cast<ValuedCard*>(&valuedCard) == nullptr)
        throw CardException("Trying to convert another derived class of 'Card' into a 'ValuedCard'");

    *this = dynamic_cast<ValuedCard&>(valuedCard);
}

ValuedCard::ValuedCard(unique_ptr<Card> valuedCard){
    if (dynamic_cast<ValuedCard*>(valuedCard.get()) == nullptr)
        throw CardException("Trying to convert another derived class of 'Card' into a 'ValuedCard'");

    *this = *(dynamic_cast<ValuedCard*>(valuedCard.release()));
}

ValuedCard::ValuedCard(Card *valuedCard) {
    if (dynamic_cast<ValuedCard*>(valuedCard) == nullptr)
        throw CardException("Trying to convert another derived class of 'Card' into a 'ValuedCard'");
    *this = *(dynamic_cast<ValuedCard*>(valuedCard));
}

CardColor ValuedCard::getColor() const {
    return color_;
}


int ValuedCard::getValue() const {
    return value_;
}



//----- Displayers :

string ValuedCard::cardColorToString() const {
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

string ValuedCard::print() const {
    std::stringstream card("");
    card << "|" << value_ << "_" << this->cardColorToString() << "|";
    return card.str();
}


ostream& operator<<(ostream& stream, const Card& card){
    stream << card.print();
    return stream;
}

// cout << Valued_Card;  Example : |3_orange|
ostream& operator<<(ostream& stream, const ValuedCard& valued_card){
    stream << valued_card.print();
    return stream;
}



bool operator<(const ValuedCard& leftCard, const ValuedCard& rightCard){
    return leftCard.getValue() < rightCard.getValue();
}
bool operator>(const ValuedCard& leftCard, const ValuedCard& rightCard){
    return  operator< (rightCard,leftCard);
}
bool operator<=(const ValuedCard& leftCard, const ValuedCard& rightCard){
    return !operator> (leftCard, rightCard);
}
bool operator>=(const ValuedCard& leftCard, const ValuedCard& rightCard){
    return !operator< (leftCard,rightCard);
}

