#include "Game_interface.h"


void Game_interface::launch_Schotten_Totten1() {

    const int MAX_CLAN_CARD_STRENGTH = 9;
    const int MIN_CLAN_CARD_STRENGTH = 1;
    const int NUMBER_CLAN_CARDS = compute_number_cards(MIN_CLAN_CARD_STRENGTH, MAX_CLAN_CARD_STRENGTH);

    Card_game& clan_card_game = Card_game::getInstance( MIN_CLAN_CARD_STRENGTH, MAX_CLAN_CARD_STRENGTH);

}
