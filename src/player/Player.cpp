#include "Player.h"
#include "board/Border.h"
#include "deck/Deck.h"

#include <iostream>
#include <utility>
#include <vector>
#include <memory>

using namespace std;

class Border;
class Deck;


Player::Player(string name_, int id_, int max_card) : name(std::move(name_)), id(id_), hand{}, max_cards(max_card), claimed_borders{} {}

std::ostream& operator<<(std::ostream& stream, const Player& player){
   stream << player.print_player();
    return stream;
}


string Player::displayHand() const{
    std::stringstream stream("");
    stream << "Player's hand: ";
    int i =0;
    for (const auto& cardPtr : hand) {
        stream << " (" << i++ << "): " << *cardPtr << " ";  // Utilisez la méthode print() de la classe Card pour afficher le contenu de chaque carte
    }
    return stream.str();
}

string Player::print_player() const{
    std::stringstream stream("");
    stream << "-----------------\n";
    stream << "Player " << id << "\n";
    stream << "Name: " << name << "\n";
    stream << displayHand();
    stream << '\n';
    stream << "-----------------\n";
    return stream.str();
}



void Player::add_card_into_hand(std::unique_ptr<Card>  card_) {
    if (hand.size() == max_cards) {
        throw PlayerException("The hand is full");
    }
    hand.push_back(std::move(card_));
}

std::unique_ptr<Card>  Player::remove_card_from_hand(int card_index) {
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


void Player::play_card(int card_index, Border& border) {
    if (card_index < 0 || card_index >= hand.size()) {
        throw PlayerException("Invalid card index");
    }

    std::unique_ptr<Card> card = remove_card_from_hand(card_index);

    if (auto valued_card = dynamic_cast<ValuedCard*>(card.get())) {
        border.addValueCard(std::make_unique<ValuedCard>(std::move(card)), this);
    } else {
        dynamic_cast<TacticCard*>(card.get());
        TacticHandler::getInstance().playTacticCard(
                std::make_unique<TacticCard>(std::move(card)),
                this,
                border.getBorderId()
                );
//            border.addTacticalCard(std::move(unique_tactic_card), this);
    }
}

void Player::draw_card(Deck& deck_) {
    auto drawn_card = deck_.drawCard();
    add_card_into_hand(std::move(drawn_card));
}

void Player::claim_borders(Border& border_){
    unsigned int borderId = border_.getBorderId();
    //border_.getClaimed();
    if (borderId > 9 || borderId < 0) {                                   // Remarque 1
        throw std::out_of_range("The border index > 9");
    }
    claimed_borders.push_back(borderId);

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



