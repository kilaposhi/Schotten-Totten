#include "Card.h"


Clan_card::Clan_card(CardColor Color, int Strength) : color(Color), strength(Strength) {
    if (1 > strength && strength > 9  )
        throw CardException("Card strength must be : 1 <= strength <= 9");
}

CardColor Clan_card::getColor() const {
    return color;
}

int Clan_card::getStrength() const {
    return strength;
}


ostream& operator<<(ostream& stream, const Clan_card& clan_card){
    stream << "|" << clan_card.getStrength() << '_' << clan_card.getColor() << '|';
    return stream;
}


ostream& operator<<(ostream& stream, CardColor color) {
    static const string card_colors[] = {
            "red",
            "green",
            "blue",
            "purple",
            "orange",
            "brown"};
    return stream << card_colors[color];
}


