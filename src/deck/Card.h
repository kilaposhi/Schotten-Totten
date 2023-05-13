
#ifndef SCHOTTEN_TOTTEN_CARD_H
#define SCHOTTEN_TOTTEN_CARD_H

#include <iostream>
#include <initializer_list>
#include <string>
#include <sstream>
#include <memory>


using std::string, std::ostream, std::initializer_list, std::unique_ptr ;


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

    virtual string print() const;
    virtual unique_ptr<Card> clone();
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

    CardColor getColor() const;
    int getValue() const;
    string cardColorToString() const;


    string print() const override;
    unique_ptr<Card> clone() override;
};

ostream& operator<<(ostream& stream, const Card& Card);
// cout << Valued_Card;    Example : |3_orange|
ostream& operator<<(ostream& stream, const Valued_Card& valued_card);


class Tactic_card : public Card {

};



#endif //SCHOTTEN_TOTTEN_CARD_H
