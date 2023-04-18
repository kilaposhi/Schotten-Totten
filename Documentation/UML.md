
## UML version 1 :
Notre UML est porté vers markdown avec [mermaid](https://mermaid.js.org).
  
- [Syntaxe des diagrammes de classes](https://mermaid.js.org/syntax/classDiagram.html)
- [Liste des manières de l'utiliser](https://mermaid.js.org/ecosystem/integrations.html), perso j'utilise le plugin de Jetbrains
- [Ancien UML](https://codimd.math.cnrs.fr/miJRpGXeRKuiDBEZmn28rw?both#)

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
