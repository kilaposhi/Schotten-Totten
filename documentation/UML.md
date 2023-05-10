
## UML version 1 :
Notre UML est porté de PlantUML vers markdown avec [mermaid](https://mermaid.js.org).
  
- [Syntaxe des diagrammes de classes avec mermaid](https://mermaid.js.org/syntax/classDiagram.html)
- [Liste des manières de l'utiliser](https://mermaid.js.org/ecosystem/integrations.html), perso j'utilise le plugin de Jetbrains
- [Ancien UML](https://codimd.math.cnrs.fr/VEjH14SwRfq9q9YtunKFbg?both)

### Changements :
- Ajout des "-", "+"...
- Ajout des relations entre les classes **, elles ne sont pas forcément claires, et pourront changer**
- `Stone_tiles` devient simplement `Stone`
- Tableau de bool pour savoir les _slots available_ dans la classe `Stone` 
- Création de la classe `Board` pour gérer la vie des `Stone`, car cela réduit le couplage à la Classe `Game` qui gère déjà la vie des `Valued_Card`
- Héritage pour les cartes avec `Card`.
- Enlever le lien entre `Player` et `Stone`

> Notre UML va surement changer avec l'ajout de design pattern etc... 
> N'hésitez pas à le critiquer, et à le modifier


```mermaid
---
title: Architecture Schotten-Totten
---
classDiagram

%% ------ Relations
    Card_game *-- Valued_Card
    Game <|-- Tactic_variant
    Card <|-- Tactic_card
    Card <|-- Valued_Card
    Deck o-- Card
    Card "0..7" --o "0..1" Player
    Card "0..9" --o "0..1" Stone
    Stone "0..5" -- "0..1" Player
    Game "0..*" -- "2" Player
    Game "1" *-- "1" Board
    Board "9" *-- "1" Stone
    Game "1" o-- "1..2" Deck
    Tactic_card <|-- Elite_troop
    Tactic_card <|-- Ruse
    Tactic_card <|-- Combat_Mode

%%---------- class
class Game_interface {
    + launch_Schotten_Totten1();
}

class Game {
        - clan_card_deck : Deck
        - board : Board
        + setupGame()
}


class Card_game {
    <<Singleton>>
    - number_valued_card : int
    - valued_cards_ : Card**
    - Card_game(min_card_value_: int, max_card_value_: int )
    .$ getInstance(num_card = 0 : int, min_card = 0 : int, max_card = 0 : int)  Card_game&
    + getCard(card_index : size_t) Card&
}

class Tactic_variant {
    - tactic_card_deck : Deck
    - number_of_tactic_cards = 10 : const int
    + getNbTacticCards()  int
    + setupGame()

}


class Board {
    - number_of_stone_tiles = 9 : const int
    - stone_tiles : Stone[number_of_stone_tiles]
    - winner : &Player
}


class Card
    

class Card{
    - color_ : CardColor
    - value_ : int<1 to 9>
}

class Tactic_card{
    - name: string
    - description: string
    + getName() string
    + getDescription() string
}

class Elite_troop {
    
}
class Ruse {
    
}
    
        
class Stone{
    - claimed : bool = false
    - winner& Player
    - slot_number = 3 : unsigned int
    - cardSlotsAvailable vector~bool~
    - tactic_slot : Card
    - player_1_combination: Card[slot_number]
    - player_2_combination:  Card[slot_number]
    + getNbStoneTiles() int
    + addCard()
}

class Player{
    - id: <1 or 2>
    - number_of_cards : int
    - hand : ~Card~
    - max_cards : int<6 to 7>
    - claimed_stones : list ~bool~
    + play_card()
    + draw_card() Card
    + getClaimed_stones() 
    + claim_stone()
    + getNumber_of_cards() int
}

class Deck{
    - cards: vector~const Card*~
    - number_of_cards : int
    + Deck(cards : vector~const Card*~)
    + isEmpty() bool
    + draw_card() Card
    + getNumber_of_cards() int
}

    
class Score{
- score_p1: int
- score_p2: int
- round: int
+p1_gagne()
+p2_gagne()
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
    


```


```mermaid
---
Uml simple
---
classDiagram
Card_game *-- Valued_Card
Game <|-- Tactic_variant
Card <|-- Tactic_card
Card <|-- Valued_Card
Deck o-- Card
Card "0..7" --o "0..1" Player
Card "0..9" --o "0..1" Stone
Stone "0..5" -- "0..1" Player
Game "0..*" -- "2" Player
Game "1" *-- "1" Board
Board "9" *-- "1" Stone
Game "1" o-- "1..2" Deck
Tactic_card <|-- Elite_troop
Tactic_card <|-- Ruse
Tactic_card <|-- Combat_Mode

```