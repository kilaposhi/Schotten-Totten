#include "Board.h"
#include "Border.h"

#include <vector>
#include <string>

Board::Board(int numberBorder, Player* player1, Player* player2): numberBorder_(numberBorder), winner_(nullptr), player1_(player1), player2_(player2) {
    borders_.reserve(numberBorder_);
    for (int borderID = 0; borderID < numberBorder_; borderID++) {
        borders_.emplace_back(borderID, player1, player2);
    }
}

int Board::getNumberBorder() const {
    return numberBorder_;
}

Player* Board::getWinner() const {
    return winner_;
}


Player * Board ::getPlayer(int id) {
    if (id ==1)
        return player1_;
    else return player2_;
}
const std::vector<Border>& Board::getBorders() const {
    return borders_;
}

Border &Board::getBorderByID(int ID) {
    if (ID < 0 || ID >= numberBorder_)
        throw BoardException("This Border id does not exist");
    return borders_[ID];
}

string Board::str() const {
    std::stringstream stream("");
    stream << "The board :\n Player 1 \t\t\t||||\t\t\t\t Player2\n ";
    stream << "------------------------------------------------";
    stream << "-------------------------------------------------\n";
    for (int i=0; i<numberBorder_; i++) {
        stream << borders_[i].str() << '\n' ;
    }
    return stream.str();
}


bool Board::hasWinner() {
    if (player1_->getNumClaimedBorder() > 5) {
        setWinner(player1_);
        return true;
    }
    if (player2_->getNumClaimedBorder() > 5) {
        setWinner(player2_);
        return true;
    }

    int player1_count{0};
    int player2_count{0}; // Adjacent count
    for (size_t i = 0; i < getNumberBorder(); i++){
        Border& border = getBorderByID(i);
        if (border.isClaimed()){
            if (player1_->getID() == border.getWinnerBorder()->getID()){
                player1_count++;
                player2_count =  0;
            }
            else {
                player2_count++;
                player1_count = 0;
            }
        }
        if (player1_count == 3){
            setWinner(player1_);
            return true;
        }
        if (player2_count == 3){
            setWinner(player2_);
            return true;
        }
    }
    return false;
}

void Board::setWinner(Player* player) {
    winner_ = player;
}

ostream &operator<<(ostream &stream, const Board &board) {
    stream << board.str();
    return stream;
}

