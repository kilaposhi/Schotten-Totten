#ifndef SCHOTTEN_TOTTEN_PLAYER_H
#define SCHOTTEN_TOTTEN_PLAYER_H

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <variant>

#include "deck/Card.h"
#include "board/Border.h"

using std::vector, std::list, std::array, std::string;

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
     int id;
     Player* player;
     vector<unique_ptr<Card>> hand;
     int max_cards;
     vector<int> claimed_borders;

public:

    ~Player()=default;
    Player(int id_,  Player* p, int max_cards_);

    Player& operator = (const Player&) = delete;
    Player(const Player&) = delete;

    void add_card_into_hand(std::unique_ptr<Card>  card_);
    std::unique_ptr<Card>  remove_card_from_hand(int card_index);
    void play_card(int card_index, Border& border_);
    void draw_card(Deck deck_);
    void claim_borders(Border& border_);
    vector<int> getClaimed_borders();
    [[nodiscard]] int getNumber_of_cards() const;
    int static getId(Player* player);
    void display_hand() const;

};


#endif// SCHOTTEN_TOTTEN_PLAYER_H
