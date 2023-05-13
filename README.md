# Big Schotten-Totten

# Sommaire :

- [Liens utiles](#Liens-utiles)
- [UML](#uml-version-2)
- [Tâches à faire](#tasks)
- [Utilisation de Git](#Git)

## Liens utiles

- Le [Trello de l'équipe](https://trello.com/b/XQj4rIn7/shotten-totten "Trello LO21")
- Le [Rapport n°1](https://fr.overleaf.com/project/6419a39393e938ac5e40ea3e)(Overleaf)
  
**Ressources :**  
- [Refactoring guru](https://refactoring.guru) Explications BD des **designs patterns** et des **bonnes pratiques** du refactoring AKA *"comment écrire du **clean code**" ?* 
- [Grepper](https://www.grepper.com) : Extension web qui donne des petites solutions de code dans le navigateur (Faire ses recherches en anglais)  
  <img alt="Example grepper" src="images/grepper_example.png" style="width: 85%; height: 70%" >    
  

# Tasks

- [ ] Faire le rapport 2 
- [x] Coder `Card` et `Card_game` @kilaposhi
- [ ] Coder `Stone`  et `Board`. (Comme `Card` et `Game_Card`)
- [ ] Coder la fonction `compute_combination(3 Valued_Card)` pour calculer les combinaisons de Poker, avec plein de fonctions dans `module/` (prototypes dans la branche [combination](https://github.com/kilaposhi/Shotten-Totten/tree/combination)
- [x] Coder `Deck` @kilaposhi
- [ ] Coder `Player`
- [ ] Coder les `Tactic_card` et `Tactic_card_game` (construire les cartes tactiques avec un fichier XML)

  
  
## UML version 2

```mermaid
---
title: Architecture Schotten-Totten V2
---
classDiagram

%% ------ Relations
Card <|-- Tactic_card
Card <|-- Valued_Card
Deck *-- Card
Deck *-- DeckInfo
Deck -- DeckCreator
%%    Card "0..7" --* "0..1" Hand
Player *-- Hand
Combination "0..9" --* "0..1" Border
Board "9" *-- "1" Border
Tactic_card <|-- Elite_troop
Tactic_card <|-- Ruse
Tactic_card <|-- Combat_Mode
CardColor -- Valued_Card 
DeckType -- Deck

%%---------- class
class Game_interface{
+ launch_Schotten_Totten1();
  }

class Card {
+ virtual print() string
+ virtual clone() unique_ptr~Card~
  }


class Valued_Card{
- color : CardColor
- value : int<1 to 9>
+ override print() string
+ override clone() unique_ptr~Card~
  }

class Tactic_card{
- name: string
- description: string
+ override print() string
+ override clone() unique_ptr~Card~
  }


class Board {
- numberBorders = 9 : const int
- Borders : Stone[number_of_stone_tiles]
- winner : &Player
  }

class Combination{
- cards : vector~Valued_Card~
- sumValues : int
  }

class Border{
- claimed : bool = false
- winner& Player
- slot_number = 3 : unsigned int
- cardSlotsAvailable vector~bool~
- tactic_slot : Tactic_Card
- player_1_combination: Combination
- player_2_combination:  Combination
+ addCard()
  }

class Hand {
- cards : vector~unique_ptr~Card~~
+ refill()
+ playCard(Card)
  }

class Player{
- id: <1 or 2>
- number_of_cards : int
- hand : Hand
- max_cards : int<6 to 7>
- claimed_stones : list ~bool~
+ play_card()
+ draw_card() Card
+ getClaimed_stones()
+ claim_stone()
+ getNumber_of_cards() int
  }

class Deck{
- deckInfo : DeckInfo
- cards: vector~Card*~
+ Deck(const Deck&)
+ operator=(const Deck&) Deck&
+ isEmpty() bool
+ drawCard() Card
+ getNumberRemainingCards() int
  }

class DeckInfo {
- deckType: DeckType
- total_number_card : int
- min_value_card, max_value_card : int
  }

class DeckCreator {
<<Builder>>
+ createClanDeck()
+ build() Deck
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

class DeckType{
<<Enumeration>>
ValuedCard
TacticCard
DiscardDeck
}


```

[voir UML version 1](documentation/UML.md)  
  

## Git

[Aide sur l'utilisation de git ](documentation/aide_git.md)

# Avant-propos

> This repository is under the **GNU General Public License v3.0**

# Crédits

Le Schotten-totten a été créé par Reiner Knizia et publié en 1999.