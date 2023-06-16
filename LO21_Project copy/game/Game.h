#ifndef SCHOTTEN_TOTTEN_GAME_H
#define SCHOTTEN_TOTTEN_GAME_H

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
//#include <process>


#include "deck/DeckFactory.h"
#include "player/Player.h"
#include "board/Border.h"
#include "board/Board.h"
#include "console/console.h"
#include "board/GameTracker.h"


class Game {
private:
    bool gameOver;
    unique_ptr<Player> player1_, player2_;
    Deck clanDeck, tacticDeck, discardDeck;
    DeckInfo deckInfo;
    unique_ptr<Board> board_;
    bool tacticVersion_{false};
    bool basic_ ;
    bool expert_;

public :
    Game();
    void launchSchottenTotten1();
    void setGameVersion();
    void create_board();
    void create_player(int id);
    void create_AI();
    void create_deck();
    void start_game();
    void round();
    void roundAI();
    void playAI(AI * computer);
    void playAIBasic(Player* computer);
    void play(Player* player);
    void drawCard(Player* player);
    void pause(int n);
    void quit();
    void gameAIvsAI();
};
void clearScreen();

#endif //SCHOTTEN_TOTTEN_GAME_H

