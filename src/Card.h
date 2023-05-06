
#ifndef SHOTTEN_TOTTEN_CARD_H
#define SHOTTEN_TOTTEN_CARD_H

#include <iostream>
#include <string>

using std::string;

class CardException{
private:
    string message;
public:
    CardException(string Message) : message(Message){}

};

class Card {
private:
public:

    Card();
    ~Card()=default;
    Card(const Card& card)=default;
    Card& operator=(const Card& card) = default;
};

enum class CardColor{ red, green, blue, purple, orange, brown };

class Clan_card : public Card {
private:
    CardColor color;
    int strength;

public:
    Clan_card(CardColor Color, int Strength);
    ~Clan_card()=default;
    Clan_card(const Clan_card& clan_card)=default;
    Clan_card& operator=(const Clan_card& clan_card)= default;

    CardColor getColor() const;
    int getStrength() const;
};

class Tactic_card : public Card {

};




#endif //SHOTTEN_TOTTEN_CARD_H
