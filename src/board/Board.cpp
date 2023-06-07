#include "Board.h"

int Board::getNumberBorder() const {
    return numberBorder;
}

Player *Board::getWinner() const {
    return winner;
}

const list<Border> Board::getBorders() const {
    return borders;
}




