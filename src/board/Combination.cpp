#ifndef SCHOTTEN_TOTTEN_COMBINATION_H
#define SCHOTTEN_TOTTEN_COMBINATION_H

#include <algorithm>
#include "Combination.h"
#include "deck/Card.h"


Combination::Combination(int maxNumberCards) : maxNumberCards_(maxNumberCards) {
    valuedCards_.reserve(maxNumberCards_);
    tacticCards_.reserve(1);
}


Combination::Combination(Combination &&combination) :
        maxNumberCards_ {combination.maxNumberCards_},
        combinationType_{combination.combinationType_},
        hasTacticCard_{combination.hasTacticCard_},
        sumValues_{combination.sumValues_}
{
    this->valuedCards_ = std::move(combination.valuedCards_);
    this->tacticCards_= std::move(combination.tacticCards_);
}


Combination &Combination::operator=(Combination &&combination) {
    maxNumberCards_ =combination.maxNumberCards_;
    combinationType_=combination.combinationType_;
    hasTacticCard_=combination.hasTacticCard_;
    sumValues_=combination.sumValues_;
    this->valuedCards_ = std::move(combination.valuedCards_);
    this->tacticCards_= std::move(combination.tacticCards_);
    return *this;
}


int Combination::getSum() const {
    if (combinationType_ == CombinationType::NONE)
        throw CombinationException("Combination does not have a type yet, is not complete");
    return sumValues_;
}

CombinationType Combination::getType() const {
    if (combinationType_ == CombinationType::NONE)
        throw CombinationException("Combination does not have a type yet");
    return combinationType_;
}

int Combination::getNumberValuedCards() const {
    return valuedCards_.size() ;
}


int Combination::getNumberTacticCards() const {
    return tacticCards_.size() ;
}


int Combination::getNumberCards() const {
    return valuedCards_.size() + tacticCards_.size();
}


int Combination::getMaxNumberCards() const {
    return maxNumberCards_;
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
    if (valuedCards_.size() == maxNumberCards_)
        combinationType_ = compute_combination();
}


void Combination::push_back(unique_ptr<TacticCard> tacticCard) {
    if (getNumberCards() + 1 > maxNumberCards_)
        throw CombinationException("Can't add more cards than than 'maxNumberCards_'");
    if (!hasTacticCard_) hasTacticCard_ = true;
    tacticCards_.push_back(std::move(tacticCard));
}


void Combination::pop_card(std::unique_ptr<ValuedCard> valueCard) {
    auto it = std::find_if(valuedCards_.begin(), valuedCards_.end(),
                           [&valueCard](const std::unique_ptr<ValuedCard>& card) {
                               return card.get() == valueCard.get();
                           });

    if (it == valuedCards_.end()) {
        throw CombinationException("This card is not present in the combination ");
    } else {
        valuedCards_.erase(it);
    }
}


void Combination::pop_card(unique_ptr<TacticCard> tacticCard) {
    auto it = std::find_if(tacticCards_.begin(), tacticCards_.end(),
                           [&tacticCard](const std::unique_ptr<TacticCard>& card) {
                               return card.get() == tacticCard.get();
                           });

    if (it == tacticCards_.end()) {
        throw CombinationException("This card is not present in the combination ");
    } else {
        tacticCards_.erase(it);
    }
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
    int n  = getNumberValuedCards();
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


string Combination::print() const {
    std::stringstream combination;

    for (const auto& valuedCard : valuedCards_) {
        combination << valuedCard->print() << " ";
    }

    for (const auto& tacticCard : tacticCards_) {
        combination << tacticCard->print() << " ";
    }

    return combination.str();
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



#endif //SCHOTTEN_TOTTEN_COMBINATION_H
