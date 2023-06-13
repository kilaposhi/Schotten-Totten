#ifndef SCHOTTEN_TOTTEN_GAME_H
#define SCHOTTEN_TOTTEN_GAME_H

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

#include "deck/DeckFactory.h"
#include "player/Player.h"
#include "board/Border.h"
#include "board/Board.h"
#include "console.h"
#include "board/GameTracker.h"


class Game {
private:
    bool gameOver;
    unique_ptr<Player> player1_, player2_;
    Deck clanDeck, tacticDeck, discardDeck;
    DeckInfo deckInfo;
    unique_ptr<Board> board_;
    bool tacticVersion_{false};

public :
    Game();
    void launchSchottenTotten1();
    void setGameVersion();
    void create_board();
    void create_player(int id);
    void create_deck();
    void start_game();
    void round();
    void play(Player* player);
    void drawCard(Player* player);
    void pause(int n);
    bool isGameOver();

    void quit();
};
void clearScreen();

#endif //SCHOTTEN_TOTTEN_GAME_H

