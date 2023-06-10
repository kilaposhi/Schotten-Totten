#include "Board.h"
#include "Border.h"

#include <vector>
#include <string>

Board::Board(int numberBorder_): numberBorder(numberBorder_), winner(nullptr) {
    for (int i = 1; i <= numberBorder; i++) {
        Border border = *new Border(i);
        borders.push_back(border);
    }
}

int Board::getNumberBorder() const {
    return numberBorder;
    }

Player* Board::getWinner() const {
    return winner;
}

const std::vector<Border>& Board::getBorders() const {
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
