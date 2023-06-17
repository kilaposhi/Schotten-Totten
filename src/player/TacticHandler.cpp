#include "player/TacticHandler.h"

TacticHandler::TacticHandler(Deck* normalDeck, DeckInfo* normalDeckInfo, Deck* tacticDeck, Deck* discardDeck, Board* board) :
        normalDeck_(normalDeck),
        normalDeckInfo_(normalDeckInfo),
        tacticDeck_(tacticDeck),
        discardDeck_(discardDeck),
        board_(board)
{
}

TacticHandler& TacticHandler::getInstance(Deck* normalDeck, DeckInfo* normalDeckInfo, Deck* tacticDeck, Deck* discardDeck, Board* board)
{
    static TacticHandler instance(normalDeck, normalDeckInfo, tacticDeck, discardDeck, board);
    return instance;
}

void TacticHandler::playTacticCard(std::unique_ptr<TacticCard> tacticCard, Player* player, int borderID)
{
    TacticType type = tacticCard->getName();

    if (type == TacticType::joker || type == TacticType::spy || type == TacticType::shield_bearer)
    {
        playEliteTroop(std::move(tacticCard), player, borderID);
    }
    else if (type == TacticType::blind_man_bluff)
    {
        playBlindManBluff(borderID);
    }
    else if (type == TacticType::mud_fight)
    {
        playMudFight(borderID);
    }
    else if (tacticCard->isRuse())
    {
        discardDeck_->putCard(std::move(tacticCard));

        if (type == TacticType::recruiter)
        {
            playRecruiter(player);
        }
        else if (type == TacticType::strategist)
        {
            playStrategist(player);
        }
        else if (type == TacticType::banshee)
        {
            Player* opponent = (board_->getPlayer(1) == player) ? board_->getPlayer(2) : board_->getPlayer(1);
            playBanshee(player, opponent);
        }
        else if (type == TacticType::traitor)
        {
            Player* opponent = (board_->getPlayer(1) == player) ? board_->getPlayer(2) : board_->getPlayer(1);
            playTraitor(player, opponent);
        }
    }
}

void TacticHandler::playEliteTroop(std::unique_ptr<TacticCard> tacticCard, Player* player, int borderId)
{
    board_->getBorderByID(borderId).addTacticalCard(std::move(tacticCard), player);
}

void TacticHandler::activeEliteTroop(std::unique_ptr<TacticCard> tacticCard, Combination* combination)
{
    Player* player = combination->getPlayerID();
    TacticType tacticType = tacticCard->getName();
    int value;
    CardColor color;

    if (tacticType == TacticType::joker)
    {
        AI* ai = dynamic_cast<AI*>(player);

        if (ai == nullptr)
        {
            value = askPlayerValue(player, { normalDeckInfo_->min_card_value, normalDeckInfo_->max_card_value });
            color = askPlayerColor(player, normalDeckInfo_->number_colors);
        }
        else
        {
            value = rand() % (normalDeckInfo_->max_card_value - normalDeckInfo_->min_card_value + 1) + normalDeckInfo_->min_card_value;
            int color_index = rand() % normalDeckInfo_->number_colors;
            color = *(cardColors.begin() + color_index);
        }
    }
    else if (tacticType == TacticType::shield_bearer)
    {
        AI* ai = dynamic_cast<AI*>(player);

        if (ai == nullptr)
        {
            value = askPlayerValue(player, { 1, 3 });
            color = askPlayerColor(player, normalDeckInfo_->number_colors);
        }
        else
        {
            value = rand() % 2 + 1;
            int color_index = rand() % normalDeckInfo_->number_colors;
            color = *(cardColors.begin() + color_index);
        }
    }
    else if (tacticType == TacticType::spy)
    {
        value = 7;
        AI* ai = dynamic_cast<AI*>(player);

        if (ai == nullptr)
        {
            color = askPlayerColor(player, normalDeckInfo_->number_colors);
        }
        else
        {
            int color_index = rand() % normalDeckInfo_->number_colors;
            color = *(cardColors.begin() + color_index);
        }
    }

    combination->push_back(std::make_unique<ValuedCard>(value, color));
}

void TacticHandler::playBlindManBluff(int borderId)
{
    if (board_->getBorderByID(borderId).hasMudFight())
    {
        throw TacticHandlerException("The stone is taken by MudFight");
    }
    else
    {
        board_->getBorderByID(borderId).setNoCombinationRules();
    }
}

void TacticHandler::playMudFight(int borderId)
{
    if (board_->getBorderByID(borderId).hasBlindManBluff())
    {
        throw TacticHandlerException("The stone is taken by Blind Man Bluff");
    }
    else
    {
        board_->getBorderByID(borderId).setMaxNumberCard(4);
    }
}

void TacticHandler::playRecruiter(Player* player)
{
    std::cout << "Please pick a deck. [1] Clan Deck [2] Tactic Deck\n";
    int deck;
    AI* ai = dynamic_cast<AI*>(player);

    if (ai == nullptr)
    {
        deck = askPlayerValue(player, { 1, 2 });
    }
    else
    {
        deck = rand() % 1 + 1;
    }

    std::cout << "Here's your current hand:\n";
    player->displayHand();

    if (deck == 1)
    {
        std::cout << "Drawing 3 cards from the Clan Deck...\n";

        for (int j = 0; j < 3; j++)
        {
            player->draw_card(*normalDeck_);
        }
    }
    else
    {
        std::cout << "Drawing 3 cards from the Tactic Deck...\n";

        for (int j = 0; j < 3; j++)
        {
            player->draw_card(*tacticDeck_);
        }
    }

    std::cout << "Here is your new hand after drawing:\n";
    player->displayHand();

    std::cout << "Please choose two cards from your hand to place under the corresponding deck:\n";
    player->displayHand();

    for (int i = 0; i < 2; i++)
    {
        std::cout << "Choose card " << (i + 1) << ": ";
        int cardIndex;
        AI* ai = dynamic_cast<AI*>(player);

        if (ai == nullptr)
        {
            cardIndex = askPlayerValue(player, { player->getNumber_of_cards() - 3, player->getNumber_of_cards() - 1 });
        }
        else
        {
            cardIndex = (player->getNumber_of_cards() - 1 - player->getNumber_of_cards() - 3 + 1) + player->getNumber_of_cards() - 3;
        }

        Card* selectedCard = player->getCardAtIndex(cardIndex).get();
        player->remove_card_from_hand(cardIndex);

        if (deck == 1)
        {
            normalDeck_->putCard(std::unique_ptr<Card>(selectedCard));
        }
        else
        {
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
        if (board_->getBorderByID(i).isClaimed())
        {
            continue;
        }

        const auto& valuedCards = board_->getBorderByID(i).getPlayerCombination(player).getValuedCards();

        for (const auto& valuedCard : valuedCards)
        {
            allCards.push_back(valuedCard);
            std::cout << " [" << index++ << "] " << *valuedCard; // Use *valuedCard to display the card
        }

        const auto& tacticCards = board_->getBorderByID(i).getPlayerCombination(player).getTacticCards();

        for (const auto& tacticCard : tacticCards)
        {
            allCards.push_back(tacticCard);
            std::cout << " [" << index++ << "] " << *tacticCard; // Use *tacticCard to display the card
        }
    }

    std::cout << "Pick a card. Type the index of the card you would like to pick: ";
    int card;
    AI* ai = dynamic_cast<AI*>(player);

    if (ai == nullptr)
    {
        card = askPlayerValue(player, { 0, index });
    }
    else
    {
        card = rand() % index;
    }

    const Card* selectedCard = allCards[card];
    discardDeck_->removeCard(selectedCard);

    int borderIndex;

    if (typeid(*selectedCard) == typeid(ValuedCard))
    {
        borderIndex = board_->findBorderIndexByValuedCard(*static_cast<const ValuedCard*>(selectedCard), player);
    }
    else
    {
        borderIndex = board_->findBorderIndexByTacticCard(*static_cast<const TacticCard*>(selectedCard), player);
    }

    board_->getBorderByID(borderIndex).getPlayerCombination(player).removeCardFromCombination(const_cast<Card*>(selectedCard));
    player->add_card_into_hand( unique_ptr<Card> (std::move(allCards[card])));

    std::cout << "Do you want to play it on a border [1] or to put it back in the deck [2]? ";
    int choice;

    if (ai == nullptr)
    {
        choice = askPlayerValue(player, { 1, 2 });
    }
    else
    {
        choice = rand() % 1 + 1;
    }

    if (choice == 1)
    {
        std::cout << "Please enter the index of the border you want to pick:\n";
        int border_index;

        if (ai == nullptr)
        {
            border_index = askPlayerValue(player, { 0, board_->getNumberBorder() - 1 });
        }
        else
        {
            border_index = rand() % board_->getNumberBorder() - 1;
        }

        while (board_->getBorderByID(border_index).isClaimed())
        {
            std::cout << "The border is already claimed. Please enter a different index:\n";

            if (ai == nullptr)
            {
                border_index = askPlayerValue(player, { 0, board_->getNumberBorder() - 1 });
            }
            else
            {
                border_index = rand() % board_->getNumberBorder() - 1;
            }
        }

        player->play_card(player->getNumber_of_cards() - 1, border_index, board_);
    }
    else
    {
        player->remove_card_from_hand(player->getNumber_of_cards() - 1);
        normalDeck_->addToSide(unique_ptr<Card> (std::move(allCards[card]))); // Use std::move(allCards[card]) to transfer ownership of the card
    }
}
void TacticHandler::playBanshee(Player* player, Player* opponent)
{
    std::vector<Card*> allCards;
    int index = 0;

    for (int i = 0; i < board_->getNumberBorder(); i++)
    {
        if (board_->getBorderByID(i).isClaimed())
        {
            continue;
        }

        const auto& valuedCards = board_->getBorderByID(i).getPlayerCombination(opponent).getValuedCards();

        for (const auto& valuedCard : valuedCards)
        {
            allCards.push_back(valuedCard);
            std::cout << " [" << index++ << "] " << *valuedCard; // Use *valuedCard to display the card
        }

        const auto& tacticCards = board_->getBorderByID(i).getPlayerCombination(opponent).getTacticCards();

        for (const auto& tacticCard : tacticCards)
        {
            allCards.push_back(tacticCard);
            std::cout << " [" << index++ << "] " << *tacticCard; // Use *tacticCard to display the card
        }
    }

    std::cout << "Pick a card. Type the index of the card you would like to pick: ";
    int card;
    AI* ai = dynamic_cast<AI*>(player);

    if (ai == nullptr)
    {
        card = askPlayerValue(player, { 0, index });
    }
    else
    {
        card = rand() % index;
    }

    const Card* selectedCard = allCards[card];
    int borderIndex;

    if (typeid(*selectedCard) == typeid(ValuedCard))
    {
        borderIndex = board_->findBorderIndexByValuedCard(*static_cast<const ValuedCard*>(selectedCard), opponent);
    }
    else
    {
        borderIndex = board_->findBorderIndexByTacticCard(*static_cast<const TacticCard*>(selectedCard), opponent);
    }

    board_->getBorderByID(borderIndex).getPlayerCombination(opponent).removeCardFromCombination(const_cast<Card*>(selectedCard));
    discardDeck_->removeCard(selectedCard);

    player->add_card_into_hand(unique_ptr<Card> (std::move(allCards[card])));
}
void TacticHandler::playTraitor(Player* player, Player* opponent)
{
    std::vector<Card*> allCards;
    int index = 0;

    for (int i = 0; i < board_->getNumberBorder(); i++)
    {
        if (board_->getBorderByID(i).isClaimed())
        {
            continue;
        }

        const auto& valuedCards = board_->getBorderByID(i).getPlayerCombination(opponent).getValuedCards();

        for (const auto& valuedCard : valuedCards)
        {
            allCards.push_back(valuedCard);
            std::cout << " [" << index++ << "] " << *valuedCard; // Use *valuedCard to display the card
        }

        const auto& tacticCards = board_->getBorderByID(i).getPlayerCombination(opponent).getTacticCards();

        for (const auto& tacticCard : tacticCards)
        {
            allCards.push_back(tacticCard);
            std::cout << " [" << index++ << "] " << *tacticCard; // Use *tacticCard to display the card
        }
    }

    std::cout << "Pick a card. Type the index of the card you would like to pick: ";
    int card;
    AI* ai = dynamic_cast<AI*>(player);

    if (ai == nullptr)
    {
        card = askPlayerValue(player, { 0, index });
    }
    else
    {
        card = rand() % index;
    }

    const Card* selectedCard = allCards[card];
    int borderIndex;

    if (typeid(*selectedCard) == typeid(ValuedCard))
    {
        borderIndex = board_->findBorderIndexByValuedCard(*static_cast<const ValuedCard*>(selectedCard), opponent);
    }
    else
    {
        borderIndex = board_->findBorderIndexByTacticCard(*static_cast<const TacticCard*>(selectedCard), opponent);
    }

    board_->getBorderByID(borderIndex).getPlayerCombination(opponent).removeCardFromCombination(const_cast<Card*>(selectedCard));
    discardDeck_->removeCard(selectedCard);

    std::cout << "Please enter the index of the border you want to pick:\n";
    int border_index;

    if (ai == nullptr)
    {
        border_index = askPlayerValue(player, { 0, board_->getNumberBorder() - 1 });
    }
    else
    {
        border_index = rand() % board_->getNumberBorder() - 1;
    }

    while (board_->getBorderByID(border_index).isClaimed())
    {
        std::cout << "The border is already claimed. Please enter a different index:\n";

        if (ai == nullptr)
        {
            border_index = askPlayerValue(player, { 0, board_->getNumberBorder() - 1 });
        }
        else
        {
            border_index = rand() % board_->getNumberBorder() - 1;
        }
    }

    player->play_card(player->getNumber_of_cards() - 1, border_index, board_);
}
