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
    maxPlayerCard = 6;
    DeckFactory deckFactory;
    clanDeck = deckFactory.createClanDeck();
    deckInfo = deckFactory.getDeckInfo();
    board = std::make_unique<Board>(9, player1.get(), player2.get());
    if (tacticVersion_){
        tacticDeck = deckFactory.createTacticDeck();
        discardDeck.clear();
        //Initialize tacticHandler
        TacticHandler::getInstance(&clanDeck, &deckInfo, &tacticDeck, &discardDeck, board.get());
        maxPlayerCard = 7;
    }
    create_players();
}


void Game::create_players(){
    std::cout<<"The one who traveled near Scotland the most recently is the player 1 \n";
    std::cout<<"Player 1 Please give your name: \n.";
    std::string name;
    std::cin>>name;
    player1 = std::make_unique<Player>(name, 1, maxPlayerCard);
    player2 = std::make_unique<Player>(name, 1, maxPlayerCard);
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

