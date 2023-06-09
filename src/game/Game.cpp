#include "Game.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "board/Border.h"



void Game::play(Player player1, Player player2, ) {
    std::cout << "Start of the game\n";

    pause(15);
    while (round) {
        play(player1);
        round = ?;
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
void Game::play(Player player)
{
    std::cout << "Player <<player.getId() <<, it is your turn !" << player1ID << std::endl;
    player.displayHand();
    pause(2);
    std::cout << "Please type the index of the card you want to pick.\n";
    int card_index;
    std::cin >> card_index;
    std::cout << "Please type the index of the border you want to pick.\n";
    int border_index;
    std::cin >> border_index;
    player1.play_card(card_index, borders[border_index]);
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
