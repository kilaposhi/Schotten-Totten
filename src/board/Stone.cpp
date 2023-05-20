#include "Stone.h"

Combination Stone::compute_combination(Player player)
{
    combination = getCombination(player);
    n = size(combination);
    if (n<3)
    {
        throw CombinationException("There is not enough cards to claim the stone");
    }
    else
        if (Color(combination,n) && Run(combination,n) ) return Combination::ColorRun ;
        else if (Color(combination,n)) return Combination::Color;
        else if (ThreeOfAKind(combination,n)) return Combination::ThreeOfAKind;
        else if (Run(combination,n)) return Combination::Run;
        else return Combination::Sum;
}

bool Color(vector<Card*> combination, int n)
{
    bool color = true;
    int i = 0;
    while (i < n - 1 && color)
    {
        color = (combination[i]->getColor() == combination[i + 1]->getColor());
        i++;
    }
    return color;
}

bool ThreeOfAKind(vector<Card*> combination, int n)
{
    bool three = true;
    int i = 0;
    while (i < n - 1 && three)
    {
        combination[i]->getValue()== combination[i+1]->getValue();
        i++;
    }
    return three;
}

bool Run(vector<Card*> combination,int n)
{
    sort(combination.begin(), combination.end());
    run = true;
    int i = 0;
    while (i < n - 1 && run)
    {
        combination[i]->getValue()== combination[i+1]->getValue()-1;
        i++;
    }
    return run;
}
