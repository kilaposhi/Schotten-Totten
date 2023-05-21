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
    Card* tactic_slot;
    Card** player_1_combination;
    Card** player_2_combination;

public:
    Stone()=default;
    ~Stone()=default;
    Stone(const Stone& stone)=default;
    Stone& operator=(const Stone& stone) =default;

    void addCard() const;
    string compute_combination();

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
