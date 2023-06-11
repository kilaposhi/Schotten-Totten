#ifndef SCHOTTEN_TOTTEN_CONSOLE_H
#define SCHOTTEN_TOTTEN_CONSOLE_H

#include "player/Player.h"
#include "deck/DeckFactory.h"


int askPlayerValue(Player* player, std::array<int,2> rangeValue);
int askValue(std::array<int,2> rangeValue);
CardColor askPlayerColor(Player* player, int numberColors);


#endif //SCHOTTEN_TOTTEN_CONSOLE_H
