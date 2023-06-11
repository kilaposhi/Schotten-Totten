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
private :
    int numberBorder_;
    std::vector<Border> borders_;
    Player* winner;

public :
    explicit Board(int numberBorder);
    ~Board() = default;

    [[nodiscard]] int getNumberBorder() const;
    [[nodiscard]] Player* getWinner() const ;
    [[nodiscard]] const std::vector<Border>& getBorders() const;
    Border& getBorderByID(int ID);

    string print() const;
    Player* hasWinner();
    void setWinner();
};
#endif //SHOTTEN_TOTTEN_BOARD_H
