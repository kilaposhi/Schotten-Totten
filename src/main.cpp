#include <iostream>

#include "deck/Card.h"
#include "deck/Deck.h"


int main() {

    //-----launch_Schotten_Totten1:

    unique_ptr<Card> card1 = make_unique<ValuedCard>(2, CardColor::orange);
    cout << *card1 << '\n' << '\n';

    Deck clanDeck = DeckFactory().createClanDeck();
    clanDeck.shuffle();



    Deck discardDeck;
    for (int i = 0; i < 15; ++i)
        discardDeck.putCard(clanDeck.drawCard());
    discardDeck.print();
    cout << '\n';

    clanDeck.print();
    return 0;


}

