```mermaid
 ---
title: Architecture Schotten-Totten
---
classDiagram

%% ------ Relations
Card <|-- TacticCard
Card <|-- ValuedCard
CardColor -- ValuedCard
TacticType -- TacticCard
Observer<|--GameTracker
GameTracker "1" --> "2" Deck 
GameTracker "1" --> "*" Card
GameTracker "1" --> "*" Player 
GameTracker "1" --> "*" Combination
Deck "1"*-- "0..*" Card
Deck -- DeckFactory
%%    Card "0..7" --* "0..1" Hand
Combination "1"*--"1" CombinationType
Combination "0..*" --> "1..*" ValuedCard
Combination "0..*" --> "1..*" TacticCard
Player "1"*--"1" Hand
Player --> Card
Player --> Border
Player --> Deck
Combination "2" --* "1" Border
Board "1" *-- "9" Border
Border "0..*" -- "1" Player
Border "0..*" -- "1" Combination
Border "1" -- "0..*" ValuedCard
Border "1" -- "0..*" TacticCard
%%---------- class
  class Game_interface{
    + launch_Schotten_Totten1();
  }

  class Card {
      <<abstact>>
    + virtual print() string
  }


  class ValuedCard{
    - color_ : CardColor
    - value_ : int<1 to 9>
    + ValuedCard(int, CardColor)
    + print() string
    + getColor() CardColor
    + getValue() int
  }

  class TacticCard{
    - name: TacticType
    - description: string
    + TacticCard(TacticType)
    + print() string
    + getName() TacticType
    + getDescription() string
  }


  class Board {
    - numberBorders : const int
    - borders : std::vector<Border>
    - winner : Player*
    + Board()
    +getNumberBorder() const int
    +getWinner() Player*
    +getBorders() const std::vector<Border>&
    +print() string
  }

  
    class Combination {
        +hasTacticCard_: bool
        -valuedCards_: vector<unique_ptr<ValuedCard>>
        -tacticCards_: vector<unique_ptr<TacticCard>>
        -maxNumberCards_: int
        -sumValues_: int
        -combinationType_: CombinationType
        +Combination(int)
        +Combination(const Combination&)
        +operator=(const Combination&)
        +getSum() const int
        +getType() const CombinationType
        +getNumberCards() const int
        +getNumberValuedCards() const int
        +getNumberTacticCards() const int
        +getMaxNumberCards() const int
        +push_back(unique_ptr<ValuedCard>)
        +pop_card(unique_ptr<ValuedCard>)
        +push_back(unique_ptr<TacticCard>)
        +pop_card(unique_ptr<TacticCard>)
        +treatTacticCards()
        +getValuedCard(int) const ValuedCard*
        +getTacticCard(int) const TacticCard*
        +print() const string
    }
  class Border {
        -claimed: bool
        -winner: Player*
        -slot_number: unsigned int
        -player_1_combination: Combination
        -player_2_combination: Combination
        +Border(unsigned int)
        +operator=(const Border&)
        +addValueCard(unique_ptr<ValuedCard>, Player*)
        +removeValueCard(unique_ptr<ValuedCard>, Player*)
        +addTacticalCard(unique_ptr<TacticCard>, Player*)
        +removeTacticalCard(unique_ptr<TacticCard>, Player*)
        +getSlotNumber() unsigned int
        +getWinnerBorder() Player*
        +getClaimed()  bool
        +print() string
    }

    class Player{
        -name: string
        -id: int
        -hand: vector<unique_ptr<Card>>
        -max_cards: int
        -claimed_borders: vector<unsigned int>
        +Player(string, int, int)
        +add_card_into_hand(unique_ptr<Card>)
        +remove_card_from_hand(int): unique_ptr<Card>
        +play_card(int, Border&)
        +draw_card(Deck)
        +claim_borders(Border&)
        +getClaimed_borders(): vector<unsigned int>
        +getNumber_of_cards(): int
        +getId(): int
        +displayHand() const
        +print_player() const
    }

  class Deck{
    - cards: vector<Card*>
    + Deck(Deck&&)
    + operator=(Deck&&) Deck&
    + isEmpty() bool
    + shuffle()
    + print()
    + clear()
    + drawCard() unique_ptr<Card>
    + putCard(card : unique_ptr<Card>)
    + getNumberRemainingCards() int
  }


class DeckFactory {
  <<Factory>>
  - cards : vector<unique_ptr<Card>>
  - number_cards : int
  - number_colors : int
  - min_card_value : int
  - max_card_value : int
  - setRangeValue(min_value: int, max_value: int)
  - setNumberColors(num_colors: int)
  - createValuedCard()
  - createTacticCard()
  - build() Deck
  + createClanDeck() Deck
  + createTacticDeck() Deck
  }

  class Observer { 
  + update()}
  
  class GameTracker {
  - remainingCardsDeck : Deck 
  - playedCardsDeck : Deck 
  + update() 
  + GameTracker( Deck& tacticDeck,  Deck& clanDeck);
  + copyDeck(Deck tacticDeck, Deck clanDeck);
  + transferCard();
  + getRemainingCardDeck() Deck&  ;
  + getPlayerCardsDeck() Deck& ;}

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

class TacticType {
    <<Enumeration>>
joker
spy
shield_bearer
blind_man_bluff
mud_fight
recruiter
strategist
banshee
traitor
}



class CombinationType{
  <<Enumeration>>
        NONE
        ColorRun
        Run
        Color
        ThreeOfAKind
        Sum
    }
```
