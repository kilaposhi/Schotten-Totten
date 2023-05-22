cmake_minimum_required(VERSION 3.24)
project(Schotten_Totten)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

option(OPTIMIZE "Allow compiler optimizations.  Set to OFF to disable" OFF)

if(NOT OPTIMIZE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
endif()

add_executable(Schotten_Totten
        src/deck/Card.cpp
        src/deck/Card.h
        src/Game_interface.cpp
        src/Game_interface.h
        src/player/Player.cpp
        src/player/Player.h
#        src/board/Stone.cpp
#        src/board/Stone.h
        src/main.cpp
        src/deck/Deck.cpp
        src/deck/DeckFactory.cpp)
