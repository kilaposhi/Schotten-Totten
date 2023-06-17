#include "GameTracker.h"


TrackedPlayer::TrackedPlayer(Player *player) : player_(player) {
    playedTacticCard_.reserve(5);
    playedValuedCard_.reserve(25);
}

Player *TrackedPlayer::getPlayer() const {
    return player_;
}

void TrackedPlayer::trackCard(const TacticCard& card) {
    if (card.getName() == TacticType::joker)
        hasPlayedJoker_ = true;
    playedTacticCard_.push_back(card);
}

void TrackedPlayer::trackCard(const ValuedCard& card) {
    playedValuedCard_.push_back(card);
}

size_t TrackedPlayer::getNumberTacticCardPlayed() const {
    return playedTacticCard_.size();
}

bool TrackedPlayer::canPlayJoker() const {
    if (hasPlayedJoker_)
        return false;
    return true;
}


GameTracker::GameTracker(Player *player1, Player *player2)
    : player1_(player1), player2_(player2){

}

GameTracker &GameTracker::getInstance(Player *player1, Player *player2) {
    static unique_ptr<GameTracker> instance (new GameTracker(player1, player2));

    bool no_argument = !player1 && !player2;
    if (no_argument)
        return *instance;

    bool different_instance = instance->player1_.getPlayer() != player1 && instance->player2_.getPlayer() != player2;
    if (different_instance)
        instance.reset(new GameTracker(player1, player2));

    //    bool emptyInstance = !instance->player1_ && !instance->normalDeckInfo_ && !instance->tacticDeck_ && !instance->discardDeck_ && !instance->board_;
    //    if (emptyInstance)
    //        throw GameTrackerException("Returning an empty instance of GameTracker (not initialized)");
    return *instance;
}

TrackedPlayer &GameTracker::getTrackedPlayer(Player *player) {
    if (player == player1_.getPlayer())
        return player1_;
    return player2_;
}

TrackedPlayer &GameTracker::getOpponentTrackedPlayer(Player *player) {
    if (player == player1_.getPlayer())
        return player2_;
    return player1_;
}

void GameTracker::trackCard(Player *player, const ValuedCard& card) {
    this->getTrackedPlayer(player).trackCard(card);
}

void GameTracker::trackCard(Player *player, const TacticCard& card) {
    this->getTrackedPlayer(player).trackCard(card);
}

bool GameTracker::canPlayTacticCard(Player *player) {
    bool hasPlayedMoreTacticCard = getTrackedPlayer(player).getNumberTacticCardPlayed() > getOpponentTrackedPlayer(player).getNumberTacticCardPlayed();
    if (hasPlayedMoreTacticCard)
        return false;
    return true;
}

bool GameTracker::canPlayJoker(Player *player) {
    return getTrackedPlayer(player).canPlayJoker();
}

/*void GameTracker::copyDeck(Deck tacticDeck, Deck clanDeck) {
    // Copie des cartes tactiques dans remainingCardsDeck
    for (int i = 0; i < tacticDeck.getNumberRemainingCards(); i++) {
        std::unique_ptr<Card> tacticCard = tacticDeck.drawCard();
        remainingCardsDeck.putCard(std::move(tacticCard));
    }

    // Copie des cartes de valeur dans remainingCardsDeck
    for (int i = 0; i < clanDeck.getNumberRemainingCards(); i++) {
        std::unique_ptr<Card> valuedCard = clanDeck.drawCard();
        remainingCardsDeck.putCard(std::move(valuedCard));
    }
}
*/


//void GameTracker::transferCard() {
//    if (remainingCardsDeck.isEmpty()) {
//        throw std::runtime_error("Le deck remainingCardsDeck est vide.");
//    }
//
//    std::unique_ptr<Card> transferredCard = remainingCardsDeck.drawCard(); // Retirer la carte du remainingCardsDeck
//    playedCardsDeck.putCard(std::move(transferredCard)); // Transférer la carte au playedCardsDeck
//}
