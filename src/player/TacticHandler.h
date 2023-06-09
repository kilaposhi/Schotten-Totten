#ifndef SCHOTTEN_TOTTEN_TACTICHANDLER_H
#define SCHOTTEN_TOTTEN_TACTICHANDLER_H

#include <memory>
#include <iostream>

#include "deck/Card.h"
#include "board/Combination.h"
#include "Player.h"
#include "board/Board.h"
#include "deck/Deck.h"
#include "deck/DeckFactory.h"
#include "console.h"

using std::unique_ptr;

class Board;
class Combination;

//Singleton
class TacticHandler {
public:
    ~TacticHandler() = default;
public:
    static TacticHandler& getInstance(
            Deck* normalDeck=nullptr,
            DeckInfo* normalDeckInfo = nullptr,
            Deck* tacticDeck = nullptr,
            Deck* discardDeck = nullptr,
            Board* board = nullptr
                    );
    void playTacticCard(unique_ptr<TacticCard> tacticCard, Player* player, int borderID = -1);
    void activeEliteTroop(unique_ptr<TacticCard> tacticCard, Combination* combination);
private:
    TacticHandler(Deck *normalDeck, DeckInfo* normalDeckInfo, Deck *tacticDeck, Deck *discardDeck, Board *board);
    void playBlindManBluff(int borderId);
    void playMudFight(int borderId);
    void playEliteTroop(unique_ptr<TacticCard> tacticCard, Player* player, int borderId);
    size_t chooseBorderToAdd(const string& text, Player* player);
    size_t chooseBorderToRemove(const string& text, Player* player);
    void draw_card(Player* player);
    void playRecruiter( Player* player);
    void playStrategist(Player* player);
    void playBanshee(Player* player, Player* opponent);
    void playTraitor(Player* player, Player* opponent);
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
