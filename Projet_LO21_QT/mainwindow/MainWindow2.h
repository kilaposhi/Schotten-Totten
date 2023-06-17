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

class MainWindow2 : public QWidget {
    Q_OBJECT

public:
    MainWindow2(QWidget *parent, Player* player1, Player* player2, Deck* clanDeck, Deck* tacticDeck, Board* board, Game* game);
    void updateUI();
    void newTurn();

private slots :
    void handleEndTurn();
    void handleCardSelected1(int index);
    void handleCardSelected2(int index);
    void handleBorderSelected(int index);
    void handleTacticDeckClicked();
    void handleClanDeckClicked();
    void askClaim();

signals :
         //void hasThrown();

private :
    Game* game_;
    /*Player* player1_;
    Player* player2_;
    Deck* clanDeck_;
    Deck* tacticDeck_;*/
    //BoardView* boardV;
    TacticDeckView* tacticDeckV;
    ClanDeckView* clanDeckV;
    HandView* handVP1 = nullptr;
    HandView* handVP2 = nullptr;
    HandView* actualHand;
    //HandView* otherHand;
    BoardView* boardV;
    QGridLayout* window;

    Player* player1;
    Player* player2;
    Board* board;
    Deck* tacticDeck;
    Deck* clanDeck;

    Player* actualPlayer;
    Player* otherPlayer;

    int handIndex;
    int borderIndex;
    int state; // gère si on est au moment de jouer ou de claim


};

#endif // MAINWINDOW_H
