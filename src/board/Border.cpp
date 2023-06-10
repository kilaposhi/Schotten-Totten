#include "deck/Card.h"
#include "player/Player.h"
#include "Border.h"


Border::Border(unsigned int slot_number): claimed(false), slot_number(slot_number), player_1_combination(3), player_2_combination(3)
        {}


void Border::addValueCard(std::unique_ptr<ValuedCard> valued_card, Player* player) {
    int playerId = player->getId();
    if (playerId == 1) {
        player_1_combination.push_back(std::move(valued_card));
    } else if (playerId == 2) {
        player_2_combination.push_back(std::move(valued_card));
    }
}


void Border::addTacticalCard(std::unique_ptr<TacticCard> tactic_card, Player* player) {
    int playerId = player->getId();
    if(playerId == 1){
        player_1_combination.push_back(std::move(tactic_card));
    }
    else if(playerId == 2){
        player_2_combination.push_back(std::move(tactic_card));
    }
}


void Border::removeValueCard(std::unique_ptr<ValuedCard> valued_card, Player* player) {
    if(player->getId() == 1){
        player_1_combination.pop_card(std::move(valued_card));
    }
    else if(player->getId() == 2){
        player_2_combination.pop_card(std::move(valued_card));
    }
}


void Border::removeTacticalCard(std::unique_ptr<TacticCard> tactic_card, Player* player) {
    if(player->getId() == 1){
        player_1_combination.pop_card(std::move(tactic_card));
    }
    else if(player->getId() == 2){
        player_2_combination.pop_card(std::move(tactic_card));
    }
}


unsigned int Border::getSlotNumber() const {
    return slot_number;
}


Player Border::getWinner() const {
    return *winner;
}


bool Border::getClaimed() const {
    return claimed;
}

string Border::print() const {
    std::stringstream border("");
    border << "Player 1 :";
    border << player_1_combination.print();
    border << "Player 2 :";
    border << player_2_combination.print();
    return border.str();
}

void Border::setClaimed(bool claimed) {

}


ostream &operator<<(ostream &stream, const Border& border) {
    stream << border.print();
    return stream;
}

