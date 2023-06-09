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
    bool hasTacticCard_{false};

public:
    int getSum() const;
    CombinationType getType() const;
    int getNumberCards() const;
    int getMaxNumberCards() const;
    int getNumberValuedCards() const;
    int getNumberTacticCards() const;
    void push_back(unique_ptr<ValuedCard> valuedCard);
    void push_back(unique_ptr<TacticCard> tacticCard);
    void treatTacticCards();
    ValuedCard* getValuedCard(int index) const;
    TacticCard* getTacticCard(int index) const;
private:
    std::vector<unique_ptr<ValuedCard>> valuedCards_;
    std::vector<unique_ptr<TacticCard>> tacticCards_;
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
    int getRank() const;
};

class CombinationException{
private:
    string exception;
public:
    CombinationException(string Exception) : exception(Exception){}
    string what() const { return exception;}

};
ostream& operator<<(ostream& stream, const Combination& combination);
const Combination& bestCombination(const Combination& combo1, const Combination& combo2) ;
string combinationTypeToString(CombinationType type) ;
#endif //PROJET_COMBINATION_H


