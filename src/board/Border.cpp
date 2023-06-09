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



bool Border::claim(Player* claimer){
    GameTracker& gameTracker =  GameTracker::getInstance();
    Player* opponent = gameTracker.getOpponent(claimer);
    Combination &claimer_combi = getPlayerCombination(claimer);
    Combination& opps_combi = getPlayerCombination(opponent);
    if(isClaimed())
        throw BorderException("The border is already claimed");
    if (claimer_combi.getNumberCards() < claimer_combi.getMaxNumberCards()) {
        cout << "You have not placed enough cards on this border \n";
        return false;
    }
    if(claimer_combi.isComplete() && opps_combi.isComplete()){
        if (claimer_combi.getNumberTacticCards()>0)
            claimer_combi.treatTacticCards();
        if (opps_combi.getNumberTacticCards()>0)
            opps_combi.treatTacticCards();
        Combination best = bestCombination(claimer_combi, opps_combi);
        if (best.getMaxNumberCards() == 0){
            cout << "Your combination are perfectly equals !";
            return false;
        }
        if (best == opps_combi) {
            cout << "Your combination is less than your opponent’s";
            return false;
        }
        if ( best == claimer_combi) {
            claimed = true;
            winner_ = claimer;
            claimer->claim_borders(*this);
            cout << claimer->getName() << " has won the border " << borderID_ << " !\n";
            return true;
        }
    }
    return false;
//    if(!opps_combi.isComplete()){
//        if(//isTacticVersion()
//        0 == 1 ){ // pour ne jamais y passer pour le moment
//            throw BorderException("Je l'ai pas fait encore");
//        }
//        else {
//            Combination best= bestCombination(getPlayerCombination(claimer),
//                                              gameTracker.getOpponentBestPossibleCombinationClassicVersion(
//                                                              getPlayerCombination(opponent)));
//            if (best == getPlayerCombination(opponent)) {
//                cout << "Your opponent can still have a better combination on this border\n";
//                return false;
//            }
//            if (best.getMaxNumberCards() == 0){
//                cout << "Your opponent can have at least a perfect equality with you! \n";
//                return false;
//            }
//            claimed = true;
//            winner_ = claimer;
//            claimer->claim_borders(*this);
//            cout <<  claimer->getName() << " has won the border " << borderID_ << "\n";
//            return true;
//        }
//    }
}

string Border::str() const {
    std::stringstream stream("");
    stream << "[ " << player_1_combination->str() << "] ";
    stream << " Border " << borderID_ << " ";
    if (claimed)
        stream << "claimed by " << *winner_ ;
    else
        stream << "is unclaimed";
    stream << " (Tactic Card:";
    if (!blindManBluff && !mudFight)
        stream << " None ";
    if (blindManBluff)
        stream << " Blind-Man's Bluff";
    if (mudFight)
        stream << " Mud Fight";
    stream << ")  ";
    stream << "[ " << player_2_combination->str() << "] ";
    return stream.str();
}


ostream &operator<<(ostream &stream, const Border& border) {
    stream << border.str();
    return stream;
}

