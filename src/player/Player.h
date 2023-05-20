#ifndef SCHOTTEN_TOTTEN_PLAYER_H
#define SCHOTTEN_TOTTEN_PLAYER_H

#include <iostream>
#include <vector>
#include <list>
#include <string>

#include "deck/Card.h"
#include "board/Border.h"
#include "board/Stone.h"

using std::vector, std::list, std::array, std::string;

class Stone;
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
     vector<unsigned int> claimed_borders_vector;

public:

    ~Player()=default;
    Player(Player* p, int max_cards_);

    Player& operator = (const Player&) = delete;

    void add_card_into_hand(unique_ptr<Card> card_);
    unique_ptr<Card> remove_card_from_hand(int card_index);
    void play_valued_card(int card_index, Border& border_);
    void play_tactical_card(int card_index, Border& border_);
    void draw_card(Deck deck_);
    void claim_borders_vector(Border& border_);
    vector<int> getClaimed_borders_vector();
    [[nodiscard]] int getNumber_of_cards() const;

};


#endif// SCHOTTEN_TOTTEN_PLAYER_H
