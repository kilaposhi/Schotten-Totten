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
    int version;

public :
    [[noreturn]] Game();
    Board create_board();
    void create_player1();
    void create_player2();
    void create_deck();
    void start_game();
    void round(Player player1, Player player2, Board board);
    void play(Board board);
    void pause(int n);
    bool isGameOver();

    void quit();
};

#endif //SCHOTTEN_TOTTEN_GAME_H

