#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "player/Player.h"
#include "board/Board.h"
#include "deck/Deck.h"
#include "board/BoardView.h"
#include "deck/DeckView.h"
#include "game/Game.h"
#include "hand/HandView.h"
#include "deck/DeckView.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent, Player* player1, Player* player2, Deck* clanDeck, Deck* tacticDeck, Board* board, Game* game);
    void updateUI();
    void newTurn();

private slots :
    void handleEndTurn();
    void handleCardSelected(int index);
    void handleBorderSelected(int index);
    void handleTacticDeckClicked();
    void handleClanDeckClicked();
    void askClaim();

signals :
    //void hasThrown();

private :
    Player* player1;
    Player* player2;
    Deck* clanDeck;
    Deck* tacticDeck;
    Board* board;
    Game* game;

//    Player* player1_;
//    Player* player2_;
//    Deck* clanDeck_;
//    Deck* tacticDeck_;
//    BoardView* boardV;

    TacticDeckView* tacticDeckV;
    ClanDeckView* clanDeckV;

    HandView* handVP1 = nullptr;
    HandView* handVP2 = nullptr;
    HandView* actualHand;
//    HandView* otherHand;

    BoardView* boardV;
    QGridLayout* window;

    Player* actualPlayer;
    Player* otherPlayer;

    int handIndex;
    int borderIndex;
    int state; // gère si on est au moment de jouer ou de claim


};

#endif // MAINWINDOW_H
