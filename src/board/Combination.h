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
    std::vector<ValuedCard> cards;
    unsigned int sumValues;
    CombinationType type = CombinationType::Sum; // Définir une valeur par défaut
    unsigned int max_cards;
public:
    Combination(int n);
    int getSum() const;
    int size() const;
    CombinationType getType() const;
    void push_back(const ValuedCard &card);

    bool ColorRun(int n);
    bool Color(int n);
    bool ThreeOfAKind(int n);
    bool Run(int n);
    unsigned int getMax() const;

    bool operator<(const Combination& other) const; // Déclaration de l'opérateur <
    CombinationType compute_combination() const;

};

bool operator<(CombinationType left, CombinationType right);

class CombinationException {
private:
    std::string exception; // Utiliser le type std::string
public:
    CombinationException(std::string Exception) : exception(Exception) {}
    CombinationType getType() const;
    std::string what() const { return exception; }
};

#endif // PROJET_COMBINATION_H

