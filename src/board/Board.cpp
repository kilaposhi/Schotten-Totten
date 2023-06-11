//
// Created by berth on 09/06/2023.
//
#include "Board.h"
#include "Border.h"

#include <vector>
#include <string>

Board::Board(int numberBorder): numberBorder_(numberBorder), winner(nullptr) {
    borders_.reserve(numberBorder_);
    for (int borderID = 0; borderID < numberBorder_; borderID++) {
        borders_.emplace_back(borderID);
    }
}

int Board::getNumberBorder() const {
    return numberBorder_;
}

Player* Board::getWinner() const {
    return winner;
}

const std::vector<Border>& Board::getBorders() const {
    return borders_;
}

Border &Board::getBorderByID(int ID) {
    if (ID < 0 || ID >= numberBorder_)
        throw BoardException("This Border id does not exist");
    return borders_[ID];
}

string Board::print() const {
    std::stringstream board("");
    for (int i=0; i<numberBorder_; i++) {
        board << borders_[i].print() << '\n'; //créer une méthode dans border
    }
    return board.str();
}


ostream &operator<<(ostream &stream, const Board &board) {
    stream << board.print();
    return stream;
}

Player* Board::hasWinner() {
    int player1Count = 0;
    int player2Count = 0;
    int adjacentCount = 1;
    Player* win = borders_[0].getWinnerBorder();
    int i = 1;
    while (win == nullptr && i<getNumberBorder()) {
        win = borders_[i].getWinnerBorder();
        i++;
    }
    int player1;
    if (win != nullptr) {
        player1 = win->getId();
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
            if (winner->getId() == player1) {
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
    winner = this->hasWinner();
}


