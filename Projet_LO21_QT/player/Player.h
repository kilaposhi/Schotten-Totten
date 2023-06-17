#ifndef SCHOTTEN_TOTTEN_PLAYER_H
#define SCHOTTEN_TOTTEN_PLAYER_H

#include "board/Board.h"
#include "card/Card.h"
#include "deck/Deck.h"

#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include <string>
#include <variant>
#include <sstream>
#include <stdexcept>


class GameTracker;


class PlayerException : public std::exception {
private:
    std::string message;

public:
    explicit PlayerException(std::string errorMessage)
        : message(std::move(errorMessage)) {}

    [[nodiscard]]const char* what() const noexcept override {
        return message.c_str();
    }
};

class Border;

class Player {
protected:
    std::string name;
    int max_cards;
    int id_;
    std::vector<unsigned int> claimed_borders;
    void add_card_into_hand(std::unique_ptr<Card> card_);
    std::unique_ptr<Card> remove_card_from_hand(int card_index);
    std::vector<unique_ptr<Card>> hand;

public:

    ~Player()=default;
    explicit Player(std::string nom_, int id, int max_card);

    Player& operator = (const Player&) = delete;
    Player(const Player&) = delete;

    void play_card(int card_index, int borderIndex, Board* board);
    void draw_card(Deck& deck_);
    void fillHand(Deck& deck);
    void claim_borders(Border& border_);
    std::vector<unsigned int> getClaimed_borders(); // --> OK
    [[nodiscard]] int getNumber_of_cards() const; // --> OK
    int getID() const;
    std::unique_ptr<Card>& getCardAtIndex(std::size_t index);
    std::string getName() const { return name; }
    std::string displayHand() const; // --> OK
    std::string displayCard(int index_card) const;
    std::string print_player() const; // --> OK
};

std::ostream& operator<<(std::ostream& f, const Player& player);

class AI : public Player {
public:
    AI(unsigned int max_cards, const std::string& name);
    unsigned int pick_a_card(Border* border);
    unsigned int pick_a_border(Board * board);
    unsigned int claim_a_border(Board * board, Player* enemy);

};


#endif// SCHOTTEN_TOTTEN_PLAYER_H
