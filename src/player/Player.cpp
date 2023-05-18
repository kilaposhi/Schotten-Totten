#include "Player.h"
#include "board/Stone.h"
#include "deck/Deck.h"

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Stone;
class Deck;

//Remarque1: Peut être ce serait bien d'avoir une variable nb_borders à leurs création (y en a 9 dans ST 1 et 7 dans le 2)
//Remarque 2: J'ai ajouter des méthodes get à Stone/Border pour manipuler ses attributs.

Player::Player(int id_, int max_cards_):
id(id_), number_of_cards(0), hand(),
max_cards(max_cards_),
claimed_borders_array({}),
claimed_borders_vector({})
{}

void Player::add_card_into_hand(unique_ptr<Card> card_) {
    if (hand.size() > max_cards) {
        throw PlayerException("The hand is full");
    }
    hand.push_back(std::move(card_));
}

unique_ptr<Card> Player::delete_card_from_hand(int card_index) {
    if (hand.empty()) {
        throw PlayerException("The hand is empty");
    }
    if (card_index > hand.size()) {
        throw PlayerException("Index not found in hand");
    }
    std::unique_ptr<Card> returned_card = std::move(hand[card_index]);
    hand.erase(hand.begin() + card_index);
    return returned_card;
}

void Player::play_card(int card_index, Stone& border_) {
    std::unique_ptr<Card> played_card = delete_card_from_hand(card_index);
    border_.addCard(std::move(played_card));
}

unique_ptr<Card> Player::draw_card(Deck deck_) {
    auto drawn_card = deck_.drawCard();
    add_card_into_hand(std::move(drawn_card));
    return drawn_card;
}

void Player::claim_borders_vector(Stone& border_){
    int border_num = border_.getNbStone();
    border_.claim(id);
    if (border_num > 9) {                                   // Remarque 1
        throw std::out_of_range("The border index > 9");
    }
    claimed_borders_vector.push_back(border_num);

}
vector<int> Player::getClaimed_borders_vector(){
    vector<int> tab_of_claimed_borders;
    int count = 0;
    for (int borders : claimed_borders_vector) {
        tab_of_claimed_borders.push_back(claimed_borders_vector[count]);
        count++;
    }
    return tab_of_claimed_borders;

}

int Player::getNumber_of_cards() const{return this->number_of_cards;}





