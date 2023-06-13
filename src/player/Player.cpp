#include "Player.h"
#include "board/Border.h"
#include "deck/Deck.h"

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <sstream>

using namespace std;

Player::Player(string name_, int id, int max_card) : name(std::move(name_)), id_(id), max_cards(max_card) {}

AI::AI(unsigned int max_cards, const string& name) : Player(name, 2, max_cards) {}

string Player::displayHand() const {
    std::stringstream stream("");
    stream << "Player " << id_ << " hand: ";
    int i = 0;
    for (const auto& cardPtr : hand) {
        stream << " (" << i++ << "): " << *cardPtr << " ";
    }
    return stream.str();
}

string Player::displayCard(int index_card) const {
    std::stringstream card("");
    card << *hand[index_card];
    return card.str();
}

std::unique_ptr<Card>& Player::getCardAtIndex(int index) {
    if (index < 0 || index >= hand.size()) {
        throw PlayerException("Invalid card index.");
    }
    return hand[index];
}

string Player::print_player() const {
    std::stringstream stream("");
    stream << "-----------------\n";
    stream << "Player " << id_ << ": " << name << "\n";
    stream << displayHand();
    stream << '\n';
    stream << "-----------------\n";
    return stream.str();
}

void Player::add_card_into_hand(std::unique_ptr<Card> card_) {
    if (hand.size() == max_cards) {
        throw PlayerException("The hand is full");
    }
    hand.push_back(std::move(card_));
}

std::unique_ptr<Card> Player::remove_card_from_hand(int card_index) {
    if (hand.empty()) {
        throw PlayerException("The hand is empty");
    }
    if (card_index >= hand.size()) {
        throw PlayerException("Index not found in hand");
    }
    std::unique_ptr<Card> returned_card = std::move(hand[card_index]);
    hand.erase(hand.begin() + card_index);
    return returned_card;
}

void Player::play_card(int card_index, int borderIndex, Board* board) {
    if (card_index < 0 || card_index >= hand.size()) {
        throw PlayerException("Invalid card index");
    }
    if (borderIndex < 0 || borderIndex >= board->getNumberBorder()) {
        throw PlayerException("Invalid border index");
    }

    std::unique_ptr<Card> card = remove_card_from_hand(card_index);

    if (auto valued_card = dynamic_cast<ValuedCard*>(card.get())) {
        board->getBorderByID(borderIndex).addValueCard(
                std::make_unique<ValuedCard>(std::move(card)),
                this
        );
    } else {
        TacticHandler::getInstance().playTacticCard(
                std::make_unique<TacticCard>(std::move(card)),
                this,
                borderIndex
        );
    }
}

void Player::draw_card(Deck& deck_) {
    if (!deck_.isEmpty()) {
        auto drawn_card = deck_.drawCard();
        add_card_into_hand(std::move(drawn_card));
    } else {
        throw PlayerException("Can't draw card because the deck is empty");
    }
}

void Player::fillHand(Deck& deck) {
    if (hand.size() == max_cards) {
        throw PlayerException("The hand is already full");
    }

    for (size_t i = 0; i < max_cards; i++) {
        draw_card(deck);
    }
}

void Player::claim_borders(Border& border_) {
    unsigned int borderId = border_.getBorderId();
    if (borderId > 9 || borderId < 0) {
        throw std::out_of_range("The border index > 9");
    }
    claimed_borders.push_back(borderId);
}

vector<unsigned int> Player::getClaimed_borders() {
    vector<unsigned int> tab_of_claimed_borders;
    for (unsigned int borders : claimed_borders) {
        tab_of_claimed_borders.push_back(borders);
    }
    return tab_of_claimed_borders;
}

int Player::getNumber_of_cards() const {
    return hand.size();
}

int Player::getID() const {
    return id_;
}

std::ostream& operator<<(std::ostream& stream, const Player& player) {
    stream << "Player " << player.getID();
    return stream;
}

int AI::pick_a_card(Border* border) {
    // Ajoutez ici la logique pour choisir la meilleure carte parmi les possibilités
    // Remplacez cette ligne par votre logique réelle
    return 0; // Exemple : retourne une valeur par défaut
}

int AI::claim_a_border(Board* board, Player* enemy) {
    // Ajoutez ici la logique pour choisir la meilleure frontière à réclamer
    // Remplacez cette ligne par votre logique réelle
    return 0; // Exemple : retourne une valeur par défaut
}
