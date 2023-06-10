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
    // int n = valuedCards_.size(); pas besoin de cette ligne
    if (isColor() && isRun())
        return true;
    return false;
}

bool Combination::isColor(){
    int n = valuedCards_.size();
    bool color = true;
    int i = 0;
    while (i < n - 1 && color)
    {
        if (color == (valuedCards_[i]->getColor() != valuedCards_[i + 1]->getColor())) color = false;
        i++;
    }
    return color;
}

bool Combination::isThreeOfAKind(){
    int n = valuedCards_.size();
    bool three = true;
    int i = 0;
    while (i < n - 1 && three)
    {
        if (valuedCards_[i]->getValue() != valuedCards_[i + 1]->getValue()) three = false;
        i++;
    }
    return three;
}

bool Combination::isRun(){
    int n = valuedCards_.size();
    std::sort(valuedCards_.begin(), valuedCards_.end());
    bool run = true;
    int i = 0;
    while (i < n - 1 && run)
    {
        if (valuedCards_[i]->getValue() != valuedCards_[i + 1]->getValue() - 1) run = false;
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

ostream& operator<<(ostream& stream, const Combination& Combination){
    stream << Combination.print();
    return stream;
}

#endif //SCHOTTEN_TOTTEN_COMBINATION_H
