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
    int numberBorder;
    std::vector<Border> borders;
    Player* winner;

public :
    explicit Board(int numberBorder_);
    ~Board() = default;

    [[nodiscard]] int getNumberBorder() const;
    [[nodiscard]] Player* getWinner() const ;
    [[nodiscard]] const std::vector<Border>& getBorders() const;
    [[nodiscard]] virtual string print() const;
};
#endif //SHOTTEN_TOTTEN_BOARD_H

