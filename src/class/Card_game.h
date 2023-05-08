#ifndef SHOTTEN_TOTTEN_CARD_GAME_H
#define SHOTTEN_TOTTEN_CARD_GAME_H

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <memory>

#include "Card.h"

using std::string, std::array, std::cout, std::initializer_list, std::unique_ptr, std::make_unique, std::size_t, std::vector;


unsigned int compute_number_cards(unsigned int min_value, unsigned int max_value );

class Card_game {
private:
    const int number_valued_cards_;
    const int min_card_value_, max_card_value_;
    const unique_ptr<unique_ptr<Valued_Card>[]> valued_cards_; // T <=> Valued_Card**

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

    const Valued_Card& getCard(size_t card_index) const;
    vector<Valued_Card> getCards() const;

    void display_all_cards() const;

};



#endif //SHOTTEN_TOTTEN_CARD_GAME_H
