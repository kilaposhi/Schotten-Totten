
#ifndef SCHOTTEN_TOTTEN_CARD_H
#define SCHOTTEN_TOTTEN_CARD_H

#include <iostream>
#include <initializer_list>
#include <exception>
#include <string>
#include <sstream>
#include <memory>
#include <utility>


using std::string, std::ostream, std::initializer_list, std::unique_ptr , std::move;


class CardException : std::exception {
private:
    string exception_;
public:
    explicit CardException(string&& exception) : exception_(std::move(exception)){}
    [[nodiscard]] const char* what() const noexcept override{ return exception_.c_str();}
};

// Abstract class
class Card {
private:
public:
    Card() = default;
    virtual ~Card() = default;
    Card(const Card& card) = default;
    Card& operator=(const Card& card) = default;

    virtual string print() const = 0;
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
    explicit ValuedCard(Card& valuedCard);
    explicit ValuedCard(Card* valuedCard);
    explicit ValuedCard(unique_ptr<Card> valuedCard);
//    explicit ValuedCard(Card&& valuedCard);
    ~ValuedCard() override = default;
    ValuedCard(const ValuedCard& valuedCard) = default;
    ValuedCard& operator=(const ValuedCard& valuedCard) = default;
public:
    CardColor getColor() const;
    int getValue() const;
    string cardColorToString() const;
public:
    string print() const override;
};

ostream& operator<<(ostream& stream, const Card& Card);
// cout << Valued_Card;    Example : |3_orange|
ostream& operator<<(ostream& stream, const ValuedCard& valued_card);


inline bool operator<(const ValuedCard& leftCard, const ValuedCard& rightCard);
inline bool operator>(const ValuedCard& leftCard, const ValuedCard& rightCard);
inline bool operator<=(const ValuedCard& leftCard, const ValuedCard& rightCard);
inline bool operator>=(const ValuedCard& leftCard, const ValuedCard& rightCard);

class Tactic_card : public Card {

};



#endif //SCHOTTEN_TOTTEN_CARD_H
