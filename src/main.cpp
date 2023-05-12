#include <iostream>

#include "Class/Card.h"
#include "Class/Card_game.h"
#include "Class/Deck.h"


int main() {

    //-----launch_Schotten_Totten1:
    const int MAX_CLAN_CARD_STRENGTH = 9;
    const int MIN_CLAN_CARD_STRENGTH = 1;
    const int NUMBER_CLAN_CARDS = 54;

    unique_ptr<Card> card1 = make_unique<Valued_Card>(2, CardColor::orange);
    cout << *card1 << '\n' << '\n';

    Card_game& game = Card_game::getInstance(NUMBER_CLAN_CARDS,MIN_CLAN_CARD_STRENGTH, MAX_CLAN_CARD_STRENGTH);
    auto clan_cards = game.getCards();
    Deck deck(clan_cards);
    Deck discardDeck;
    for (int i = 0; i < 15; ++i) {
        Card card = deck.drawCard();
        discardDeck.putCard(card);
    }
    discardDeck.print();
    cout << '\n';

    deck.print();
    return 0;
}

