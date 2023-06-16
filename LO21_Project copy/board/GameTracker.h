#ifndef SCHOTTEN_TOTTEN_GAMETRACKER_H
#define SCHOTTEN_TOTTEN_GAMETRACKER_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

#include "deck/Card.h"
#include "player/Player.h"
#include "board/Combination.h"
#include "deck/DeckFactory.h"


class TrackedPlayer{
public:
    explicit TrackedPlayer(Player* player);
    Player* getPlayer() const;
    void trackCard(const ValuedCard& card);
    void trackCard(const TacticCard& card);
    size_t getNumberTacticCardPlayed() const;
    bool canPlayJoker() const;
private:
    Player* player_{nullptr};
    std::vector<ValuedCard> playedValuedCard_;
    std::vector<TacticCard> playedTacticCard_;
    bool hasPlayedJoker_{false};
};



class GameTracker {

public:
    static GameTracker& getInstance(
            Player* player1 = nullptr,
            Player* player2 = nullptr
    );
    void trackCard(Player* player, const ValuedCard& card);
    void trackCard(Player* player, const TacticCard& card);
    bool canPlayTacticCard(Player* player);
    bool canPlayJoker(Player* player);
    [[nodiscard]] const Deck& getRemainingCardDeck() const;
    [[nodiscard]] const Deck& getPlayerCardsDeck() const;
private:
    GameTracker(Player* player1, Player* player2);
    TrackedPlayer& getTrackedPlayer(Player* player);
    TrackedPlayer& getOpponentTrackedPlayer(Player* player);
private:
    Deck remainingCards_;
//    Player *player1, *player2;
    TrackedPlayer player1_, player2_;

};


class GameTrackerException : public std::exception {
private:
    std::string message;

public:
    explicit GameTrackerException(string  errorMessage)
            : message(std::move(errorMessage)) {}

    [[nodiscard]]const char* what() const noexcept override {
        return message.c_str();
    }
};


#endif //SCHOTTEN_TOTTEN_GAMETRACKER_H
