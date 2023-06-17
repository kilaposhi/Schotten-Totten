#include "Board.h"

#include "border/Border.h"

#include <vector>
#include <string>


Board::Board(int numberBorder, Player* player1, Player* player2): numberBorder_(numberBorder), winner_(nullptr) {
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


Player* Board::hasWinner() {
    int player1Count = 0;
    int player2Count = 0;
    int adjacentCount = 1;
    Player* win = borders_[0].getWinnerBorder();
    int i = 1;
    while (win == nullptr && i < getNumberBorder()) {
        win = borders_[i].getWinnerBorder();
        i++;
    }
    int player1;
    if (win != nullptr) {
        player1 = win->getID();
    }
    else {
        player1 = -1;
    }
    Player* last = win;
    while ((i<getNumberBorder()) && (player1Count<5) && (player2Count<5) && (adjacentCount<3) ) {
        Player* winner = borders_[i].getWinnerBorder();
        if (winner != nullptr) {
            if (winner == last) {
                adjacentCount += 1;
            }
            else {
                adjacentCount = 1;
            }
            if (winner->getID() == player1) {
                player1Count += 1;
            }
            else {
                player2Count +=1;
            }

        }
        i++;
    }
    if (i>=getNumberBorder() && (player1Count<5) && (player2Count<5) && (adjacentCount<3)) {
        return nullptr;
    }
    else {
        return win;
    }
}

void Board::setWinner() {
    winner_ = this->hasWinner();
}

ostream &operator<<(ostream &stream, const Board &board) {
    stream << board.str();
    return stream;
}
