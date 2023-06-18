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
    virtual bool isRuse() { return false; };
    [[nodiscard]] virtual string str() const = 0;
};


enum class CardColor{
    red,
    green,
    blue,
    yellow,
    purple,
    orange,
    brown,
    End
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
    [[nodiscard]] CardColor getColor() const;
    [[nodiscard]] int getValue() const;
    [[nodiscard]] string str() const override;
private:
    CardColor color_;
    int value_{};
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
    traitor
};

class TacticCard : public Card {
public :
    explicit TacticCard(TacticType type);
    TacticCard(unique_ptr<Card> tacticCard);
    TacticCard(const TacticCard&) = default;
    TacticCard& operator=(const TacticCard&) = default;
    [[nodiscard]] TacticType getName() const;
    [[nodiscard]] string getDescription() const;
    bool isRuse() override;
    [[nodiscard]] string str() const override;
private :
    TacticType name;
    string description;
};

string tacticTypeToString(TacticType type) ;
string createTacticDescription(TacticType type);

bool operator<(const ValuedCard& leftCard, const ValuedCard& rightCard);
bool operator>(const ValuedCard& leftCard, const ValuedCard& rightCard);
bool operator<=(const ValuedCard& leftCard, const ValuedCard& rightCard);
bool operator>=(const ValuedCard& leftCard, const ValuedCard& rightCard);
bool operator==(const ValuedCard& leftCard, const ValuedCard& rightCard);
bool operator!=(const ValuedCard& leftCard, const ValuedCard& rightCard);

bool operator==(const TacticCard& leftCard, const TacticCard& rightCard);
bool operator!=(const TacticCard& leftCard, const TacticCard& rightCard);
ostream& operator<<(ostream& stream, const Card& Card);
// cout << Valued_Card;    Example : |3_orange|
ostream& operator<<(ostream& stream, const ValuedCard& valued_card);
ostream& operator<<(ostream& stream, const TacticCard& tactic_card);

#endif //SCHOTTEN_TOTTEN_CARD_H
