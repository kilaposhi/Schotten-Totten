#ifndef SCHOTTEN_TOTTEN_PLAYER_H
#define SCHOTTEN_TOTTEN_PLAYER_H

#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include <string>
#include <variant>
#include <sstream>

#include "deck/Card.h"
#include "board/Border.h"
#include "board/Board.h"
#include "deck/Deck.h"
#include "TacticHandler.h"
#include "board/Combination.h"
#include "board/GameTracker.h"

class GameTracker;

using std::vector;
using std::list;
using std::array;
using std::string;


class PlayerException : public std::exception {
private:
    std::string message;

public:
    explicit PlayerException(string  errorMessage)
            : message(std::move(errorMessage)) {}

    [[nodiscard]]const char* what() const noexcept override {
        return message.c_str();
    }
};

class Border;
class AI;


class Player {
protected:
    string name;
    size_t max_cards;
    size_t numValuedCard{0};
    int id_;
    vector<unsigned int> claimed_borders;
    vector<unique_ptr<Card>> hand;
    unsigned int score;
    friend class TacticHandler;
protected:
    void add_card_into_hand(std::unique_ptr<Card>  card_);
    std::unique_ptr<Card>  remove_card_from_hand(int card_index);
    void setMaxNumberCards(size_t number);
public:

    ~Player()=default;
    explicit Player(string nom_, int id, int max_card);
    Player();

    Player& operator = (const Player&) = delete;
    Player(const Player&) = delete;

    void play_card(int card_index, int borderIndex, Board* board);
    void draw_card(Deck& deck_);
    void fillHand(Deck& deck);
    void claim_borders(const Border& border);
    vector<unsigned int> getClaimed_borders();
    [[nodiscard]] int getNumber_of_cards() const;
    int getID() const;
    std::unique_ptr<Card>& getCardAtIndex(int index);
    string getName() const { return name; }
    unsigned int getScore() const {return score;}
    unsigned int newScore(int add) ;
    string displayHand() const;
    string displayCard(int index_card) const;
    string print_player() const; // --> OK
    bool hasValuedCard() const;
    virtual bool isAI() { return false; };

};

std::ostream& operator<<(std::ostream& s, const Player& player);


class AI : public Player {
public:
    AI(const string& name, int id, unsigned int max_cards );
    unsigned int pick_a_card(Border* border);
    unsigned int pick_a_border(Board * board);
    unsigned int claim_a_border(Board * board, Player* enemy);
    bool isAI() override { return true; }

};


#endif// SCHOTTEN_TOTTEN_PLAYER_H
