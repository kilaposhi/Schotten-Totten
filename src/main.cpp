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

// ----------------Deck
    Deck classicDeck = DeckFactory().createClassicDeck();
    classicDeck.print();
    cout << classicDeck;

    return 0;


}

