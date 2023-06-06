cmake_minimum_required(VERSION 3.24)
project(Schotten_Totten)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(
        Schotten_Totten
        src/main.cpp

        src/deck/Deck.cpp
        src/deck/Deck.h
        src/deck/DeckFactory.cpp
        src/deck/DeckFactory.h
        src/deck/Card.cpp
        src/deck/Card.h

        src/board/Combination.h
        src/board/Combination.cpp

        src/Game_interface.cpp
        src/Game_interface.h

#        src/player/Player.cpp
#        src/player/Player.h

)