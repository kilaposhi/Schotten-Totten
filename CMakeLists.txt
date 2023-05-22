cmake_minimum_required(VERSION 3.24)
project(Schotten_Totten)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(Schotten_Totten
        src/deck/Card.cpp
        src/deck/Card.h
        src/Game_interface.cpp
        src/Game_interface.h
        src/player/Player.cpp
        src/player/Player.h
        src/main.cpp
        src/deck/Deck.cpp
        src/deck/DeckFactory.cpp
        src/board/Board.cpp
        src/board/Border.cpp
        src/board/GameTracker.cpp
        src/module/Combination.cpp src/board/Border.cpp)