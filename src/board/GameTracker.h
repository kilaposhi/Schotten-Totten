#ifndef SCHOTTEN_TOTTEN_GAMETRACKER_H
#define SCHOTTEN_TOTTEN_GAMETRACKER_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "deck/Card.h"
#include "player/Player.h"
#include "board/Combination.h"
#include "deck/Deck.h"


// Classe abstraite pour les observateurs
class Observer {
public:
    virtual void update() = 0;
};


// Classe GameTracker qui est l'observateur
class GameTracker : public Observer {
private:
    Deck remainingCardsDeck;
    Deck playedCardsDeck;

public:
    GameTracker(const Deck& tacticDeck, const Deck& clanDeck);
    void update() override;
    void copyDeck(Deck tacticDeck, Deck clanDeck);
    void transferCard();
    [[nodiscard]] const Deck& getRemainingCardDeck() const;
    [[nodiscard]] const Deck& getPlayerCardsDeck() const;
};





#endif //SCHOTTEN_TOTTEN_GAMETRACKER_H
