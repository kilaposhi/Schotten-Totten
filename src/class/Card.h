
#ifndef SHOTTEN_TOTTEN_CARD_H
#define SHOTTEN_TOTTEN_CARD_H

#include <iostream>
#include <initializer_list>
#include <string>


using std::string, std::ostream, std::initializer_list ;


class CardException{
private:
    string exception;
public:
    CardException(string Exception) : exception(Exception){}

    string what() const { return exception;}
};


class Card {
private:
public:
    Card()=default;
    ~Card()=default;
    Card(const Card& card)=default;
    Card& operator=(const Card& card) = default;
};


// TODO make Enum colors modular to create any card game
enum class CardColor{
    red,
    green,
    blue,
    purple,
    orange,
    brown
};

extern initializer_list<CardColor> CardColors;

class Valued_Card : public Card {
private:
    CardColor color_;
    int value_;

public:
    Valued_Card(int Value, CardColor Color);
    ~Valued_Card()=default;
    Valued_Card(const Valued_Card& valuedCard)=default;
    Valued_Card& operator=(const Valued_Card& valuedCard)= default;

    string cardColorToString() const;
    CardColor getColor() const;
    int getValue() const;
};

// cout << Card;    Example : |3_orange|
ostream& operator<<(ostream& stream, const Valued_Card& valued_card);


class Tactic_card : public Card {

};



#endif //SHOTTEN_TOTTEN_CARD_H
