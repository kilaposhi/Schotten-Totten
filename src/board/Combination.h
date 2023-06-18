#ifndef PROJET_COMBINATION_H
#define PROJET_COMBINATION_H

#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>

#include "player/TacticHandler.h"
#include "deck/Card.h"
#include "player/Player.h"

enum class CombinationType {
    NONE,
    ColorRun,
    Run,
    Color,
    ThreeOfAKind,
    Sum
};

class Player;

class Combination {
public:
    explicit Combination(int maxNumberCards, Player* player);
    ~Combination() = default;
    Combination(const Combination&);
    Combination& operator=(const Combination&);
public:
    [[nodiscard]] int getSum() const;
    [[nodiscard]] CombinationType getType() const;
    [[nodiscard]] int getNumberCards() const;
    int getNumberValuedCards() const;
    int getNumberTacticCards() const;
    [[nodiscard]] int getMaxNumberCards() const;
    Player* getPlayerID() const;
    void push_back(unique_ptr<ValuedCard> valuedCard);
    void push_back(unique_ptr<TacticCard> tacticCard);
    unique_ptr<ValuedCard> pop_card(const ValuedCard& valuedCard);
    unique_ptr<TacticCard> pop_card(const TacticCard& tacticCard);
    void setMaxNumberCards(int maxNumberCards);
    void setNoCombinationRule();
    void removeCardFromCombination(Card* card);
    void treatTacticCards();
    std::vector<ValuedCard*>  getValuedCards() const;
    std::vector<TacticCard*>  getTacticCards() const;
    [[nodiscard]] string str() const;
    string displayCards() const;
    int getRank() const;
    bool isComplete() const;
    bool operator==(const Combination& other) const;
    const Combination& getConstReference();
    unique_ptr<ValuedCard> valuedCardBack();
    unique_ptr<TacticCard> tacticCardBack();
    //Combination& operator=(const Combination& other);
//    Card* getCardByIndex(size_t index) const;
    [[nodiscard]] ValuedCard& getValuedCard(size_t index) const;
    [[nodiscard]] TacticCard& getTacticCard(size_t index) const;
private:
    Player* player_;
    std::vector<unique_ptr<ValuedCard>> valuedCards_;
    std::vector<unique_ptr<TacticCard>> tacticCards_;
    int maxNumberCards_{0};
    int sumValues_{0};
    bool hasTacticCard_{false};
    bool noCombinationRule_{false};
    CombinationType combinationType_{CombinationType::NONE};

private:
    CombinationType compute_combination();
    bool isColorRun();
    bool isThreeOfAKind();
    bool isRun();
    bool isColor();
};

ostream& operator<<(ostream& stream, const Combination& combination);
string combinationTypeToString(CombinationType type) ;

class CombinationException: public std::exception{
private:
    std::string message;
public:
    explicit CombinationException(string  errorMessage)
            : message(std::move(errorMessage)) {}

    [[nodiscard]]const char* what() const noexcept override {
        return message.c_str();
    }

};
const Combination& bestCombination(const Combination& combo1, const Combination& combo2) ;
int findBestCombination(const std::vector<Combination>& combinations);
#endif //PROJET_COMBINATION_H
