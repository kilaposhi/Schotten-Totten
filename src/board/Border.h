#ifndef PROJET_BORDER_H
#define PROJET_BORDER_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "deck/Card.h"
#include "player/Player.h"
#include "board/Combination.h"

class Combination;

class Player;

class Border {
private:
    bool claimed;
    Player* winner{};
    unsigned int slot_number;
    static Combination player_1_combination;
    static Combination player_2_combination;
    std::vector<std::unique_ptr<TacticCard>> player_1_tactic_card;
    std::vector<std::unique_ptr<TacticCard>> player_2_tactic_card;

public:
    explicit Border(unsigned int slot_number);
    ~Border() = default;
    Border(const Border& border) = default;
    Border& operator=(const Border& border) = delete;

    static void addValueCard(unique_ptr<ValuedCard> card, Player* player);
    void addTacticalCard(std::unique_ptr<TacticCard> tactic_card, Player* player);
    void removeTacticalCard(Player* player);
    unsigned int getSlotNumber() const;
    Player getWinner() const;
    bool getClaimed() const;

    void setWinner(Player* winner);
    void setClaimed(bool claimed);

};

#endif // PROJET_BORDER_H