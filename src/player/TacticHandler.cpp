#include "TacticHandler.h"

TacticHandler::TacticHandler(Deck *normalDeck, DeckInfo *normalDeckInfo, Deck *tacticDeck, Deck *discardDeck, Board *board):
        normalDeck_(normalDeck),
        normalDeckInfo_(normalDeckInfo),
        tacticDeck_(tacticDeck),
        discardDeck_(discardDeck),
        board_(board){}


TacticHandler &TacticHandler::getInstance(Deck *normalDeck, DeckInfo* normalDeckInfo, Deck *tacticDeck, Deck *discardDeck, Board *board) {
    static unique_ptr<TacticHandler> instance (new TacticHandler(normalDeck, normalDeckInfo, tacticDeck, discardDeck, board));

    bool no_argument = !normalDeck && !tacticDeck && !discardDeck && !board;
    if (no_argument)
        return *instance;

    bool different_instance = instance->normalDeck_ != normalDeck && instance->normalDeckInfo_ != normalDeckInfo && instance->tacticDeck_ != tacticDeck &&
            instance->discardDeck_ != discardDeck && instance->board_ != board;
    if (different_instance)
        instance.reset(new TacticHandler(normalDeck, normalDeckInfo, tacticDeck, discardDeck, board));

    bool emptyInstance = !instance->normalDeck_ && !instance->normalDeckInfo_ && !instance->tacticDeck_ && !instance->discardDeck_ && !instance->board_;
    if (emptyInstance)
        throw TacticHandlerException("Returning an empty instance of TacticHandler (not initialized)");

    return *instance;
}


void TacticHandler::playTacticCard(unique_ptr<TacticCard> tacticCard, Player *player, int borderID) {
    TacticType type = tacticCard->getName();
    bool isEliteTroop = type == TacticType::joker || type == TacticType::spy || type == TacticType::shield_bearer;
    if (isEliteTroop)
        this->playEliteTroop(std::move(tacticCard), player, borderID);
    if (type == TacticType::blind_man_bluff) this->playBlindManBluff(borderID);
    if (type == TacticType::mud_fight) this->playMudFight(borderID);
    else if (tacticCard->isRuse())
    {
        discardDeck_->putCard(std::move(tacticCard));
        if (type == TacticType::recruiter) playRecruiter(player);
        if (type == TacticType::strategist) playStrategist(player);
        if (type == TacticType::banshee ) {
            if (board_->getPlayer(1) == player)
                playBanshee(player, board_->getPlayer(2) );
            else playBanshee(player, board_->getPlayer(1));

        }
        if (type == TacticType::traitor) {
            if (board_->getPlayer(1) == player)
                playTraitor(player, board_->getPlayer(2) );
            else playTraitor(player, board_->getPlayer(1));
        }
    }

// else if  || ||
//type  || ) {
//// Type de carte tactique non pris en charge, vous pouvez gérer l'erreur en conséquence
//throw PlayerException("Unsupported tactic card type");
}


void TacticHandler::playEliteTroop(unique_ptr<TacticCard> tacticCard, Player *player, int borderId) {
    board_->getBorderByID(borderId).addTacticalCard(std::move(tacticCard), player);
}


void TacticHandler::activeEliteTroop(unique_ptr<TacticCard> tacticCard, Combination* combination) {
    Player *player = combination->getPlayerID();
    TacticType tacticType = tacticCard->getName();
    int value;
    CardColor color;
    if (tacticType == TacticType::joker) {
        value = askPlayerValue(player, {normalDeckInfo_->max_card_value, normalDeckInfo_->max_card_value});
        color = askPlayerColor(player, normalDeckInfo_->number_colors);
    }
    if (tacticType == TacticType::shield_bearer){
        value = askPlayerValue(player, {1, 3});
        color = askPlayerColor(player, normalDeckInfo_->number_colors);
    }
    if (tacticType == TacticType::spy){
        value = 7;
        color = askPlayerColor(player, normalDeckInfo_->number_colors);
    }

    combination->push_back(std::make_unique<ValuedCard>(value, color));

}

void TacticHandler::playBlindManBluff(int borderId) {
    if (board_->getBorderByID(borderId).hasMudFight())
        throw TacticHandlerException("The stone is taken by MudFight");
    else
    board_->getBorderByID(borderId).setNoCombinationRules();
}


void TacticHandler::playMudFight(int borderId) {
    if (board_->getBorderByID(borderId).hasBlindManBluff())
        throw TacticHandlerException("The stone is taken by Blind Man Bluff");
    else
    board_->getBorderByID(borderId).setMaxNumberCard(4);
}

void TacticHandler::playRecruiter( Player* player) {

    std::cout << "Please pick a deck. [1] Clan Deck [2] Tactic Deck\n";
    int deck = askPlayerValue(player, {1, 2});

    std::cout << "Here's your current hand :\n";
    player->displayHand();

    if (deck == 1) {
        std::cout << "Drawing 3 cards from the Clan Deck...\n";
        for (int j = 0; j < 3; j++) {
            player->draw_card(*normalDeck_);
        }
    } else {
        std::cout << "Drawing 3 cards from the Tactic Deck...\n";
        for (int j = 0; j < 3; j++) {
            player->draw_card(*tacticDeck_);
        }
    }

    std::cout << "Here is your new hand after drawing:\n";
    player->displayHand();

    std::cout << "Please choose two cards from your hand to place under the corresponding deck.\n";
    player->displayHand();

    for (int i = 0; i < 2; i++) {
        std::cout << "Choose card " << (i+1) << ": ";
        int cardIndex = askPlayerValue(player, {player->getNumber_of_cards() - 3, player->getNumber_of_cards() - 1});
        Card* selectedCard = player->getCardAtIndex(cardIndex).get();
        player->remove_card_from_hand(cardIndex);

        if (deck == 1) {
            normalDeck_->putCard(std::unique_ptr<Card>(selectedCard));
        } else {
            tacticDeck_->putCard(std::unique_ptr<Card>(selectedCard));
        }
    }

    std::cout << "Cards placed under the decks.\n";
    std::cout << "Here is your final hand:\n";
    player->displayHand();
}
void TacticHandler::playStrategist(Player* player)
{
    std::vector<Card*> allCards;
    int index = 0;

    for (int i = 0; i < board_->getNumberBorder(); i++)
    {
        if (board_->getBorderByID(i).isClaimed()) continue;

        const auto& valuedCards = board_->getBorderByID(i).getPlayerCombination(player).getValuedCards();
        for (const auto& valuedCard : valuedCards) {
            allCards.push_back(valuedCard);
            std::cout << " [" << index++ << "] " << *valuedCard; // Utilisez *valuedCard pour afficher la carte
        }

        const auto& tacticCards = board_->getBorderByID(i).getPlayerCombination(player).getTacticCards();
        for (const auto& tacticCard : tacticCards) {
            allCards.push_back(tacticCard);
            std::cout << " [" << index++ << "] " << *tacticCard; // Utilisez *tacticCard pour afficher la carte
        }
    }

    std::cout << "Pick a card. Type the index of the card you would like to pick: ";
    int card = askPlayerValue(player, {0, index});
    const Card* selectedCard = allCards[card];
    discardDeck_->removeCard(selectedCard);
    int borderIndex;
    if (typeid(selectedCard) == typeid(ValuedCard)) {
        borderIndex = board_->findBorderIndexByValuedCard(*static_cast<const ValuedCard*>(selectedCard), player);
    } else {
        borderIndex = board_->findBorderIndexByTacticCard(*static_cast<const TacticCard*>(selectedCard), player);
    }

    board_->getBorderByID(borderIndex).getPlayerCombination(player).removeCardFromCombination(
            const_cast<Card *>(selectedCard));
    player->add_card_into_hand( unique_ptr<Card> (std::move(allCards[card])));
    std::cout << "Do you want to play it on a border [1] or to put it back in the deck [2] ?";
    int choice = askPlayerValue(player, {1,2});
    if (choice == 1)
    {
        std::cout << "Please enter the index of the border you want to pick:\n";
        int border_index = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
        while (board_->getBorderByID(border_index).isClaimed())
        {
            std::cout << "The border is already claimed. Please enter a different index:\n";
            border_index = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
        }
        player->play_card(player->getNumber_of_cards() - 1,border_index, board_ );
    }
    else {
        player->remove_card_from_hand(player->getNumber_of_cards() - 1);
        normalDeck_->addToSide( unique_ptr<Card> (std::move(allCards[card]))); // Utilisez std::move(allCards[card]) pour transférer la possession de la carte
    }
}

void TacticHandler::playBanshee(Player* player, Player* opponent)
{
    std::vector<Card*> allCards;
    int index = 0;

    for (int i = 0; i < board_->getNumberBorder(); i++)
    {
        if (board_->getBorderByID(i).isClaimed()) continue;

        const auto& valuedCards = board_->getBorderByID(i).getPlayerCombination(opponent).getValuedCards();
        for (const auto& valuedCard : valuedCards) {
            allCards.push_back(valuedCard);
            std::cout << " [" << index++ << "] " << *valuedCard; // Utilisez *valuedCard pour afficher la carte
        }

        const auto& tacticCards = board_->getBorderByID(i).getPlayerCombination(opponent).getTacticCards();
        for (const auto& tacticCard : tacticCards) {
            allCards.push_back(tacticCard);
            std::cout << " [" << index++ << "] " << *tacticCard; // Utilisez *tacticCard pour afficher la carte
        }
    }

    std::cout << "Pick a card. Type the index of the card you would like to pick: ";
    int card = askPlayerValue(player, {0, index});

    const Card* selectedCard = allCards[card];
    int borderIndex;
    if (typeid(selectedCard) == typeid(ValuedCard)) {
         borderIndex = board_->findBorderIndexByValuedCard(*static_cast<const ValuedCard*>(selectedCard), opponent);
    } else {
        borderIndex = board_->findBorderIndexByTacticCard(*static_cast<const TacticCard*>(selectedCard), opponent);
    }

    board_->getBorderByID(borderIndex).getPlayerCombination(opponent).removeCardFromCombination(
            const_cast<Card *>(selectedCard));


    // Supprimer la carte de la défausse
    discardDeck_->removeCard(selectedCard);

    // Ajouter la carte au deck normal
    normalDeck_->addToSide(std::unique_ptr<Card>(std::move(allCards[card]))); // Utilisez std::move(allCards[card]) pour transférer la possession de la carte
}


void TacticHandler::playTraitor(Player* player, Player* opponent)
{std::vector<Card*> allCards;
    int index = 0;

    for (int i = 0; i < board_->getNumberBorder(); i++)
    {
        if (board_->getBorderByID(i).isClaimed()) continue;

        const auto& valuedCards = board_->getBorderByID(i).getPlayerCombination(opponent).getValuedCards();
        for (const auto& valuedCard : valuedCards) {
            allCards.push_back(valuedCard);
            std::cout << " [" << index++ << "] " << *valuedCard; // Utilisez *valuedCard pour afficher la carte
        }

        const auto& tacticCards = board_->getBorderByID(i).getPlayerCombination(opponent).getTacticCards();
        for (const auto& tacticCard : tacticCards) {
            allCards.push_back(tacticCard);
            std::cout << " [" << index++ << "] " << *tacticCard; // Utilisez *tacticCard pour afficher la carte
        }
    }

    std::cout << "Pick a card. Type the index of the card you would like to pick: ";
    int card = askPlayerValue(player, {0, index});

    const Card* selectedCard = allCards[card];
    int borderIndex;
    if (typeid(selectedCard) == typeid(ValuedCard)) {
        borderIndex = board_->findBorderIndexByValuedCard(*static_cast<const ValuedCard*>(selectedCard), opponent);
    } else {
        borderIndex = board_->findBorderIndexByTacticCard(*static_cast<const TacticCard*>(selectedCard), opponent);
    }

    board_->getBorderByID(borderIndex).getPlayerCombination(opponent).removeCardFromCombination(
            const_cast<Card *>(selectedCard));


    // Supprimer la carte de la défausse
    discardDeck_->removeCard(selectedCard);
    std::cout << "Please enter the index of the border you want to pick:\n";
    int border_index = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
    while (board_->getBorderByID(border_index).isClaimed())
    {
        std::cout << "The border is already claimed. Please enter a different index:\n";
        border_index = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
    }
    player->play_card(player->getNumber_of_cards() - 1,border_index, board_ );
}
