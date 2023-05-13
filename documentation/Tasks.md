

# Projet Global :
### Important :
- [ ] Mettre tout le code dans un namespace `Shotten_Totten`.
Permet d'éviter les collisions de noms avec les librairies du C 
- [ ] Faire les classes d'exceptions pour chaque classes

### Taches [Optionnelles](#optionnel)

## Classe `Deck`, `DeckCreator` :
- [ ] Créer une classe `DeckException` et vérifier
les valeurs passées dans `DeckCreator`, et les exceptions de `Deck`
- [ ] Rendre modulaire le choix des couleurs des cartes dans la création des `Valued_Card`
- [ ] Créer les cartes tactiques à partir d'un fichier JSON
- [ ] Implémenter `createTacticCard` de `DeckCreator`


#### Optionnel
- [ ] Pour chaque fichier repenser aux `const` pour les arguments, les méthodes, les attributs, etc...
- [ ] Marquer des variables `explicit` : Interdit les conversions implicites
- [ ] Utiliser les `static_cast<T>` et `dynamic_cast<T>` au lieu des C-style cast `(int)`
- [ ] Veiller à initialiser chaque variable (mieux avec les `{}`, ex : `int max{10}` )
- [ ] Formatter le code
    - Les noms de variables :  ex `CamelCase` pour les classes et `snake_case` pour les fonctions.
    - `int attribut_` : pour attributs privés
