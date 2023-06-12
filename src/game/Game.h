#ifndef SCHOTTEN_TOTTEN_GAME_H
#define SCHOTTEN_TOTTEN_GAME_H

#include <iostream>
#include <thread>
#include <chrono>
#include "player/Player.h"
#include "board/Border.h"
#include "board/Board.h"


class Game {
private:
    Player* player1;
    Player* player2;
    bool gameOver;
    Deck clanDeck, tacticDeck, discardDeck;
    unique_ptr<Board> board;
    bool tacticVersion_{false};

public :
    Game();
    void launchSchottenTotten1();
    void setGameVersion();
    void startGame();
    void round(Player player1, Player player2, Board board);
    void play(Board board);
    void pause(int n);
    bool isGameOver();

    void quit();
};

#endif //SCHOTTEN_TOTTEN_GAME_H

