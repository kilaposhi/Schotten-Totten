#ifndef PROJET_COMBINATION_H
#define PROJET_COMBINATION_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "deck/Card.h"
#include "player/Player.h"
enum class CombinationType {
    ColorRun,
    Run,
    Color,
    ThreeOfAKind,
    Sum
};

class Combination {
private:
    std::vector<Card> cards;
    int sumValues;
    CombinationType type = NULL;

public:
    int getSum() const;
    CombinationType getType() const;
    void push_back(const ValuedCard &card);
    CombinationType compute_combination() const;
    bool ColorRun(int n );
    bool ThreeOfAKind(int n);
    bool Run(int n);
    friend class Border;
};

class CombinationException{
private:
    string exception;
public:
    CombinationException(string Exception) : exception(Exception){}
    CombinationType getType() const;
    string what() const { return exception;}

};
#endif //PROJET_COMBINATION_H






