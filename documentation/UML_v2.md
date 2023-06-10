---
title: Architecture Schotten-Totten V2
---

classDiagram

%% ------ Relations
Game "1..1" -- "2..2" Player
Game "1..1" -- "9..9" Border
Game "1..1" -- "1..1" Board
Game "1..1" -- "0..n" Deck
Card <|-- Tactic_card
Card <|-- ValuedCard
Deck "1"*-- "0..*" Card
Deck "1" *-- "1" DeckInfo
Deck -- DeckFactory
Player "1"*--"1" Hand
Combination "1" --* "2" Border
Board "1" *-- "9" Border
Border <|-- GameTracker
Tactic_card <|-- Elite_troop
Tactic_card <|-- Ruse
Tactic_card <|-- Combat_Mode
CardColor -- ValuedCard
DeckType -- Deck

%%---------- class
class Game_interface {
    + launch_Schotten_Totten1()
}

class Card {
    + virtual print(): string
    + virtual clone(): unique_ptr<Card>
}

class ValuedCard{
    - color: CardColor
    - value: int<1 to 9>
    + override print(): string
    + override clone(): unique_ptr<Card>
}

class Tactic_card{
    - name: string
    - description: string
    + override print(): string
    + override clone(): unique_ptr<Card>
}

class Board {
    - numberBorders: const int = 9
    - Borders: Stone[number_of_stone_tiles]
    - winner: &Player
}

class Combination{
    - cards: vector<ValuedCard>
    - sumValues: int
    + getSum(): int
    + push_back(const ValuedCard& card)
}

class Border{
    - claimed: bool = false
    - winner: Player
    - slot_number: unsigned int
    - player_1_combination: Combination
    - player_2_combination:  Combination
    - player_1_tactic_card: vector<unique_ptr<Tactic_card>>
    - player_2_tactic_card: vector<unique_ptr<Tactic_card>>
    + addValueCard(const ValuedCard& card, int player_id)
    + addTacticalCard(const TacticalCard& card, int player_id)
    + removeTacticalCard(int player_id)
    + getSlotNumber(): unsigned int
    + getWinner(): Player
    + getClaimed(): bool
    + setWinner()
    + setClaimed()
}

class Game{
    - bool gameOver
    - int version
    + Game()
    + create_game()
    + round(Player player1, Player player2, Board board)
    + play(Board board)
    + pause(int n)
    + isGameOver(): bool 
}

class GameTracker{
    - Deck remainingCardsDeck
    - Deck playedCardsDeck
    + GameTracker(const Deck& tacticDeck, const Deck& clanDeck)
    + update(): void
    + copyDeck(Deck tacticDeck, Deck clanDeck)
    + transferCard()
    + const Deck& getRemainingCardsDeck() const
    + const Deck& getPlayedCards() const
}

class Hand {
    - cards: vector<unique_ptr<Card>>
    + refill()
    + playCard(Card)
}

class Player{
    - id: <1 or 2>
    - number_of_cards: int
    - hand: Hand
    - max_cards: int<6 or 7>
    - claimed_stones: vector<int>
    + Player(string nom_, int id_, int max_card)
    + add_card_into_hand(std::unique_ptr<Card>  card_)
    + remove_card_from_hand(int card_index): std::unique_ptr<Card>
    + play_card(int card_index, Border& border, vector<unique_ptr<Card>>&& discardDeck)
    + draw_card(Deck deck_): Card
    + getClaimed_borders(Border& border_): void 
    + claim_stone(): vector<unsigned int>
    + getNumber_of_cards(): int
    + getId(): int
    + displayHand(): void
    + print_player(): void
}

class Deck{
    - deckInfo: DeckInfo
    - cards: vector<Card*>
    + Deck(const Deck&)
    + operator=(const Deck&): Deck&
    + isEmpty(): bool
    + drawCard(): Card
    + getNumberRemainingCards(): int
}

class DeckInfo {
    - deckType: DeckType
    - total_number_card: int
    - min_value_card: int
    - max_value_card: int
}

class DeckFactory {
    <<Builder>>
    + createClanDeck(): Deck
    + build(): Deck
}

%%-------- Enum class
class CardColor {
    <<Enumeration>>
    blue
    purple
    green
    red
    orange
    brown
}

class DeckType{
    <<Enumeration>>
    ValuedCard
    TacticCard
    DiscardDeck
}
