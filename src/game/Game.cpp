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
        int numberWonRound = askValue({1, 15});

        bool playAgainstAI = askYesNo("Do you want to play against the AI?");
        if (playAgainstAI) {
            create_AI();
            while (!GameOver(numberWonRound)) {
                roundAI();
            }
        } else {
            create_player(2);
            while (!GameOver(numberWonRound))  {
                round();
            }
        }
    }

    if (player1_->getScore() > player2_->getScore()) {
        std::cout << player1_->getName() << " won the game\n";
    } else {
        std::cout << player2_->getName() << " won the game\n";
    }
}

void Game::create_player(int id) {
    if (id == 1) {
        std::cout << "The one who traveled near Scotland most recently is player 1.\n";
    }
    std::cout << "Player " << id << ", please enter your name:\n";
    std::string name;
    std::cin >> name;
    int maxPlayerCard = (tacticVersion_) ? 7 : 6;
    if (id == 1) {
        player1_ = std::make_unique<Player>(name, id, maxPlayerCard);
    } else {
        player2_ = std::make_unique<Player>(name, id, maxPlayerCard);
    }
}

void Game::gameAIvsAI() {

    std::cout << "Enter a name for AI player 1:\n";
    std::string name1;
    std::cin >> name1;
    name1 += " AI";
    int maxPlayerCard = (tacticVersion_) ? 7 : 6;
    player1_ = std::make_unique<AI>( name1, 1, maxPlayerCard);

    std::cout << "Enter a name for AI player 2:\n";
    std::string name2;
    std::cin >> name2;
    name2 += " AI";
    player2_ = std::make_unique<AI>( name2, 2, maxPlayerCard);
    create_deck();
    create_board();
    GameTracker& gameTracker = createGameTracker();
    player1_->fillHand(clanDeck);
    player2_->fillHand(clanDeck);
    std::cout << "Start of the game\n";
    std::cout << "How many rounds ?\n";
    int numberRound = askValue({1, 15});

    while(!GameOver(numberRound)){
        while (board_->hasWinner() == nullptr) {

            std::cout << "It is the turn of " << player1_->getName() << "!\n";
            playAIBasic(static_cast<AI*>(player1_.get()), player2_.get(), gameTracker);
            pause(2);
            if (board_->hasWinner() != nullptr) {
                std::cout << "Player " << board_->hasWinner()->getName() << " won!\n";
                Player *winner = board_->hasWinner();
                Player *looser = (player1_.get() != board_->hasWinner()) ? player1_.get() : player2_.get();
                winner->newScore(5);
                looser->newScore(winner->getClaimed_borders().size());
                break;
            }
            std::cout << "It is the turn of " << player2_->getName() << "!\n";
            playAIBasic(static_cast<AI*>(player2_.get()), player1_.get(), gameTracker);
            pause(2);
            if (board_->hasWinner() != nullptr) {
                std::cout << "Player " << board_->hasWinner()->getName() << " won!\n";
                Player *winner = board_->hasWinner();
                Player *looser = (player1_.get() != board_->hasWinner()) ? player1_.get() : player2_.get();
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
    if (player1_->getScore()>player2_->getScore()) std::cout << player1_->getName()<< "won ! \n" ;
    else std::cout << player2_->getName()<< "won the game! \n" ;
    std::cout << "End of the game\n";
    quit();
}

void Game::create_AI() {
    std::cout << player1_->getName() << ", please enter a name for the AI opponent:\n";
    std::string name;
    std::cin >> name;
    name += " AI";
    int maxPlayerCard = (tacticVersion_) ? 7 : 6;
    player2_ = std::make_unique<AI>( name, 2, maxPlayerCard);
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
    if (tacticVersion_) {
        TacticHandler::getInstance(&clanDeck, &deckInfo, &tacticDeck, &discardDeck, board_.get());
    }
}

GameTracker& Game::createGameTracker(){
    GameTracker& gameTracker = GameTracker::getInstance();
    return gameTracker;
}

void Game::round() {
    create_deck();
    create_board();
    GameTracker& gameTracker = createGameTracker();
    player1_->fillHand(clanDeck);
    player2_->fillHand(clanDeck);

    std::cout << "Start of the game\n";

    while (board_->hasWinner() == nullptr) {
        std::cout << "Player " << player1_->getName() << ", it's your turn!\n";
        play(player1_.get(), player2_.get(), gameTracker);
        clearScreen();
        pause(2);
        if (board_->hasWinner() != nullptr) {
            std::cout << "Player " << board_->hasWinner()->getName() << " won!\n";
            Player *winner = board_->hasWinner();
            Player *looser = (player1_.get() != board_->hasWinner()) ? player1_.get() : player2_.get();
            winner->newScore(5);
            looser->newScore(winner->getClaimed_borders().size());
            break;
        }
        std::cout << "Player " << player2_->getName() << "'s turn\n";
        play(player2_.get(), player1_.get(), gameTracker);
        clearScreen();
        if (board_->hasWinner() != nullptr) {
            std::cout << "Player " << board_->hasWinner()->getName() << " won!\n";
            Player *winner = board_->hasWinner();
            Player *looser = (player1_.get() != board_->hasWinner()) ? player1_.get() : player2_.get();
            winner->newScore(5);
            looser->newScore(winner->getClaimed_borders().size());
            break;
        }
        pause(2);
    }

    std::cout << "End of the round \n";
    quit();
}

void Game::roundAI() {
    create_deck();
    create_board();
    GameTracker& gameTracker = createGameTracker();
    player1_->fillHand(clanDeck);
    player2_->fillHand(clanDeck);

    std::cout << "Start of the game\n";

    while (board_->hasWinner() == nullptr) {
        std::cout << "It's your turn, " << player1_->getName() << "!\n";
        play(player1_.get(), player2_.get(),gameTracker );
        clearScreen();
        pause(2);
        if (board_->hasWinner() != nullptr) {
            std::cout << "Player " << board_->hasWinner()->getName() << " won!\n";
            Player *winner = board_->hasWinner();
            Player *looser = (player1_.get() != board_->hasWinner()) ? player1_.get() : player2_.get();
            winner->newScore(5);
            looser->newScore(winner->getClaimed_borders().size());
            break;
        }

        clearScreen();

        std::cout << "It's your turn, " << player2_->getName() << "!\n";
        if (basic_) playAIBasic(dynamic_cast<AI *>(player2_.get()), player1_.get(), gameTracker);
        else playAI(dynamic_cast<AI *>(player2_.get()), player1_.get(), gameTracker);
        pause(2);
        if (board_->hasWinner() != nullptr) {
            std::cout << "Player " << board_->hasWinner()->getName() << " won!\n";
            Player *winner = board_->hasWinner();
            Player *looser = (player1_.get() != board_->hasWinner()) ? player1_.get() : player2_.get();
            winner->newScore(5);
            looser->newScore(winner->getClaimed_borders().size());
            break;
        }
        clearScreen();
        pause(3);
    }

    std::cout << "End of the round\n";
    quit();
}
void Game::playAIBasic(AI* computer, Player* opponent, GameTracker& gameTracker) {
    AI* ai = dynamic_cast<AI*>(computer);
    if (ai == nullptr) {
        return;
    }
    computer->displayHand();
    int card_index = rand() % computer->getNumber_of_cards();

    while (typeid(computer->getCardAtIndex(card_index))== typeid(TacticCard) && !gameTracker.canPlayTacticCard(computer)) {
        card_index = rand() % computer->getNumber_of_cards();
    }

    unsigned int border_index;
    if (computer->getCardAtIndex(card_index)) border_index = 0;
    else {
        do {
            border_index = rand() % board_->getNumberBorder();
        } while (board_->getBorderByID(border_index).isClaimed() ||
                 board_->getBorderByID(border_index).getPlayerCombination(computer).getNumberCards() ==
                 board_->getBorderByID(border_index).getPlayerCombination(computer).getMaxNumberCards());
    }
    if (expert_) {
        for (unsigned int j = 0; j < board_->getNumberBorder(); j++) {
            if (!board_->getBorderByID(j).isClaimed()){
            if (board_->getBorderByID(j).getPlayerCombination(player1_.get()).getNumberCards() == board_->getBorderByID(j).getPlayerCombination(player1_.get()).getMaxNumberCards() && board_->getBorderByID(j).getPlayerCombination(player2_.get()).getNumberCards() == board_->getBorderByID(j).getPlayerCombination(player1_.get()).getMaxNumberCards()) {
                if (board_->getBorderByID(j).getPlayerCombination(computer) == bestCombination(board_->getBorderByID(j).getPlayerCombination(computer), board_->getBorderByID(j).getPlayerCombination(opponent))) {
                    board_->getBorderByID(j).claim(computer, opponent, gameTracker);
                }
            }}
        }
    }

    std::cout << computer->getName() << " is playing the card " << computer->displayCard(card_index) << " on border " << border_index << ".\n";
    computer->play_card(card_index, border_index, board_.get());
    std::cout << *board_ << '\n';

    std::cout << computer->getName() << " is drawing a card.\n";
    bool playerHasDrawn = false;
    if (tacticVersion_ && !tacticDeck.isEmpty()) {
        int answer = rand() % 2;
        if (answer == 1) {
            try {
                if (computer->getNumber_of_cards() < 7){
                computer->draw_card(tacticDeck);
                playerHasDrawn = true;
            }
            } catch (const PlayerException& e) {
                std::cout << "Error: " << e.what() << std::endl;
                return;
            }
        }
    }

    if (!expert_) {
        if (!board_->getBorderByID(border_index).isClaimed()){
        if (board_->getBorderByID(border_index).getPlayerCombination(player1_.get()).getNumberCards() == board_->getBorderByID(border_index).getPlayerCombination(player1_.get()).getMaxNumberCards() && board_->getBorderByID(border_index).getPlayerCombination(player2_.get()).getNumberCards() == board_->getBorderByID(border_index).getPlayerCombination(player1_.get()).getMaxNumberCards()) {
            if (board_->getBorderByID(border_index).getPlayerCombination(computer) == bestCombination(board_->getBorderByID(border_index).getPlayerCombination(computer), board_->getBorderByID(border_index).getPlayerCombination(opponent))) {
                board_->getBorderByID(border_index).claim(computer, opponent, gameTracker);
            }
        }
    }}

    if (!playerHasDrawn && !clanDeck.isEmpty()) {
        try {if (computer->getNumber_of_cards() < 7) {
                computer->draw_card(clanDeck);
            }} catch (const PlayerException& e) {
            std::cout << "Error: " << e.what() << std::endl;
            return;
        }
    }
}

void Game::playAI(AI* computer, Player* opponent, GameTracker& gameTracker) {
    if (expert_) {
        for (unsigned int j = 0; j < board_->getNumberBorder(); j++) {
            if (board_->getBorderByID(j).getPlayerCombination(player1_.get()).getNumberCards() >= 3 &&
                board_->getBorderByID(j).getPlayerCombination(player2_.get()).getNumberCards() >= 3) {
                if (board_->getBorderByID(j).getPlayerCombination(computer) ==
                    bestCombination(board_->getBorderByID(j).getPlayerCombination(computer),
                                    board_->getBorderByID(j).getPlayerCombination(player2_.get()))) {
                    try {
                        board_->getBorderByID(j).claim(computer, opponent, gameTracker);
                    } catch (const BorderException &e) {
                        std::cout << e.what() << '\n';
                    }
                }
            }
        }
    }
    unsigned int border_index = computer->pick_a_border(board_.get());
    Border* selected_border = &board_->getBorderByID(border_index);
    unsigned int card_index = computer->pick_a_card(selected_border);
    std::cout << computer->getName() << " is playing the card " << computer->displayCard(card_index) << " on border " << border_index << ".\n";

    computer->play_card(card_index, border_index, board_.get());
    std::cout << computer->getName() << " is playing the card " << computer->displayCard(card_index) << " on border " << border_index << ".\n";
    if (!expert_){
        border_index = computer->claim_a_border(board_.get(), player1_.get());
        if (border_index != 0) {
            std::cout << computer->getName() << " is claiming border " << border_index << ".\n";
            try {
                board_->getBorderByID(border_index).claim(computer, opponent, gameTracker);
            } catch (const BorderException &e) {
                std::cout << e.what() << '\n';
            }
        }
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

void Game::play(Player* player, Player* opponent, GameTracker& gameTracker) {
    clearScreen();
    cout << board_->str() << '\n';
    cout << player->displayHand() << '\n';
    if (expert_) {
        bool playerWantsToClaim = askYesNo("Would you like to claim a border?");
        if (playerWantsToClaim) {
            std::cout << "Please enter the index of the border you want to claim:\n";

            unsigned int border_index = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
            try {
                board_->getBorderByID(border_index).claim(player, opponent, gameTracker);
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
        bool playerWantsToPass = askYesNo("Do you want to pass your turn?\n");
        if (playerWantsToPass) {
            std::cout << "Please enter the index of the card you want to pick:\n";
            int card_index = askPlayerValue(player, {0, player->getNumber_of_cards() - 1});
            int border_index;
            if (player->getCardAtIndex(card_index)->isRuse()) {
                border_index = 0;
            } else {
                std::cout << "Please enter the index of the border you want to pick:\n";
                border_index = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
                while (board_->getBorderByID(border_index).isClaimed()) {
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
        int border_index ;
        if(player->getCardAtIndex(card_index)->isRuse()) border_index=-1;
        else {
            std::cout << "Please enter the index of the border you want to play on:\n";
            border_index = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
            while (board_->getBorderByID(border_index).isClaimed()) {
                std::cout << "The border is already claimed. Please enter a different index:\n";
                border_index = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
            }
        }


        player->play_card(card_index, border_index, board_.get());
        std::cout << *board_ << '\n';
    }

    if (!expert_) {
        bool playerWantsToClaim = askYesNo("Do you want to claim a border?");
        if (playerWantsToClaim) {
            std::cout << "Please enter the index of the border you want to claim:\n";

            unsigned int border_index = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
            try {
                board_->getBorderByID(border_index).claim(player, opponent, gameTracker);
            } catch (const BorderException &e) {
                std::cout << e.what() << '\n';
            }
        }
    }

    draw_card(player);
}

void Game::draw_card(Player* player) {
    std::cout << "Drawing a card\n";
    bool playerHasDrawn = false;

    if (tacticVersion_) {
        std::cout << "From which deck do you want to draw?\n";
        std::cout << "[0] Normal Deck (" << clanDeck.getNumberRemainingCards() << " cards remaining)\n";
        std::cout << "[1] Tactic Deck (" << tacticDeck.getNumberRemainingCards() << " cards remaining)\n";
        int answer = askPlayerValue(player, {0, 1});
        if (answer == 1) {
            if (tacticDeck.isEmpty()) {
                std::cout << "The tactic Deck is empty!\n";
            } else {
                player->draw_card(tacticDeck);
                playerHasDrawn = true;
            }
        }
    }

    if (!playerHasDrawn) {
        if (clanDeck.isEmpty()) {
            std::cout << "The clan Deck is empty!\n";
        } else {
            player->draw_card(clanDeck);
        }
    }

    std::cout << "New hand: " << player->displayHand() << '\n';
}

void Game::quit() {
    gameOver = true;
}

void Game::clearScreen() {
    std::cout << "\033c";
}
void Game::pause(int n) {
    //std::cout << "Pause de 30 secondes...\n";
    std::this_thread::sleep_for(std::chrono::seconds(n));
    //std::cout << "Reprise de la partie\n";
}

bool Game::GameOver(int nbRound)
{
    return gameOver = ((player1_->getScore()) == nbRound*5) ||  ((player2_->getScore()) == nbRound*5);

}
