# Big Schotten-Totten

# Sommaire :

- [Liens utiles](#Liens-utiles)
- [Tâches à faire](#tasks)
- [UML](#uml-version-2)
- [Utilisation de Git](#Git)

## Liens utiles

- Le [Trello de l'équipe](https://trello.com/b/XQj4rIn7/shotten-totten "Trello LO21")
- Le [Rapport n°1](https://fr.overleaf.com/project/6419a39393e938ac5e40ea3e)(Overleaf)
  
**Ressources :**  
- [Refactoring guru](https://refactoring.guru) Explications BD des **designs patterns** et des **bonnes pratiques** du refactoring AKA *"comment écrire du **clean code**" ?* 
- [Grepper](https://www.grepper.com) : Extension web qui donne des petites solutions de code dans le navigateur (Faire ses recherches en anglais)  
  <img alt="Example grepper" src="documentation/images/grepper_example.png"/>

  

# Tasks

- [x] `Deck`, `DeckBuilder` : @kilaposhi
- [x] `Card` : @kilaposhi
- [ ] `Player`
- [ ] `Border`
- [ ] `Board`
- [ ] [Rapport 2](documentation/rapport_2.md)

Faire les grosses classes de l'UML ci dessous:
[Lien vers les tâches précise](documentation/Tasks.md)
  
  
## UML version 2

```mermaid
---
title: Architecture Schotten-Totten V2
---
classDiagram

%% ------ Relations
Card <|-- Tactic_card
Card <|-- ValuedCard
Deck "1"*-- "0..*" Card
Deck "1" *-- "1" DeckInfo
Deck -- DeckBuilder
%%    Card "0..7" --* "0..1" Hand
Player "1"*--"1" Hand
Combination "1" --* "2" Border
Board "1" *-- "9" Border
Tactic_card <|-- Elite_troop
Tactic_card <|-- Ruse
Tactic_card <|-- Combat_Mode
CardColor -- ValuedCard 
DeckType -- Deck

%%---------- class
class Game_interface{
+ launch_Schotten_Totten1();
  }

class Card {
+ virtual print() string
+ virtual clone() unique_ptr~Card~
  }


class ValuedCard{
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
- cards : vectorValuedCard
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

class DeckBuilder {
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
```
                   (                                     
                   )\ )    )          )    )             
                  (()/( ( /(       ( /( ( /(   (         
                   /(_)))\())  (   )\()))\()) ))\  (     
                  (_)) ((_)\   )\ (_))/(_))/ /((_) )\ )  
                  / __|| |(_) ((_)| |_ | |_ (_))  _(_/(  
                  \__ \| ' \ / _ \|  _||  _|/ -_)| ' \)) 
                  |___/)_||_|\___) \__) \__|\___||_||_|  
                    ( /(      ( /( ( /(   (              
                    )\()) (   )\()))\()) ))\  (          
                   (_))/  )\ (_))/(_))/ /((_) )\ )       
                   | |_  ((_)| |_ | |_ (_))  _(_/(       
                   |  _|/ _ \|  _||  _|/ -_)| ' \))      
                    \__|\___/ \__| \__|\___||_||_|       
```

> This repository is under the **GNU General Public License v3.0**

# Crédits

Le Schotten-totten a été créé par Reiner Knizia et publié en 1999.