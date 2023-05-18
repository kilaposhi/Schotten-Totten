#include "deck/Card.h"
#include "player/Player.h"
#include "board/Combination.h"
#include "Border.h"

Border::Border(Player& winner, unsigned int slot_number)
        : claimed(false), winner(winner), slot_number(slot_number) {}

void Border::addCard(const Card& card) {
    card_slot_available.push_back(card);
}

void Border::addCardTactical(const Tactic_card& card) {
    tactic_slot = card;
}

unsigned int Border::getNbBorder() const {
    return slot_number;
}

Player& Border::getWinner() {
    return winner;
}

void Border::setWinner(Player& winner) {
    this->winner = winner;
}

void Border::setClaimed(bool claimed) {
    this->claimed = claimed;
}

void Border::setPlayer1Combination(const Combination& player_1_combination) {
    this->player_1_combination = player_1_combination;
}

void Border::setPlayer2Combination(const Combination& player_2_combination) {
    this->player_2_combination = player_2_combination;
}
