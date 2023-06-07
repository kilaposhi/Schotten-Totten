#include <iostream>

#include "deck/Card.h"
#include "deck/Deck.h"
#include "player/Player.h"


int main() {

    //-----launch_Schotten_Totten1:

    unique_ptr<Card> card1 = make_unique<ValuedCard>(2, CardColor::orange);
    cout << "Carte 1: " << *card1 << '\n' << '\n';
    // cout << "Test de la méthode print() de Card:\n";
    // card1->print();
    // Ce test ne fonctionne pas

    unique_ptr<Card> card2 = make_unique<ValuedCard>(2, CardColor::orange);
    cout << "Carte 2: " << *card1 << '\n' << '\n';

    // Test du constructeur de Player OK
    // std::cout << "Celui qui a voyage recemment le plus près de l'Ecosse sera le joueur 1:\n ";
    /*
    std::cout << "Joueur 1, entrez votre nom : \n";
    string name1, name2;
    std::cin >> name1;
    std::cout << "Joueur 2, entrez votre nom : \n";
    std::cin >> name2;


    int playerId1 = 1;
    int playerId2 = 2;
    int max_card = 7;
    Player player1("Martin", playerId1, max_card);
    Player player2("Léna", playerId2, max_card);
    */

    // Test de print_player() OK
    /*
    player1.print_player();
    player2.print_player();

    // Test de add_cart_into_hand OK (Je l'ai remise en private tt de suite après)
    player1.add_card_into_hand(std::move(card1));
    cout << "Avec une carte dans la main?\n";
    player1.print_player();
     */


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

