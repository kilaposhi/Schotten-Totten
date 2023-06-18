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
    cout << "Quick Description " << *tacticCard << tacticCard->getDescription() << '\n';
    bool isEliteTroop = type == TacticType::joker || type == TacticType::spy || type == TacticType::shield_bearer;
    if (isEliteTroop)
        return this->playEliteTroop(std::move(tacticCard), player, borderID);
    if (type == TacticType::blind_man_bluff) return this->playBlindManBluff(borderID);
    if (type == TacticType::mud_fight) return this->playMudFight(borderID);
    if (tacticCard->isRuse())
    {
        discardDeck_->putCard(std::move(tacticCard));
        if (type == TacticType::recruiter) return playRecruiter(player);
        if (type == TacticType::strategist) return playStrategist(player);
        Player* opponent  = GameTracker::getInstance().getOpponent(player);
        if (type == TacticType::banshee ) return playBanshee(player, opponent);
        if (type == TacticType::traitor) return playTraitor(player, opponent);
    }
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
    Border& border = board_->getBorderByID(borderId);
    if (border.hasMudFight())
        throw TacticHandlerException("The border is taken by MudFight");
    if (border.isClaimed())
        throw TacticHandlerException("The border is already claimed");
    board_->getBorderByID(borderId).setNoCombinationRules();
}


void TacticHandler::playMudFight(int borderId) {
    Border& border = board_->getBorderByID(borderId);
    if (border.hasBlindManBluff())
        throw TacticHandlerException("The border is taken by Blind Man Bluff's");
    if (border.isClaimed())
        throw TacticHandlerException("The border is already claimed");
    board_->getBorderByID(borderId).setMaxNumberCard(4);
}


void TacticHandler::playRecruiter( Player* player) {
    size_t maxNumberCards = player->max_cards;
    player->setMaxNumberCards(maxNumberCards + 3);

    for (size_t i = 0; i < 3; i++){
        std::cout << "Please pick a deck. [1] Clan Deck [2] Tactic Deck\n";
        int deckIndex = askPlayerValue(player, {1, 2});
        if (deckIndex == 1) {
            player->draw_card(*normalDeck_);
        }
        else {
            player->draw_card(*tacticDeck_);
            }
        cout << "\tCard drawn : " << player->displayCard(player->getNumber_of_cards() - 1) << '\n';
    }

    std::cout << "Please choose two cards from your hand you want ot get rid of\n";
    player->displayHand();

    for (int i = 1; i <= 2; i++) {
        std::cout << "Choose card " << (i) << ": ";
        int cardIndex = askPlayerValue(player, {0, player->getNumber_of_cards() - 1});
        auto selectedCard = player->remove_card_from_hand(cardIndex);
        if (dynamic_cast<ValuedCard*>(selectedCard.get()))
            normalDeck_->putCard(std::move(selectedCard));
        else
            tacticDeck_->putCard(std::move(selectedCard));
    }

    std::cout << "Cards placed under the decks.\n";
    //std::cout << "Here is your final hand:\n";
    player->displayHand();
    player->setMaxNumberCards(maxNumberCards);
}

size_t TacticHandler::chooseBorderToRemove(const string& text, Player* player)
{
    cout << board_->str() << '\n';
    bool claimed = false;
    bool playerHasNoCards = false;
    size_t borderIndex;
    do {
        cout << text << '\n';
        borderIndex = askPlayerValue(player, {0, board_->getNumberBorder() - 1});
        Border& borderSelected = board_->getBorderByID(borderIndex);
        if (borderSelected.isClaimed())
            claimed = true;
        Combination& combination = borderSelected.getPlayerCombination(player);
        if (combination.getNumberCards() == 0)
            playerHasNoCards = true;
    } while (claimed || playerHasNoCards);
    return borderIndex;
}

size_t TacticHandler::chooseBorderToAdd(const string& text, Player* player){
    cout << board_->str() << '\n';
    bool claimed =  true;
    bool playerHasMaxCards = true;
    size_t borderIndex;
    do {
        cout << text << '\n';
        borderIndex = askPlayerValue(player, {0, board_->getNumberBorder() -1});
        Border& borderSelected = board_->getBorderByID(borderIndex);
        if (!borderSelected.isClaimed())
            claimed = false;
        Combination& combination = borderSelected.getPlayerCombination(player);
        if (combination.getNumberCards() <= combination.getMaxNumberCards())
            playerHasMaxCards = false;
    } while (claimed || playerHasMaxCards);
    return borderIndex;
}

void TacticHandler::playStrategist(Player* player)
{
    size_t borderIndex = chooseBorderToRemove("Choose an unclaimed Border then one of your Card to move somewhere else", player);
    Combination& combiSelected = board_->getBorderByID(borderIndex).getPlayerCombination(player);

    cout << "Here are yours cards on the Border " << borderIndex <<" ";
    cout <<  combiSelected.displayCards() << '\n';
    std::cout << "Pick a card. Type the index of the card you would like to pick: \n";
    int combiIndex = askPlayerValue(player, {0, combiSelected.getNumberCards() -1});

    unique_ptr<ValuedCard> valuedCard = nullptr;
    unique_ptr<TacticCard> tacticCard = nullptr;
    bool tactic = false;
    if (combiIndex > combiSelected.getNumberValuedCards() - 1)
        valuedCard = combiSelected.pop_card(combiSelected.getValuedCard(combiIndex));
    else {
        tactic = true;
        tacticCard = combiSelected.pop_card(combiSelected.getTacticCard(combiIndex));
    }

    std::cout << "Do you want to play it on a border [1] or to put it back in the deck [2] ?";
    int choice = askPlayerValue(player, {1,2});
    if (choice == 1)
    {
        borderIndex = chooseBorderToAdd("Please enter the index of the border you want to play the card :", player);
        Border& border = board_->getBorderByID(borderIndex);
        if (tactic)
            border.addTacticalCard(std::move(tacticCard), player);
        else
            border.addValueCard(std::move(valuedCard), player);
    }
    else {
        if (tactic)
            discardDeck_->pushCardTop(std::move(tacticCard));
        else
            discardDeck_->pushCardTop(std::move(valuedCard));
    }
    cout << "Card successfully played! \n";
    cout << "New board \n" << board_->str() << '\n';
}

void TacticHandler::playBanshee(Player* player, Player* opponent)
{
    size_t borderIndex = chooseBorderToRemove("Choose the Border where you'd like to discard one of your opponent's card", opponent);
    Combination& combiSelected = board_->getBorderByID(borderIndex).getPlayerCombination(opponent);

    cout << "Here are yours opponent cards on the Border " << borderIndex <<" ";
    cout <<  combiSelected.displayCards() << '\n';
    std::cout << "Pick a card. Type the index of the card you would like to pick: \n";
    int combiIndex = askPlayerValue(player, {0, combiSelected.getNumberCards() -1});

    unique_ptr<ValuedCard> valuedCard = nullptr;
    unique_ptr<TacticCard> tacticCard = nullptr;
    bool tactic = false;
    if (combiIndex > combiSelected.getNumberValuedCards() - 1)
        valuedCard = combiSelected.pop_card(combiSelected.getValuedCard(combiIndex));
    else {
        tactic = true;
        tacticCard = combiSelected.pop_card(combiSelected.getTacticCard(combiIndex));
    }

    if (tactic)
        discardDeck_->pushCardTop(std::move(tacticCard));
    else
        discardDeck_->pushCardTop(std::move(valuedCard));

    cout << "Card successfully discarded! \n";
    cout << "New board \n" << board_->str() << '\n';
}


void TacticHandler::playTraitor(Player* player, Player* opponent)
{
    size_t borderIndex = chooseBorderToRemove("Choose the Border where you'd like to get one of your opponent's card", opponent);
    Combination& combiSelected = board_->getBorderByID(borderIndex).getPlayerCombination(opponent);

    cout << "Here are yours opponent cards on the Border " << borderIndex <<" ";
    cout <<  combiSelected.displayCards() << '\n';
    for (size_t i = 0; i < combiSelected.getNumberValuedCards(); i++)
        cout << " (" << i << "): " << combiSelected.getValuedCard(i);
    std::cout << "Pick a card. Type the index of the card you would like to pick: \n";
    int combiIndex = askPlayerValue(player, {0, combiSelected.getNumberValuedCards() -1});

    unique_ptr<ValuedCard> valuedCard = combiSelected.pop_card(combiSelected.getValuedCard(combiIndex));

    borderIndex = chooseBorderToAdd("Please enter the index of the border you want to pick to play the stolen card:", player);
    Border& border = board_->getBorderByID(borderIndex);
    border.addValueCard(std::move(valuedCard), player);

    cout << "Card successfully played! \n";
    cout << "New board \n" << board_->str() << '\n';
}
