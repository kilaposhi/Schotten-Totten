#include "Card.h"


Clan_card::Clan_card(CardColor Color, int Strength) : color(Color), strength(Strength) {
    if (strength < 1 || strength > 9  )
        throw CardException("Card strength must be : 1 <= strength <= 9");
}

CardColor Clan_card::getColor() const {
    return color;
}

int Clan_card::getStrength() const {
    return strength;
}




//----- Displayers :

string card_color_to_string(CardColor card_color) {
    switch (card_color) {
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
ostream& operator<<(ostream& stream, const Clan_card& clan_card){
    stream << "|" << clan_card.getStrength() << '_' <<
              card_color_to_string(clan_card.getColor()) << '|';
    return stream;
}




