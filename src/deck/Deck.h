class Deck {
public:

    Deck()=default;
    Deck(vector<unique_ptr<Card>>&& cards); // constructor used by 'DeckFactory'
    ~Deck()=default;
    Deck(const Deck&) = delete;
    Deck& operator=(const Deck &) = delete;
    Deck(Deck&&) noexcept ;
    Deck& operator=(Deck &&otherDeck) noexcept;

public:
    void shuffle();
    [[nodiscard]] bool isEmpty() const;
    unique_ptr<Card> drawCard();
    void putCard(unique_ptr<Card> card);
    [[nodiscard]] int getNumberRemainingCards() const;
    void print() const;
    void clear();

private:
    vector<unique_ptr<Card>> cards_;
};

ostream& operator<<(ostream& stream, const Deck& deck);

#endif //SCHOTTEN_TOTTEN_DECK_H

