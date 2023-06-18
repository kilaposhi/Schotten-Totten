cmake_minimum_required(VERSION 3.24)
project(Schotten_Totten)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(
        Schotten_Totten
        src/main.cpp

        src/board/Board.h
        src/board/Board.cpp
        src/board/Combination.h
        src/board/Combination.cpp
        src/board/Border.h
        src/board/Border.cpp

        src/deck/Card.h
        src/deck/Card.cpp
        src/deck/Deck.h
        src/deck/Deck.cpp
        src/deck/DeckFactory.h
        src/deck/DeckFactory.cpp

        src/game/Game.h
        src/game/Game.cpp

        src/board/GameTracker.h
        src/board/GameTracker.cpp


        src/player/Player.h
        src/player/Player.cpp

        #src/Game_interface.cpp
        #src/Game_interface.h

        #src/GameVIew.cpp
        #src/GameVIew.h
        src/player/TacticHandler.h
        src/player/TacticHandler.cpp
        src/console.h
        src/console.cpp
)

