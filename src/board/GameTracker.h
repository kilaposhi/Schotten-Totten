//
// Created by tassili on 18/05/2023.
//

#ifndef SCHOTTEN_TOTTEN_GAMETRACKER_H
#define SCHOTTEN_TOTTEN_GAMETRACKER_H
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
    void update() override {
        // Mettre à jour les decks lorsque la carte est jouée
        // à partir de la classe Stone
        playedCardsDeck.putCard(remainingCardsDeck.drawCard());
    }

};



#endif //SCHOTTEN_TOTTEN_GAMETRACKER_H
