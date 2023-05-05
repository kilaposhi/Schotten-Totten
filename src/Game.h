#ifndef SHOTTEN_TOTTEN_GAME_H
#define SHOTTEN_TOTTEN_GAME_H


class Game {

public:

    Game();
    ~Game();
    Game(const Game& stone);
    const Game& operator=(const Game& stone);
};


#endif //SHOTTEN_TOTTEN_GAME_H
