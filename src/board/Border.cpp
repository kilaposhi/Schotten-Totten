#include "deck/Card.h"
#include "player/Player.h"
#include "board/Combination.h"
#include "Border.h"

class Player;

Border::Border(unsigned int slot_number)
        : claimed(false), slot_number(slot_number){}

void Border::addValueCard(std::unique_ptr<ValuedCard> card, Player* player) {
    int playerId = Player::getId(player);
    if (playerId == 1) {
        player_1_combination.push_back(std::move(card));
    } else if (playerId == 2) {
        player_2_combination.push_back(std::move(card));
    }
}

void Border::addTacticalCard(std::unique_ptr<Tactic_card> tactic_card, Player* player) {
    int playerId = Player::getId(player);
    if(playerId == 1){
        player_1_tactic_card.push_back(std::move(tactic_card));
    }
    else if(playerId == 2){
        player_2_tactic_card.push_back(std::move(tactic_card));
    }
}

void Border::addCard(unique_ptr<Card> card, Player* player) {
    if (auto valuedCard = dynamic_cast<ValuedCard*>(card.get())) {
        addValueCard(unique_ptr<ValuedCard>(dynamic_cast<ValuedCard*>(card.release())), player);
    }
    else {
        addTacticalCard(unique_ptr<Tactic_card>(dynamic_cast<Tactic_card*>(card.release())), player);
    }
}

void Border::removeTacticalCard(Player* player) {
    int playerId = Player::getId(player);
    if(playerId == 1){
        player_1_tactic_card.pop_back();
    }
    else if(playerId == 2){
        player_2_tactic_card.pop_back();
    }
}


unsigned int Border::getSlotNumber() const {
    return slot_number;
}


Player Border::getWinner() const {
    return* winner;
}


bool Border::getClaimed() const {
    return claimed;
}


void Border::setWinner(Player* winner) {
    this->winner = winner;
}


void Border::setClaimed(bool claimed) {
    this->claimed = claimed;
}





