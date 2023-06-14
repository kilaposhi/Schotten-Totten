#include "Game.h"

Game::Game() : gameOver(false), player1_(nullptr), player2_(nullptr) {
    launchSchottenTotten1();
}

void Game::setGameVersion() {
    std::cout << "Which version do you want to play? : [1] Classic | [2] Tactic\n";
    int version = askValue({1, 2});
    tacticVersion_ = (version == 2);
}

void Game::launchSchottenTotten1() {
    setGameVersion();
    create_player(1);
    bool playAgainstAI = askYesNo("Do you want to play against the AI?");
    if (playAgainstAI)
        create_AI();
    else
        create_player(2);
    cout << "How many rounds do you want to play?\n";
    int numberRound = askValue({1, 15});
    for (size_t i = 0; i < numberRound; i++) {
        if (playAgainstAI)
            roundAI();
        else
            round();
    }
}

void Game::create_player(int id) {
    if (id == 1)
        std::cout << "The one who traveled near Scotland the most recently is player 1.\n";
    std::cout << "Player " << id << ", please enter your name:\n";
    std::string name;
    std::cin >> name;
    int maxPlayerCard = (tacticVersion_) ? 7 : 6;
    if (id == 1)
        player1_ = std::make_unique<Player>(name, id, maxPlayerCard);
    else
        player2_ = std::make_unique<Player>(name, id, maxPlayerCard);
}

void Game::create_AI() {
    std::cout << player1_->getName() << " please enter a name for the AI opponent:\n";
    std::string name;
    std::cin >> name;
    name += " AI";
    int maxPlayerCard = (tacticVersion_) ? 7 : 6;
    player2_ = std::make_unique<AI>(maxPlayerCard, name);
}

void Game::create_deck() {
    DeckFactory deckFactory;
    clanDeck = deckFactory.createClanDeck();
    clanDeck.shuffle();
    deckInfo = deckFactory.getDeckInfo();
    if (tacticVersion_) {
        tacticDeck = deckFactory.createTacticDeck();
        tacticDeck.shuffle();
        discardDeck.clear();
    }
}

void Game::create_board() {
    board_ = std::make_unique<Board>(9, player1_.get(), player2_.get());
    //initialization GameTracker Sinleton
    GameTracker::getInstance(player1_.get(), player2_.get());
    if (tacticVersion_)
        TacticHandler::getInstance(&clanDeck, &deckInfo, &tacticDeck, &discardDeck, board_.get());
}

void Game::round() {
    create_deck();
    create_board();
    player1_->fillHand(clanDeck);
    player2_->fillHand(clanDeck);
    std::cout << "Start of the game\n";
    while (board_->hasWinner() == nullptr) {
        std::cout << "Player " << player1_->getName() << ", it's your turn!\n";
        cout << "Player " << player2_->getName() << ", don't look at the screen!\n";
        play(player1_.get());
        pause(2);
        if (isGameOver()) {
            std::cout << "Player " << player1_->getName() << " won!\n";
            break;
        }
        std::cout << *player2_ << "'s turn\n";
        play(player2_.get());
        if (isGameOver()) {
            std::cout << "Player " << player2_->getName() << " won!\n";
            break;
        }
        pause(6);
    }
    std::cout << "End of the game\n";
    quit();
}

void Game::play(Player* player) {
    cout << board_->str() << '\n';
    cout << player->displayHand() << '\n';

    bool canPlayCard = false;
    for (unsigned int i = 0; i < player->getNumber_of_cards(); i++) {
        if (dynamic_cast<ValuedCard*>(player->getCardAtIndex(i).get())) {
            canPlayCard = true;
            break;
        }
    }

    bool canClaimBorder = false;
    for (unsigned int i = 0; i < board_->getNumberBorder(); i++) {
        if (board_->getBorderByID(i).getPlayerCombination(player).getNumberCards() != board_->getBorderByID(i).getPlayerCombination(player).getMaxNumberCards()) {
            canClaimBorder = true;
            break;
        }
    }

    if (!canPlayCard || !canClaimBorder) {
        bool playerWantsToPass = askYesNo("Do you want to pass your turn?\n");
        if (playerWantsToPass) {
            std::cout << "Please enter the index of the card you want to pick:\n";
            int card_index = askPlayerValue(player, {0, player->getNumber_of_cards() - 1});
            std::cout << "Please enter the index of the border you want to pick:\n";
            int border_index = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
            while (board_->getBorderByID(border_index).isClaimed()) {
                std::cout << "The border is already claimed. Please enter a different index:\n";
                border_index = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
            }
            player->play_card(card_index, border_index, board_.get());
            std::cout << *board_ << '\n';
        }
    } else {
        std::cout << "Please enter the index of the card you want to play:\n";
        int card_index = askPlayerValue(player, {0, player->getNumber_of_cards() - 1});
        std::cout << "Please enter the index of the border you want to play on:\n";
        int border_index = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
        while (board_->getBorderByID(border_index).isClaimed()) {
            std::cout << "The border is already claimed. Please enter a different index:\n";
            border_index = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
        }
        player->play_card(card_index, border_index, board_.get());
        std::cout << *board_ << '\n';
    }

    bool playerWantsToClaim = askYesNo("Would you like to claim a border?");
    if (playerWantsToClaim) {
        std::cout << "Please enter the index of the border you want to claim:\n";
        int border_index2 = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
        try {
            // board_->getBorderByID(border_index2).claim();
        } catch (const BorderException& e) {
            std::cout << e.what() << '\n';
        }
    }

    drawCard(player);
    pause(5);
    clearScreen();
}

void Game::playAI(AI* computer) {
    int card_index = rand() % computer->getNumber_of_cards(); // Initialise card_index à une valeur par défaut
    int border_index;
    if (tacticVersion_) {
        border_index = rand() % board_->getNumberBorder();
        while (board_->getBorderByID(border_index).isClaimed()) {
            border_index = rand() % board_->getNumberBorder();
        }
    } else {
        vector<Combination> possibilities;
        for (int i = 0; i < board_->getNumberBorder(); i++) {
            card_index = computer->pick_a_card(&board_->getBorderByID(i));
            std::unique_ptr<ValuedCard> card = std::make_unique<ValuedCard>(*computer->getCardAtIndex(card_index));

            Combination combination(board_->getBorderByID(i).getPlayerCombination(computer));
            if (!combination.getNumberCards() == 0 && combination.getType() != CombinationType::NONE) {
                combination.push_back(std::move(card));
                possibilities.push_back(std::move(combination));
            }
        }
        if (!possibilities.empty()) {
            border_index = findBestCombination(possibilities);
        }
    }

    computer->play_card(card_index, border_index, board_.get());
    std::cout << "The computer is playing the card " << computer->displayCard(card_index) << " on the border " << border_index << ".\n";

    border_index = computer->claim_a_border(board_.get(), player1_.get());
    if (border_index != 0) {
        std::cout << "The computer is claiming the border " << border_index << ".\n";
        // board_->getBorderByID(border_index).claim();
    }

    std::cout << "Drawing a card\n";
    bool playerHasDrawn = false;
    if (tacticVersion_ && !tacticDeck.isEmpty()) {
        int answer = rand() % 2;
        if (answer == 1) {
            computer->draw_card(tacticDeck);
            playerHasDrawn = true;
        }
    }

    if (!playerHasDrawn && !clanDeck.isEmpty()) {
        computer->draw_card(clanDeck);
    }
}

void Game::roundAI() {
    create_deck();
    create_board();
    player1_->fillHand(clanDeck);
    player2_->fillHand(clanDeck);

    std::cout << "Start of the game\n";

    while (board_->hasWinner() == nullptr) {
        std::cout << "It's your turn, " << player1_->getName() << "!\n";
        //1play(player1_.get());

        pause(0);

        if (isGameOver()) {
            std::cout << "Congratulations! You won!\n";
            break;
        }

        pause(5);

        std::cout << "The computer is playing...\n";
        playAI(static_cast<AI*>(player2_.get()));
        std::cout << "The computer is playing...\n";
        if (isGameOver()) {
            std::cout << "You lost! Better luck next time!\n";
            break;
        }

        pause(15);
    }

    std::cout << "End of the game\n";
    quit();
}

void Game::drawCard(Player* player) {
    std::cout << "Drawing a card...\n";
    bool playerHasDrawn = false;

    if (tacticVersion_ && !tacticDeck.isEmpty()) {
        std::cout << "From which deck do you want to draw?\n";
        std::cout << "\t[0] Normal Deck (" << clanDeck.getNumberRemainingCards() << " cards remaining)\n";
        std::cout << "\t[1] Tactic Deck (" << tacticDeck.getNumberRemainingCards() << " cards remaining)\n";
        int answer = askPlayerValue(player, {0, 1});

        if (answer == 1) {
            player->draw_card(tacticDeck);
            playerHasDrawn = true;
        }
    }

    if (!playerHasDrawn && !clanDeck.isEmpty()) {
        player->draw_card(clanDeck);
    }

    cout << "Card obtained :" << player->displayCard(player->getNumber_of_cards() - 1) << '\n';
    std::cout << "New hand: " << player->displayHand() << '\n';
}

void Game::pause(int n) {
    std::this_thread::sleep_for(std::chrono::seconds(n));
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

void clearScreen() {
//    std::cout << "\033c";
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}
