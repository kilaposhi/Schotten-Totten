#include "Combination.h"

#include <algorithm>


Combination::Combination(int maxNumberCards, Player* player) : player_(player), maxNumberCards_(maxNumberCards) {
    valuedCards_.reserve(maxNumberCards_);
    tacticCards_.reserve(1);
}
Combination::Combination(const Combination& other)
    : player_(other.player_),
    valuedCards_(other.valuedCards_.size()),
    tacticCards_(other.tacticCards_.size()),
    maxNumberCards_(other.maxNumberCards_),
    sumValues_(other.sumValues_),
    hasTacticCard_(other.hasTacticCard_),
    noCombinationRule_(other.noCombinationRule_),
    combinationType_(other.combinationType_)
{
    for (size_t i = 0; i < other.valuedCards_.size(); ++i) {
        valuedCards_[i] = std::make_unique<ValuedCard>(*other.valuedCards_[i]);
    }
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


Player *Combination::getPlayerID() const {
    return player_;
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

void Combination::setNoCombinationRule() {
    noCombinationRule_ = true;
}

void Combination::treatTacticCards() {
    while (!tacticCards_.empty()) {
        TacticHandler::getInstance().activeEliteTroop(std::move(tacticCards_.back()), this);
        tacticCards_.pop_back();
    }
    hasTacticCard_ = false;
    combinationType_ = compute_combination();
}


CombinationType Combination::compute_combination(){
    if (hasTacticCard_)
        treatTacticCards();
    if (noCombinationRule_)
        return CombinationType::Sum;
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


string Combination::str() const {
    std::stringstream stream("");
    //    stream << *player_  << " :";
    if (this->getNumberCards() == 0) {
        stream << "No cards !";
        return stream.str();
    }
    for (const auto& valuedCard : valuedCards_) {
        stream << valuedCard->str() << " ";
    }

    for (const auto& tacticCard : tacticCards_) {
        stream << tacticCard->str() << " ";
    }
    return stream.str();
}


ostream& operator<<(ostream& stream, const Combination& combination)
{
    stream << combination.str();
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
    if (combo1.getType() == CombinationType::NONE && combo2.getType() == CombinationType::NONE) {
        return combo1;
    }
    else if (combo1.getType() == CombinationType::NONE) {
        return combo2;
    }
    else if (combo2.getType() == CombinationType::NONE) {
        return combo1;
    }
    else if (combo1.getRank() < combo2.getRank()) {
        return combo2;
    }
    else if (combo1.getRank() > combo2.getRank()) {
        return combo1;
    }
    else {
        return (combo1.getSum() > combo2.getSum()) ? combo1 : combo2;
    }
}


bool Combination::operator==(const Combination& other) const {
    // Comparez les attributs des combinaisons pour déterminer si elles sont égales
    return (valuedCards_ == other.valuedCards_) ;
} //on ne les trie pas car on veut que les combinaisons soient identiques


int findBestCombination(const std::vector<Combination>& combinations) {
    if (combinations.empty()) {
        throw std::logic_error("The list of combinations is empty.");
    }

    const Combination* best = &combinations[0];
    unsigned int index = 0;
    for (size_t i = 1; i < combinations.size(); ++i) {
        const Combination& current = combinations[i];
        if (current == bestCombination(*best, current)) {
            best = &current;
            index = i;
        }
    }

    return index;
}
