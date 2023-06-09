#ifndef PROJET_BORDER_H
#define PROJET_BORDER_H

#include <iostream>
#include <initializer_list>
#include <exception>
#include <string>
#include <sstream>
#include <memory>
#include <utility>

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
    Combination player_1_combination;
    Combination player_2_combination;

public:
    explicit Border(unsigned int slot_number, Combination player1Combination, Combination player2Combination1);
    ~Border() = default;
    Border(const Border& border) = default;
    Border& operator=(const Border& border) = delete;

public:
    void addValueCard(unique_ptr<ValuedCard> valued_card, Player* player);
    void removeValueCard(unique_ptr<ValuedCard> valued_card, Player* player);
    void addTacticalCard(unique_ptr<TacticCard> tactic_card, Player* player);
    void removeTacticalCard(unique_ptr<TacticCard> tactic_card, Player* player);
    unsigned int getSlotNumber() const;
    Player getWinner() const;
    bool getClaimed() const;
    // A FAIRE
    void Claimed(bool claimed); // Lorsque que l'on appelle cette fonction, elle vérifie le nombre de cartes sur la borne et avec combination, la combinaison gagnante. Elle met aussi à jour le winner
    string print() const;
};

ostream& operator<<(ostream& stream, const Border& Border);

#endif // PROJET_BORDER_H