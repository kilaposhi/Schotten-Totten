
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

class ValuedCard : public Card {
private:
    CardColor color_;
    int value_;

public:
    ValuedCard(int Value, CardColor Color);
    ~ValuedCard()=default;
    ValuedCard(const ValuedCard& valuedCard)=default;
    ValuedCard& operator=(const ValuedCard& valuedCard)= default;

    CardColor getColor() const;
    int getValue() const;
    string cardColorToString() const;

    string print() const override;
    unique_ptr<Card> clone() override;
};

ostream& operator<<(ostream& stream, const Card& Card);
// cout << Valued_Card;    Example : |3_orange|
ostream& operator<<(ostream& stream, const ValuedCard& valued_card);




enum class TacticType {
    joker,
    spy,
    shield_bearer,
    blind_man_bluff,
    mud_fight,
    recruiter,
    strategist,
    banshee,
    traiter
};


class TacticCard : public Card {
private :
    TacticType name;
    string description;
public :
    TacticCard(TacticType type);
    TacticCard(const TacticCard&) = delete;
    TacticCard& operator=(const TacticCard&) = delete;
    TacticType getName() const;
    string getDescription() const;
    string cardNameToString() const;
    string print() const override;
};

ostream& operator<<(ostream& stream, const TacticCard& tactic_card);

class EliteTroop : public TacticCard {
private :
    CardColor color_;
    int value_;
public :
    CardColor getColor() const;
    int getValue() const;
    void setColor(CardColor color);
    void setValue(int val);
};


#endif //SCHOTTEN_TOTTEN_CARD_H
