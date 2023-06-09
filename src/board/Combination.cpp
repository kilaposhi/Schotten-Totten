#ifndef SCHOTTEN_TOTTEN_COMBINATION_H
#define SCHOTTEN_TOTTEN_COMBINATION_H

#include "Combination.h"
#include "deck/Card.h"

Combination::Combination(int maxNumberCards) : maxNumberCards_(maxNumberCards) {
    valuedCards_.reserve(maxNumberCards_);
    tacticCards_.reserve(1);
}

int Combination::getSum() const {
    if (combinationType_== CombinationType::NONE)
        throw CombinationException("Combination does not have a type yet, is not complete");
    return sumValues_;
}

CombinationType Combination::getType() const {
    if (combinationType_ == CombinationType::NONE)
        throw CombinationException("Combination does not have a type yet");
    return combinationType_;
}

int Combination::getNumberCards() const {
    return valuedCards_.size() + tacticCards_.size();
}

ValuedCard* Combination::getValuedCard(int index) const {
    if (index < 0 || index >= valuedCards_.size()) {
        throw CombinationException("Index out of range");
    }
    return valuedCards_[index].get();
}
TacticCard* Combination::getTacticCard(int index) const {
    if (index < 0 || index >= tacticCards_.size()) {
        throw CombinationException("Index out of range");
    }
    return tacticCards_[index].get();
}

int Combination::getNumberValuedCards() const {
    return valuedCards_.size() ;
}
int Combination::getNumberTacticCards() const {
    return tacticCards_.size() ;
}

int Combination::getMaxNumberCards() const {
    return maxNumberCards_;
}

void Combination::setMaxNumberCards(int maxNumberCards) {
    if (maxNumberCards <= maxNumberCards_)
        throw CombinationException("Can't set maxNumberCards of 'Combination' to a number `<=` than it already is");
    maxNumberCards_ = maxNumberCards;
}

void Combination::push_back(unique_ptr<ValuedCard> valuedCard) {
    if (getNumberCards() + 1 > maxNumberCards_)
        throw CombinationException("Can't add more cards than than 'maxNumberCards_'");
    sumValues_ += valuedCard->getValue();
    valuedCards_.push_back(std::move(valuedCard));
    /*if (valuedCards_.size() == maxNumberCards_)
        combinationType_ = compute_combination();*/
}

void Combination::push_back(unique_ptr<TacticCard> tacticCard) {
    if (getNumberCards() + 1 > maxNumberCards_)
        throw CombinationException("Can't add more cards than than 'maxNumberCards_'");
    if (!hasTacticCard_) hasTacticCard_ = true;
    tacticCards_.push_back(std::move(tacticCard));
}

void Combination::treatTacticCards() {
    for (const auto& tacticCard : tacticCards_){
//        push_back(std::make_unique<ValuedCard>())
    }
    hasTacticCard_ = false;
    combinationType_ = compute_combination();
}

 CombinationType Combination::compute_combination(){
    if (hasTacticCard_)
        throw CombinationException("Need to treat the tactic cards before computing the combination");
    int n = valuedCards_.size();
    if (n < maxNumberCards_)
    {
        throw CombinationException("There is not enough cards to claim the stone");
    }
    else
    if (isColorRun()) return CombinationType::ColorRun ;
    else if (isColor()) return CombinationType::Color;
    else if (isThreeOfAKind()) return CombinationType::ThreeOfAKind;
    else if (isRun()) return CombinationType::Run;
    else return CombinationType::Sum;
}

bool Combination::isColorRun() {

    if (isColor() && isRun())
        return true;
    return false;
}

bool Combination::isColor(){
    std::vector<int> ColorCount(static_cast<int>(CardColor::End), 0);
    unsigned int n = valuedCards_.size();
    bool color = false;
    int i = 0;
    while (i < n  && !color)
    {
        if (++ColorCount[static_cast<int>(valuedCards_[i]->getColor())] == 3) color = true;
        i++;
    }
    return color;
}

bool Combination::isThreeOfAKind(){
    int n = valuedCards_.size();
    std::sort(valuedCards_.begin(), valuedCards_.end(),
              [](const std::unique_ptr<ValuedCard>& a, const std::unique_ptr<ValuedCard>& b) {
                  return a->getValue() < b->getValue();
              });

    bool three = false;
    int i = 0;
    int count = 1;
    while (i < n - 1 && !three)
    {
        if (valuedCards_[i]->getValue() == valuedCards_[i + 1]->getValue()) {
            count++;
            if (count == 3) {
                three = true;
                std::cout << "brelan";
            }
        } else {
            count = 1; // Reset count for a new value
        }
        i++;
    }
    return three;
}



bool Combination::isRun(){
    int n = valuedCards_.size();
    std::sort(valuedCards_.begin(), valuedCards_.end(),
              [](const std::unique_ptr<ValuedCard>& a, const std::unique_ptr<ValuedCard>& b) {
                  return a->getValue() < b->getValue();
              });
    bool run = false;
    unsigned int consecutiveCount = 1;
    int i = 0;
    while (i < n - 1 && !run)
    {
        if (valuedCards_[i]->getValue() == valuedCards_[i + 1]->getValue() - 1) {
            consecutiveCount++;
        } else {
            consecutiveCount = 1; // reset count if cards are not consecutive
        }
        if (consecutiveCount == 3) run = true;
        i++;
    }
    return run;
}

ostream& operator<<(ostream& stream, const Combination& combination)
{
    unsigned int n = combination.getNumberValuedCards();

    for (unsigned int i = 0; i <n; i++)
    {
        std::cout<< *(combination.getValuedCard(i));
    }
    unsigned int m = combination.getNumberTacticCards();
    for (unsigned int i = 0; i <m; i++)
    {
        std::cout<< *(combination.getTacticCard(i));
    }
    return stream;
}

string combinationTypeToString(CombinationType type) {
    switch (type) {
        case CombinationType::ColorRun: return "Color run";
        case CombinationType::Color : return "Color";
        case CombinationType::Run : return "Run";
        case CombinationType::ThreeOfAKind : return "Three of a kind";
        case CombinationType::Sum : return "Sum";
        case CombinationType::NONE : return "NONE";
        default:
            throw CombinationException("Trying to convert unknown combination type to string");
    }
}
int Combination::getRank() const {
    switch (combinationType_) {
        case CombinationType::NONE:
            return 0;
        case CombinationType::Sum:
            return 1;
        case CombinationType::ThreeOfAKind:
            return 2;
        case CombinationType::Color:
            return 3;
        case CombinationType::Run:
            return 4;
        case CombinationType::ColorRun:
            return 5;
        default:
            throw CombinationException("Invalid combination type");
    }
}
const Combination& bestCombination(const Combination& combo1, const Combination& combo2) {
    if (combo1.getRank() < combo2.getRank()) {
        return combo2;
    }
    else if (combo1.getRank() > combo2.getRank()) {
        return combo1;
    }
    else {
        return (combo1.getSum() > combo2.getSum()) ? combo1 : combo2;
    }
}


#endif //SCHOTTEN_TOTTEN_COMBINATION_H
