cmake_minimum_required(VERSION 3.24)
project(Schotten_Totten)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(
        Schotten_Totten
        src/main.cpp

        src/board/Board.cpp
        src/board/Board.h
        src/board/Combination.cpp
        src/board/Combination.h
        src/board/Border.cpp
        src/board/Border.h

        src/deck/Card.cpp
        src/deck/Card.h
        src/deck/Deck.cpp
        src/deck/Deck.h
        src/deck/DeckFactory.cpp
        src/deck/DeckFactory.h

        src/game/Game.cpp
        src/game/Game.h
        src/board/GameTracker.cpp
        src/board/GameTracker.h

        src/player/Player.cpp
        src/player/Player.h

        #src/Game_interface.cpp
        #src/Game_interface.h

        #src/GameVIew.cpp
        #src/GameVIew.h
        src/player/TacticHandler.cpp
        src/player/TacticHandler.h
        src/console.h src/console.cpp)
