#ifndef SCHOTTEN_TOTTEN_PLAYER_H
#define SCHOTTEN_TOTTEN_PLAYER_H

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <variant>

#include "deck/Card.h"
#include "board/Border.h"
#include "board/Stone.h"

using std::vector;
using std::list;
using std::array;
using std::string;

class Border;
class Deck;

class PlayerException : public std::exception {
private:
    std::string message;

public:
    explicit PlayerException(const string& errorMessage)
            : message(errorMessage) {}

    [[nodiscard]]const char* what() const noexcept override {
        return message.c_str();
    }
};


class Player {
private:
    string name;
    int id;
    vector<unique_ptr<Card>> hand;
    int max_cards;
    vector<unsigned int> claimed_borders;
    void add_card_into_hand(std::unique_ptr<Card>  card_); // ATTENTION, c'est temporaire.
    std::unique_ptr<Card>  remove_card_from_hand(int card_index);

public:

    ~Player()=default;
    explicit Player(string nom_, int id_, int max_card);

    Player& operator = (const Player&) = delete;
    Player(const Player&) = delete;

    friend std::ostream& operator<<(std::ostream& f, const Player& player);
    // void play_card(int card_index, Border& border_);
    // void draw_card(Deck deck_);
    // void claim_borders(Border& border_);
    // vector<unsigned int> getClaimed_borders();
    // [[nodiscard]] int getNumber_of_cards() const;
    // int getId();
    void displayHand() const;
    void print_player() const;


};




#endif// SCHOTTEN_TOTTEN_PLAYER_H
