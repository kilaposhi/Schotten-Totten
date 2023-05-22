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
    // createClanDeck() return Deck (Deck is an r-value)
    // So we are using the move constructor here
    Deck clanDeck ( DeckFactory().createClanDeck() );
//    Deck clanDeck = DeckFactory().createClanDeck();
//    Deck clanDeck;
//    clanDeck = DeckFactory().createClanDeck(); // Move assignement

    clanDeck.print();
//    Deck otherDeck = clanDeck; // Error copy constructor is deleted
    Deck otherDeck = std::move(clanDeck); // Move constructor only




    return 0;
}

