#include <iostream>
#include <string>


#include "deck/DeckFactory.h"
#include "board/Board.h"
#include "game/Game.h"

using std::cout;

int main() {
    Player player1("oui", 7);
    Player player2("non",7);
    Board board(9, &player1, &player2);
    Deck clanDeck = DeckFactory().createClanDeck();
    DeckInfo clanDeckInfo = DeckFactory().getDeckInfo();
    clanDeck.shuffle();
    Deck tacticDeck = DeckFactory().createTacticDeck();
    Deck discardDeck;
    TacticHandler instance = TacticHandler::getInstance(&clanDeck, &clanDeckInfo, &tacticDeck, &discardDeck, &board);


    for (int i = 0; i < 4; i++) {
        player1.draw_card(clanDeck);
        player2.draw_card(clanDeck);
    }

    for (int i = 0; i < 4; i++) {
        tacticDeck.drawCard();
    }
    player1.draw_card(tacticDeck);
    player1.draw_card(tacticDeck);
    cout << player1.displayHand() << "\n";
    player1.play_card(1, board.getBorderByID(0));
    player1.play_card(1, board.getBorderByID(0));
    player1.play_card(3, board.getBorderByID(0));
    player2.play_card(1, board.getBorderByID(0));
    player2.play_card(1, board.getBorderByID(0));
    player2.play_card(1, board.getBorderByID(0));
    player1.play_card(2, board.getBorderByID(0));
    player2.play_card(0, board.getBorderByID(0));

    cout << board.print();

}

/*
        Board board(9);

        int max_cards_per_hand;
        static bool tactic;
        bool valid = false;

        while(!valid){
            std::cout << "Would you like to play the tactic version ? yes/no \n";
            std::string answer;
            std::cin >> answer;
            if (answer == "yes"){
                Deck tacticDeck = DeckFactory().createTacticDeck();
                tacticDeck.shuffle();
                tacticDeck.print();
                max_cards_per_hand = 7;
                tactic = true;
                valid = true;
            }
            else if (answer == "no") {
                max_cards_per_hand = 6;
                tactic = false;
                valid = true;
            }
        }

        // board.print();
        std::cout << "Who traveled near Scotland the most recently. \n";
        std::cout << "You are player 1! Please give your name and id \n.";
        std::string name;
        std::cin >> name;
        Player player1(name, 1, max_cards_per_hand);
        std::cout << "Player 2 please give your name and id \n.";
        std::cin >> name;
        Player player2(name, 2, max_cards_per_hand);
        Game game( &player1, &player2);
        game.play(player1, player2, board);

        return 0;
    }


*/
/*
    // conversion ValuedCard vers Card est implicite
    unique_ptr<Card> reCard = std::move(reCard);

// ----------------Deck
    // createClanDeck() return Deck (Deck is an r-value)
    // So we are using the move constructor here
//    Deck clanDeck = DeckFactory().createClanDeck();
//    Deck clanDeck;
//    clanDeck = DeckFactory().createClanDeck(); // Move assignement

//    Deck otherDeck = clanDeck; // Error copy constructor is deleted
//    Deck otherDeck = std::move(clanDeck); // Move constructor only

//----------- Combination
try {
    unique_ptr<Card> card_test = make_unique<ValuedCard>(2, CardColor::orange);
    unique_ptr<ValuedCard> valuedCard= make_unique<ValuedCard>(move(card_test));
    Combination combination(4);
//    combination.push_back(move(valuedCard));
//    combination.push_back(make_unique<TacticCard>(TacticType::traiter));
    combination.push_back(make_unique<ValuedCard>(6, CardColor::orange));
    combination.push_back(make_unique<ValuedCard>(7, CardColor::brown));
    combination.push_back(make_unique<ValuedCard>(5, CardColor::brown));
    combination.push_back(make_unique<ValuedCard>(1, CardColor::orange));
    //cout << "numberCardRemaining :" << combination.getSum();
    cout << combination ;

} catch(CombinationException e){
    cout << e.what();
}

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
  
    //on crée les cartes, les mélange et les affiche
//    create_borders();
    //on crée les bornes
    //on demande aux 2 joueurs quels ids ils souhaitent choisir
//    Player(int id1,  Player* p, int max_cards_)
//    Player(int id2,  Player* p, int max_cards_)
    //on crée les joueurs
    //on distribue les cartes aux joueurs
    //on a
   // std::vector<std::unique_ptr<Border>> = create_borders();




    Deck discardDeck;
    for (int i = 0; i < 15; ++i)
        discardDeck.putCard(clanDeck.drawCard());
    discardDeck.print();
    cout << '\n';

    clanDeck.print();
    */
