#include <iostream>

#include "class/Card.h"
#include "class/Deck/Deck.h"


int main() {

    //-----launch_Schotten_Totten1:
    const int MAX_CLAN_CARD_STRENGTH = 9;
    const int MIN_CLAN_CARD_STRENGTH = 1;
    const int NUMBER_CLAN_CARDS = 54;

    unique_ptr<Card> card1 = make_unique<Valued_Card>(2, CardColor::orange);
    cout << *card1 << '\n' << '\n';

    DeckCreator deckCreator;
    Deck deck = deckCreator.createClanDeck().build();
    Deck discardDeck;
    for (int i = 0; i < 15; ++i) {
        discardDeck.putCard(deck.drawCard());
    }
    discardDeck.print();
    cout << '\n';

    deck.print();
    return 0;
}

