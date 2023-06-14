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

unsigned int AI::pick_a_card(Border* border) {
    unsigned int max = 0;
    unsigned int index = rand() % hand.size();

    if (border->getPlayerCombination(this).getNumberCards() == 0) {
        return index;   }
    else if (border->getPlayerCombination(this).getNumberCards() == 1) {
        for (unsigned int j = 0; j < hand.size(); j++) {
            std::unique_ptr<ValuedCard> card = std::make_unique<ValuedCard>(*hand[j]);
            int potential = 0;

            if (card->getValue() == border->getPlayerCombination(this).getValuedCard(0)->getValue()) {
                potential++;
            }
            else if (abs(card->getValue() - border->getPlayerCombination(this).getValuedCard(0)->getValue()) == 1) {
                potential++;
            }
            else if (abs(card->getValue() - border->getPlayerCombination(this).getValuedCard(0)->getValue()) == 2) {
                potential++;
            }
            if (card->getColor() == border->getPlayerCombination(this).getValuedCard(0)->getColor()) {
                potential++;
            }

            if (potential > max) {
                max = potential;
                index = j;
            }
        }
    }
    else {
        vector<Combination> possibilities;

        for (unsigned int j = 0; j < hand.size(); j++) {
            std::unique_ptr<ValuedCard> card = std::make_unique<ValuedCard>(*hand[j]);
            Combination combination(border->getPlayerCombination(this));
            combination.push_back(std::move(card));
            possibilities.push_back(combination);
        }

        index = findBestCombination(possibilities);
    }
    return index;
}

unsigned int AI::pick_a_border(Board *board) {
    unsigned int max = 0;
    unsigned int index = rand() % board->getNumberBorder() ;
    vector<Combination> possibilities;
    for (unsigned int j = 0; j < board->getNumberBorder(); j++) {
        if (board->getBorderByID(j).getPlayerCombination(this).getNumberCards() == 0) {
            continue;
        } else if (board->getBorderByID(j).getPlayerCombination(this).getNumberCards() == 1) {
            std::unique_ptr<ValuedCard> card = std::make_unique<ValuedCard>(
                    *hand[this->pick_a_card(&(board->getBorderByID(j)))]);
            int potential = 0;
            if (card->getValue() == board->getBorderByID(j).getPlayerCombination(this).getValuedCard(0)->getValue()) {
                potential++;
            } else if (abs(card->getValue() -
                           board->getBorderByID(j).getPlayerCombination(this).getValuedCard(0)->getValue()) == 1) {
                potential++;
            } else if (abs(card->getValue() -
                           board->getBorderByID(j).getPlayerCombination(this).getValuedCard(0)->getValue()) == 2) {
                potential++;
            }
            if (card->getColor() == board->getBorderByID(j).getPlayerCombination(this).getValuedCard(0)->getColor()) {
                potential++;
            }

            if (potential > max) {
                max = potential;
                index = j;
            }
        } else {
            std::unique_ptr<ValuedCard> card = std::make_unique<ValuedCard>(
                    *hand[this->pick_a_card(&(board->getBorderByID(j)))]);
            Combination combination(board->getBorderByID(j).getPlayerCombination(this));
            combination.push_back(std::move(card));
            possibilities.push_back(combination);
            index = findBestCombination(possibilities);

        }
    }

   return index;
}

unsigned int AI::claim_a_border(Board* board, Player* enemy) {
    unsigned int numBorders = board->getNumberBorder();
    unsigned int index = 0;

    for (unsigned int j = 0; j < numBorders; j++) {
        if (board->getBorderByID(j).isClaimed() || board->getBorderByID(j).getPlayerCombination(this).getNumberCards() != board->getBorderByID(j).getPlayerCombination(this).getMaxNumberCards()) {
            continue;
        }

        if (board->getBorderByID(j).getPlayerCombination(this) == bestCombination(board->getBorderByID(j).getPlayerCombination(this), board->getBorderByID(j).getPlayerCombination(enemy))) {
            index = j;
            break;
        }
    }

    return index;
}
