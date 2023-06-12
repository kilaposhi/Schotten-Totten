# Notes du commit
1) Suppression de l'attribut Player* player dans la classe Player
2) Modification de la méthode getid
3) Passage de vector<int> claimed_borders; à vector<unsigned int> claimed_borders;
4) Passage de vector< int> Player::getClaimed_borders(); à vector<unsigned int> Player::getClaimed_borders()
5) Création de void displayHand(); pour afficher la main
6) Initialisation du nombre max de cartes dans la main du joueur
7) Réindentation des atributs de Player
8) Changement d'écriture de mes using ... car Clion me l'a demandé (étrange mais bon...)
9) Ajout d'un attribut nom au Player. C'est plus sympas pour l'affichage du jeu
10) Ajout d'une méthode str() pour afficher le joueur
11) Changements du main mis en commentaire 
12) Copier coller de Card.h Car impossible de le merge 
13) Remplacement de Tactic_card par TacticCard pour être en accord 
14) Mise en commentaire de copy_vector_card dans deck car ca compile pas
15) Copier coller de tout de répertoir deck car impossible de merge
16) Ajout de la ligne "card_index -= 1;" dans remove_card_from_hand() pour que l'indice colle avec ce que l'utilisateur voit
17) Ajout de la méthode displayClaimedBorders() pour afficher les claimed borders
