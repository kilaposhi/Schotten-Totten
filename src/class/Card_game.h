#ifndef SCHOTTEN_TOTTEN_CARD_GAME_H
#define SCHOTTEN_TOTTEN_CARD_GAME_H

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <memory>

#include "Card.h"

using std::string, std::array, std::cout, std::initializer_list, std::unique_ptr, std::make_unique, std::size_t, std::vector;


unsigned int compute_number_cards(unsigned int min_value, unsigned int max_value );

//Singleton because anybody can have access to it???
class Card_game {
private:
    const int number_valued_cards_;
    const int min_card_value_, max_card_value_;
    const unique_ptr<unique_ptr<Card>[]> valued_cards_; // T <=> Valued_Card**

    void create_valued_cards();
    Card_game(int min_card_value, int max_card_value);

public:

    static Card_game& getInstance(int num_valued_cards=0, int min_card_value=0, int max_card_value=0);
    ~Card_game();
    Card_game(const Card_game&)=delete;
    Card_game& operator=(const Card_game&)=delete;

    inline int getNumberValuedCards() const;
    inline int getMinCardValue() const;
    inline int getMaxCardValue() const;

    const Card* getCard(size_t card_index) const;
    vector<const Card*> getCards() const;

    void display_all_cards() const;

};



#endif SCHOTTEN_TOTTEN_CARD_GAME_H
