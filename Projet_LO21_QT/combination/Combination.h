#ifndef COMBINATION_H
#define COMBINATION_H

#include "hand/TacticHandler.h"
#include "card/Card.h"
#include "board/Board.h"

#include <stdexcept>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>


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
    Combination& operator=(const Combination&) = delete;
public:
    [[nodiscard]] int getSum() const;
    [[nodiscard]] CombinationType getType() const;
    [[nodiscard]] int getNumberCards() const;
    int getNumberValuedCards() const;
    int getNumberTacticCards() const;
    Player* getPlayerID() const;
    [[nodiscard]] int getMaxNumberCards() const;
    void push_back(unique_ptr<ValuedCard> valuedCard);
    void pop_card(unique_ptr<ValuedCard> valuedCard);
    void push_back(unique_ptr<TacticCard> tacticCard);
    void pop_card(unique_ptr<TacticCard> tacticCard);
    void setMaxNumberCards(int maxNumberCards);
    void setNoCombinationRule();
    void treatTacticCards();
    ValuedCard* getValuedCard(int index) const;
    TacticCard* getTacticCard(int index) const;
    [[nodiscard]] string str() const;
    int getRank() const;
    bool operator==(const Combination& other) const;
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

#endif // COMBINATION_H
