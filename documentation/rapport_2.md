 
On utilisera `Deck`  avec les cartes `vector<unique_ptr<Card>>`, des `.move()` pour changer les cartes de place (dans les `Hand`,...)
- Utilisation de `DeckBuilder` pour les différents `Deck` [Builder pattern](https://refactoring.guru/design-patterns/builder)

[what's polymorphic type](https://stackoverflow.com/questions/2032361/whats-polymorphic-type-in-c)

- Observer etc pour jouer les `TacticCard` et lancer leur script
  [Bonne vidéo sur les observer](https://www.youtube.com/watch?v=A_MsXney3EU)


- renommer `Stone` en `Border`
- On rajoute un cast de `unique_ptr<Card>` vers `unique_ptr<ValuedCard>` pour les `Border` [stackoverflow](https://stackoverflow.com/questions/17417848/stdunique-ptr-with-derived-class) , pour interdire de jouer des `TacticCard` sur les bornes.


```mermaid
---
title : Deck and Cards
---
classDiagram

    DeckFactory -- Deck
    Deck "1" *-- "0..*" Card
    class DeckFactory{
        - setNumberColors(num_colors: int)
        - setCardRange(min:int, max:int)
        + createClanDeck() DeckBuilder&
        + createTacticDeck() DeckBuilder&
        + build() Deck
    }

    class Deck{
        - cards : vector~unique_ptr~Card~~
        + shuffle()
        + drawCard() unique_ptr~Card~
        + putCard(unique_ptr<Card>)
        + getRemainingCards() int
    }

```


```mermaid
---
title : Board, Border and Player
---
classDiagram

    class Border{
        - Combination1 vector~ValuedCard~
    }
```

**Fonctionnement de la règle de claimed by completion**
- Un listener des `Border` pour l'écoute des nouvelles cartes. Création d'un deck du même type que le jeu actuel pour savoir quel cartes ont été joué

```mermaid
classDiagram
    class CardTracker{
<<can be a Singleton>>
- remainingCards : Deck = DeckBuilder.createClanDeck()
- playedCards : Deck
}
```
- Inconvénient 2 fois plus de `Card` (-- memoire), plus rapide car pas besoin d'itérer sur le Singleton `Jeu`, et moins de couplage avec cette classe, plus de modularité etc...


# Réflexions architectures

En élaborant notre architecture, comme nous sommes nouveaux à la programmation orienté objet, naturellement nous nous 
sommes inspirés de l'exemple de jeu de cartes vu en TD, le **set**. 

Nous avons donc créé un Singleton `Card_game`, (équivalent à `Jeu` pour le `Set`) 
dont la seule responsabilité est de créer les cartes dynamiquement, de les rendre accessible à toutes les 
classes grâce à la fonction `static` `getInstance()`, et de les libérer de la mémoire.  

Cependant, pour le Schotten-Totten cela pose plusieurs problèmes.
- On s'attend à créer au moins 2 jeux de cartes, les *cartes tactiques* et *cartes clan*. De plus si l'on pense à l'implémentation du Schotten-Totten 2 ou d'un autre jeu de cartes, on voudrait pouvoir créer des jeux différents :
Pour le Schotten-Totten 2 il y a 60 cartes *valuées* (comme les cartes clans) avec des valeurs allant de 0 à 11 et avec 5 couleurs.
  
  Donc, on a rendu le Singleton `Card_game` instantiable avec des paramètres pour créer différents jeux de cartes valuées
dans cette [Pull Request](https://github.com/kilaposhi/Schotten-Totten/pull/3)
- Mais l'utilisation de ce Singleton ne me parait pas claire, et pas intuitive. En effet, intuitivement on voudrait
créer directement la pioche et les cartes en même temps (d'ailleurs en anglais pioche se dit *deck* et jeu de cartes aussi !).
      
  Ainsi, on se passe les cartes comme dans le vrai jeu et chaque carte n'existe qu'une fois.
- C'est bizarre d'avoir une classe qui crée les cartes. Puis tous les objets restants se passent des références de cartes du Singleton. 

### Créer les cartes en même temps que la pioche.

- Cela implique que toutes les classes comme `Player`, `Border` etc composent la classe `Card`, cartes qui sont alloués dynamiquement, 
donc toutes les classes doivent libérer la mémoire de leurs cartes.  
  
  **Solution :** On utilisera les *smart pointers* de la librairie `#include <memory>`, avec le type `unique_ptr<Card>` qui gèrent la mémoire automatiquement et la libèrent forcément à la destruction de l'objet, ou même lors d'une exception. 
  On utilisera les méthodes `std::move()`, `std::reset()`, etc pour changer le propriétaire des cartes.

### Pourquoi l'allocation dynamique ?

Question légitime, car rajoute de la complexité, moins lisible, besoin de comprendre les pointeurs, etc. 

1. **La durée de vie** : On veut pouvoir se passer les `Card` (en réalité les `unique_ptr<Card>`) même si elle n'ont pas été crées au même endroit.
  
  
2. Le **polymorphisme**
Dans le cas de `Deck`, il contient des `Card`. Pour pouvoir faire des `Deck` de sous classes de `Card` (comme `ValuedCard` et `TacticCard`), il faut utiliser l'allocation dynamique, Exemple :
    ```cpp
    // Allocation dynamique :
    BaseClass* base = new DerivedClass();
    // Polymorphisme avec allocation dynamique :
    Card* valued_card = new ValuedCard(1, CardColor::red);

    // Besoin de libérer la mémoire
    delete card;
    delete valued_card;
    ```
    Avec les ***smart pointers*** on a :
    ```C++
    // Alloc dynamique classique
    int* dynamic_int = new int(1);
    // Alloc dynamique avec unique_ptr :
    #include <memory> // Lib pour les smarts pointer 
    std::unique_ptr<int> dynamic_int = std::make_unique<int>(1);
    // Plus besoin de libérer la mémoire

    // polymorphisme :                                       
    std::unique_ptr<Card> valued_card = std::make_unique<ValuedCard>(3, CardColor::red);
    std::unique_ptr<Card> tactic_card = std::make_unique<TacticCard>(Tactic::Joker);

    using std::unique_ptr, std::make_unique, std::move; // pour ne pas mettre de `std::`
    //Pour changer le owner d'un unique_ptr 
    unique_ptr<Card> new_card = move(valued_card); 
    ```
   Pour les **tableaux dynamiques**, on utilisera les `vector`
    ```C++
    // Plutôt que les C-like dynamic array :
    Card** cards = new Card*[54];
   // On préférera les `std:vector` :
   #include <vector>
   using std::vector;
   vector<Card*> cards;
   // avec les `unique_ptr` :
   vector<unique_ptr<Card>> cards;
    ```
