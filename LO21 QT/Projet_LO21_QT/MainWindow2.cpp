#include "MainWindow2.h"
#include "BoardView.h"
#include "HandView.h"
#include "DeckView.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "CardView.h"
#include <QMessageBox>
#include <QGridLayout>
#include "SignalMessageBox.h"
#include <QThread>

MainWindow2::MainWindow2(QWidget *parent, Player* player1, Player* player2, Deck* clanDeck, Deck* tacticDeck, Board* board, Game* game)
    :QWidget(parent), game_(game), player1(player1), player2(player2), board(board), tacticDeck(tacticDeck), clanDeck(clanDeck)
{

    QMessageBox::information(nullptr, "Round Start", "The round is starting.");
    handVP1 = new HandView(this, player1);
    handVP2 = new HandView(this, player2);
    //actualHand = handVP2;
    actualPlayer = player2;

    tacticDeckV = new TacticDeckView(this, tacticDeck);
    clanDeckV = new ClanDeckView(this, clanDeck);
    boardV = new BoardView(this, board);

    QHBoxLayout* decks = new QHBoxLayout;
    decks->addWidget(clanDeckV);
    if (game_->getVersion()) {
        decks->addWidget(tacticDeckV);
    }

    window = new QGridLayout;
    window->addWidget(boardV, 0, 0);
    window->addLayout(decks, 1, 0);
    window->addWidget(actualHand, 2, 0);

    setLayout(window);
    newTurn();

    //while (board->hasWinner() == nullptr) {
    /*QString turn1 =  QString::fromStdString(player1->getName()) + "it's your turn ! \n" +  QString::fromStdString(player2->getName())+ " don't look at the screen!\n";
        QMessageBox *endTurn = new QMessageBox;
        endTurn->setText(turn1);
        //endTurn->exec();
        connect(endTurn, &QMessageBox::accepted, this, &MainWindow::handleEndTurn);
        endTurn->exec();//les cartes de la main du joueur sont cliquables*/

    connect(handVP1, &HandView::cardSelected, this, &MainWindow2::handleCardSelected1);
    connect(handVP2, &HandView::cardSelected, this, &MainWindow2::handleCardSelected2);
    connect(boardV, &BoardView::borderChoice, this, &MainWindow2::handleBorderSelected);

    connect(tacticDeckV, &TacticDeckView::clicked, this, &MainWindow2::handleTacticDeckClicked);
    connect(clanDeckV, &ClanDeckView::clicked, this, &MainWindow2::handleClanDeckClicked);



    //player1->play_card(handIndex, borderIndex, board);
    window->update();

    /*
        play(player1_.get());
        pause(2);
        if (isGameOver()) {
            QString over = "Player " + QString::number(player1_->getID()) + " won!\n";
            QMessageBox::information(nullptr, "Game over", over);
            break;
        }
        QString turn2 =  QString::fromStdString(player1_->getName()) + "it's your turn ! \n" +  QString::fromStdString(player2_->getName())+ " don't look at the screen!\n";
        MyMessageBox messageBox2(nullptr, 2);
        messageBox2.setText(turn2);
        messageBox2.exec();
        play(player2_.get());
        if (isGameOver()) {
            QString over = "Player " + QString::number(player2_->getID()) + " won!\n";
            QMessageBox::information(nullptr, "Game over", over);
            break;
        }
        pause(15);
*/


    //window->update();

    //boardV = new BoardView(this, board);




    //}
}


void MainWindow2::handleEndTurn() {
    state = 1;//moment de jouer

    qDebug() << "dans handleEndTurn";

    delete actualHand;
    actualHand = new HandView(this, actualPlayer);
    window->addWidget(actualHand, 2, 0);
    window->update();

    for (CardView* cardV : actualHand->getHandList()) {
        cardV->setEnabled(true);
    }
    /*for (CardView* cardV : otherHand->getHandList()) {
        cardV->setEnabled(false);
    }*/
    window->update();
}

void MainWindow2::handleCardSelected1(int index){
    qDebug() << "dans handleCardSelected";
    handIndex = index;
    for (BorderView* borderV : boardV->getBordersV()) {
        borderV->getBorderButton()->setEnabled(true);
    }
}

void MainWindow2::handleCardSelected2(int index){
    qDebug() << "dans handleCardSelected";
    handIndex = index;
    for (BorderView* borderV : boardV->getBordersV()) {
        borderV->getBorderButton()->setEnabled(true);
    }
}

void MainWindow2::handleBorderSelected(int index) {

    if (state==1) {//choisit la border où poser la carte
        actualPlayer->play_card(handIndex, index, board);
        delete actualHand;
        actualHand = new HandView(this, actualPlayer);
        window->addWidget(actualHand, 2, 0);
        window->update();

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

void MainWindow2::handleTacticDeckClicked(){
    clanDeckV->setEnabled(false);
    tacticDeckV->setEnabled(false);

    actualPlayer->draw_card(*tacticDeck);

    delete actualHand;
    actualHand = new HandView(this, actualPlayer);
    window->addWidget(actualHand, 2, 0);
    window->update();

    if (game_->isGameOver()) {
        QString over = "Game over :" + QString::fromStdString(actualPlayer->getName()) + " won !";
        QMessageBox::information(this, "Game Over", over);
    }
    else {
        newTurn();
    }

}

void MainWindow2::handleClanDeckClicked(){
    clanDeckV->setEnabled(false);
    tacticDeckV->setEnabled(false);
    actualPlayer->draw_card(*clanDeck);

    delete actualHand;
    actualHand = new HandView(this, actualPlayer);
    window->addWidget(actualHand, 2,0);
    window->update();

    if (game_->isGameOver()) {
        QString over = "Game over :" + QString::fromStdString(actualPlayer->getName()) + " won !";
        QMessageBox::information(this, "Game Over", over);
    }
    else {
        newTurn();
    }

}

void MainWindow2::askClaim() {
    int response = QMessageBox::question(this, "Claim", "Do you want to claim a border ?", QMessageBox::Yes | QMessageBox::No);

    if (response == QMessageBox::Yes) {
        state = 2;
        for (BorderView* borderV : boardV->getBordersV()) {
            borderV->getBorderButton()->setEnabled(true);
        }
        //renvoie à handleBorderSelected()
    }
    else {
        tacticDeckV->setEnabled(true);
        clanDeckV->setEnabled(true);
    }
}

void MainWindow2::newTurn(Player* player){

    QString turn1 =  QString::fromStdString(player->getName()) + "it's your turn ! \n";// +  QString::fromStdString(otherPlayer->getName())+ " don't look at the screen!\n";
    QMessageBox *endTurn = new QMessageBox;
    endTurn->setText(turn1);
    connect(endTurn, &QMessageBox::accepted, this, &MainWindow2::handleEndTurn);
    endTurn->exec();//les cartes de la main du joueur sont cliquables
}


void MainWindow2::updateUI() {
    handVP1->updateHV();
    handVP2->updateHV();
    boardV->updateBV();
    window->update();
}

