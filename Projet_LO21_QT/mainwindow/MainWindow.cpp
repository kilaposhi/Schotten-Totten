#include "MainWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QGridLayout>
#include <QThread>

MainWindow::MainWindow(QWidget *parent, Player* player1, Player* player2, Deck* clanDeck, Deck* tacticDeck, Board* board, Game* game)
    :QWidget(parent), player1(player1), player2(player2), clanDeck(clanDeck), tacticDeck(tacticDeck), board(board), game(game)
{

    QMessageBox::information(nullptr, "Round Start", "The round is starting.");
    handVP1 = new HandView(this, player1);
    handVP2 = new HandView(this, player2);
    actualHand = handVP2;
    actualPlayer = player2;

    tacticDeckV = new TacticDeckView(this, tacticDeck);
    clanDeckV = new ClanDeckView(this, clanDeck);
    boardV = new BoardView(this, board);

    QHBoxLayout* decks = new QHBoxLayout;
    decks->addWidget(clanDeckV);
    decks->addWidget(tacticDeckV);
    tacticDeckV->setVisible(game->getVersion());
    /*if (game->getVersion()) {
        decks->addWidget(tacticDeckV);
    }*/

    window = new QGridLayout;
    window->addWidget(boardV, 0, 0);
    window->addLayout(decks, 1, 0);
    window->addWidget(actualHand, 2, 0);

    setLayout(window);
    newTurn();
    window->update();
}


void MainWindow::newTurn(){
    //disconnect(actualHand, &HandView::cardSelected, this, &MainWindow::handleCardSelected);
    actualHand->setVisible(false);
    if (actualPlayer == player1) {
        actualPlayer = player2;
        otherPlayer = player1;
        actualHand = handVP2;
        //connect(handVP2, &HandView::cardSelected, this, &MainWindow::handleCardSelected);
    }
    else {
        actualPlayer = player1;
        otherPlayer = player2;
        actualHand = handVP1;
        //connect(handVP1, &HandView::cardSelected, this, &MainWindow::handleCardSelected);
    }
    //connect(actualHand, &HandView::cardSelected, this, &MainWindow::handleCardSelected);

    QString turn1 =  QString::fromStdString(actualPlayer->getName()) + " it's your turn ! \n" +  QString::fromStdString(otherPlayer->getName())+ " don't look at the screen!\n";
    QMessageBox *endTurn = new QMessageBox;
    endTurn->setText(turn1);
    disconnect(endTurn, &QMessageBox::accepted, this, &MainWindow::handleEndTurn);
    actualHand->setVisible(false);


    connect(endTurn, &QMessageBox::accepted, this, &MainWindow::handleEndTurn);
    endTurn->exec();//les cartes de la main du joueur sont cliquables
}


void MainWindow::handleEndTurn() {
    disconnect(actualHand, &HandView::cardSelected, this, &MainWindow::handleCardSelected);

    state = 1;//moment de jouer

    actualHand = new HandView(this, actualPlayer);
    actualHand->setVisible(true);
    window->addWidget(actualHand, 2, 0);
    window->update();


    for (CardView* cardV : actualHand->getHandList()) {
        cardV->setEnabled(true);
    }
    connect(actualHand, &HandView::cardSelected, this, &MainWindow::handleCardSelected);



    /*for (CardView* cardV : otherHand->getHandList()) {
        cardV->setEnabled(false);
    }*/
    window->update();
    //essaye de faire un addCardInto Hand alors que la main est déjà full

}

void MainWindow::handleCardSelected(int index){
    qDebug() << "dans handleCardSelected";
    disconnect(actualHand, &HandView::cardSelected, this, &MainWindow::handleCardSelected);

    handIndex = index;

    connect(boardV, &BoardView::borderChoice, this, &MainWindow::handleBorderSelected);
    for (BorderView* borderV : boardV->getBordersV()) {
        if (borderV->getBorder()->getPlayerCombination(actualPlayer).getNumberCards() < borderV->getBorder()->getPlayerCombination(actualPlayer).getMaxNumberCards()) {
            borderV->getBorderButton()->setEnabled(true);
        }
    }
}

void MainWindow::handleBorderSelected(int index) {

    if (state==1) {//choisit la border où poser la carte
        actualPlayer->play_card(handIndex, index, board);
        delete actualHand;
        actualHand = new HandView(this, actualPlayer);
        window->addWidget(actualHand, 2, 0);
        window->update();

        disconnect(boardV, &BoardView::borderChoice, this, &MainWindow::handleBorderSelected);
        delete boardV;
        boardV = new BoardView(this, board);
        window->addWidget(boardV, 0, 0);
        window->update();


        askClaim();

    }
    else {//choisit une board à claim
        //claim
        askClaim();
    }

}

void MainWindow::handleTacticDeckClicked() {
    clanDeckV->setEnabled(false);
    tacticDeckV->setEnabled(false);

    if (actualPlayer->getNumber_of_cards() < 6) {
        actualPlayer->draw_card(*tacticDeck);

        delete actualHand;
        actualHand = new HandView(this, actualPlayer);
        window->addWidget(actualHand, 2, 0);
        window->update();
    }

    if (game->isGameOver()) {
        QString over = "Game over: " + QString::fromStdString(actualPlayer->getName()) + " won!";
        QMessageBox::information(this, "Game Over", over);
    } else {
        newTurn();
    }
}

void MainWindow::handleClanDeckClicked() {
    clanDeckV->setEnabled(false);
    tacticDeckV->setEnabled(false);

    if (actualPlayer->getNumber_of_cards() < 6) {
        actualPlayer->draw_card(*clanDeck);

        delete actualHand;
        actualHand = new HandView(this, actualPlayer);
        window->addWidget(actualHand, 2, 0);
        window->update();
    }

    if (game->isGameOver()) {
        QString over = "Game over: " + QString::fromStdString(actualPlayer->getName()) + " won!";
        QMessageBox::information(this, "Game Over", over);
    } else {
        newTurn();
    }
}


void MainWindow::askClaim() {
    int response = QMessageBox::question(this, "Claim", "Do you want to claim a border ?", QMessageBox::Yes | QMessageBox::No);
    disconnect(tacticDeckV, &TacticDeckView::clicked, this, &MainWindow::handleTacticDeckClicked);
    disconnect(clanDeckV, &ClanDeckView::clicked, this, &MainWindow::handleClanDeckClicked);


    if (response == QMessageBox::Yes) {
        state = 2;
        connect(boardV, &BoardView::borderChoice, this, &MainWindow::handleBorderSelected);
        for (BorderView* borderV : boardV->getBordersV()) {
            borderV->getBorderButton()->setEnabled(true);
        }
        //renvoie à handleBorderSelected()
    }
    else {
        connect(tacticDeckV, &TacticDeckView::clicked, this, &MainWindow::handleTacticDeckClicked);
        connect(clanDeckV, &ClanDeckView::clicked, this, &MainWindow::handleClanDeckClicked);

        tacticDeckV->setEnabled(true);
        clanDeckV->setEnabled(true);
    }
}




void MainWindow::updateUI() {
    handVP1->updateHV();
    handVP2->updateHV();
    boardV->updateBV();
    window->update();
}
