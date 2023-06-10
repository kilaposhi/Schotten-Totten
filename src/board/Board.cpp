//
// Created by berth on 09/06/2023.
//
#include "Board.h"
#include "Border.h"

#include <vector>
#include <string>

Board::Board(int numberBorder_): numberBorder(numberBorder_), winner(nullptr) {
    for (int i = 1; i <= numberBorder; i++) {
        Border border(i);
        borders.push_back(&border);
    }
}

int Board::getNumberBorder() const {
    return numberBorder;
}

Player* Board::getWinner() const {
    return winner;
}

const std::vector<Border*>& Board::getBorders() const {
    return borders;
}

/* string Board::print() const {
    std::stringstream board("");
    const Border* borders= this->getBorders();
    for (int i=0; i<getNumberBorder(); i++) {
        board << borders[i].print() //créer une méthode dans border
    }
    return board.str();
} */

string Board::print() const{return "Board::print()";}

ostream &operator<<(ostream &stream, const Board &board) {
    stream << board.print();
    return stream;
}

Player* Board::hasWinner() {
    const std::vector<Border*>& borders = this->getBorders();
    int player1Count = 0;
    int player2Count = 0;
    int adjacentCount = 1;
    Player* win = borders[0]->getWinnerBorder();
    int i = 1;
    while (win == nullptr && i<getNumberBorder()) {
        win = borders[i]->getWinnerBorder();
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
        Player* winner = borders[i]->getWinnerBorder();
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


