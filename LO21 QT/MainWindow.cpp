#include "MainWindow.h"
#include "BoardView.h"
#include "HandView.h"
#include "DeckView.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "CardView.h"
#include <QMessageBox>
#include "signalmessagebox.h"

MainWindow::MainWindow(QWidget *parent, Player* player1, Player* player2, Deck* clanDeck, Deck* tacticDeck, Board* board, Game* game)
    :QWidget(parent), game_(game), player1(player1), player2(player2), board(board)//player1_(player1), player2_(player2), clanDeck_(clanDeck), tacticDeck_(tacticDeck)
{
    QMessageBox::information(nullptr, "Round Start", "The round is starting.");
    handVP1 = new HandView(this, player1);
    handVP2 = new HandView(this, player2);
    actualHand = handVP2;
    otherHand = handVP1;
    tacticDeckV = new TacticDeckView(this, tacticDeck);
    clanDeckV = new ClanDeckView(this, clanDeck);
    boardV = new BoardView(this, board);

    QHBoxLayout* decks = new QHBoxLayout;
    decks->addWidget(clanDeckV);
    if (game_->getVersion()) {
        decks->addWidget(tacticDeckV);
    }

    window = new QVBoxLayout;
    window->addWidget(boardV);
    window->addLayout(decks);
    window->addWidget(handVP1);

    setLayout(window);

    //while (board->hasWinner() == nullptr) {
        QString turn1 =  QString::fromStdString(player1->getName()) + "it's your turn ! \n" +  QString::fromStdString(player2->getName())+ " don't look at the screen!\n";
        QMessageBox *endTurn = new QMessageBox;
        endTurn->setText(turn1);
        //endTurn->exec();
        connect(endTurn, &QMessageBox::accepted, this, &MainWindow::handleEndTurn);
        endTurn->exec();//les cartes de la main du joueur sont cliquables

        connect(handVP1, &HandView::cardSelected, this, &MainWindow::handleCardSelected);
        connect(boardV, &BoardView::borderChoice, this, &MainWindow::handleBorderSelected);

        //player1->play_card(handIndex, borderIndex, board);

        //connect(this, &MainWindow::played, handVP1, &HandView::handlePlayed);
        //connect(this, &MainWindow::played, boardV, &BoardView::handlePlayed);
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



    /*SignalMessageBox* messageBox1 = new SignalMessageBox(this, 1);
    messageBox1->setText(turn1);

    messageBox1->exec();

    connect(messageBox1, &SignalMessageBox::dialogClosed, this, &MainWindow::handleEndBox);
*/


    //window->update();

    //boardV = new BoardView(this, board);




//}

/*void MainWindow::handleEndBox(int playerID) {
    qDebug() << playerID;
    if (playerID == 2) {
        actualHand = handVP2;
    }
    else {
        actualHand = handVP1;
    }
    for (CardView* cardV : actualHand->getHandList()) {
        cardV->setEnabled(true);
    }
}*/}

void MainWindow::handleEndTurn() {
    //qDebug() << "Dans fonction";
    HandView* temp = actualHand;
    actualHand = otherHand;
    otherHand = temp;
    for (CardView* cardV : actualHand->getHandList()) {
        cardV->setEnabled(true);
    }
    for (CardView* cardV : otherHand->getHandList()) {
        cardV->setEnabled(false);
    }
    window->update();
}

void MainWindow::handleCardSelected(int index){
    handIndex = index;
    for (BorderView* borderV : boardV->getBordersV()) {
        borderV->getBorderButton()->setEnabled(true);
    }
}

void MainWindow::handleBorderSelected(int index) {
    player1->play_card(handIndex, index, board);

    qDebug() << player1->displayHand();
    qDebug() << board->str();
    tacticDeckV->setEnabled(true);
    clanDeckV->setEnabled(true);
    updateUI();


}

void MainWindow::updateUI() {
    handVP1->updateHV();
    handVP2->updateHV();
    boardV->updateBV();
    window->update();
}

