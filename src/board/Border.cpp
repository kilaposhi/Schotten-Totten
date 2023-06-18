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

Combination &Border::getPlayerCombination(Player *player) const{
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

Player* Border::getWinnerBorder() const {
    return winner_;
}


bool Border::isClaimed() const {
    return claimed;
}

void Border::setMaxNumberCard(int maxNumberCard) {
    mudFight = true;
    player_1_combination->setMaxNumberCards(maxNumberCard);
    player_2_combination->setMaxNumberCards(maxNumberCard);
}

void Border::setNoCombinationRules() {
    blindManBluff = true;
    player_1_combination->setNoCombinationRule();
    player_2_combination->setNoCombinationRule();
}



bool Border::claim(Player* claimer, Player* opponent, GameTracker& gameTracker){
    bool isClaimSucceeded = false;
    if(isClaimed())
        throw BorderException("The border is already claimed");
    if(getPlayerCombination(claimer).getNumberCards() < getPlayerCombination(claimer).getMaxNumberCards())
        throw BorderException("You have not placed enough cards on this border");
    if(getPlayerCombination(opponent).getNumberCards() == getPlayerCombination(opponent).getMaxNumberCards()){
        const Combination& best = bestCombination(getPlayerCombination(claimer).getConstReference(),
                                                  getPlayerCombination(opponent).getConstReference());
        if (best == getPlayerCombination(opponent))
            throw BorderException("Your combination is less than your opponent’s");
        claimed = true;
        winner_ = claimer;
        isClaimSucceeded = true;
        cout << "You have won the border " << borderID_ << "\n";
        return isClaimSucceeded;
    }
    else if(getPlayerCombination(opponent).getNumberCards() < getPlayerCombination(opponent).getMaxNumberCards()){
        if(//isTacticVersion()
        0 == 1 ){ // pour ne jamais y passer pour le moment
            throw BorderException("Je l'ai pas fait encore");
        }
        else {
            const Combination &best = bestCombination(getPlayerCombination(claimer).getConstReference(),
                                                      gameTracker.getOpponentBestPossibleCombinationClassicVersion(
                                                              getPlayerCombination(opponent)));
            if (best == getPlayerCombination(opponent))
                throw BorderException("Your opponent can still has a better combination on this border");
            claimed = true;
            winner_ = claimer;
            isClaimSucceeded = true;
            cout <<  claimer->getName() << "has won the border " << borderID_ << "\n";
            return isClaimSucceeded;
        }
    }
    return isClaimSucceeded;
}

string Border::str() const {
    std::stringstream stream("");
//    stream << "Border " << borderID_ << " : \n";
    stream << "[ " << player_1_combination->str() << "] ";
    stream << " Border " << borderID_ << " ";
    if (claimed)
        stream << "claimed by" << *winner_ ;
    else
        stream << "is unclaimed";
    stream << " (Tactic Card :";
    if (!blindManBluff && !mudFight)
        stream << " None ";
    if (blindManBluff)
        stream << " Blind-Man's Bluff ";
    if (mudFight)
        stream << " Mud Fight ";
    stream << ")  ";
    stream << "[ " << player_2_combination->str() << "] ";
    return stream.str();
}

//void Border::Claimed(bool claimed) {}


ostream &operator<<(ostream &stream, const Border& border) {
    stream << border.str();
    return stream;
}

