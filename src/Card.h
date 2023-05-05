
#ifndef SHOTTEN_TOTTEN_CARD_H
#define SHOTTEN_TOTTEN_CARD_H


class Card {
private:
public:

    Card() =default;
    ~Card()=default;
    Card(const Card& stone)=default;
    Card& operator=(const Card& stone) = default;
};


class Clan_card : public Card {

};




#endif //SHOTTEN_TOTTEN_CARD_H
