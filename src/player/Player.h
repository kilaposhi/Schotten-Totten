#ifndef SCHOTTEN_TOTTEN_PLAYER_H
#define SCHOTTEN_TOTTEN_PLAYER_H

#include <iostream>
#include <vector>
#include <list>
#include <string>

#include "deck/Card.h"
#include "board/Stone.h"
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
     int number_of_cards;
     vector<unique_ptr<Card>> hand;
     int max_cards; // Maybe just narrow 'number_of_cards'
     array<bool, 9> claimed_borders_array;
     vector<int> claimed_borders_vector;

public:

    Player()=default;
    ~Player()=default;
    Player(int id_, int max_cards_); // Surcharged constructor

    Player& operator = (const Player&) = default;

    void add_card_into_hand(unique_ptr<Card> card_);
    unique_ptr<Card> delete_card_from_hand(int card_index);
    void play_card(int card_index, Stone& stone_);
    unique_ptr<Card> draw_card(Deck deck_);
    void claim_borders_vector(Stone& border_);
    vector<int> getClaimed_borders_vector();
    [[nodiscard]] int getNumber_of_cards() const;

};


#endif// SCHOTTEN_TOTTEN_PLAYER_H
