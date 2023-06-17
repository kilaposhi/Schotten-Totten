#ifndef SCHOTTEN_TOTTEN_GAME_H
#define SCHOTTEN_TOTTEN_GAME_H

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <process.h>

class Player;
class AI;

#include "deck/DeckFactory.h"
#include "player/Player.h"
#include "board/Border.h"
#include "board/Board.h"
#include "console.h"
#include "board/GameTracker.h"
class GameTracker;

class Game {
private:
    bool gameOver;
    std::unique_ptr<Player> player1_;
    std::unique_ptr<Player> player2_;
    Deck clanDeck, tacticDeck, discardDeck;
    DeckInfo deckInfo;
    std::unique_ptr<Board> board_;
    bool tacticVersion_{false};
    bool basic_;
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
    void playAI(AI* computer, Player* opponent, GameTracker& gameTracker);
    void playAIBasic(AI* computer, Player* opponent, GameTracker& gameTracker);
    void play(Player* player, Player* opponent, GameTracker& gameTracker);
    void draw_card(Player* player);
    void pause(int n);
    void quit();
    void gameAIvsAI();
    void clearScreen();
    GameTracker& createGameTracker();

};

void clearScreen();

#endif //SCHOTTEN_TOTTEN_GAME_H

