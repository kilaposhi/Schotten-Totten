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

