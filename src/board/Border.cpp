#include "deck/Card.h"
#include "player/Player.h"
#include "Border.h"


Border::Border(int borderID, Player* player1, Player* player2):
        borderID_(borderID),
        player_1_combination(make_unique<Combination>(NUMBER_CARDS, player1)),
        player_2_combination(make_unique<Combination>(NUMBER_CARDS, player2))
        {}

Border::Border(Border &&border) :
        borderID_(border.borderID_),
        claimed(border.claimed),
        winner_(border.winner_),
        player_1_combination(std::move(border.player_1_combination)),
        player_2_combination(std::move(border.player_2_combination))
        { }

Border &Border::operator=(Border &&border) {
    if (this == &border)
        return *this;
    this->borderID_ = border.borderID_;
    this->claimed = border.claimed;
    this->winner_ = border.winner_;
    this->player_1_combination = std::move(border.player_1_combination);
    this->player_2_combination = std::move(border.player_2_combination);
    return *this;
}

Combination &Border::getPlayerCombination(Player *player) {
    bool isPlayer1 = player == player_1_combination->getPlayerID();
    if (isPlayer1)
        return *player_1_combination;
    return *player_2_combination;
}

void Border::addValueCard(std::unique_ptr<ValuedCard> valued_card, Player* player) {
    getPlayerCombination(player).push_back(std::move(valued_card));
}


void Border::addTacticalCard(std::unique_ptr<TacticCard> tactic_card, Player* player) {
    getPlayerCombination(player).push_back(std::move(tactic_card));
}


void Border::removeValueCard(std::unique_ptr<ValuedCard> valued_card, Player* player) {
    getPlayerCombination(player).pop_card(std::move(valued_card));
}


void Border::removeTacticalCard(std::unique_ptr<TacticCard> tactic_card, Player* player) {
    getPlayerCombination(player).pop_card(std::move(tactic_card));
}


Player* Border::getWinnerBorder() const {
    return winner_;
}


bool Border::getClaimed() const {
    return claimed;
}

void Border::setMaxNumberCard(int maxNumberCard) {
    player_1_combination->setMaxNumberCards(maxNumberCard);
    player_2_combination->setMaxNumberCards(maxNumberCard);
}

void Border::setNoCombinationRules() {
    player_1_combination->setNoCombinationRule();
    player_2_combination->setNoCombinationRule();
}

string Border::print() const {
    std::stringstream border("");
    border << "Border " << borderID_ << " : \n";
    border << "\t Player 1 :";
    border << player_1_combination->print();
    border << "\t Player 2 :";
    border << player_2_combination->print();
    return border.str();
}

//void Border::Claimed(bool claimed) {}


ostream &operator<<(ostream &stream, const Border& border) {
    stream << border.print();
    return stream;
}

