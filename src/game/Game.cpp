#include "Game.h"

Game::Game() : gameOver_(false), player1_(nullptr), player2_(nullptr) {
    launchSchottenTotten1();
}

void Game::setGameVersion() {
    onWindows_ = askYesNo("Are you playing on Windows? (for the pause system)");
    std::cout << "Which version do you want to play? [1] Classic | [2] Tactic\n";
    int version = askValue({1, 2});
    tacticVersion_ = (version == 2);
    expert_ = askYesNo("Do you want to play the expert version ?");
}

void Game::launchSchottenTotten1() {
    setGameVersion();
    bool AIvsAI = askYesNo("Game AI vs AI");
    if (AIvsAI) {
//        gameAIvsAI();
        create_AI(1);
        create_AI(2);
    } else {
        create_player(1);
        bool playAgainstAI = askYesNo("Do you want to play against the AI?");
        if (playAgainstAI) {
            create_AI(2);
//            while (!GameOver(numberWonRound)) {
//                roundAI();
//            }
        } else {
            create_player(2);
        }
    }
    cout << "How many rounds do you want to play? \n";
    int numberWonRound = askValue({1, 15});

//    bool playAgainstAI = askYesNo("Do you want to play against the AI?");
//    if (playAgainstAI) {
//        create_AI(2);
//        while (!GameOver(numberWonRound)) {
//            roundAI();
//        }
//    } else {
//        create_player(2);
    std::cout << "Start of the round\n";
    int i = 0;
    while (!GameOver(numberWonRound))  {
        round(++i);
    }
//    }
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

void Game::create_AI(int id) {
    std::cout << "The AI will be Player " << id << ", please enter the AI name:\n";
    std::string name;
    std::cin >> name;
    int maxPlayerCard = (tacticVersion_) ? 7 : 6;
    if (id == 1) {
        player1_ = std::make_unique<AI>(name, id, maxPlayerCard);
    } else {
        player2_ = std::make_unique<AI>(name, id, maxPlayerCard);
    }
}

void Game::create_deck() {
    DeckFactory deckFactory;
    clanDeck_ = deckFactory.createClanDeck();
    clanDeck_.shuffle();
    deckInfo_ = deckFactory.getDeckInfo();
    if (tacticVersion_) {
        tacticDeck_ = deckFactory.createTacticDeck();
        tacticDeck_.shuffle();
        discardDeck_.clear();
    }
}

void Game::create_board() {
    board_ = std::make_unique<Board>(9, player1_.get(), player2_.get());
    // Initialization of GameTracker Singleton
    GameTracker::getInstance(player1_.get(), player2_.get());
    if (tacticVersion_) {
        TacticHandler::getInstance(&clanDeck_, &deckInfo_, &tacticDeck_, &discardDeck_, board_.get());
    }
}


void Game::round(int numberRound) {
    create_deck();
    create_board();
    player1_->fillHand(clanDeck_);
    player2_->fillHand(clanDeck_);

    std::cout << "Start of the round " << numberRound << "\n";
    bool roundOver = false;
    hasClaimed_ = false;
    while (!roundOver) {
        play(player1_.get());
        if (hasClaimed_){
            hasClaimed_ = false;
           if(board_->hasWinner()){
               roundOver = true;
               break;
           }
        }
        std::cout << "Player " << player2_->getName() << "'s turn\n";
        play(player2_.get());
        if (hasClaimed_){
            hasClaimed_ = false;
            if(board_->hasWinner()){
                roundOver = true;
                break;
            }
        }
    }
    Player* winner = board_->getWinner();
    Player* opponent = GameTracker::getInstance().getOpponent(winner);
    cout << "Round " << numberRound << " is over and the winner is " << *winner << "!! \n";
    winner->newScore(5);
    opponent->newScore(winner->getClaimed_borders().size());
    std::cout << "End of the round \n";
    cout << "Current scores :\n";
    cout << winner->print_player();
    cout << opponent->print_player();
    pause();
    bool answer = askPlayerYesNo(winner, "Do you want to quit the game?");
    if (answer) quit();
}

void Game::play(Player* player) {
    clearScreen();
    std::cout << "Player " << player->getName() << ", it's your turn!\n";
    cout << board_->str() << '\n';
    cout << player->displayHand() << '\n';

    if (expert_)
        claim(player);

    bool canPlayCard = false;
    for (size_t i = 0; i < board_->getNumberBorder(); i++) {
        if (!board_->getBorderByID(i).getPlayerCombination(player).isComplete()) {
            canPlayCard = true;
            break;
        }
    }

    if (!player->hasValuedCard() || !canPlayCard) {
        bool playerWantsToPass = askYesNo("Do you want to pass your turn?\n");
        if (playerWantsToPass) {
            draw_card(player);
            return;
        }
    }
    if (player->getNumber_of_cards() > 0) {
        std::cout << "Please enter the index of the card you want to play:\n";
        int card_index = askPlayerValue(player, {0, player->getNumber_of_cards() - 1});
        int border_index ;
        if(player->getCardAtIndex(card_index)->isRuse()) border_index=0;
        else
            border_index = this->chooseBorder("Please enter the index of the border you want to play on:\n", player);

        player->play_card(card_index, border_index, board_.get());
        std::cout << *board_ << '\n';
    }

    if (!expert_)
        claim(player);
    draw_card(player);
    cout << "\n Good turn \n STOP LOOKING AT THE SCREEN " << player->getName()<< "!!!\n";
//    pause();
}

void Game::claim(Player* player){
    bool playerWantsToClaim = askPlayerYesNo(player,"Do you want to claim a border?");
    if (playerWantsToClaim) {
        bool claimed =  true;
        int borderIndex;
        do {
            claimed =  true;
            std::cout << "Please enter the index of the border you want to claim:\n";
            borderIndex = askPlayerValue(player, {0, board_->getNumberBorder() -1});
            Border& borderSelected = board_->getBorderByID(borderIndex);
            if (!borderSelected.isClaimed())
                claimed = false;
        } while (claimed);

        hasClaimed_ = board_->getBorderByID(borderIndex).claim(player);
    }
}

size_t Game::chooseBorder(const string& text, Player* player){
    bool claimed =  true;
    bool playerHasMaxCards = true;
    size_t borderIndex;
    do {
        claimed =  true;
        playerHasMaxCards = true;
        cout << text << '\n';
        borderIndex = askPlayerValue(player, {0, board_->getNumberBorder() -1});
        Border& borderSelected = board_->getBorderByID(borderIndex);
        if (!borderSelected.isClaimed())
            claimed = false;
        Combination& combination = borderSelected.getPlayerCombination(player);
        if (!combination.isComplete())
            playerHasMaxCards = false;
    } while (claimed || playerHasMaxCards);
    return borderIndex;
}

void Game::draw_card(Player* player) {
    std::cout << "Drawing a card\n";
    bool playerHasDrawn = false;

    if (tacticVersion_) {
        std::cout << "From which deck do you want to draw?\n";
        std::cout << "[0] Normal Deck (" << clanDeck_.getNumberRemainingCards() << " cards remaining)\n";
        std::cout << "[1] Tactic Deck (" << tacticDeck_.getNumberRemainingCards() << " cards remaining)\n";
        int answer = askPlayerValue(player, {0, 1});
        if (answer == 1) {
            if (tacticDeck_.isEmpty()) {
                std::cout << "The tactic Deck is empty!\n";
            } else {
                player->draw_card(tacticDeck_);
                playerHasDrawn = true;
            }
        }
    }

    if (!playerHasDrawn) {
        if (clanDeck_.isEmpty()) {
            std::cout << "The clan Deck is empty!\n";
            return;
        } else {
            player->draw_card(clanDeck_);
        }
    }
    std::cout << "Card drawn :"  << player->displayCard(player->getNumber_of_cards() - 1) << '\n';
    std::cout << "New hand: " << player->displayHand() << '\n';
}

void Game::quit() {
    gameOver_ = true;
}

void Game::clearScreen() {
    std::cout << "\033c";
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}
void Game::pause() {
    if (onWindows_) system("pause");
    else system("read");
}

bool Game::GameOver(int nbRound)
{
    return gameOver_ = ((player1_->getScore()) == nbRound * 5) || ((player2_->getScore()) == nbRound * 5);
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
                        board_->getBorderByID(j).claim(computer);
                    }
                }}
        }
    }

    std::cout << computer->getName() << " is playing the card " << computer->displayCard(card_index) << " on border " << border_index << ".\n";
    computer->play_card(card_index, border_index, board_.get());
    std::cout << *board_ << '\n';

    std::cout << computer->getName() << " is drawing a card.\n";
    bool playerHasDrawn = false;
    if (tacticVersion_ && !tacticDeck_.isEmpty()) {
        int answer = rand() % 2;
        if (answer == 1) {
            try {
                if (computer->getNumber_of_cards() < 7){
                    computer->draw_card(tacticDeck_);
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
                    board_->getBorderByID(border_index).claim(computer);
                }
            }
        }}

    if (!playerHasDrawn && !clanDeck_.isEmpty()) {
        try {if (computer->getNumber_of_cards() < 7) {
                computer->draw_card(clanDeck_);
            }} catch (const PlayerException& e) {
            std::cout << "Error: " << e.what() << std::endl;
            return;
        }
    }
}

//void Game::playAI(AI* computer, Player* opponent, GameTracker& gameTracker) {
//    if (expert_) {
//        for (unsigned int j = 0; j < board_->getNumberBorder(); j++) {
//            if (board_->getBorderByID(j).getPlayerCombination(player1_.get()).getNumberCards() >= 3 &&
//                board_->getBorderByID(j).getPlayerCombination(player2_.get()).getNumberCards() >= 3) {
//                if (board_->getBorderByID(j).getPlayerCombination(computer) ==
//                    bestCombination(board_->getBorderByID(j).getPlayerCombination(computer),
//                                    board_->getBorderByID(j).getPlayerCombination(player2_.get()))) {
//                    try {
//                        board_->getBorderByID(j).claim(computer);
//                    } catch (const BorderException &e) {
//                        std::cout << e.what() << '\n';
//                    }
//                }
//            }
//        }
//    }
//    unsigned int border_index = computer->pick_a_border(board_.get());
//    Border* selected_border = &board_->getBorderByID(border_index);
//    unsigned int card_index = computer->pick_a_card(selected_border);
//    std::cout << computer->getName() << " is playing the card " << computer->displayCard(card_index) << " on border " << border_index << ".\n";
//
//    computer->play_card(card_index, border_index, board_.get());
//    std::cout << computer->getName() << " is playing the card " << computer->displayCard(card_index) << " on border " << border_index << ".\n";
//    if (!expert_){
//        border_index = computer->claim_a_border(board_.get(), player1_.get());
//        if (border_index != 0) {
//            std::cout << computer->getName() << " is claiming border " << border_index << ".\n";
//            try {
//                board_->getBorderByID(border_index).claim(computer);
//            } catch (const BorderException &e) {
//                std::cout << e.what() << '\n';
//            }
//        }
//    }
//
//    std::cout << computer->getName() << " is drawing a card.\n";
//    bool playerHasDrawn = false;
//    if (tacticVersion_ && !tacticDeck_.isEmpty()) {
//        int answer = rand() % 2;
//        if (answer == 1) {
//            computer->draw_card(tacticDeck_);
//            playerHasDrawn = true;
//        }
//    }
//
//    if (!playerHasDrawn && !clanDeck_.isEmpty()) {
//        computer->draw_card(clanDeck_);
//    }
//}
//
//void Game::roundAI() {
//    create_deck();
//    create_board();
//    GameTracker& gameTracker = GameTracker::getInstance();
//    player1_->fillHand(clanDeck_);
//    player2_->fillHand(clanDeck_);
//
//    std::cout << "Start of the game\n";
//
//    while (board_->hasWinner() == nullptr) {
//        std::cout << "It's your turn, " << player1_->getName() << "!\n";
//        play(player1_.get());
//        clearScreen();
//        pause(2);
//        if (board_->hasWinner() != nullptr) {
//            std::cout << "Player " << board_->hasWinner()->getName() << " won!\n";
//            Player *winner = board_->hasWinner();
//            Player *looser = (player1_.get() != board_->hasWinner()) ? player1_.get() : player2_.get();
//            winner->newScore(5);
//            looser->newScore(winner->getClaimed_borders().size());
//            break;
//        }
//
//        clearScreen();
//
//        std::cout << "It's your turn, " << player2_->getName() << "!\n";
//        if (basic_) playAIBasic(dynamic_cast<AI *>(player2_.get()), player1_.get(), gameTracker);
//        else playAI(dynamic_cast<AI *>(player2_.get()), player1_.get(), gameTracker);
//        pause(2);
//        if (board_->hasWinner() != nullptr) {
//            std::cout << "Player " << board_->hasWinner()->getName() << " won!\n";
//            Player *winner = board_->hasWinner();
//            Player *looser = (player1_.get() != board_->hasWinner()) ? player1_.get() : player2_.get();
//            winner->newScore(5);
//            looser->newScore(winner->getClaimed_borders().size());
//            break;
//        }
//        clearScreen();
//        pause(3);
//    }
//
//    std::cout << "End of the round\n";
//    quit();
//}
//void Game::gameAIvsAI() {
//
//    std::cout << "Enter a name for AI player 1:\n";
//    std::string name1;
//    std::cin >> name1;
//    name1 += " AI";
//    int maxPlayerCard = (tacticVersion_) ? 7 : 6;
//    player1_ = std::make_unique<AI>( name1, 1, maxPlayerCard);
//
//    std::cout << "Enter a name for AI player 2:\n";
//    std::string name2;
//    std::cin >> name2;
//    name2 += " AI";
//    player2_ = std::make_unique<AI>( name2, 2, maxPlayerCard);
//    create_deck();
//    create_board();
//    GameTracker& gameTracker = GameTracker::getInstance();
//    player1_->fillHand(clanDeck_);
//    player2_->fillHand(clanDeck_);
//    std::cout << "Start of the game\n";
//    std::cout << "How many rounds ?\n";
//    int numberRound = askValue({1, 15});
//
//    while(!GameOver(numberRound)){
//        while (board_->hasWinner() == nullptr) {
//
//            std::cout << "It is the turn of " << player1_->getName() << "!\n";
//            playAIBasic(static_cast<AI*>(player1_.get()), player2_.get(), gameTracker);
//            pause(2);
//            if (board_->hasWinner() != nullptr) {
//                std::cout << "Player " << board_->hasWinner()->getName() << " won!\n";
//                Player *winner = board_->hasWinner();
//                Player *looser = (player1_.get() != board_->hasWinner()) ? player1_.get() : player2_.get();
//                winner->newScore(5);
//                looser->newScore(winner->getClaimed_borders().size());
//                break;
//            }
//            std::cout << "It is the turn of " << player2_->getName() << "!\n";
//            playAIBasic(static_cast<AI*>(player2_.get()), player1_.get(), gameTracker);
//            pause(2);
//            if (board_->hasWinner() != nullptr) {
//                std::cout << "Player " << board_->hasWinner()->getName() << " won!\n";
//                Player *winner = board_->hasWinner();
//                Player *looser = (player1_.get() != board_->hasWinner()) ? player1_.get() : player2_.get();
//                winner->newScore(5);
//                looser->newScore(winner->getClaimed_borders().size());
//                break;
//            }
//
//        }
//        clearScreen();
//        create_deck();
//        create_board();
//        player1_->fillHand(clanDeck_);
//        player2_->fillHand(clanDeck_);
//    }
//    if (player1_->getScore()>player2_->getScore()) std::cout << player1_->getName()<< "won ! \n" ;
//    else std::cout << player2_->getName()<< "won the game! \n" ;
//    std::cout << "End of the game\n";
//    quit();
//}
//
