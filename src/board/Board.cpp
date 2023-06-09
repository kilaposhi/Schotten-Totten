#include "Board.h"
#include "Border.h"
#include "Border.cpp"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>


const int Board::getNumberBorder() const {
    return numberBorder;
}

Player* Board::getWinner() const {
    return winner;
};

std::vector<Border> Board::getBorders() const{
    return borders;
};

Board::Board (){
    for (unsigned int i=1; i<=getNumberBorder(); i++){
        Border border(i);
        borders.push_back(border);
    }
}

/* string Board::print() const {
    std::stringstream board("");
    const Border* borders= this->getBorders();
    for (int i=0; i<getNumberBorder(); i++) {
        board << borders[i].print() //créer une méthode dans border
    }
    return board.str();
} */

ostream& operator<<(ostream& stream, const Board& board){
    stream << board.print();
    return stream;
}