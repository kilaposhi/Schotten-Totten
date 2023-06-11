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
    int player1ID;
    int player2ID;
    bool gameOver;
    int maxPlayerCard;
    unique_ptr<Player> player1, player2;
    Deck clanDeck, tacticDeck, discardDeck;
    DeckInfo deckInfo;
    unique_ptr<Board> board;
    bool tacticVersion_{false};

public :
    Game();
    void launchSchottenTotten1();
    void setGameVersion();
    Board create_board();
    void create_players();
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

