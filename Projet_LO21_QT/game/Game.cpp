#include "Game.h"

#include "GameConfiguration.h"
#include "mainwindow/MainWindow.h"
#include "deck/DeckFactory.h"
#include "console/Console.h"
#include "hand/TacticHandler.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include<string>
#include <QApplication>
#include <QMessageBox>
#include <QString>
#include <QInputDialog>
#include <QString>
#include <QMessageBox>


Game::Game(int argc, char *argv[]): gameOver(false), player1_(nullptr), player2_(nullptr){
    launchSchottenTotten1(argc,argv);
}


bool Game::getVersion() const {
    return tacticVersion_;
}


int Game::launchSchottenTotten1(int argc, char *argv[]) {
    QApplication app1(argc, argv);

    GameConfiguration config;
    config.show();

    app1.exec();
    tacticVersion_ = config.getVersion();
    expertVersion_= config.getExpert();
    create_player(config.getPlayer1(),config.getPlayer2());
    create_deck();
    create_board();
    player1_->fillHand(clanDeck);
    player2_->fillHand(clanDeck);

    MainWindow* window = new MainWindow(nullptr, player1_.get(), player2_.get(), &clanDeck, &tacticDeck, board_.get(), this);
    window->show();

    return app1.exec();
}


void Game::create_player(QString p1, QString p2)
{
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
        } catch (const BorderException& e) {
        cout << e.what();
    }

    }
    drawCard(player);
    pause(5);
    clearScreen();
}


void Game::clearScreen(){
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
