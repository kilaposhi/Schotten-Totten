#include "Card.h"

initializer_list<CardColor> CardColors = {CardColor::red,
                                          CardColor::green,
                                          CardColor::blue,
                                          CardColor::yellow,
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


TacticCard::TacticCard(TacticType type) {
    name = type;
    description = createTacticDescription(type);
}

TacticType TacticCard::getName() const{
    return name;
}

string TacticCard::getDescription() const {
    return description;
}


//----- Displayers :

string cardColorToString(CardColor color) {
    switch (color) {
        case CardColor::red: return "red";
        case CardColor::green : return "green";
        case CardColor::blue : return "blue";
        case CardColor::yellow : return "yellow";
        case CardColor::purple : return "purple";
        case CardColor::orange : return "orange";
        case CardColor::brown : return "brown";
        default:
            throw CardException("Trying to convert unknown CardColor to string");
    }
}

string tacticTypeToString(TacticType type) {
    switch (type) {
        case TacticType::joker : return "joker";
        case TacticType::spy : return "spy";
        case TacticType::shield_bearer : return "shield bearer";
        case TacticType::blind_man_bluff : return "blind man's bluff";
        case TacticType::mud_fight : return "mud fight";
        case TacticType::recruiter : return "recruiter";
        case TacticType::strategist : return "strategist";
        case TacticType::banshee : return "banshee";
        case TacticType::traiter : return "traiter";
        default:
            throw CardException("Trying to convert unknown TacticType to string");
    }
}

string ValuedCard::print() const {
    std::stringstream card("");
    card << "|" << value_ << "_" << cardColorToString(color_) << "|";
    return card.str();
}


string TacticCard::print() const {
    std::stringstream card("");
    card << "|" << tacticTypeToString(name) << "|";
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


ostream& operator<<(ostream& stream, const TacticCard& tactic_card){
    stream << tactic_card.print();
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


string createTacticDescription(TacticType type) {
    switch(type) {
        case TacticType::joker : return "Clan card of which you \n"
                                        "choose the color and strength when \n"
                                        "claiming the Stone you play it on. \n"
                                        "Each player can only have one \n"
                                        "Joker on his side of the border. If \n"
                                        "you have already played a Joker and \n"
                                        "you draw the second one, you must \n"
                                        "keep it in your hand until the end \n"
                                        "of the game";
        case TacticType::spy : return "Clan card of strength 7 of \n"
                                      "which you choose the color when \n"
                                      "claiming the Stone you play it on.";
        case TacticType::shield_bearer : return " Clan card of \n"
                                                "strength 1, 2, or 3 of which you \n"
                                                "choose the color when claiming the \n"
                                                "Stone you play it on.";
        case TacticType::blind_man_bluff : return "To claim the \n"
                                                  "Stone that has Blind-Man’s Bluff \n"
                                                  "on it, add only the strength of \n"
                                                  "the cards played on it, without \n"
                                                  "taking into account any possible \n"
                                                  "combinations";
        case TacticType::mud_fight : return "To claim the Stone that \n"
                                            "has Mud Fight on it, you must make \n"
                                            "combinations with four cards on \n"
                                            "either side of the Stone.";
        case TacticType::recruiter : return "Draw three cards from \n"
                                            "one or both of the decks. Choose \n"
                                            "two cards from your entire hand \n"
                                            "and place them at the bottom of \n"
                                            "the corresponding deck.";
        case TacticType::strategist : return "Choose a Clan or \n"
                                             "Tactic card on your \n"
                                             "side of the border on an\n"
                                             "unclaimed Stone. Place it face-up \n"
                                             "on a different unclaimed Stone or \n"
                                             "discard it face-up next to the deck.";
        case TacticType::banshee : return "Choose a Clan or Tactic \n"
                                          "card on your opponent’s side of the \n"
                                          "border on an unclaimed Stone and \n"
                                          "discard it face-up next to the deck. ";
        case TacticType::traiter : return "Choose a Clan card on your \n"
                                          "opponent’s side of the border on an \n"
                                          "unclaimed Stone and place it on an \n"
                                          "unclaimed Stone on your side.";
        default :
            throw CardException("Trying to get the description of an unknown tactic card");
    }
}

