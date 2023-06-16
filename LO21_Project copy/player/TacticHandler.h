#ifndef SCHOTTEN_TOTTEN_TACTICHANDLER_H
#define SCHOTTEN_TOTTEN_TACTICHANDLER_H

#include <memory>
#include <ostream>

#include "deck/Card.h"
#include "board/Combination.h"
#include "Player.h"
#include "board/Board.h"
#include "deck/Deck.h"
#include "deck/DeckFactory.h"
#include "console/console.h"

using std::unique_ptr;

class Board;
class Combination;

//Singleton
class TacticHandler {
public:
    ~TacticHandler() = default;
public:
    static TacticHandler& getInstance(
            Deck* normalDeck = nullptr,
            DeckInfo* normalDeckInfo = nullptr,
            Deck* tacticDeck = nullptr,
            Deck* discardDeck = nullptr,
            Board* board = nullptr
                    );
    void playTacticCard(unique_ptr<TacticCard> tacticCard, Player* player, int borderID = -1);
    void activeEliteTroop(unique_ptr<TacticCard> tacticCard, Combination* combination);
private:
    TacticHandler(Deck *normalDeck, DeckInfo* normalDeckInfo, Deck *tacticDeck, Deck *discardDeck, Board *board);
    void discardCard(unique_ptr<Card> card) const;
    void playBlindManBluff(int borderId);
    void playMudFight(int borderId);
    void playEliteTroop(unique_ptr<TacticCard> tacticCard, Player* player, int borderId);
    void playRecruiter(Player* player);
//    playStragist(Player* player)
//    playBanshee(Player* opponent)
//    playTraiter(Player* player, Player* opponent)
private:
    Deck *normalDeck_{nullptr};
    DeckInfo* normalDeckInfo_{nullptr};
    Deck *tacticDeck_{nullptr};
    Deck *discardDeck_{nullptr};
    Board *board_{nullptr};
};


class TacticHandlerException : public std::exception {
private:
    std::string message;

public:
    explicit TacticHandlerException(string  errorMessage)
            : message(std::move(errorMessage)) {}

    [[nodiscard]]const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //SCHOTTEN_TOTTEN_TACTICHANDLER_H
