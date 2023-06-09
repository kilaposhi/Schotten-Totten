#ifndef BOARD_H
#define BOARD_H

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

class Player;
class Border;

class Board {
private :
    int numberBorder_;
    std::vector<Border> borders_;
    Player* winner_{nullptr};

public :
    explicit Board(int numberBorder, Player* player1, Player* player2);
    ~Board() = default;

    [[nodiscard]] int getNumberBorder() const;
    [[nodiscard]] Player* getWinner() const ;
    [[nodiscard]] const std::vector<Border>& getBorders() const;
    Border& getBorderByID(int ID);

    string str() const;
    Player* hasWinner();
    void setWinner();
};

ostream &operator<<(ostream &stream, const Board &board);


#endif // BOARD_H
