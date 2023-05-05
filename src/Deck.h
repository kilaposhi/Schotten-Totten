#ifndef SHOTTEN_TOTTEN_DECK_H
#define SHOTTEN_TOTTEN_DECK_H


class Deck {

public:

    Deck();
    ~Deck();
    Deck(const Deck& stone);
    const Deck& operator=(const Deck& stone);
};


#endif //SHOTTEN_TOTTEN_DECK_H
