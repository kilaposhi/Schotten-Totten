#include "console.h"

#include "card/Card.h"

int askPlayerValue(Player* player, std::array<int,2> rangeValue){
    cout << *player << " ";
    return askValue(rangeValue);
}


bool askYesNo(const string& question){
    bool result;
    string answer;
    bool isValid = false;
    do {
        cout<< question << " (y/n) " << '\n';
        std::cin >> answer;
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        bool yes = answer == "yes" || answer == "y";
        bool no = answer == "no" || answer == "n";
        if (yes) {
            result = true;
            isValid = true;
        }
        if (no){
            result = false;
            isValid = true;
        }
    } while(!isValid);
    return result;
}


int askValue(std::array<int, 2> rangeValue){
    int result;
    bool isValid = false;
    if (rangeValue[0] > rangeValue[1])
        throw std::out_of_range("rangeValue is impossible");
    do {
        cout<< "Choose a value between " << rangeValue[0] << " and " << rangeValue[1] << '\n';
        std::cin >> result;
        if (result >= rangeValue[0] && result <= rangeValue[1])
            isValid = true;
        if (std::cin.fail()) {
            std::cout<< "Wrong input, please try again!\n";
            std::cin.clear(); // Reset std::cin error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
        } else if (result >= rangeValue[0] && result <= rangeValue[1]) {
            isValid = true;
        }
    } while(!isValid);
    return result;
}


CardColor askPlayerColor(Player* player, int numberColors){
    cout << "Here are the colors:\n";
    for (int i = 0; i < static_cast<int>(CardColor::End); i++){
        CardColor color = static_cast<CardColor>(i);
        cout << i << " : " << cardColorToString(color) << "\t";
    }
    int color_index = askPlayerValue(player, {0, numberColors});
    CardColor result = static_cast<CardColor>(color_index);
    return result;
}


