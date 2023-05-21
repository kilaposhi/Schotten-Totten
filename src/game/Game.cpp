# include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>

#include "board/Border.h"

class Border;

void create_borders(){
    borders = vector<new Border, 9>;
    
}


void Game::play(Player player1, Player player2) {
    std::cout << "Début de la partie\n";
    create_game();
    player1.draw_card();
    player2.draw_card();
    while (true) {
        std::cout << "Tour du joueur " << player1ID << std::endl;

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
}

void pause() {
    std::cout << "Pause de 30 secondes...\n";
    std::this_thread::sleep_for(std::chrono::seconds(30));
    std::cout << "Reprise de la partie\n";
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