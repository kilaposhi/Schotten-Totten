#include "deck/Card.h"
#include "player/Player.h"
#include "board/Combination.h"
#include "Border.h"

Border::Border(unsigned int slot_number)
        : claimed(false), slot_number(slot_number){}

void Border::addValueCard(const ValuedCard &card, int player_id) {
    if(player_id == 1){
        player_1_combination.push_back(card);
    }
    else if(player_id == 2){
        player_2_combination.push_back(card);
    }
}

void Border::addTacticalCard(const Tactic_card& tactic_card, int player_id) {
    if(player_id == 1){
        player_1_tactic_card.push_back(tactic_card);
    }
    else if(player_id == 2){
        player_2_tactic_card.push_back(tactic_card);
    }
}

void Border::removeTacticalCard(int player_id) {
    if(player_id == 1){
        player_1_tactic_card.pop_back();
    }
    else if(player_id == 2){
        player_2_tactic_card.pop_back();
    }
}


unsigned int Border::getSlotNumber() const {
    return slot_number;
}

Player Border::getWinner() const {
    return winner;
}

bool Border::getClaimed() const {
    return claimed;
}

void Border::setWinner(Player winner) {
    this->winner = winner;
}

void Border::setClaimed(bool claimed) {
    this->claimed = claimed;
}



