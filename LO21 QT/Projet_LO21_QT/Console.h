#ifndef CONSOLE_H
#define CONSOLE_H


#include <string>
#include "Player.h"


int askPlayerValue(Player* player, std::array<int,2> rangeValue);
int askValue(std::array<int,2> rangeValue);
bool askYesNo( const string& question);
CardColor askPlayerColor(Player* player, int numberColors);


#endif // CONSOLE_H
