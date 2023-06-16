#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Player.h"
#include "Board.h"
#include "Deck.h"
#include "BoardView.h"
#include "DeckView.h"
#include "Game.h"
#include "HandView.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent, Player* player1, Player* player2, Deck* clanDeck, Deck* tacticDeck, Board* board, Game* game);
    void updateUI();

private slots :
    void handleEndTurn();
    void handleCardSelected(int index);
    void handleBorderSelected(int index);

signals :
    void layed();

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
    HandView* otherHand;
    BoardView* boardV;
    QVBoxLayout* window;
    Player* player1;
    Player* player2;
    Board* board;

    int handIndex;
    int borderIndex;


};

#endif // MAINWINDOW_H
