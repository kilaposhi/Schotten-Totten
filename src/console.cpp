#include "console.h"

<<<<<<< HEAD
=======

>>>>>>> origin/main
int askPlayerValue(Player* player, std::array<int,2> rangeValue){
    cout << *player << " ";
    return askValue(rangeValue);
}

<<<<<<< HEAD
=======

>>>>>>> origin/main
bool askYesNo( string question){
    bool result;
    string answer;
    bool isValid = false;
    do {
<<<<<<< HEAD
        cout<< question << " (Y/n) " << '\n';
=======
        cout<< question << " (y/n) " << '\n';
>>>>>>> origin/main
        std::cin >> answer;
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        bool yes = answer == "yes" || answer == "y";
        bool no = answer == "no" || answer == "n";
        if (yes) {
            result = true;
            isValid = true;
<<<<<<< HEAD
=======

>>>>>>> origin/main
        }
        if (no){
            result = false;
            isValid = true;
        }
    } while(!isValid);
    return result;
}

<<<<<<< HEAD
int askValue(std::array<int,2> rangeValue){
=======

int askValue(std::array<int, 2> rangeValue){
>>>>>>> origin/main
    int result;
    bool isValid = false;
    if (rangeValue[0] > rangeValue[1])
        throw std::out_of_range("rangeValue is impossible");
    do {
<<<<<<< HEAD
        cout<< "Choose a value between " << rangeValue[0] << " and " << rangeValue[1] << '\n';
        std::cin >> result;
        if (result >= rangeValue[0] && result <= rangeValue[1])
            isValid = true;
=======
        std::cout<< "Choose a value between " << rangeValue[0] << " and " << rangeValue[1] << '\n';
        std::cin >> result;
        if (std::cin.fail()) {
            std::cout<< "Wrong input, please try again!\n";
            std::cin.clear(); // Reset std::cin error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
        } else if (result >= rangeValue[0] && result <= rangeValue[1]) {
            isValid = true;
        }
>>>>>>> origin/main
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
