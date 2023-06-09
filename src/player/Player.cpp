#include "Player.h"
#include "board/Border.h"
#include "deck/Deck.h"

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Border;
class Deck;


Player::Player(string name_, int id_, int max_card, vector<unsigned int> claimed_borders_) : name(name_), id(id_), hand{}, max_cards(max_card), claimed_borders{claimed_borders_} {}

std::ostream& operator<<(std::ostream& f, const Player& player){
    int i = 0;
    for (const auto& card : player.hand) {
        // Afficher les informations de la carte dans le flux
        f << "carte" << i << *card << " ";
        i ++;
    }
    return f;
}


void Player::displayHand() const{
    cout << "Player's hand: ";
    for (const auto& cardPtr : hand) {
        cout << *cardPtr;  // Utilisez la méthode print() de la classe Card pour afficher le contenu de chaque carte
    }

}

void Player::print_player() const{
    std::cout << "-----------------\n";
    std::cout << "Player " << id << "\n";
    std::cout << "Name: " << name << "\n";
    displayHand();
    cout << "\n";
    std::cout << "-----------------\n";
}



void Player::add_card_into_hand(std::unique_ptr<Card>  card_) {
    if (hand.size() == max_cards) {
        throw PlayerException("The hand is full");
    }
    hand.push_back(std::move(card_));
}

std::unique_ptr<Card>  Player::remove_card_from_hand(int card_index) {
    card_index -= 1;
    if (hand.empty()) {
        throw PlayerException("The hand is empty");
    }
    if (card_index == hand.size()) {
        throw PlayerException("Index not found in hand");
    }
    std::unique_ptr<Card> returned_card = std::move(hand[card_index]);
    hand.erase(hand.begin() + card_index);
    return returned_card;
}

/*
void Player::play_card(int card_index, Border& border_) {
    auto played_card = remove_card_from_hand(card_index);
    border_.addCard(std::move(played_card), player);
}
*/
/*
void Player::draw_card(Deck deck_) {
    auto drawn_card = deck_.drawCard();
    add_card_into_hand(std::move(drawn_card));
}
*/
void Player::claim_borders(Border& border_){
    unsigned int border_num = border_.getSlotNumber();
    border_.setClaimed(id);
    if (border_num > 9) {                                   // Remarque 1
        throw std::out_of_range("The border index > 9");
    }
    claimed_borders.push_back(border_num);

}

vector<unsigned int> Player::getClaimed_borders(){
    vector<unsigned int> tab_of_claimed_borders;
    unsigned int count = 0;
    for (unsigned int borders : claimed_borders) {
        tab_of_claimed_borders.push_back(claimed_borders[count]);
        count++;
    }
    return tab_of_claimed_borders;
}

int Player::getNumber_of_cards() const{return hand.size();}

int Player::getId() const{
    return id;
}




