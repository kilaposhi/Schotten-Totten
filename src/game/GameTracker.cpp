#include "GameTracker.h"

#include <stdexcept>
#include <vector>

#include "deck/Card.h"
#include "deck/Deck.h"

void GameTracker::update() {
    playedCardsDeck.putCard(remainingCardsDeck.drawCard());
}

void GameTracker::copyDeck(Deck tacticDeck, Deck clanDeck) {
    remainingCardsDeck.clear(); // Supprime les cartes existantes dans remainingCardsDeck
    remainingCardsDeck.putCard(tacticDeck.drawCard()); // Ajoute les cartes du tacticDeck
    remainingCardsDeck.putCard(clanDeck.drawCard()); // Ajoute les cartes du clanDeck
}

void GameTracker::transferCard() {
    if (remainingCardsDeck.isEmpty()) {
        throw std::runtime_error("Le deck remainingCardsDeck est vide.");
    }

    std::unique_ptr<Card> transferredCard = remainingCardsDeck.drawCard(); // Retirer la carte du remainingCardsDeck
    playedCardsDeck.putCard(std::move(transferredCard)); // Transférer la carte au playedCardsDeck
}

