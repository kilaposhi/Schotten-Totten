#ifndef SCHOTTEN_TOTTEN_GAME_H
#define SCHOTTEN_TOTTEN_GAME_H

#include <iostream>
#include <thread>
#include <chrono>
#include "player/Player.h"
#include "board/Border.h"
#include "board/Board.h"

class Player;
class Border;

class Game {
private:
    int player1ID;
    int player2ID;
    bool gameOver;

public:
    Game(Player* player1, Player* player2);
    void create_game();
    void play(Player player1, Player player2, Board board);
    void play(Player player);
    void pause(int n);
    bool isGameOver();
};

#endif //SCHOTTEN_TOTTEN_GAME_H
