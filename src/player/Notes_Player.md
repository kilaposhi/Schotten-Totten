# LA CLASSE PLAYER

## Un joueur a:
- Un id entre 1 et 2
- Des cartes à lui
- Des frontières devant lui
- Des pioches devant lui

## Un joueur peu:
- Jouer une carte de sa main
  - La retirer de sa main
  - La poser sur une frontière
  - Diminuer le nombre de cartes du joueur de 1
- Piocher dans les pioches
  - Retirer la carte au dessus de la pile de pioche
  - La mettre à la fin de la main
  - Augmenter le nombre du joueur de carte de 1
- Revendiquer une frontière
  - Passer le statut de la frontière au statut de revendiqué
  - Passer le bool à l'indice de la borne revendiquée à 1 dans 
    la liste des bornes revendiquées du joueur