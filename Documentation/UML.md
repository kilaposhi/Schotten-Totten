
## UML version 1 :
Notre UML est porté vers markdown avec [mermaid](https://mermaid.js.org).
  
- [Syntaxe des diagrammes de classes](https://mermaid.js.org/syntax/classDiagram.html)
- [Liste des manières de l'utiliser](https://mermaid.js.org/ecosystem/integrations.html), perso j'utilise le plugin de Jetbrains
- [Ancien UML](https://codimd.math.cnrs.fr/miJRpGXeRKuiDBEZmn28rw?both#)

```plantuml
skinparam titleBorderRoundCorner 5
skinparam titleBorderThickness 2
skinparam titleBorderColor black


title Architecture Shotten-Totten
class Game 
{
    number_of_clan_cards: const 54
    number_of_tactical_cards: const 10
    number_of_stone_tiles : const 9
    getNbClanCards()
    getNbTactialCards()
    getNbStoneTiles()
}


class Clan_card{
    color: enum <bleu, violet, vert, rouge, orange, marron>
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

Tactical_card "0..8" -- "0..1" Player
'(Tactical_card, Player) .. Player_has_Card

Clan_card "0..8" --- "0..1" Player
'(Clan_card, Player) .. Player_has_Card

Stone_tiles "0..5" -- "0..1" Player
'(Stone_tiles, Player) .. Player_claim_Stone_tiles

'Deck "1..3" -- "2..2" Player
'(Deck, Player) .. Player_draws

Clan_card "0..*" -- "0..1" Deck
'(Clan_card, Deck) .. Deck_contains

Clan_card "0..4" -- "0..1" Stone_tiles
'(Clan_card, Stone_tiles) .. Stone_tiles_contains

Tactical_card "0..*" -- "0..1" Deck
'(Tactical_card, Deck) .. Deck_contains

Tactical_card "0..4" -- "0..1" Stone_tiles
'(Tactical_card, Stone_tiles) .. 'Stone_tiles_contains

Game "0..*" -- "2..2" Player
'(Game, Player) .. Player_plays_Game

Game "1..1" -- "9..9" Stone_tiles
'(Game, Stone_tiles) .. Stone_tiles_associate_Game

Game "1..1" -- "1..1" Deck
'(Game, Deck) .. Deck_associate_Game

Game "1..1" -- "10..10" Tactical_card
'(Game, Stone_tiles) .. Stone_tiles_associate_Game

Game "1..1" -- "54..54" Clan_card
'(Game, Clan_card) .. Stone_tiles_associate_Game
```
### Changements :
- Ajout des "-", "+"...
- Tableau de bool pour savoir les _slots available_ 

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
    %% <<Singleton>>
    - deck : Deck
    - stone_tiles Stone_tiles
}

class NormalVariant {
    + setupGame()
}

class Clan_card{
    - color : CardColor
    - value : int<1 to 9>
}

class Tactic_card{
    - name: string
    - description: string
}

class Stone_tiles{
    - int<1 to 9>
    - Player vainqueur
    player_1_combination: linked list <0 to 4 cards>
    player_2_combination: linked list <0 to 4 cards>
    claim: enum <0, 1, 2>
}

class Stone{
- claimed : bool
- slot_number = 3 : unsigned int
- vector~bool~ cardSlotsAvailable
}

class Player{
-id: <1 or 2>
- hand : vector~Card~
+play_card()
+claimed_stone_tiles()
}

class Card_game{
number_of_cards: const 54
getNbCards()
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

note for Tactical_card  "Un joker ne peut être présent plus d'une\n fois d un même côté de la frontière"

%% ------ Relations
Game <|-- NormalVariant


````
