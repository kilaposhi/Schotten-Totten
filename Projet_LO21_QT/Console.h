#ifndef SCHOTTEN_TOTTEN_CONSOLE_H
#define SCHOTTEN_TOTTEN_CONSOLE_H

#include <string>
#include "Player.h"
#include "DeckFactory.h"
#include <QDialog>


int askPlayerValue(Player* player, std::array<int,2> rangeValue);
int chooseGameMode();
int chooseNumberRound();
int askValue(const std::array<int, 2>& rangeValue);
bool askYesNo(const string& question);
CardColor askPlayerColor(Player* player, int numberColors);


#endif //SCHOTTEN_TOTTEN_CONSOLE_H
