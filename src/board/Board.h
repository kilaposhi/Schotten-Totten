#ifndef SHOTTEN_TOTTEN_BOARD_H
#define SHOTTEN_TOTTEN_BOARD_H

#include "Border.h"
#include "Border.cpp"

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


class Board {
private :
    const int numberBorder = 9;
    std::vector<Border> borders;
    Player* winner = nullptr;

public :
    Board();
    ~Board() = default;

    const int getNumberBorder() const;
    Player* getWinner() const ;
    std::vector<Border> getBorders() const;

    virtual string print() const;
};
#endif //SHOTTEN_TOTTEN_BOARD_H
