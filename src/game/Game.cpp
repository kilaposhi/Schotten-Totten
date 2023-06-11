#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "deck/DeckFactory.h"


[[noreturn]] Game::Game(): gameOver(0){
    std::cout << "A quelle version jouez vous: [1] Classique | [2] Tactique:";
    int version_ = 1;
    std::cin >> version_;
    while(version_ != 1 or version_ != 2){
        std::cout << "Vous n'avez pas entré une valeur acceptable. \n A quelle version jouez vous: [1] Classique | [2] Tactique:";
        std::cin >> version_;
    }
    version = version_;
}


Board create_board(){
    //Create Board:
    std::cout << "how many borders are there ?" << "\n";
    int nbBorders;
    std::cin >> nbBorders;
    Board board(nbBorders);
    return board;
}

void Game::create_player1(){
    std::cout<<"The one who traveled near Scotland the most recently is the player 1 \n";
    std::cout<<"Player 1 Please give your name: \n.";
    std::string name;
    std::cin>>name;
    if(version == 1){
        Player player1(name, 1, 6);
    }
    else{
        Player player1(name, 1, 7);
    }
}

void Game::create_player2(){
    std::cout<<"Player 2 Please give your name: \n.";
    std::string name;
    std::cin>>name;
    if(version == 1){
        Player player2(name, 1, 6);
    }
    else{
        Player player2(name, 1, 7);
    }
}

void Game::create_deck(){ // Créer les cartes par la même occasion
    Deck clanDeck = DeckFactory().createClanDeck();
    clanDeck.shuffle();
    if(version == 2){
        Deck tacticDeck = DeckFactory().createTacticDeck();
        tacticDeck.shuffle();
    }
}

void Game::startGame() {
    //demande qui a voyagé le plus près de l'ecosse
    //demandes aux joueurs leurs noms
    //lance plusieurs rounds
    //annonce le vainqueur final (pourrait peut être être un attribut de Game
}

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

