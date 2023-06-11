#include "console.h"

int askPlayerValue(Player* player, std::array<int,2> rangeValue){
    cout << *player << '\n';
    return askValue(rangeValue);
}

int askValue(std::array<int,2> rangeValue){
    int result;
    bool isValid = false;
    do {
        cout<< "Choose a value between " << rangeValue[0] << " and " << rangeValue[1];
        std::cin >> result;
        if (result >= rangeValue[0] && result <= rangeValue[1])
            isValid = true;
    } while(!isValid);
    return result;
}


CardColor askPlayerColor(Player* player, int numberColors){
    cout << "Here are the colors : \n";
    auto color_iterator = cardColors.begin();
    for (size_t i = 0; i < numberColors; i++){
        CardColor color = *color_iterator++;
        cout << i << " : " << cardColorToString(color) << "\t";
    }
    int color_index = askPlayerValue(player, {0, numberColors});
    CardColor result = *(cardColors.begin() + color_index);
    return result;
}
