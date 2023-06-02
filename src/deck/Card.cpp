#include "Card.h"

initializer_list<CardColor> CardColors = {CardColor::red,
                                          CardColor::green,
                                          CardColor::blue,
                                          CardColor::purple,
                                          CardColor::brown,
                                          CardColor::orange};

ValuedCard::ValuedCard(int Value, CardColor Color) : value_(Value), color_(Color) {}

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


unique_ptr<Card> Card::clone() {
    throw CardException("Cloning an empty Card");
}


string Card::print() const {
    throw CardException("Printing an empty Card");
}

string ValuedCard::print() const {
    std::stringstream card("");
    card << "|" << value_ << "_" << this->cardColorToString() << "|";
    return card.str();
}


unique_ptr<Card> ValuedCard::clone() {
    return std::make_unique<ValuedCard>(*this);
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

TacticType TacticCard::getName() const{
    return name;
}

CardColor EliteTroop::getColor() const{
    return color_;
}

int EliteTroop::getValue() const {
    return value_;
}

void EliteTroop::setColor(CardColor color){
    color_=color;
}

void EliteTroop::setValue(int val){
    value_=val;
}

string TacticCard::cardNameToString() const {
    switch (name) {
        case TacticType::joker1: return "joker";
        case TacticType::joker2 : return "joker";
        case TacticType::espion : return "espion";
        case TacticType::porte_bouclier : return "porte bouclier";
        case TacticType::colin_maillard : return "colin maillard";
        case TacticType::combat_de_boue : return "combat de boue";
        case TacticType::chasseur_de_tete : return "chasseur de tête";
        case TacticType::stratege : return "stratege";
        case TacticType::banshee : return "banshee";
        case TacticType::traitre : return "traitre";
        default:
            throw CardException("Trying to convert unknown TacticType to string");
    }
}

string TacticCard::print() const {
    std::stringstream card("");
    card << "|" << this->cardNameToString() << "|";
    return card.str();
}


