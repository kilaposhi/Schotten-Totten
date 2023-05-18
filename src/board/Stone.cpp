#include "Stone.h"

string Stone::compute_combination(Player player)
{
    combination = getCombination(player);
    n = size(combination);
    if (n<3)
    {
        printf("Il n'y a pas assez de cartes pour revandiquer une borne")
        return NULL;
    }
    else
        if (isCouleur(combination) && isSuite(combination) ) return "Suite Couleur";
        else if (isCouleur(combination)) return "Couleur";
        else if (isBrelan(combination)) return "Brelan";
        else if (isSuite(combination)) return "Suite";
        else return "Somme";
}

bool isCouleur(vector<Card*> combination)
{
    return (combination[0]->getColor()== combination[1]->getColor() && combination[1]->getColor() == combination[2]->getColor());
}

bool isBrelan(vector<Card*> combination)
{
    return (combination[0]->getValue()== combination[1]->getValue() && combination[1]->getValue() == combination[2]->getValue());
}

bool isSuite(vector<Card*> combination)
{
    sort(combination.begin(), combination.end());
    return(combination[0]->getValue()== combination[1]->getValue() - 1 && combination[1]->getValue() == combination[2]->getValue() -1 )
}
