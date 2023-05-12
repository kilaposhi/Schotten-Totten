#ifndef SCHOTTEN_TOTTEN_DECKCREATOR_H
#define SCHOTTEN_TOTTEN_DECKCREATOR_H

#include "Deck.h"

enum class DeckType{
    ValuedCard,
    TacticCard
};

class DeckCreator {
private:
    DeckType deckType;
    int number_cards_;
    int min_card_value_ = 0;
    int max_card_value_;
    const unique_ptr<unique_ptr<Card>[]> cards_; // T <=> Valued_Card**

//    DeckCreator& setTypeCards(DeckType deckType);

    // ValuedCards method
    DeckCreator& setNumberCards(int number_cards);
    DeckCreator& setMinValueCard(int min_card_value);
    DeckCreator& setMaxValueCard(int max_card_value );
    DeckCreator& setNumberColors(int max_card_value );
    DeckCreator& setRangeValue(int min_card_value, int max_card_value);

    void create_valued_cards();

public:
    DeckCreator(DeckType deckType);
    DeckCreator(const DeckCreator&)=default;
    DeckCreator& operator=(const DeckCreator&)=default;
    ~DeckCreator()=default;

    void createClanDeck();
    void createTacticDeck();
    Deck& build();
};


#endif //SCHOTTEN_TOTTEN_DECKCREATOR_H
