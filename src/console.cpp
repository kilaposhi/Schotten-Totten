#include "console.h"

int random(int min, int max) {
    if (min == max)
        return min;
    mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> gen(min, max);
    int a = gen(rng);
    return a;
}

int askPlayerValue(Player* player, std::array<int,2> rangeValue){
    cout <<"(" << *player << ") ";
    if (rangeValue[0] > rangeValue[1])
        throw std::out_of_range("rangeValue is impossible");
    if (player->isAI()) {
        int result = random(rangeValue[0], rangeValue[1]);
        cout << "Value chosen : " << result << '\n';
//        system("read");
//        system("pause");
        return result;
    }
    return askValue(rangeValue);
}

bool askPlayerYesNo(Player* player, const string& question){
    cout <<"(" << *player << ") ";
    if (player->isAI()) {
        bool result = random(0, 1);
        cout << "Answer : " << result << '\n';
        return result;
    }
    return askYesNo(question);

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
