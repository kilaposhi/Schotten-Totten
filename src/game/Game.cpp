#include "Game.h"

Game::Game() : gameOver(false), player1_(nullptr), player2_(nullptr) {
    launchSchottenTotten1();
}

void Game::setGameVersion() {
    std::cout << "Which version do you want to play? [1] Classic | [2] Tactic\n";
    int version = askValue({1, 2});
    tacticVersion_ = (version == 2);
    expert_ = askYesNo("Do you want to play the expert version ?");
}

void Game::launchSchottenTotten1() {
    setGameVersion();
    bool AIvsAI = askYesNo("Game AI vs AI");
    if (AIvsAI) {
        gameAIvsAI();
    } else {
        create_player(1);
        int numberRound = askValue({1, 15});

        bool playAgainstAI = askYesNo("Do you want to play against the AI?");
        if (playAgainstAI)
        {
            create_AI();
            for (size_t i = 0; i < numberRound; i++)
            {roundAI();}}
        else
            { create_player(2);
            for (size_t i = 0; i < numberRound; i++)
            {round();}}
    }


    if (player1_->getScore() > player2_->getScore())
        std::cout << player1_->getName() << " won the game\n";
    else
        std::cout << player2_->getName() << " won the game\n";
}
void Game::create_player(int id) {
    if (id == 1)
        std::cout << "The one who traveled near Scotland most recently is player 1.\n";
    std::cout << "Player " << id << ", please enter your name:\n";
    std::string name;
    std::cin >> name;
    int maxPlayerCard = (tacticVersion_) ? 7 : 6;
    if (id == 1)
        player1_ = std::make_unique<Player>(name, id, maxPlayerCard);
    else
        player2_ = std::make_unique<Player>(name, id, maxPlayerCard);
}

void Game::gameAIvsAI() {
    std::cout << "Enter a name for AI player 1:\n";
    std::string name1;
    std::cin >> name1;
    name1 += " AI";
    int maxPlayerCard = (tacticVersion_) ? 7 : 6;
    player1_ = std::make_unique<Player>(name1, 1, maxPlayerCard);

    std::cout << "Enter a name for AI player 2:\n";
    std::string name2;
    std::cin >> name2;
    name2 += " AI";
    player2_ = std::make_unique<Player>(name2, 2, maxPlayerCard);
    create_deck();
    create_board();
    player1_->fillHand(clanDeck);
    player2_->fillHand(clanDeck);
    std::cout << "Start of the game\n";
    std::cout << "How many rounds ?\n";
    int numberRound = askValue({1, 15});
    for (size_t i = 0; i < numberRound; i++) {
        while (board_->hasWinner() == nullptr) {
            std::cout << "It is the turn of " << player1_->getName() << "!\n";
            playAIBasic(player1_.get());
            pause(2);
            if (board_.get()->hasWinner() != nullptr) {
                std::cout << "Player " << board_.get()->hasWinner()->getName() << " won!\n";
                Player *winner = board_.get()->hasWinner();
                Player *looser;
                (player1_.get() != board_.get()->hasWinner()) ? looser = player1_.get() : looser = player2_.get();
                winner->newScore(5);
                looser->newScore(winner->getClaimed_borders().size());
                break;
            }
            std::cout << "It is the turn of " << player2_->getName() << "!\n";
            playAIBasic(player2_.get());
            pause(2);
            if (board_.get()->hasWinner() != nullptr) {
                std::cout << "Player " << board_.get()->hasWinner()->getName() << " won!\n";
                Player *winner = board_.get()->hasWinner();
                Player *looser;
                (player1_.get() != board_.get()->hasWinner()) ? looser = player1_.get() : looser = player2_.get();
                winner->newScore(5);
                looser->newScore(winner->getClaimed_borders().size());
                break;
            }
        }
        clearScreen();
        create_deck();
        create_board();
        player1_->fillHand(clanDeck);
        player2_->fillHand(clanDeck);
    }
    std::cout << "End of the game\n";
    quit();
}

void Game::create_AI() {
    std::cout << player1_->getName() << ", please enter a name for the AI opponent:\n";
    std::string name;
    std::cin >> name;
    name += " AI";
    int maxPlayerCard = (tacticVersion_) ? 7 : 6;
    basic_ = askYesNo("Do you want the AI to be basic ?");
    if (basic_)
        player2_ = std::make_unique<Player>(name, 2, maxPlayerCard);
    else
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
    // Initialization of GameTracker Singleton
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
        clearScreen();
        pause(2);
        if ( board_.get()->hasWinner() != nullptr) {
            std::cout << "Player " << board_.get()->hasWinner()->getName() << " won!\n";
            Player * winner = board_.get()->hasWinner() ;
            Player * looser;
            (player1_.get()!=board_.get()->hasWinner()) ? looser = player1_.get() : looser = player2_.get();
            winner->newScore(5);
            looser->newScore(winner->getClaimed_borders().size());
            break;
        }
        std::cout << "Player " << player2_->getName() << "'s turn\n";
        play(player2_.get());
        clearScreen();
        if (board_.get()->hasWinner() != nullptr) {
            std::cout << "Player " << board_.get()->hasWinner()->getName() << " won!\n";
            Player * winner = board_.get()->hasWinner() ;
            Player * looser;
            (player1_.get()!=board_.get()->hasWinner()) ? looser = player1_.get() : looser = player2_.get();
            winner->newScore(5);
            looser->newScore(winner->getClaimed_borders().size());
            break;
        }
        pause(2);
    }
    std::cout << "End of the game\n";
    quit();
}

void Game::playAI(AI* computer) {
    unsigned int border_index = computer->pick_a_border(board_.get());
    Border* selected_border = &board_->getBorderByID(border_index);
    unsigned int card_index = computer->pick_a_card(selected_border);
    std::cout << computer->getName() << " is playing the card " << computer->displayCard(card_index) << " on border " << border_index << ".\n";

    computer->play_card(card_index, border_index, board_.get());
    std::cout << computer->getName() << " is playing the card " << computer->displayCard(card_index) << " on border " << border_index << ".\n";

    border_index = computer->claim_a_border(board_.get(), player1_.get());
    if (border_index != 0) {
        std::cout << computer->getName() << " is claiming border " << border_index << ".\n";
        // board_->getBorderByID(border_index).claim();
    }

    std::cout << computer->getName() << " is drawing a card.\n";
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

void Game::play(Player* player) {
    cout << board_->str() << '\n';
    cout << player->displayHand() << '\n';
    if (expert_) {
        bool playerWantsToClaim = askYesNo("Would you like to claim a border?");
        if (playerWantsToClaim) {
            std::cout << "Please enter the index of the border you want to claim:\n";

            unsigned int border_index = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
            try {
                //board_->getBorderByID(border_index2).claim();
            } catch (const BorderException &e) {
                std::cout << e.what() << '\n';
            }
        }
    }

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
        bool playerWantsToPass = askYesNo("Do you want to pass your turn?");
        if (playerWantsToPass) {
            std::cout << "Please enter the index of the card you want to pick:\n";
            int card_index = askPlayerValue(player, {0, player->getNumber_of_cards() - 1});
            int border_index;
            if (player->getCardAtIndex(card_index)->isRuse())
            {
                border_index=-1;
            }
            else {
                std::cout << "Please enter the index of the border you want to pick:\n";
                border_index = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
                while (board_->getBorderByID(border_index).isClaimed())
                {
                    std::cout << "The border is already claimed. Please enter a different index:\n";
                    border_index = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
                }
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
    if (!expert_) {
        bool playerWantsToClaim = askYesNo("Would you like to claim a border?");
        while (playerWantsToClaim) {
            std::cout << "Please enter the index of the border you want to claim:\n";

            unsigned int border_index = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
            try {
                //board_->getBorderByID(border_index2).claim();
            } catch (const BorderException &e) {
                std::cout << e.what() << '\n';
            }
        }
    }

    drawCard(player);
    pause(2);
}

void Game::playAIBasic(Player* computer) {
    int card_index = rand() % computer->getNumber_of_cards();
    unsigned int border_index;

    do {
        border_index = rand() % board_->getNumberBorder();
    } while (board_->getBorderByID(border_index).isClaimed());

    if (expert_) {
        for (unsigned int j = 0; j < board_->getNumberBorder(); j++) {
            if (board_->getBorderByID(j).getPlayerCombination(player1_.get()).getNumberCards() >= 3 && board_->getBorderByID(j).getPlayerCombination(player2_.get()).getNumberCards() >= 3)
            {
                if (board_->getBorderByID(j).getPlayerCombination(computer) == bestCombination(board_->getBorderByID(j).getPlayerCombination(computer),board_->getBorderByID(j).getPlayerCombination(player2_.get())))
                {
                    //board_->getBorderByID(j).claim(computer, clanDeck_.get(), tacticDeck_.get());
                }
            }
        }
    }

    std::cout << computer->getName() << " is playing the card " << computer->displayCard(card_index) << " on border " << border_index << ".\n";
    computer->play_card(card_index, border_index, board_.get());
    std::cout << *board_ << '\n';

    if (!expert_) {
        if (board_->getBorderByID(border_index).getPlayerCombination(player1_.get()).getNumberCards() >= 3 && board_->getBorderByID(border_index).getPlayerCombination(player2_.get()).getNumberCards() >= 3)
        {
            if (board_->getBorderByID(border_index).getPlayerCombination(computer) == bestCombination(board_->getBorderByID(border_index).getPlayerCombination(computer),board_->getBorderByID(border_index).getPlayerCombination(player2_.get())))
            {
                //board_->getBorderByID(border_index).claim(computer, clanDeck_.get(), tacticDeck_.get());
            }
        }
    }

    std::cout << computer->getName() << " is drawing a card.\n";
    bool playerHasDrawn = false;
    if (tacticVersion_ && !tacticDeck.isEmpty()) {
        int answer = rand() % 2;
        if (answer == 1) {
            try {
                computer->draw_card(tacticDeck);
                playerHasDrawn = true;
            } catch (const PlayerException& e) {
                std::cout << "Error: " << e.what() << std::endl;
                return;
            }
        }
    }

    if (!playerHasDrawn && !clanDeck.isEmpty()) {
        try {
            computer->draw_card(clanDeck);
        } catch (const PlayerException& e) {
            std::cout << "Error: " << e.what() << std::endl;
            return;
        }
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
        play(player1_.get());

        pause(2);

        if (board_.get()->hasWinner() != nullptr) {
            std::cout << "Player " << board_.get()->hasWinner()->getName() << " won!\n";
            Player * winner = board_.get()->hasWinner() ;
            Player * looser;
            (player1_.get()!=board_.get()->hasWinner()) ? looser = player1_.get() : looser = player2_.get();
            winner->newScore(5);
            looser->newScore(winner->getClaimed_borders().size());
            break;
        }

        pause(5);

        std::cout << player2_->getName() << " is playing...\n";
        if (tacticVersion_) {
            playAIBasic(static_cast<AI*>(player2_.get()));
        } else {
            // playAI(static_cast<AI*>(player2_.get()));
            playAIBasic(static_cast<AI*>(player2_.get()));

        }

        std::cout << player2_->getName() << " is playing...\n";
        if (board_.get()->hasWinner() != nullptr) {
            std::cout << "Player " << board_.get()->hasWinner()->getName() << " won!\n";
            Player * winner = board_.get()->hasWinner() ;
            Player * looser;
            (player1_.get()!=board_.get()->hasWinner()) ? looser = player1_.get() : looser = player2_.get();
            winner->newScore(5);
            looser->newScore(winner->getClaimed_borders().size());
            break;
        }
        pause(3);
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

    cout << "Card obtained: " << player->displayCard(player->getNumber_of_cards() - 1) << '\n';
    std::cout << "New hand: " << player->displayHand() << '\n';
}

void Game::pause(int n) {
    std::this_thread::sleep_for(std::chrono::seconds(n));
}

void Game::quit() {
    gameOver = true;
}

void clearScreen() {
    cout << "\033c";
}
