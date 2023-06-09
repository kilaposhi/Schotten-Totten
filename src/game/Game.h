#ifndef SCHOTTEN_TOTTEN_GAME_H
#define SCHOTTEN_TOTTEN_GAME_H

#include <iostream>
#include <thread>
#include <chrono>
#include "player/Player.h"

class Player;
class Border;

class Game {
private:
    int player1ID;
    int player2ID;
    bool gameOver;

public:
    Game(Player* player1, Player* player2) : player1ID(player1->getId(player1)), player2ID(player2->getId(player2)) {}
    void create_game();
    void play(Player player1, Player player2);
    void pause();
    bool isGameOver();
};

#endif //SCHOTTEN_TOTTEN_GAME_H
