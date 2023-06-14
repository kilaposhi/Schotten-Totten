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


// else if (type == TacticType::recruiter || type == TacticType::strategist ||
//type == TacticType::banshee || type == TacticType::traiter) {
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
    board_->getBorderByID(borderId).setNoCombinationRules();
}


void TacticHandler::playMudFight(int borderId) {
    board_->getBorderByID(borderId).setMaxNumberCard(4);
}


