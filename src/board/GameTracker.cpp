#include "GameTracker.h"

#include <stdexcept>
#include <vector>

#include "deck/Card.h"
#include "deck/Deck.h"

GameTracker::GameTracker(const Deck& tacticDeck, const Deck& clanDeck) {
    //copyDeck(tacticDeck, clanDeck);
}


const Deck& GameTracker::getRemainingCardDeck() const {
    return remainingCardsDeck;
}


const Deck& GameTracker::getPlayerCardsDeck() const {
    return playedCardsDeck;
}


void GameTracker::update() {
    playedCardsDeck.putCard(remainingCardsDeck.drawCard());
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


void GameTracker::transferCard() {
    if (remainingCardsDeck.isEmpty()) {
        throw std::runtime_error("Le deck remainingCardsDeck est vide.");
    }

    std::unique_ptr<Card> transferredCard = remainingCardsDeck.drawCard(); // Retirer la carte du remainingCardsDeck
    playedCardsDeck.putCard(std::move(transferredCard)); // Transférer la carte au playedCardsDeck
}
