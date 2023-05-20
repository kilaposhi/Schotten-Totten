#ifndef PROJET_BORDER_H
#define PROJET_BORDER_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "deck/Card.h"
#include "player/Player.h"
#include "board/Combination.h"

class Player;

class Border {
private:
    bool claimed;
    Player& winner;
    unsigned int slot_number;
    Combination player_1_combination;
    Combination player_2_combination;
    std::vector<Tactic_card> player_1_tactic_card;
    std::vector<Tactic_card> player_2_tactic_card;

public:
    explicit Border(unsigned int slot_number);
    ~Border() = default;
    Border(const Border& border) = default;
    Border& operator=(const Border& border) = delete;

    void addValueCard(const ValuedCard& card, int player_id);
    void addTacticalCard(const Tactic_card& tactic_card, int player_id);
    void removeTacticalCard(int player_id);
    unsigned int getSlotNumber() const;
    Player getWinner() const;
    bool getClaimed() const;
    void setWinner(Player winner);
    void setClaimed(bool claimed);

};

#endif // PROJET_BORDER_H
