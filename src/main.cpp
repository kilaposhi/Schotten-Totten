#include <iostream>
#include <string>

#include "deck/Card.h"
#include "deck/Deck.h"
#include "deck/DeckFactory.h"
#include "Game_interface.h"
#include "board/Border.h"
#include "board/Combination.h"
#include "board/GameTracker.h"
#include "game/Game.h"
#include "player/Player.h"


int main() {

//------------------- Card
    unique_ptr<Card> card1 = make_unique<ValuedCard>(2, CardColor::orange);
    unique_ptr<ValuedCard> newCard = make_unique<ValuedCard>(move(card1));


    // conversion ValuedCard vers Card est implicite
    unique_ptr<Card> reCard = std::move(newCard);

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
    Combination combination(3);
//    combination.push_back(move(valuedCard));
//    combination.push_back(make_unique<TacticCard>(TacticType::traiter));
    combination.push_back(make_unique<ValuedCard>(1, CardColor::orange));
    combination.push_back(make_unique<ValuedCard>(1, CardColor::orange));
    combination.push_back(make_unique<ValuedCard>(1, CardColor::orange));
    cout << "numberCardRemaining :" << combination.getSum();
} catch(CombinationException e){
    cout << e.what();
}

    //-----launch_Schotten_Totten1:
    Deck clanDeck = DeckFactory().createClanDeck();
    clanDeck.shuffle();
//    clanDeck.print();
    //on crée les cartes, les mélange et les affiche
//    create_borders();
    //on crée les bornes
    //on demande aux 2 joueurs quels ids ils souhaitent choisir
//    Player(int id1,  Player* p, int max_cards_)
//    Player(int id2,  Player* p, int max_cards_)
    //on crée les joueurs
    //on distribue les cartes aux joueurs
    //on a

    return 0;


}

