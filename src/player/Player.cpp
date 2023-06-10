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


void Player::play_card(int card_index, Border& border) {
    if (card_index < 0 || card_index >= hand.size()) {
        throw PlayerException("Invalid card index");
    }

    std::unique_ptr<Card> card = remove_card_from_hand(card_index);

    if (auto valued_card = dynamic_cast<ValuedCard*>(card.get())) {
        std::unique_ptr<ValuedCard> unique_valued_card = std::make_unique<ValuedCard>(*valued_card);
        border.addValueCard(std::move(unique_valued_card), this);
    } else if (auto tactic_card = dynamic_cast<TacticCard*>(card.get())) {
        TacticType type = tactic_card->getName();
        if (type == TacticType::joker || type == TacticType::spy || type == TacticType::shield_bearer ||
            type == TacticType::blind_man_bluff || type == TacticType::mud_fight) {
            std::unique_ptr<TacticCard> unique_tactic_card(tactic_card);
            border.addTacticalCard(std::move(unique_tactic_card), this);
        } else if (type == TacticType::recruiter || type == TacticType::strategist ||
                   type == TacticType::banshee || type == TacticType::traiter) {
            // Ajouter la carte à la défausse
            // defausse.push_back(std::move(card)); --> où est défausse
        } else {
            // Type de carte tactique non pris en charge, vous pouvez gérer l'erreur en conséquence
            throw PlayerException("Unsupported tactic card type");
        }
    } else {
        // Type de carte non pris en charge, vous pouvez gérer l'erreur en conséquence
        throw PlayerException("Unsupported card type");
    }
}

void Player::draw_card(Deck deck_) {
    auto drawn_card = deck_.drawCard();
    add_card_into_hand(std::move(drawn_card));
}

void Player::claim_borders(Border& border_){
    unsigned int border_num = border_.getSlotNumber();
    //border_.getClaimed();
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
