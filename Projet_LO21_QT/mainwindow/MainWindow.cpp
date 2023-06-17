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
    if (game->getVersion()) {
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

        //connect(actualHand, &HandView::cardSelected, this, &MainWindow::handleCardSelected);
        //connect(boardV, &BoardView::borderChoice, this, &MainWindow::handleBorderSelected);

        //connect(tacticDeckV, &TacticDeckView::clicked, this, &MainWindow::handleTacticDeckClicked);
        //connect(clanDeckV, &ClanDeckView::clicked, this, &MainWindow::handleClanDeckClicked);



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


void MainWindow::handleEndTurn() {
    state = 1;//moment de jouer

    qDebug() << "dans handleEndTurn";
    //disconnect(actualHand, &HandView::cardSelected, this, &MainWindow::handleCardSelected);
    qDebug() << "après disconnect";
    //delete actualHand;
    qDebug() << "après delete";

    actualHand = new HandView(this, actualPlayer);
    window->addWidget(actualHand, 2, 0);
    window->update();
    qDebug() << "après windows uptdate";

    for (CardView* cardV : actualHand->getHandList()) {
        cardV->setEnabled(true);
    }
    qDebug() << "après setEnable";

    connect(actualHand, &HandView::cardSelected, this, &MainWindow::handleCardSelected);
    qDebug() << "après connect";


    /*for (CardView* cardV : otherHand->getHandList()) {
        cardV->setEnabled(false);
    }*/
    window->update();
    qDebug() << "après update";
    //essaye de faire un addCardInto Hand alors que la main est déjà full

}

void MainWindow::handleCardSelected(int index){
    qDebug() << "dans handleCardSelected";
    disconnect(actualHand, &HandView::cardSelected, this, &MainWindow::handleCardSelected);

    handIndex = index;

    connect(boardV, &BoardView::borderChoice, this, &MainWindow::handleBorderSelected);
    for (BorderView* borderV : boardV->getBordersV()) {
        borderV->getBorderButton()->setEnabled(true);
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

void MainWindow::handleTacticDeckClicked(){
    clanDeckV->setEnabled(false);
    tacticDeckV->setEnabled(false);

    actualPlayer->draw_card(*tacticDeck);

    delete actualHand;
    actualHand = new HandView(this, actualPlayer);
    window->addWidget(actualHand, 2, 0);
    window->update();

    if (game->isGameOver()) {
        QString over = "Game over :" + QString::fromStdString(actualPlayer->getName()) + " won !";
        QMessageBox::information(this, "Game Over", over);
    }
    else {
        newTurn();
    }

}

void MainWindow::handleClanDeckClicked(){
    clanDeckV->setEnabled(false);
    tacticDeckV->setEnabled(false);
    actualPlayer->draw_card(*clanDeck);

    delete actualHand;
    actualHand = new HandView(this, actualPlayer);
    window->addWidget(actualHand, 2,0);
    window->update();

    if (game->isGameOver()) {
        QString over = "Game over :" + QString::fromStdString(actualPlayer->getName()) + " won !";
        QMessageBox::information(this, "Game Over", over);
    }
    else {
        newTurn();
    }

}

void MainWindow::askClaim() {
    int response = QMessageBox::question(this, "Claim", "Do you want to claim a border ?", QMessageBox::Yes | QMessageBox::No);

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

void MainWindow::newTurn(){
    //disconnect(actualHand, &HandView::cardSelected, this, &MainWindow::handleCardSelected);
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

    QString turn1 =  QString::fromStdString(actualPlayer->getName()) + "it's your turn ! \n" +  QString::fromStdString(otherPlayer->getName())+ " don't look at the screen!\n";
    QMessageBox *endTurn = new QMessageBox;
    endTurn->setText(turn1);
    connect(endTurn, &QMessageBox::accepted, this, &MainWindow::handleEndTurn);
    endTurn->exec();//les cartes de la main du joueur sont cliquables
}


void MainWindow::updateUI() {
    handVP1->updateHV();
    handVP2->updateHV();
    boardV->updateBV();
    window->update();
}

