#ifndef SHOTTEN_TOTTEN_CARD_GAME_H
#define SHOTTEN_TOTTEN_CARD_GAME_H

#include <iostream>
#include <string>
#include <array>
#include <memory>

#include "Card.h"

using std::string, std::array, std::cout, std::initializer_list, std::unique_ptr, std::make_unique, std::size_t;


class Card_game {
private:
    const int number_valued_cards;
    const int min_card_value, max_card_value;
    const Valued_Card** valued_cards; // TODO -> unique_ptr<Valued_Card[]>

    void create_valued_cards();

//    friend unique_ptr<Card_game> make_unique<Card_game>(Card_game&);

    Card_game(int min_card_value, int max_card_value);

public:

    static Card_game& getInstance(int num_valued_cards=0, int min_card_value=0, int max_card_value=0);
    ~Card_game();
    Card_game(const Card_game&)=delete;
    Card_game& operator=(const Card_game&)=delete;

    void display_all_cards() const;

};

unsigned int compute_number_cards(unsigned int min_value, unsigned int max_value );


#endif //SHOTTEN_TOTTEN_CARD_GAME_H
