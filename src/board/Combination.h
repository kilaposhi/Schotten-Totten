#ifndef PROJET_COMBINATION_H
#define PROJET_COMBINATION_H

#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>

#include "deck/Card.h"

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
    explicit Combination(int maxNumberCards);
    ~Combination() = default;
    Combination(const Combination&) = delete;
    Combination& operator=(const Combination&) = delete;
    Combination(Combination&& combination);
    Combination& operator=(Combination&& combination);

public:
    [[nodiscard]] int getSum() const;
    [[nodiscard]] CombinationType getType() const;
    [[nodiscard]] int getNumberCards() const;
    [[nodiscard]] int getMaxNumberCards() const;
    void push_back(unique_ptr<ValuedCard> valuedCard);
    void pop_card(unique_ptr<ValuedCard> valuedCard);
    void push_back(unique_ptr<TacticCard> tacticCard);
    void pop_card(unique_ptr<TacticCard> tacticCard);
    void treatTacticCards();
    [[nodiscard]] string print() const;

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

// ostream& operator<<(ostream& stream, const Border& Border);

class CombinationException: public std::exception{
private:
    std::string message;
public:
    explicit CombinationException(string  errorMessage)
            : message(std::move(errorMessage)) {}

    [[nodiscard]]const char* what() const noexcept override {
        return message.c_str();
    }

};
ostream& operator<<(ostream& stream, const Combination& combination);
const Combination& bestCombination(const Combination& combo1, const Combination& combo2) ;
string combinationTypeToString(CombinationType type) ;
#endif //PROJET_COMBINATION_H
