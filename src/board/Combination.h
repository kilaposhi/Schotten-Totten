#ifndef PROJET_COMBINATION_H
#define PROJET_COMBINATION_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>

#include "deck/Card.h"
#include "player/Player.h"
enum class CombinationType {
    NONE,
    ColorRun,
    Run,
    Color,
    ThreeOfAKind,
    Sum
};

class Combination {
public:
    Combination(int maxNumberCards);
    Combination(const Combination&) = default;
    Combination& operator=(const Combination&) = delete;
    ~Combination() = default;

public:
    int getSum() const;
    CombinationType getType() const;
    int getNumberCards() const;
    int getMaxNumberCards() const;
    void push_back(unique_ptr<ValuedCard> valuedCard);
    void pop_card(unique_ptr<ValuedCard> valuedCard);
    void push_back(unique_ptr<TacticCard> tacticCard);
    void pop_card(unique_ptr<TacticCard> tacticCard);
    void treatTacticCards();
    string print() const;

private:
    std::vector<unique_ptr<ValuedCard>> valuedCards_;
    std::vector<unique_ptr<TacticCard>> tacticCards_;
    bool hasTacticCard_{false};
    int maxNumberCards_{0};
    int sumValues_{0};
    CombinationType combinationType_{CombinationType::NONE};

private:
    void setMaxNumberCards(int maxNumberCards);
    CombinationType compute_combination();
    bool isColorRun();
    bool isThreeOfAKind();
    bool isRun();
    bool isColor();
};

ostream& operator<<(ostream& stream, const Border& Border);

class CombinationException : public std::exception {
private:
    string exception;
public:
    CombinationException(string Exception) : exception(Exception){}
    const char* what() const noexcept override { return exception.c_str();}
};

ostream& operator<<(ostream& stream, const Combination& combination);
const Combination& bestCombination(const Combination& combo1, const Combination& combo2) ;
string combinationTypeToString(CombinationType type) ;
#endif //PROJET_COMBINATION_H


