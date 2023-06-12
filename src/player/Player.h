#ifndef SCHOTTEN_TOTTEN_PLAYER_H
#define SCHOTTEN_TOTTEN_PLAYER_H

#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include <string>
#include <variant>
#include <sstream>

#include "deck/Card.h"
#include "board/Border.h"
#include "board/Board.h"
#include "deck/Deck.h"
#include "TacticHandler.h"

using std::vector;
using std::list;
using std::array;
using std::string;


class PlayerException : public std::exception {
private:
    std::string message;

public:
    explicit PlayerException(string  errorMessage)
            : message(std::move(errorMessage)) {}

    [[nodiscard]]const char* what() const noexcept override {
        return message.c_str();
    }
};

class Border;

class Player {
private:
    string name;
    vector<unique_ptr<Card>> hand;
    int max_cards;
    int id_;
    vector<unsigned int> claimed_borders;
    void add_card_into_hand(std::unique_ptr<Card>  card_); 
    std::unique_ptr<Card>  remove_card_from_hand(int card_index); 

public:

    ~Player()=default;
    explicit Player(string nom_, int id, int max_card);

    Player& operator = (const Player&) = delete;
    Player(const Player&) = delete;

    void play_card(int card_index, int borderIndex, Board* board);
    void draw_card(Deck& deck_);
    void fillHand(Deck& deck);
    void claim_borders(Border& border_);
    vector<unsigned int> getClaimed_borders(); // --> OK
    [[nodiscard]] int getNumber_of_cards() const; // --> OK
    int getID() const;
    string getName() const { return name; }
    string displayHand() const; // --> OK
    string print_player() const; // --> OK
};

std::ostream& operator<<(std::ostream& f, const Player& player);



#endif// SCHOTTEN_TOTTEN_PLAYER_H
