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

    unique_ptr<Card> card2 = make_unique<ValuedCard>(5, CardColor::red);
    cout << "Carte 2: " << *card2 << '\n' << '\n';

    unique_ptr<Card> card3 = make_unique<ValuedCard>(5, CardColor::blue);
    cout << "Carte 3: " << *card3 << '\n' << '\n';

    unique_ptr<Card> card4 = make_unique<ValuedCard>(4, CardColor::brown);
    cout << "Carte 4: " << *card4 << '\n' << '\n';

    unique_ptr<Card> card5 = make_unique<ValuedCard>(3, CardColor::red);
    cout << "Carte 5: " << *card5 << '\n' << '\n';

    unique_ptr<Card> card6 = make_unique<ValuedCard>(1, CardColor::red);
    cout << "Carte 6: " << *card6 << '\n' << '\n';

    unique_ptr<Card> card7 = make_unique<ValuedCard>(1, CardColor::blue);
    cout << "Carte 7: " << *card7 << '\n' << '\n';
    //Test du constructeur de Player OK

    unique_ptr<Card> card8 = make_unique<ValuedCard>(1, CardColor::yellow);
    cout << "Carte 8: " << *card8 << '\n' << '\n';

    int playerId1 = 1;
    int playerId2 = 2;
    int max_card = 7;
    vector<unsigned int> borders;
    borders.push_back(1);
    borders.push_back(4);
    borders.push_back(5);
    Player player1("Martin", playerId1, max_card, borders);
    Player player2("Lena", playerId2, max_card, borders);


    // Test de print_player() OK

    int id1, id2;
    player1.print_player();
    player2.print_player();

    id1 = player1.getId();
    id2 = player2.getId();




    // cout << "id1: " << id1 << "\n";
    // cout << "id2: " << id2 << "\n";


    // Test de add_cart_into_hand OK (Je l'ai remise en private tt de suite après)
    /*
    player1.add_card_into_hand(std::move(card1));
    player1.add_card_into_hand(std::move(card2));
    player1.add_card_into_hand(std::move(card3));
    player1.add_card_into_hand(std::move(card4));
    player1.add_card_into_hand(std::move(card5));
    player1.add_card_into_hand(std::move(card6));
    player1.add_card_into_hand(std::move(card7));


    cout << "Avec des cartes dans la main?\n";
    player1.print_player();

    player1.remove_card_from_hand(3);

    cout << "Avec une carte en moins?\n";
    player1.print_player();

    player1.add_card_into_hand(std::move(card8));

    int player1_nb_cards;
    player1_nb_cards = player1.getNumber_of_cards();

    cout << "nb de cartes de player1: " << player1_nb_cards;
    */

    /*
    Deck clanDeck = DeckFactory().createClanDeck();
    clanDeck.shuffle();



    Deck discardDeck;
    for (int i = 0; i < 15; ++i)
        discardDeck.putCard(clanDeck.drawCard());
    discardDeck.print();
    cout << '\n';

    clanDeck.print();
    */
    return 0;

}

