
## UML version 1 :
Notre UML est porté vers markdown avec [mermaid](https://mermaid.js.org).
  
- [Syntaxe des diagrammes de classes](https://mermaid.js.org/syntax/classDiagram.html)
- [Liste des manières de l'utiliser](https://mermaid.js.org/ecosystem/integrations.html), perso j'utilise le plugin de Jetbrains
- [Ancien UML](https://codimd.math.cnrs.fr/miJRpGXeRKuiDBEZmn28rw?both#)

```plantuml
@startuml 



class Clan_card{
    color: CardColor 
    value: int <1 to 9>
    getColor()
    getStrength()
   
}

class Tactical_card{
    name: string
    description: string
    getName()
    getDescription()
    
}



class Stone_tiles{
    id: int <1 to 9>
    vainqueur: string Joueur
    player_1_combination: linked list <0 to 4 cards>
    player_2_combination: linked list <0 to 4 cards>
    claim: enum <0, 1, 2>
    claimed: bool
    addCard()
    getCard()
}


class Player{
    id: <1 or 2>
    put_card()
    claimed_stone_tiles()
}



class Deck{
    cards: linked list
    empty()
    draw_card()
}

class Score{
    score_p1: int
    score_p2: int
    round: int
    
}

note top of Tactical_card : Un joker ne peut être présent plus d une\nfois d un même côté de la frontière

```
### Changements :
- Ajout des "-", "+"...
- Ajout des relations entre les classes **, elles ne sont pas forcément claires, et pourront changer**
- `Stone_tiles` devient simplement `Stone`
- `Tactical` devient `Tactic` (cf règle en anglais)
- Héritage pour la classe `Game` avec la variante de jeu
- Tableau de bool pour savoir les _slots available_ dans la classe `Stone` 
- Création de la classe `Board` pour gérer la vie des `Stone`, car cela réduit le couplage à la Classe `Game` qui gère déjà la vie des `Card`

### #TODO
- Penser à un héritage avec une seule classe `Card` qui pourrait être utilisé `Deck`

```mermaid
---
title: Architecture Shotten-Totten
---
classDiagram

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


%%---------- Class
class Game {
    - clan_card_deck : Deck
    - board : Board
    - number_of_clan_cards = 54: const int
    + getNbClanCards() : int
    + setupGame()
}

class Board {
    - number_of_stone_tiles = 9 : const int
    - stone_tiles : Stone[9]
    + setupGame()
}

class Tactic_variant {
    - tactic_card_deck : Deck
    - number_of_tactic_cards =10 : const int
    + getNbTacticCards() : int
    
}

class Clan_card{
    - color : CardColor
    - value : int<1 to 9>
    + getColor()
    + getStrength()
}

class Tactic_card{
    - name: string
    - description: string
}


class Stone{
    - claimed : bool
    - winner& Player
    - slot_number = 3 : unsigned int
    - cardSlotsAvailable vector~bool~
    - player_1_combination: linked list <0 to 4 cards>
    - player_2_combination: linked list <0 to 4 cards>
    + getNbStoneTiles()
}

class Player{
-id: <1 or 2>
- num_of_card = 6 : int
- hand : vector~Card~
+play_card()
+claimed_stone_tiles()
}

class Card_game{
number_of_cards: const 54
getNbCards()
}

class Deck{
- cards: list~Card~
+isEmpty()
+draw_card()
}

class Score{
score_p1: int
score_p2: int
round: int

}

note for Tactic_card  "Un joker ne peut être présent plus d'une\n fois d un même côté de la frontière"

%% ------ Relations
Game <|-- Tactic_variant
Tactic_card "0..8" -- "0..1" Player
Clan_card "0..8" -- "0..1" Player
Clan_card "0..4" -- "0..1" Stone
Stone "0..5" -- "0..1" Player
Deck "1..3" -- "2..2" Player
Clan_card "0..*" --o "0..1" Deck
Tactic_card "0..*" --o "0..1" Deck
Tactic_card "0..4" --o "0..1" Stone
Game "0..*" -- "2" Player
Game "1" *-- "1" Board 
Game "1" o-- "1..2" Deck
Tactic_variant "1" *-- "10" Tactic_card
Game "1" *-- "54" Clan_card


```
