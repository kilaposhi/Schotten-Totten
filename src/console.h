#ifndef SCHOTTEN_TOTTEN_CONSOLE_H
#define SCHOTTEN_TOTTEN_CONSOLE_H

#include <string>
#include <random>
#include "player/Player.h"


int random(int min, int max);
int askPlayerValue(Player* player, std::array<int,2> rangeValue);
int askValue(std::array<int,2> rangeValue);
bool askYesNo( const string& question);
CardColor askPlayerColor(Player* player, int numberColors);


#endif //SCHOTTEN_TOTTEN_CONSOLE_H
