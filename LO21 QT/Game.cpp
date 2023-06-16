#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include<string>

#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QInputDialog>

#include "TacticHandler.h"
#include "DeckFactory.h"
#include "Board.h"
#include "Game.h"
#include "BoardView.h"
#include "GameConfiguration.h"
#include "HandView.h"
#include <QMessageBox>
#include "MainWindow.h"
#include <QString>
#include "MyMessageBox.h"



class Board;


Game::Game(int argc, char *argv[]): gameOver(false), player1_(nullptr), player2_(nullptr){
    launchSchottenTotten1(argc,argv);
}

/*Deck Game::getClanDeck() const {
    return clanDeck;
}

Deck Game::getTacticDeck() const {
    return &tacticDeck;
}
Deck Game::getDiscardDeck() const;
DeckInfo getDeckInfo;
Board* getBoard;*/

bool Game::getVersion() const {
    return tacticVersion_;
}

/*void Game::setGameVersion(GameConfiguration config) {
    std::cout << "Which version do you want to play: [1] Classic | [2] Tactic\n";
    int version = config.chooseGameMode();
    tacticVersion_ = false;
    if (version == 2)
        tacticVersion_ = true;
}*/


int Game::launchSchottenTotten1(int argc, char *argv[]) {
    QApplication app1(argc, argv);

    GameConfiguration config;
    config.show();

    app1.exec();
    tacticVersion_ = config.getVersion();
    expertVersion_= config.getExpert();
    int numberRound = config.getNbRound();
    create_player(config.getPlayer1(),config.getPlayer2());

    //create_player("Capu", "Ness");
    create_deck();
    create_board();
    player1_->fillHand(clanDeck);
    player2_->fillHand(clanDeck);

    MainWindow* window = new MainWindow(nullptr, player1_.get(), player2_.get(), &clanDeck, &tacticDeck,board_.get(), this);
    window->show();
    //HandView* hand = new HandView(nullptr, player1_.get());
    //hand->show();
   // TacticDeckView* tactic = new TacticDeckView(nullptr, &tacticDeck);



   /* */
    /*
    for (size_t i =0; i < numberRound; i++){
        round();
    }*/

    return app1.exec();


    //setGameVersion(config);


    /* QApplication app2(argc, argv);

    BoardView bord;
    bord.show();

    return app2.exec();

*/
    /* for (size_t i =0; i < numberRound; i++){
        round();
    }*/
}


void Game::create_player(QString p1, QString p2)
{
    /*if (id == 1)
        QMessageBox::information(nullptr, "Player Identification", "The one who traveled near Scotland the most recently is Player 1");

    QString prompt = "Player " + QString::number(id) + ", please enter your name:";
    QString name = QInputDialog::getText(nullptr, "Player Name", prompt);
*/
    int maxPlayerCard = 6;
    if (tacticVersion_)
        maxPlayerCard = 7;
    player1_ = std::make_unique<Player>(p1.toStdString(), 1, maxPlayerCard);
    player2_ = std::make_unique<Player>(p2.toStdString(), 2, maxPlayerCard);
}


void Game::create_deck() {
    DeckFactory deckFactory;
    clanDeck = deckFactory.createClanDeck();
    clanDeck.shuffle();
    deckInfo = deckFactory.getDeckInfo();
    if (tacticVersion_){
        tacticDeck = deckFactory.createTacticDeck();
        tacticDeck.shuffle();
        discardDeck.clear();

    }
}

void Game::create_board() {
    board_ = std::make_unique<Board>(9, player1_.get(), player2_.get());
    if (tacticVersion_)
        TacticHandler::getInstance(&clanDeck, &deckInfo, &tacticDeck, &discardDeck, board_.get());
}


void Game::round() {
    create_deck();
    create_board();
    player1_->fillHand(clanDeck);

    player2_->fillHand(clanDeck);


    //MainWindow* window = new MainWindow(nullptr, player1_.get(), player2_.get(), board_.get(), tacticDeck, clanDeck);
    //window->show();

    /*QMessageBox::information(nullptr, "Round Start", "The round is starting.");
    while (board_->hasWinner() == nullptr) {
        QString turn1 =  QString::fromStdString(player1_->getName()) + "it's your turn ! \n" +  QString::fromStdString(player2_->getName())+ " don't look at the screen!\n";
        MyMessageBox messageBox1(nullptr, 1);
        messageBox1.setText(turn1);
        messageBox1.exec();
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
    }*/
    quit();
}


void Game::play(Player* player) {

    cout << player->displayHand() << '\n';
    std::cout << "Please type the index of the card you want to pick.\n";
    int card_index = askPlayerValue(player, {0, player->getNumber_of_cards() - 1});
    std::cout << "Please type the index of the border you want to pick.\n";
    int border_index = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
    player->play_card(card_index, border_index, board_.get());
    std::cout << *board_ << '\n';
    bool playerWantToClaim = askYesNo("Would you like to claim a border?");
    if (playerWantToClaim){
        std::cout << "Please type the index of the border you want to pick.\n";
        int border_index = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
        try {
            board_->getBorderByID(border_index); // .claim
        }catch  (BorderException e) {
            cout << e.what();
        }
    }
    drawCard(player);
    pause(5);
    clearScreen();
}


void clearScreen(){
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}


void Game::drawCard(Player* player){
    cout << "Drawing a card \n";
    bool playerHasDrawn = false;

    if (tacticVersion_){
        cout << "From which deck do you want to draw ? ";
        cout << "[0] Normal Deck (" << clanDeck.getNumberRemainingCards() <<" cards remaining) ";
        cout << "[1] Tactic Deck (" << tacticDeck.getNumberRemainingCards() << " cards remaining) \n";
        //règle tactique
        int answer = askPlayerValue(player, {0,1});
        if (answer == 1) {
            if (tacticDeck.isEmpty()) {
                cout << "The tactic Deck is empty! \n";
            } else {
                player->draw_card(tacticDeck);
                playerHasDrawn = true;
            }
        }
    }
    if (!playerHasDrawn) {
        if (clanDeck.isEmpty()){
            cout << "The clan Deck is empty! \n";
        }else
            player->draw_card(clanDeck);
    }
    cout << "New hand " << player->displayHand() << '\n';
}


void Game::pause(int n) {
    //std::cout << "Pause de 30 secondes...\n";
    std::this_thread::sleep_for(std::chrono::seconds(n));
    //std::cout << "Reprise de la partie\n";
}


bool Game::isGameOver() {
    // Exemple d'implémentation de la logique de fin de partie
    // Ici, on considère que la partie est terminée si un joueur atteint un score de 10
    int scorePlayer1 = 5; // Exemple de score pour le joueur 1
    int scorePlayer2 = 8; // Exemple de score pour le joueur 2

    if (scorePlayer1 >= 10 || scorePlayer2 >= 10) {
        gameOver = true;
        return true;
    }

    return false;
}


void Game::quit() {
    gameOver = true;
}
