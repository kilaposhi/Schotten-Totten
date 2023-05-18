#ifndef PROJET_BORDER_H
#define PROJET_BORDER_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "deck/Card.h"
#include "player/Player.h"
#include "board/Combination.h"

class Border {
private:
    bool claimed;
    Player& winner;
    unsigned int slot_number;
    std::vector<Card> card_slot_available;
    Tactic_card tactic_slot;
    Combination player_1_combination;
    Combination player_2_combination;

public:
    Border(Player& winner, unsigned int slot_number);
    ~Border() = default;
    Border(const Border& border) = default;
    Border& operator=(const Border& border) = delete;

    void addCard(const Card& card);
    void addCardTactical(const Tactic_card& card);
    unsigned int getNbBorder() const;
    Player& getWinner();
    void setWinner(Player& winner);
    void setClaimed(bool claimed);
    void setPlayer1Combination(const Combination& player_1_combination);
    void setPlayer2Combination(const Combination& player_2_combination);
};

#endif // PROJET_BORDER_H
