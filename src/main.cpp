#include <iostream>
#include "string.h"
#include "deck/Card.h"
#include "deck/Deck.h"


int main() {

//------------------- Card
    unique_ptr<Card> card1 = make_unique<ValuedCard>(2, CardColor::orange);

//    ValuedCard test1 = dynamic_cast<ValuedCard&>(*card1);
//    ValuedCard* test2 = dynamic_cast<ValuedCard*>(card1.release());
//    ValuedCard* test3 = dynamic_cast<ValuedCard*>(card1.get());

    unique_ptr<ValuedCard> newCard = make_unique<ValuedCard>(move(card1));
//    unique_ptr<ValuedCard> newCard = make_unique<ValuedCard>(card1.release());
//    unique_ptr<ValuedCard> newCard (dynamic_cast<ValuedCard*>(card1.release()));
    cout << newCard->getValue() << '\n' << '\n';

    // conversion ValuedCard vers Card est implicite
    unique_ptr<Card> reCard = std::move(newCard);

    Deck clanDeck = DeckFactory().createClanDeck();
    clanDeck.shuffle();



    Deck discardDeck;
    for (int i = 0; i < 15; ++i)
        discardDeck.putCard(clanDeck.drawCard());
//    discardDeck.print();
    cout << '\n';

//    clanDeck.print();
    return 0;
}

