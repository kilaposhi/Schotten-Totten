#ifndef SCHOTTEN_TOTTEN_STONE_H
#define SCHOTTEN_TOTTEN_STONE_H


#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "deck/Card.h"
#include "player/Player.h"
#include "board/Border.h"

using std::string, std::exception, std::vector;



class Stone : public Border{

    Stone() {}
};


#endif //SCHOTTEN_TOTTEN_STONE_H
