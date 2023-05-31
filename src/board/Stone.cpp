#include "Stone.h"

Combination Stone::compute_combination(Player player)
{
    combination = getCombination(player);
    n = size(combination);
    if (n<3)
    {
        throw CombinationException("There is not enough cards to claim the stone");
    }
    else
        if (Color(combination,n) && Run(combination,n) ) return Combination::ColorRun ;
        else if (Color(combination,n)) return Combination::Color;
        else if (ThreeOfAKind(combination,n)) return Combination::ThreeOfAKind;
        else if (Run(combination,n)) return Combination::Run;
        else return Combination::Sum;
}

bool Color(vector<Card*> combination, int n)
{
    bool color = true;
    int i = 0;
    while (i < n - 1 && color)
    {
        color = (combination[i]->getColor() == combination[i + 1]->getColor());
        i++;
    }
    return color;
}

bool ThreeOfAKind(vector<Card*> combination, int n)
{
    bool three = true;
    int i = 0;
    while (i < n - 1 && three)
    {
        combination[i]->getValue()== combination[i+1]->getValue();
        i++;
    }
    return three;
}

bool Run(vector<Card*> combination,int n)
{
    sort(combination.begin(), combination.end());
    run = true;
    int i = 0;
    while (i < n - 1 && run)
    {
        combination[i]->getValue()== combination[i+1]->getValue()-1;
        i++;
    }
    return run;
}
#ifndef SCHOTTEN_TOTTEN_STONE_H
#define SCHOTTEN_TOTTEN_STONE_H


#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "deck/Card.h"
#include "player/Player.h"

using std::string, std::exception, std::vector ;



class Stone {
private:
    bool claimed;
    Player* winner;
    unsigned int slot_number;
    vector<Card> cardSlotsAvailable;
    Card* tactic_slot; //une seule carte tactique peut etre posée par borne ? les 2 joueurs confondus
    vector<Card*> player_1_combination;
    vector<Card*> player_2_combination;
    Combination CombinaisonJoueur1;
    Combination CombinaisonJoueur2;
    Observer* observer;


public:
    Stone()=default;
    ~Stone()=default;
    Stone(const Stone& stone)=default;
    Stone& operator=(const Stone& stone) =default;
    int getNbStone() const;
    Card** getCombination(const Player player);
    void addCard() const;
    string compute_combination();
    observer->update();

};

class CombinationException{
private:
    string exception;
public:
    CombinationException(string Exception) : exception(Exception){}

    string what() const { return exception;}
};

enum class Combination {
    ColorRun,
    Run,
    Color,
    ThreeOfAKind,
    Sum
};


bool ColorRun(vector<Card*>,int n );

bool ThreeOfAKind(vector<Card*>,int n);

bool Run(vector<Card*>,int n);

#endif //SCHOTTEN_TOTTEN_STONE_H
