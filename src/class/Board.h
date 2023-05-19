

#ifndef SHOTTEN_TOTTEN_BOARD_H
#define SHOTTEN_TOTTEN_BOARD_H

class Board {
private :
    const int numberBorder = 9;
    const list<Border> borders;
    Player* winner;
public :
    Board()=default;
    ~Board()=default;

    const int getNumberBorder() const {return numberBorder};
    Player* getWinner() const {return winner};
    const list<Border> getBorders() const {return borders};

};
#endif //SHOTTEN_TOTTEN_BOARD_H
