
#include <iostream>
#include <chrono>
#include "string.h"
#include "deck/Card.h"
#include "deck/Deck.h"

void function_to_measure(){
//    Deck clanDeck = DeckFactory().createClanDeck();
    Deck clanDeck;
    clanDeck = DeckFactory().createClanDeck();
    clanDeck.drawCard();
}

void measure_execution_time(){
    using std::chrono::high_resolution_clock, std::chrono::duration_cast, std::chrono::duration, std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
    function_to_measure();
    auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << ms_double.count() << "ms\n";
}

int main() {

//------------------- Card
//    Deck clanDeck;
//    clanDeck = DeckFactory().createClanDeck();
//    Deck clanDeck = DeckFactory().createClanDeck();
//    unique_ptr<Deck> clanDeck ( DeckFactory().createClanDeck());
//    clanDeck.shuffle();

measure_execution_time();

    return 0;
}

