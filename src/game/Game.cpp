#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "deck/DeckFactory.h"
#include "board/Board.h"
#include "Game.h"


class Board;

Game::Game(): gameOver(false), player1(nullptr), player2(nullptr){
    launchSchottenTotten1();
}

void Game::setGameVersion() {
    std::cout << "A quelle version jouez vous: [1] Classique | [2] Tactique:";
    int version;
    std::cin >> version;
    while(version != 1 && version != 2){
        std::cout << "Vous n'avez pas entré une valeur acceptable. \n A quelle version jouez vous: [1] Classique | [2] Tactique:";
        std::cin >> version;
    }
    if (version == 2)
        tacticVersion_ = true;
}

void Game::launchSchottenTotten1() {
    setGameVersion();

    // Création de la board
    Board board_(9, player1, player2);

    // Création des decks
    clanDeck = DeckFactory().createClanDeck();
    DeckInfo clanDeckInfo = DeckFactory().getDeckInfo();
    clanDeck.shuffle();
    TacticHandler instance = TacticHandler::getInstance(&clanDeck, &clanDeckInfo, &tacticDeck, &discardDeck, &board_);

    // Initialisations des infos des players
    std::cout<<"The one who traveled near Scotland the most recently is the player 1 \n";
    std::cout<<"Player 1 Please give your name: \n.";
    std::string name1;
    name1 = "Josette"; //std::cin>>name1;
    std::cout<<"Player 2 Please give your name: \n.";
    std::string name2;
    name2 = "Franck"; // std::cin>>name2;
    int maxPlayerCards = 6;

    if(tacticVersion_){ // Si on joue à la version tactique
        // Création du tacticDeck
        tacticDeck = DeckFactory().createTacticDeck();
        discardDeck.clear();
        //Initialize tacticHandler
        TacticHandler::getInstance(&clanDeck, &clanDeckInfo, &tacticDeck, &discardDeck, &board_);
        maxPlayerCards = 7;
    }

    // Création des Players
    Player player1_(name1, 1, maxPlayerCards);
    Player player2_(name2, 2,maxPlayerCards);
    player1 = &player1_;
    player2 = &player2_;
    cout << *player1;
    cout << *player2;
    startGame();
}


void Game::startGame() {
    if(tacticVersion_){
        // tacticDeck.drawCard();
        int x;
        for (int i=0; i <2 ; i++) {
            x = rand() % 2;
            if (x == 0) {j
                player1->draw_card(clanDeck);
                player2->draw_card(clanDeck);
            }
            else {
                player1->draw_card(tacticDeck);
                player2->draw_card(tacticDeck);
            }
        }
    }
    for (int i=0; i <6; i++) {
        player1->draw_card(clanDeck);
        player2->draw_card(clanDeck);
    }
    cout << *player1;
    cout << *player2;
}

/*
void Game::round(Player* player1, Player* player2, Board board) {
    create_deck();

    std::cout << "Start of the game\n";


    while (board.hasWinner() == nullptr) {
        std::cout << "Player " << player1->getId() <<"'s turn" << std::endl;
        play(player1, board);

        pause(15);

        if (isGameOver()) {
            std::cout << "Player " << player1->getId() << " won!\n";
            break;
        }

        pause(15);

        std::cout << "Player " << player2->getId() <<"'s turn" << std::endl;
        play(player2, board);

        if (isGameOver()) {
            std::cout << "Player " << player2->getId() << " won!\n";
            break;
        }

        pause(15);
    }

    std::cout << "End of the game\n";
    quit();
}


void Game::play(Player* player, Board board) {
    std::cout << "Player" << player->getId() <<", it is your turn !" << std::endl;
    player->displayHand();
    pause(2);
    std::cout << "Please type the index of the card you want to pick.\n";
    int card_index;
    std::cin >> card_index;
    std::cout << "Please type the index of the border you want to pick.\n";
    int border_index;
    std::cin >> border_index;
    std::vector<Border> borders = board.getBorders();
    player.play_card(card_index, [border_index]);
    std::cout << "Would you like to claim a border? If yes, please select an index, otherwise you can type 0.\n";
    std::cin >> border_index;
    if (border_index<0 || border_index>9)
    {
        throw PlayerException("The index is not valid.");
    }
    else if (border_index==0) break;
    else {

        borders[border_index].getClaimed();

    }
    if (!deck.isEmpty) player.draw_card( deck_);
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
*/
