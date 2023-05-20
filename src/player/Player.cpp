#include "Player.h"
#include "board/Border.h"
#include "deck/Deck.h"

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Border;
class Deck;


Player::Player(Player* p, int max_card_) : player(p), hand{}, max_cards(), claimed_borders_vector{} {}

void Player::add_card_into_hand(unique_ptr<Card> card_) {
    if (hand.size() == max_cards) {
        throw PlayerException("The hand is full");
    }
    hand.push_back(std::move(card_));
}

unique_ptr<Card> Player::remove_card_from_hand(int card_index) {
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

void Player::play_valued_card(int card_index, Border& border_) {
    std::unique_ptr<Card> played_card = remove_card_from_hand(card_index);
    border_.addValueCard(std::move(played_card), id);
}

void Player::play_tactical_card(int card_index, Border& border_){
    std::unique_ptr<Card> played_card = remove_card_from_hand(card_index);
    border_.addTacticalCard(std::move(played_card), id);
}


void Player::draw_card(Deck deck_) {
    auto drawn_card = deck_.drawCard();
    add_card_into_hand(std::move(drawn_card));
}

void Player::claim_borders_vector(Border& border_){
    unsigned int border_num = border_.getSlotNumber();
    border_.setClaimed(id);
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

int Player::getNumber_of_cards() const{return hand.size();}





