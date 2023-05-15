

# Projet Global :
### Important :
- [ ] Mettre tout le code dans un namespace `Shotten_Totten`.
Permet d'éviter les collisions de noms avec les librairies du C 
- [ ] Faire les classes d'exceptions pour chaque classes

- [ ] Faire le Rapport 2

##### Cliquer pour les taches [Optionnelles](#optionnel)


## Classe `Player`
- [ ] Coder `Hand`, la main du `Player` ?? (martin)
- [ ] Coder `Player` (martin)
- [ ] Réflechir et créer un système qui permet de gérer les tours

## Classe `Border`, et `Board` :
- [ ] Coder `Border` (Lili)
- [ ] Coder la fonction `compute_combination(ValuedCard)` pour calculer les combinaisons de Poker, avec plein de fonctions dans `module/` (prototypes dans la branche [combination](https://github.com/kilaposhi/Shotten-Totten/tree/combination) (Nes)
- [ ] Coder `Board` (Capu)
  
- [ ] Coder `GameTracker` pour suivre l'état de la partie (quelles cartes ont été jouées et pas jouées):
Avec 2 `Deck`, un qui contient les cartes déjà jouées (`playedCards`), et l'autre qui contient
les cartes non jouées ( `remainingCards`). Cette classe sera utilisée pour calculer si la règle de `claim` une `Border`
si l'adversaire ne peut faire mieux. (Nes)
  
  
- [ ] Peut-être un [*observer*](https://refactoring.guru/design-patterns/observer),
  connecté au `unique_ptr<TacticCard> tactic_slot_` de `Border`, qui lorsqu'une carte **tactique** est jouée sur le *slot*
  est traité par un `TacticHandler` qui s'occupera d'appliquer l'effet de la carte.
- [ ] Pour les effets de la cartes Tactiques utilisé le [*strategy pattern*](https://refactoring.guru/design-patterns/strategy)

## Classe `Deck`, `DeckBuilder`, `Card` ... :
- [x] Coder `Card` et `ValuedCard` @kilaposhi
- [x] Coder `Deck` et `DeckBuilder` @kilaposhi
- [ ] Transformer `DeckBuilder` en `DeckFactory` @kilaposhi
   

- [ ] modularité `CardColor`, utiliser le nombre de couleurs avec une Enum avec beaucoup de couleur et en mettant le nombre de cartes voulu, ça utilise le bon nombre de couleurs ?
- [ ] Coder les `Tactic_card`  (construire les cartes tactiques avec un fichier XML, ou JSON)
- [ ] Implémenter `createTacticCard` de `DeckBuilder`
- [ ] Créer une classe `DeckException` et vérifier
les valeurs passées dans `DeckBuilder`, et les exceptions de `Deck`
- [ ] Rendre modulaire le choix des couleurs des cartes dans la création des `ValuedCard`
- [ ] Créer les cartes tactiques à partir d'un fichier JSON

# class `Game_interface` : 
- [ ] Menu pour lancer le Schotten-Totten 1, et changer de versions
, tactiques, les manches, les scores, etc...

# Qt class `Displayer`: (Nes)
- [ ] Créer les widgets pour cartes
- [ ] Créer le plateau


#### Optionnel
- [ ] Pour chaque fichier repenser aux `const` pour les arguments, les méthodes, les attributs, etc...
- [ ] Marquer des variables `explicit` : Interdit les conversions implicites
- [ ] Rajouter les `inline` devant les petites fonctions ( ou settings)
- [ ] Utiliser les `static_cast<T>` et `dynamic_cast<T>` au lieu des C-style cast `(int)`
- [ ] Veiller à initialiser chaque variable (mieux avec les `{}`, ex : `int max{10}` )
- [ ] Formatter le code
    - Les noms de variables :  ex `CamelCase` pour les classes et `snake_case` pour les fonctions.
    - `int attribut_` : pour attributs privés, et fonctions privées
    - Clean header files : La partie `public` avant la partie `private`
      - mettre 2 `private`, un pour les attributs, l'autre pour les fonctions
      - Toutes les fonctions sont définies dans le `.cpp` correspondant
