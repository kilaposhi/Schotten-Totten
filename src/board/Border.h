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
#include "Combination.h"


class BorderException : public std::exception {
private:
    std::string message;

public:
    explicit BorderException(string  errorMessage)
            : message(std::move(errorMessage)) {}

    [[nodiscard]]const char* what() const noexcept override {
        return message.c_str();
    }
};

class Player;

class Border {
private:
    bool claimed;
    Player* winner{};
    unsigned int slot_number;
    Combination player_1_combination;
    Combination player_2_combination;

public:
    explicit Border(unsigned int slot_number);
    ~Border() = default;
    Border(const Border&) = delete;
    Border& operator=(const Border& border) = delete;
    Border(Border&& border);
    Border& operator=(Border&& border);


public:
    void addValueCard(unique_ptr<ValuedCard> valued_card, Player* player);
    void removeValueCard(unique_ptr<ValuedCard> valued_card, Player* player);
    void addTacticalCard(unique_ptr<TacticCard> tactic_card, Player* player);
    void removeTacticalCard(unique_ptr<TacticCard> tactic_card, Player* player);
    [[nodiscard]] unsigned int getSlotNumber() const;
    [[nodiscard]] Player getWinner() const;
    [[nodiscard]] bool getClaimed() const;
    [[nodiscard]] string print() const;
    // A FAIRE
    // void Claimed(bool claimed); // Lorsque que l'on appelle cette fonction, elle vérifie le nombre de cartes sur la borne et avec combination, la combinaison gagnante. Elle met aussi à jour le winner
};

ostream& operator<<(ostream& stream, const Border& Border);

#endif // PROJET_BORDER_H
