cmake_minimum_required(VERSION 3.16)
project(Word_Scramble)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Necessary for Qt (MOC = Meta Object Compiler)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)

add_executable(Word_Scramble
    main.cpp
    src/player.cpp
    src/gameDynamic.cpp
    src/rand.cpp
    src/parser.cpp
    src/MainMenu.cpp
    src/playerSetup.cpp
    src/gameWindow.cpp 
    src/LoadGameWindow.cpp      
    include/MainMenu.h
    include/playerSetup.h
    include/gameWindow.h 
    include/LoadGameWindow.h    
)

include_directories(${CMAKE_SOURCE_DIR}/include)

target_link_libraries(Word_Scramble Qt6::Widgets)
target_link_libraries(Word_Scramble Qt6::Widgets Qt6::Multimedia)

configure_file(${CMAKE_SOURCE_DIR}/assets/dictionary.txt ${CMAKE_BINARY_DIR}/dictionary.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/assets/Pixel_Ponder.mp3 ${CMAKE_BINARY_DIR}/Pixel_Ponder.mp3 COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/assets/menu_background.jpg ${CMAKE_BINARY_DIR}/menu_background.jpg COPYONLY)
