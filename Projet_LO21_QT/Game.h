
#ifndef SCHOTTEN_TOTTEN_GAME_H
#define SCHOTTEN_TOTTEN_GAME_H

#include <iostream>
#include <thread>
#include <chrono>
#include "Player.h"
#include "Border.h"
#include "Board.h"
#include "console.h"


class Game {
private:
    bool gameOver;
    unique_ptr<Player> player1_, player2_;
    Deck clanDeck, tacticDeck, discardDeck;
    DeckInfo deckInfo;
    unique_ptr<Board> board_;
    bool tacticVersion_{false};

public :
    Game(int argc, char *argv[]);
    int launchSchottenTotten1(int argc, char *argv[]);
    void setGameVersion();
    void create_board();
    void create_player(QString p1, QString p2);
    void create_deck();
    void start_game();
    void round();
    void roundAI();
    void playAI();
    void play(Player* player);
    void drawCard(Player* player);
    void pause(int n);
    bool isGameOver();

    void quit();
};
void clearScreen();

#endif //SCHOTTEN_TOTTEN_GAME_H
