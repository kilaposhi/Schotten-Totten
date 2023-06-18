#ifndef SCHOTTEN_TOTTEN_GAME_H
#define SCHOTTEN_TOTTEN_GAME_H

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <process.h>

#include "deck/DeckFactory.h"
#include "player/Player.h"
#include "board/Border.h"
#include "board/Board.h"
#include "console.h"
#include "board/GameTracker.h"
class GameTracker;
class Player;
class AI;

class Game {
private:
    bool gameOver= true;
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
    void create_deck();
    void round();
    void play(Player* player);
    size_t chooseBorder(const string& text, Player* player);
    void claim(Player* player);
    void draw_card(Player* player);
    void pause(int n);
    void quit();

    void roundAI();
    void playAI(AI* computer, Player* opponent, GameTracker& gameTracker);
    void create_AI(int id);
    void playAIBasic(AI* computer, Player* opponent, GameTracker& gameTracker);
    void gameAIvsAI();
    void clearScreen();
    bool GameOver(int nbRound);

};

void clearScreen();

#endif //SCHOTTEN_TOTTEN_GAME_H

