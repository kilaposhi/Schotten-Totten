
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


enum class CardColor{
    red,
    green,
    blue,
    yellow,
    purple,
    orange,
    brown
};

class ValuedCard : public Card {
public:
    ValuedCard(int Value, CardColor Color);
    explicit ValuedCard(Card& valuedCard);
    explicit ValuedCard(Card* valuedCard);
    explicit ValuedCard(unique_ptr<Card> valuedCard);
    ~ValuedCard() override = default;
    ValuedCard(const ValuedCard& valuedCard) = default;
    ValuedCard& operator=(const ValuedCard& valuedCard) = default;
public:
    CardColor getColor() const;
    int getValue() const;
    string print() const override;
private:
    CardColor color_;
    int value_;
};

string cardColorToString(CardColor color);

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
public :
    TacticCard(TacticType type);
    TacticCard(const TacticCard&) = delete;
    TacticCard& operator=(const TacticCard&) = delete;

    TacticType getName() const;
    string getDescription() const;
    string print() const override;
private :
    TacticType name;
    string description;
};

string tacticTypeToString(TacticType type) ;
string createTacticDescription(TacticType type);

inline bool operator<(const ValuedCard& leftCard, const ValuedCard& rightCard);
inline bool operator>(const ValuedCard& leftCard, const ValuedCard& rightCard);
inline bool operator<=(const ValuedCard& leftCard, const ValuedCard& rightCard);
inline bool operator>=(const ValuedCard& leftCard, const ValuedCard& rightCard);

ostream& operator<<(ostream& stream, const Card& Card);
// cout << Valued_Card;    Example : |3_orange|
ostream& operator<<(ostream& stream, const ValuedCard& valued_card);
ostream& operator<<(ostream& stream, const TacticCard& tactic_card);

#endif //SCHOTTEN_TOTTEN_CARD_H
