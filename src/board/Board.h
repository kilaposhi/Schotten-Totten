#ifndef SHOTTEN_TOTTEN_BOARD_H
#define SHOTTEN_TOTTEN_BOARD_H

#include "Border.h"
#include "player/Player.h"


class Border;
class Player;

class Board {
private :
    const int numberBorder = 9;
    const list<Border> borders;
    Player* winner{};

public :
    Board()=default;
    ~Board()=default;

    int getNumberBorder() const;
    Player* getWinner() const;
    const list<Border> getBorders() const;
};


#endif //SHOTTEN_TOTTEN_BOARD_H