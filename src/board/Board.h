#ifndef SHOTTEN_TOTTEN_BOARD_H
#define SHOTTEN_TOTTEN_BOARD_H

#include "Border.h"
#include "player/Player.h"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <memory>


using std::string, std::ostream, std::initializer_list, std::move, std::unique_ptr;


class BoardException : std::exception {
private:
    string exception_;
public:
    explicit BoardException(string&& exception) : exception_(std::move(exception)){}
    [[nodiscard]] const char* what() const noexcept override{ return exception_.c_str();}
};

class Border;
class Player;

class Board {
public :
    explicit Board(int numberBorder, Player* player1, Player* player2);
    ~Board() = default;

    [[nodiscard]] int getNumberBorder() const;
    [[nodiscard]] const std::vector<Border>& getBorders() const;
    Border& getBorderByID(int ID);
    string str() const;
    [[nodiscard]] Player* getWinner() const ;
    bool hasWinner();
    Player* getPlayer (int id);
private:
    void setWinner(Player* player);
private :
    int numberBorder_;
    std::vector<Border> borders_;
    Player* winner_{nullptr};
    Player * player1_;
    Player * player2_;
};

ostream &operator<<(ostream &stream, const Board &board);

#endif //SHOTTEN_TOTTEN_BOARD_H
