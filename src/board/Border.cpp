#include "deck/Card.h"
#include "player/Player.h"
#include "Border.h"


Border::Border(int borderID):
        borderID_(borderID),
        claimed(false),
        player_1_combination(NUMBER_CARDS),
        player_2_combination(NUMBER_CARDS),
        winner(nullptr)
        {}

Border::Border(Border &&border) :
        borderID_(border.borderID_),
        claimed(border.claimed),
        winner(border.winner),
        player_1_combination(std::move(border.player_1_combination)),
        player_2_combination(std::move(border.player_2_combination))
        { }

Border &Border::operator=(Border &&border) {
    this->borderID_ = border.borderID_;
    this->claimed = border.claimed;
    this->winner = border.winner;
    this->player_1_combination = std::move(border.player_1_combination);
    this->player_2_combination = std::move(border.player_2_combination);
    return *this;
}

void Border::addValueCard(std::unique_ptr<ValuedCard> valued_card, Player* player) {
    int playerId = player->getId();
    if (playerId == 1) {
        player_1_combination.push_back(std::move(valued_card)); // Utilise std::move ici
    } else if (playerId == 2) {
        player_2_combination.push_back(std::move(valued_card)); // Utilise std::move ici
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


Player* Border::getWinnerBorder() const {
    return winner;
}


bool Border::getClaimed() const {
    return claimed;
}

string Border::print() const {
    std::stringstream border("");
    border << "Border " << borderID_ << " : \n";
    border << "\t Player 1 :";
    border << player_1_combination.print();
    border << "\t Player 2 :";
    border << player_2_combination.print();
    return border.str();
}

//void Border::Claimed(bool claimed) {}


ostream &operator<<(ostream &stream, const Border& border) {
    stream << border.print();
    return stream;
}

