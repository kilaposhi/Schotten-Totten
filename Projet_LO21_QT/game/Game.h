#ifndef GAME_H
#define GAME_H

#include "border/Border.h"
#include "board/Board.h"
#include "deck/Deck.h"
#include "hand/TacticHandler.h"
#include "deck/DeckFactory.h"
#include "board/Board.h"

#include <QString>

class Player;
class Game {
private:
    bool gameOver;
    unique_ptr<Player> player1_, player2_;
    Deck clanDeck, tacticDeck, discardDeck;
    DeckInfo deckInfo;
    unique_ptr<Board> board_;
    bool tacticVersion_{false};
    bool expertVersion_{false};

public :
    bool getVersion() const;

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
    void clearScreen();
    bool isGameOver();

    void quit();
};
void clearScreen();



#endif // GAME_H
