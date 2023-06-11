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

using std::unique_ptr, std::make_unique;

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
class Combination;

class Border {
private:
    bool claimed{false};
    Player* winner_{nullptr};
    int borderID_;
    const int NUMBER_CARDS = 3;
    unique_ptr<Combination> player_1_combination;
    unique_ptr<Combination> player_2_combination;

public:
    Border(int borderId, Player* player1, Player* player2);
    ~Border() = default;
    Border(const Border&) = delete;
    Border& operator=(const Border& border) = delete;
    Border(Border&& border);
    Border& operator=(Border&& border);


public:
    Combination& getPlayerCombination(Player* player);
    void addValueCard(unique_ptr<ValuedCard> valued_card, Player* player);
    void removeValueCard(unique_ptr<ValuedCard> valued_card, Player* player);
    void addTacticalCard(unique_ptr<TacticCard> tactic_card, Player* player);
    void removeTacticalCard(unique_ptr<TacticCard> tactic_card, Player* player);
    [[nodiscard]] Player* getWinnerBorder() const;
    int getBorderId() const { return borderID_; }
    [[nodiscard]] bool getClaimed() const;
    [[nodiscard]] string print() const;
    void setNoCombinationRules();
    void setMaxNumberCard(int  maxNumberCard);
    // A FAIRE
    // void Claimed(bool claimed); // Lorsque que l'on appelle cette fonction, elle vérifie le nombre de cartes sur la borne et avec combination, la combinaison gagnante. Elle met aussi à jour le winner
};

ostream& operator<<(ostream& stream, const Border& Border);

#endif // PROJET_BORDER_H
