#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "deck/DeckFactory.h"


Game::Game(): gameOver(false){
    launchSchottenTotten1();
}

void Game::setGameVersion() {
    std::cout << "A quelle version jouez vous: [1] Classique | [2] Tactique: '\n";
    int version = askValue({1,2});
    if (version == 2)
        tacticVersion_ = true;
    tacticVersion_ = false;
}

void Game::launchSchottenTotten1() {
    setGameVersion();
    create_player(1);
    create_player(2);
    create_deck();
    create_board();

}


void Game::create_player(int id){
    if (id == 1)
        std::cout<<"The one who traveled near Scotland the most recently is the player 1 \n";
    std::cout<<"Player " << id << " please give your name: \n.";
    std::string name;
    std::cin>>name;
    int maxPlayerCard = 6;
    if (tacticVersion_)
        maxPlayerCard = 7;
    if (id == 1)
        player1 = std::make_unique<Player>(name, id, maxPlayerCard);
    else
        player2 = std::make_unique<Player>(name, id , maxPlayerCard);
}


void Game::create_deck() {
    DeckFactory deckFactory;
    clanDeck = deckFactory.createClanDeck();
    deckInfo = deckFactory.getDeckInfo();
    if (tacticVersion_){
        tacticDeck = deckFactory.createTacticDeck();
        discardDeck.clear();
    }
}

void Game::create_board() {
    board = std::make_unique<Board>(9, player1.get(), player2.get());
    if (tacticVersion_)
        TacticHandler::getInstance(&clanDeck, &deckInfo, &tacticDeck, &discardDeck, board.get());
}

void Game::round(Player* player1, Player* player2, Board board) {
    create_deck();

    std::cout << "Start of the game\n";


    while (board.hasWinner() == nullptr) {
        std::cout << "Player " << player1->getID() <<"'s turn" << std::endl;
        play(player1, board);

        pause(15);

        if (isGameOver()) {
            std::cout << "Player " << player1->getID() << " won!\n";
            break;
        }

        pause(15);

        std::cout << *player2 <<  "turn" << std::endl;
        play(player2, board);

        if (isGameOver()) {
            std::cout << "Player " << player2->getID() << " won!\n";
            break;
        }

        pause(15);
    }

    std::cout << "End of the game\n";
    quit();
}


void Game::play(Player* player, Board* board) {
    std::cout << "Player" << player->getID() <<", it is your turn !" << std::endl;
    pause(2);
    cout << board->str() << '\n';
    cout << player->displayHand() << '\n';
    std::cout << "Please type the index of the card you want to pick.\n";
    int card_index = askPlayerValue(player, {0, player->getNumber_of_cards() -1});
    std::cout << "Please type the index of the border you want to pick.\n";
    int border_index = askPlayerValue(player, {0, board->getNumberBorder() - 1});
    player->play_card(card_index, border_index, board);
    std::cout << *board << '\n';
    bool playerWantToClaim = askYesNo("Would you like to claim a border?");
    if (playerWantToClaim){
        std::cout << "Please type the index of the border you want to pick.\n";
        int border_index = askPlayerValue(player, {0, board->getNumberBorder() - 1});
        try {
            board->getBorderByID(border_index); // .claim
        }catch  (BorderException e) {
            cout << e.what();
        }
    }

//    if (!clanDeck.isEmpty) player.draw_card( deck_);
}


void pause(int n) {
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

