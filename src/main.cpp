#include <iostream>

#include "Class/Card.h"
#include "Class/Card_game.h"
#include "Class/Deck.h"


int main() {

    //-----launch_Shotten_Totten1:
    const int MAX_CLAN_CARD_STRENGTH = 9;
    const int MIN_CLAN_CARD_STRENGTH = 1;
    const int NUMBER_CLAN_CARDS = 54;

    Valued_Card card(3, CardColor::brown);
    cout << card << '\n';
    Card_game& game = Card_game::getInstance(NUMBER_CLAN_CARDS,MIN_CLAN_CARD_STRENGTH, MAX_CLAN_CARD_STRENGTH);
//    Deck deck(game.getCards());

//    std::cout <<" Hello world" <<std::endl;
    return 0;
}

