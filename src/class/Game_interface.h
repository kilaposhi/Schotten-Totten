#ifndef SHOTTEN_TOTTEN_GAME_INTERFACE_H
#define SHOTTEN_TOTTEN_GAME_INTERFACE_H

#include "Card_game.h"


class Game_interface {
private:


public:
    Game_interface()=default;
    ~Game_interface()=default;
    Game_interface(const Game_interface& stone)=delete;
    Game_interface& operator=(const Game_interface& stone)=delete;

    void launch_Shotten_Totten1();
};



#endif //SHOTTEN_TOTTEN_GAME_INTERFACE_H
