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
    : player1_(player1), player2_(player2),
    player1_id(player1), player2_id(player2){}

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
    return this->getTrackedPlayer(this->getOpponent(player));
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

inline Player *GameTracker::getOpponent(Player *player) {
    if (player == player1_id)
        return player2_id;
    return player1_id;
}

const Combination& GameTracker::getOpponentBestPossibleCombinationClassicVersion(const Combination& opponentCombination){
    Combination tempCombiVC(3, nullptr);
    Combination bestCombi(3, nullptr);
    int N = remainingValuedCardsDeck.getNumberRemainingCards();
    if(opponentCombination.getNumberCards() == 0) {
        for (int i = 0; i < N - 2; i++) {
            for (int j = i + 1; j < N - 1; i++) {
                for (int k = j + 1; j < N; j++) {
                    std::unique_ptr<Card> card1 = remainingValuedCardsDeck.drawCardByIndex(
                            i); // Retirer la carte du remainingCardsDeck
                    std::unique_ptr<ValuedCard> Vcard1(dynamic_cast<ValuedCard *>(card1.release()));
                    tempCombiVC.push_back(std::move(Vcard1));
                    std::unique_ptr<Card> card2 = remainingValuedCardsDeck.drawCardByIndex(
                            j); // Retirer la carte du remainingCardsDeck
                    std::unique_ptr<ValuedCard> Vcard2(dynamic_cast<ValuedCard *>(card2.release()));
                    tempCombiVC.push_back(std::move(Vcard2));
                    std::unique_ptr<Card> card3 = remainingValuedCardsDeck.drawCardByIndex(
                            k); // Retirer la carte du remainingCardsDeck
                    std::unique_ptr<ValuedCard> Vcard3(dynamic_cast<ValuedCard *>(card3.release()));
                    tempCombiVC.push_back(std::move(Vcard3));
                    const Combination &bestCombiRef = bestCombination(tempCombiVC, bestCombi);
                    if (bestCombiRef == tempCombiVC) {
                        bestCombi = tempCombiVC;
                    }
                    unique_ptr<Card> Ccard1 = std::move(tempCombiVC.valuedCardBack());
                    remainingValuedCardsDeck.putCard(std::move(Ccard1));
                    unique_ptr<Card> Ccard2 = std::move(tempCombiVC.valuedCardBack());
                    remainingValuedCardsDeck.putCard(std::move(Ccard2));
                    unique_ptr<Card> Ccard3 = std::move(tempCombiVC.valuedCardBack());
                    remainingValuedCardsDeck.putCard(std::move(Ccard3));
                }
            }
        }
    }
    else if(opponentCombination.getNumberCards() == 1){
        bestCombi = opponentCombination;
        for (int i = 0; i < N - 1; i++) {
            for (int j = i + 1; j < N; i++) {
                    std::unique_ptr<Card> card1 = remainingValuedCardsDeck.drawCardByIndex(
                            i); // Retirer la carte du remainingCardsDeck
                    std::unique_ptr<ValuedCard> Vcard1(dynamic_cast<ValuedCard *>(card1.release()));
                    tempCombiVC.push_back(std::move(Vcard1));
                    std::unique_ptr<Card> card2 = remainingValuedCardsDeck.drawCardByIndex(
                            j); // Retirer la carte du remainingCardsDeck
                    std::unique_ptr<ValuedCard> Vcard2(dynamic_cast<ValuedCard *>(card2.release()));
                    tempCombiVC.push_back(std::move(Vcard2));
                    const Combination &bestCombiRef = bestCombination(tempCombiVC, bestCombi);
                    if (bestCombiRef == tempCombiVC) {
                        bestCombi = tempCombiVC;
                    }
                    unique_ptr<Card> Ccard1 = std::move(tempCombiVC.valuedCardBack());
                    remainingValuedCardsDeck.putCard(std::move(Ccard1));
                    unique_ptr<Card> Ccard2 = std::move(tempCombiVC.valuedCardBack());
                    remainingValuedCardsDeck.putCard(std::move(Ccard2));
            }
        }
    }
    else if(opponentCombination.getNumberCards() == 2){
        bestCombi = opponentCombination;
        for (int i = 0; i < N; i++) {
                std::unique_ptr<Card> card1 = remainingValuedCardsDeck.drawCardByIndex(
                        i); // Retirer la carte du remainingCardsDeck
                std::unique_ptr<ValuedCard> Vcard1(dynamic_cast<ValuedCard *>(card1.release()));
                tempCombiVC.push_back(std::move(Vcard1));
                const Combination &bestCombiRef = bestCombination(tempCombiVC, bestCombi);
                if (bestCombiRef == tempCombiVC) {
                    bestCombi = tempCombiVC;
                }
                unique_ptr<Card> Ccard1 = std::move(tempCombiVC.valuedCardBack());
                remainingValuedCardsDeck.putCard(std::move(Ccard1));
        }
    }

        return bestCombi;
}




/*void GameTracker::copyDeck(Deck tacticDeck, Deck clanDeck) {
    // Copie des cartes tactiques dans remainingTacticCardsDeck
    for (int i = 0; i < tacticDeck.getNumberRemainingCards(); i++) {
        std::unique_ptr<Card> tacticCard = tacticDeck.drawCard();
        remainingCardsDeck.putCard(std::move(tacticCard));
    }

    // Copie des cartes de valeur dans remainingCardsDeck
    for (int i = 0; i < clanDeck.getNumberRemainingValuedCards(); i++) {
        std::unique_ptr<Card> valuedCard = clanDeck.drawCard();
        remainingCardsDeck.putCard(std::move(valuedCard));
    }
}
*/

void GameTracker::transferValuedCardToCombination(Combination& combination) {
    if (remainingValuedCardsDeck.isEmpty()) {
        throw std::runtime_error("Le deck remainingValuedCardsDeck est vide.");
    }

    std::unique_ptr<Card> transferredCard = remainingValuedCardsDeck.drawCard(); // Retirer la carte du remainingCardsDeck
    std::unique_ptr<ValuedCard> transferredValuedCard(dynamic_cast<ValuedCard*>(transferredCard.release()));
    combination.push_back(std::move(transferredValuedCard));
    //(std::move(transferredCard)); // Transférer la carte au playedCardsDeck
}

void GameTracker::transferTacticCardToCombination(Combination& combination) {
    if (remainingTacticCardsDeck.isEmpty()) {
        throw std::runtime_error("Le deck remainingTacticCardsDeck est vide.");
    }

    std::unique_ptr<Card> transferredCard = remainingTacticCardsDeck.drawCard(); // Retirer la carte du remainingCardsDeck
    std::unique_ptr<TacticCard> transferredTacticCard(dynamic_cast<TacticCard*>(transferredCard.release()));
    combination.push_back(std::move(transferredTacticCard));
    combination.push_back(std::move(transferredTacticCard)); // Transférer la carte au playedCardsDeck
}

//void GameTracker::transferValuedCardToPlayedCardsDeck() {
//    if (remainingValuedCardsDeck.isEmpty()) {
//        throw std::runtime_error("Le deck remainingValuedCardsDeck est vide.");
//    }
//
//    std::unique_ptr<Card> transferredCard = remainingValuedCardsDeck.drawCard(); // Retirer la carte du remainingCardsDeck
//    playedCardsDeck.putCard(std::move(transferredCard)); // Transférer la carte au playedCardsDeck
//}

//void GameTracker::transferTacticCardToPlayedCardsDeck() {
//    if (remainingTacticCardsDeck.isEmpty()) {
//        throw std::runtime_error("Le deck remainingTacticCardsDeck est vide.");
//    }
//
//    std::unique_ptr<Card> transferredCard = remainingTacticCardsDeck.drawCard(); // Retirer la carte du remainingCardsDeck
//    playedCardsDeck.putCard(std::move(transferredCard)); // Transférer la carte au playedCardsDeck
//}
