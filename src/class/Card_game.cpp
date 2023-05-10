#include "Card_game.h"


unsigned int compute_number_cards(unsigned int min_value, unsigned int max_value ){
    unsigned int number_values = max_value - min_value + 1;
    unsigned int number_colors = 6; // EnumClass in .src\Card.h

    return number_values *  number_colors;;
}

void Card_game::create_valued_cards(){
    size_t card_index = 0;
    for (auto color : CardColors)
        for (int value = min_card_value_; value <= max_card_value_; value++)
            valued_cards_[card_index++]= make_unique<Valued_Card>(value, color);
}

Card_game::Card_game(int min_card_value, int max_card_value )
        : number_valued_cards_(compute_number_cards(min_card_value, max_card_value)),
        min_card_value_(min_card_value),
        max_card_value_(max_card_value),
        valued_cards_(make_unique< unique_ptr<Card>[] >(number_valued_cards_))
{
    this->create_valued_cards();
}

Card_game::~Card_game(){
    // Nothing to do thanks to the usage of unique_ptr to dynamically allocate Card, we don't need to free the memory in the destructor
}

Card_game& Card_game::getInstance(int num_valued_cards, int min_card_value, int max_card_value){

    static unique_ptr<Card_game> instance (new Card_game(min_card_value, max_card_value));

    bool no_argument = !num_valued_cards && !min_card_value && !max_card_value;
    if (no_argument)
        return *instance;

    bool different_Card_game = instance->number_valued_cards_ != num_valued_cards || instance->max_card_value_ != max_card_value;
    if (different_Card_game)
        instance.reset(new Card_game(min_card_value, max_card_value));

    return *instance;
}


int Card_game::getNumberValuedCards() const {
    return number_valued_cards_;
}

int Card_game::getMinCardValue() const {
    return min_card_value_;
}

int Card_game::getMaxCardValue() const {
    return max_card_value_;
}

const Card* Card_game::getCard(size_t card_index) const {
    bool valid_card_index = card_index >=0 && card_index < number_valued_cards_ ;
    if (!valid_card_index)
        throw std::exception();
    return valued_cards_[card_index].get();
}

vector<const Card*> Card_game::getCards() const {
    vector<const Card*> cards;
    for (int card_index = 0; card_index < number_valued_cards_; ++card_index)
        cards.push_back(getCard(card_index));

    return cards;
}

void Card_game::display_all_cards() const {
    for (size_t card_index=0 ; card_index < number_valued_cards_; card_index++)
        cout << *valued_cards_[card_index] << '\n';
}

