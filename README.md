# Big Schotten-Totten

# Sommaire :

- [Liens utiles](#Liens-utiles)
- [UML](#uml-version-2)
- [Utilisation de Git](#Git)

## Liens utiles

- Le [Trello de l'équipe](https://trello.com/b/XQj4rIn7/shotten-totten "Trello LO21")
- Le [Rapport n°1](https://fr.overleaf.com/project/6419a39393e938ac5e40ea3e)(Overleaf)
- Le [Lien UML](https://codimd.math.cnrs.fr/miJRpGXeRKuiDBEZmn28rw?edit)  
**Ressources :**  
- [Refactoring guru](https://refactoring.guru) Explications BD des **designs patterns** et des **bonnes pratiques** du refactoring AKA *"comment écrire du **clean code**" ?* 
- [Grepper](https://www.grepper.com) : Extension web qui donne des petites solutions de code dans le navigateur (Faire ses recherches en anglais)  
  <img alt="Example grepper" src="images/grepper_example.png" style="width: 85%; height: 70%" >    
  

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

>Voici un petit guide de **git**. Il n'est pas exhaustif et pas parfait (ne pas hésiter à le modifier)

Ptit conseil : Bien lire ce que git nous dit quand ça marche pas, il propose souvent les solutions au problème avec les bonnes commandes à copier-coller.  

### Installer le projet :
`git clone https://github.com/kilaposhi/Schotten-Totten.git` : Pour copier le repository sur vos machines depuis un terminal comme **git bash**.  
Si vous utilisez Clion, (Ou Visual Studio Code aussi surement), vous pouvez directement faire un nouveau projet depuis un contrôle de version ("**Create project from Version Control**").

### Bases : `add`, `commit`, `push` ...

- `git pull (origin) (branchName)` : Récupère le code sur le remote repository. `(arg)` sont optionnels.  
  `origin` est une variable *par défaut* qui désigne l'URL du remote repo (`origin == "https://github.com/kilaposhi/Shotten-Totten.git"`).  
  `branchName` : Le nom de la *remote branch* que l'on veut récupérer, par défaut la même branche que celle où l'on se trouve. (voir [branch](#branch-))  
  
 **Philosophie des commits** : Pour la clarté, un commit  doit faire **une seule** tâche, avec un message court.   
   
- `git add <files>` : Ajoute des fichiers modifiés à l'index, (en : *staged*). L'index contient les changements qui vont être `commit`.
- `git status` : **A faire AVANT de `commit`**, montre les changements *staged*, et *not staged* sur la *current branch*. Les changements *staged* vont être commit
- `git reset <files>` : Enlève les fichiers de l'index pour éviter de les commits
- `git commit -m "Message court qui explique la tâche que l'on commit"` : Créer un commit avec l'index (les *staged files*)
- `git push (origin) (branchName)` : On partage nos modifications (le `commit`) au *remote repository* (`origin`)

**Exemple de bonnes utilisation**:
  ```bash
  git add ./README
  git commit -m "Update Git section" 
  git push 
  ```
  ```bash
  git add src/Card/   # Ajoute tous les fichiers du directory Valued_Card à l'index
  git reset src/Card/testCard.cpp # On ne veut commit que la classe Valued_Card
  git status  # On vérifie que l'on va commit uniquement Valued_Card.cpp et Valued_Card.h
  git commit -m "Create Card class"
  git push 
  ```

### Branch :
- `git branch` : Liste les branches **locales** et indique sur quelle branche vous êtes avec `*` (ex: `* main`)
- `git pull origin <remoteBranch>` : `pull` une branche du *remote repository* (le github) en local, une *remote branch* (ex : `git pull origin lilian` )
- `git checkout <branchName>`: Changer de branche
- `git checkout -b <newBranchName>`: Créer une nouvelle branche

Les branches git sont différentes versions du projets.    
Lorsque l'on veut coder quelque chose :  
- Créer une nouvelle branche
- Coder, et vérifier que tout fonctionne (le projet compile)
- Avant de `push`, la branch doit être à jour : `git pull main` (met à jour avec la branche `main` => `merge` la *remote branch* main avec la *current branch* ), ou `git pull` si quelqu'un modifie la même branche que vous modifiez.
  Ainsi on règle les conflits en local.
- `git push (origin) (branchName)` : Après avoir `push` la branch sur le *remote repository*, on pourra créer une **PR (Pull Request)** avec la branche main.

La branche `main` est **protégée**,  cela veut dire que personne ne peut **push** quoi que ce soit sur la branche `main`. Il faut obligatoirement créer une **PR** pour `merge` une branche sur `main`.   
La PR, indique aux autres collaborateurs les **changements** faits par la **PR**. On peut aussi en discuter, et **critiquer** le code produit pour l'améliorer (écrire du code est différent de lire celui de quelqu'un d'autre).  

### Le fichier`.gitignore` :
- Créer un fichier `.gitignore` (ou modifier celui existant) dans lequel on écrira les `path` des fichiers et des directory que `git` doit ignorer et ne jamais sauvegarder (ne jamais commit).    
Exemple de `.gitignore` pour mon cas où j'utilise l'IDE Clion :
```
cmake-build-debug/
CMakeLists.txt
.idea/
```
 **Pourquoi git doit ignorer des fichiers:** D'une manière générale on met principalement le **code source** sur git.     
         
 Comme le repository github est **public**, tout le monde pourrait accéder à notre projet. Comme on ne veut pas que le monde ait accès à nos fichiers de config pour des questions de sécurité, on utilise `.gitignore`.   
#### Exemples de fichiers à indiquer dans le `.gitignore` :  
- Fichiers de configurations spécifique à l'IDE ou à l'OS  
- Fichiers contenant des logins, mots de passe pour une BDD, token d'API...
- Les Logs : Servent à débugger, changent tout le temps... 
- Librairies : ce sont des fichiers lourds qu'on ne modifie jamais
- Exécutables, fichiers binaires : Ne sert à rien de les sauvegarder et cause des conflits facilements

>**Remarque :** Une fois qu'un fichier a été `push` sur le repository publique il est très dur de le faire disparaitre totalement, c'est pour cela que l'on prend des précautions.

