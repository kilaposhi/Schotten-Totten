
#ifndef SHOTTEN_TOTTEN_CARD_H
#define SHOTTEN_TOTTEN_CARD_H


class Card {
private:
public:

    Card();
    ~Card();
    Card(const Card& stone);
    const Card& operator=(const Card& stone);
};


class Clan_card : public Card {

};




#endif //SHOTTEN_TOTTEN_CARD_H
