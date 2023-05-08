#include "Card_game.h"


unsigned int compute_number_cards(unsigned int min_value, unsigned int max_value ){
    unsigned int number_values = max_value - min_value + 1;
    unsigned int number_colors = 6; // EnumClass in .src\Card.h

    return number_values *  number_colors;;
}

void Card_game::create_valued_cards(){
    size_t card_index = 0;
    for (auto color : CardColors)
        for (int value = min_card_value; value <= max_card_value; value++)
            valued_cards[card_index++]= make_unique<Valued_Card>(value, color);
}

Card_game::Card_game(int min_card_value, int max_card_value ) : number_valued_cards(
                            compute_number_cards(min_card_value, max_card_value)), min_card_value(min_card_value),
                            max_card_value(max_card_value), valued_cards( unique_ptr<unique_ptr<Valued_Card>[]>(new unique_ptr<Valued_Card>[number_valued_cards]))
{
    create_valued_cards();
}

Card_game::~Card_game(){
    // Empty thanks to the usage of unique_ptr to dynamically allocate Valued_Card, we don't need to free the memory in the destructor
}

Card_game& Card_game::getInstance(int num_valued_cards, int min_card_value, int max_card_value){

    static unique_ptr<Card_game> instance (new Card_game(min_card_value, max_card_value));

    bool no_argument = !num_valued_cards && !min_card_value && !max_card_value;
    if (no_argument)
        return *instance;

    bool different_Card_game = instance->number_valued_cards != num_valued_cards || instance->max_card_value != max_card_value;
    if (different_Card_game)
        instance.reset(new Card_game(min_card_value, max_card_value));

    return *instance;
}


int Card_game::getNumberValuedCards() const {
    return number_valued_cards;
}

int Card_game::getMinCardValue() const {
    return min_card_value;
}

int Card_game::getMaxCardValue() const {
    return max_card_value;
}

const Valued_Card& Card_game::getCard(size_t card_index) const {
    bool valid_card_index = card_index >=0 && card_index < number_valued_cards ;
    if (!valid_card_index)
        throw std::exception();
    return *valued_cards[card_index];
}

void Card_game::display_all_cards() const {
    for (size_t card_index=0 ; card_index < number_valued_cards; card_index++)
        cout << *valued_cards[card_index] << '\n';
}

