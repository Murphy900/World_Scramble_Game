cmake_minimum_required(VERSION 3.10)

project(Word_Scramble)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Word_Scramble
    main.cpp
    src/player.cpp
    src/gameDynamic.cpp
    src/rand.cpp
    src/parser.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/include)

configure_file(${CMAKE_SOURCE_DIR}/assets/dictionary.txt ${CMAKE_BINARY_DIR}/dictionary.txt COPYONLY)

