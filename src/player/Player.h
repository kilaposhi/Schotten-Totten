#ifndef SCHOTTEN_TOTTEN_PLAYER_H
#define SCHOTTEN_TOTTEN_PLAYER_H

#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include <string>
#include <variant>

#include "deck/Card.h"
#include "board/Border.h"

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
    explicit PlayerException(string  errorMessage)
            : message(std::move(errorMessage)) {}

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

public:

    ~Player()=default;
    explicit Player(string nom_, int id_, int max_card);

    Player& operator = (const Player&) = delete;
    Player(const Player&) = delete;

    void add_card_into_hand(std::unique_ptr<Card>  card_); // ATTENTION, c'est temporaire.
    std::unique_ptr<Card>  remove_card_from_hand(int card_index); // ATTENTION, c'est temporaire.


    friend std::ostream& operator<<(std::ostream& f, const Player& player);
    void play_card(int card_index, Border& border);
    void draw_card(Deck deck_);
    void claim_borders(Border& border_);
    vector<unsigned int> getClaimed_borders(); // --> OK
    [[nodiscard]] int getNumber_of_cards() const; // --> OK
    [[nodiscard]] int getId() const; // --> OK
    void displayHand() const; // --> OK
    void print_player() const; // --> OK
};





#endif// SCHOTTEN_TOTTEN_PLAYER_H
