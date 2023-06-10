#ifndef SCHOTTEN_TOTTEN_PLAYER_H
#define SCHOTTEN_TOTTEN_PLAYER_H

#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include <string>
#include <variant>

#include "deck/Card.h"
#include "board/Border.h"

using std::vector;
using std::list;
using std::array;
using std::string;
using std::cout, std::make_unique;

int main(){
try {
unique_ptr<Card> card_test = make_unique<ValuedCard>(2, CardColor::orange);
unique_ptr<ValuedCard> valuedCard= make_unique<ValuedCard>(std::move(card_test));
Combination combination(4);
//    combination.push_back(move(valuedCard));
//    combination.push_back(make_unique<TacticCard>(TacticType::traiter));
combination.push_back(make_unique<ValuedCard>(6, CardColor::orange));
combination.push_back(make_unique<ValuedCard>(7, CardColor::brown));
combination.push_back(make_unique<ValuedCard>(5, CardColor::brown));
combination.push_back(make_unique<ValuedCard>(1, CardColor::orange));
//cout << "numberCardRemaining :" << combination.getSum();
cout << combination ;
} catch(CombinationException e){
cout << e.what();
}
return 0;
}

#endif// SCHOTTEN_TOTTEN_PLAYER_H
