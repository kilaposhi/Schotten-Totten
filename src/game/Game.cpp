#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>

Game::Game(Player *player1, Player *player2) {
    player1ID = (player1->getId());
    player2ID = (player2->getId()) ;
}

Board create_board(){
    //Create Board:
    std::cout << "how many borders are there ?" << "\n";
    int nbBorders;
    std::cin >> nbBorders;
    Board board(nbBorders);
    return board;
}

Player create_player1(){
    std::cout<<"The one who traveled near Scotland the most recently is the player 1 \n";
    std::cout<<"Player 1 Please give your name: \n.";
    std::string name;
    std::cin>>name;
    Player (name, 1, )
}

void Game::startGame() {
    //demande qui a voyagé le plus près de l'ecosse
    //demandes aux joueurs leurs noms
    //lance plusieurs rounds
    //annonce le vainqueur final (pourrait peut être être un attribut de Game
}
void Game::round(Player player1, Player player2, Board board) {
    std::cout << "Start of the game\n";

    pause(15);
    while (board.hasWinner() == nullptr) {
        play(player1);
        play(player2);



        //afficher la main du joueur
        //lui demander l'index de la carte qu'il souhaite joueur et sur quelle borne
        //jouer la carte
        //demander si le joueur souhaite revandiquer une borne, si oui, laquelle ?
        // : on peut faire un case
        //vérfier que 3 cartes sont sur chaque frontière de la borne
        //trouver le gagnant de la borne, vérifier qu'il n'y a pas de gagnant de la partie
        // piocher une carte


        if (isGameOver()) {
            std::cout << "Le joueur " << player1ID << " a gagné !\n";
            break;
        }

        pause();

        std::cout << "Tour du joueur " << player2ID << std::endl;
        // Logique de jeu pour le joueur 2

        if (isGameOver()) {
            std::cout << "Le joueur " << player2ID << " a gagné !\n";
            break;
        }

        pause();
    }

    std::cout << "Fin de la partie\n";
    quit();
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

