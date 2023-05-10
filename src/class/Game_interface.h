#ifndef SCHOTTEN_TOTTEN_GAME_INTERFACE_H
#define SCHOTTEN_TOTTEN_GAME_INTERFACE_H

#include "Card_game.h"


class Game_interface {
private:


public:
    Game_interface()=default;
    ~Game_interface()=default;
    Game_interface(const Game_interface& stone)=delete;
    Game_interface& operator=(const Game_interface& stone)=delete;

    void launch_Schotten_Totten1();
};



#endif SCHOTTEN_TOTTEN_GAME_INTERFACE_H
