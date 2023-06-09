#include "deck/Card.h"
#include "player/Player.h"
#include "board/Combination.h"
#include "Border.h"


Border::Border(unsigned int slot_number, Combination player1Combination, Combination player2Combination1)
        : claimed(false), slot_number(slot_number), player_1_combination(player1Combination),
          player_2_combination(player2Combination1) {
            const int maxNumberCard = 3;
            Combination player_1_combination(maxNumberCard);
            Combination player_2_combination(maxNumberCard);
        }


void Border::addValueCard(std::unique_ptr<ValuedCard> valued_card, Player* player) {
    int playerId = player->getId(player);
    if (playerId == 1) {
        player_1_combination.push_back(std::move(valued_card));
    } else if (playerId == 2) {
        player_2_combination.push_back(std::move(valued_card));
    }
}


void Border::addTacticalCard(std::unique_ptr<TacticCard> tactic_card, Player* player) {
    int playerId = player->getId(player);
    if(playerId == 1){
        player_1_combination.push_back(std::move(tactic_card));
    }
    else if(playerId == 2){
        player_2_combination.push_back(std::move(tactic_card));
    }
}


void Border::removeValueCard(std::unique_ptr<ValuedCard> valued_card, Player* player) {
    if(player->getId(player) == 1){
        player_1_combination.pop_card(std::move(valued_card));
    }
    else if(player->getId(player) == 2){
        player_2_combination.pop_card(std::move(valued_card));
    }
}


void Border::removeTacticalCard(std::unique_ptr<TacticCard> tactic_card, Player* player) {
    if(player->getId(player) == 1){
        player_1_combination.pop_card(std::move(tactic_card));
    }
    else if(player->getId(player) == 2){
        player_2_combination.pop_card(std::move(tactic_card));
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

string Border::print() const {
    std::stringstream card("");
    card << "|" << "_" << "|";
    return card.str();
}

void Border::Claimed(bool claimed) {

}

ostream &operator<<(ostream &stream, const Border& border) {
    stream << border.print();
    return stream;
}

