#include <iostream>
#include "string.h"
#include "deck/Card.h"
#include "deck/Deck.h"


int main() {

//------------------- Card
    unique_ptr<Card> card1 = make_unique<ValuedCard>(2, CardColor::orange);
    unique_ptr<ValuedCard> newCard = make_unique<ValuedCard>(move(card1));


    // conversion ValuedCard vers Card est implicite
    unique_ptr<Card> reCard = std::move(newCard);

try {
    Deck clanDeck ( *DeckFactory().createClanDeck() );
//    Deck clanDeck = *DeckFactory().createClanDeck();
//    unique_ptr<Deck> clanDeck ( DeckFactory().createClanDeck());
    clanDeck.shuffle();



    Deck discardDeck;
    for (int i = 0; i < 15; ++i)
        discardDeck.putCard(clanDeck.drawCard());
    discardDeck.print();
    cout << '\n';

} catch (const CardException& e){
    cout << e.what() <<'\n';
}
//    clanDeck.print();
    return 0;
}

