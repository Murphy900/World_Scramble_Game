//gameDynamic.h

#ifndef GAMEDYNAMIC_H
#define GAMEDYNAMIC_H

#include <string>

// This header file contains the declaration of the suggestion function
// The suggestion function provides a hint to the player by combining part of the original word with the
// scrambled word to help them guess the correct word.
std::string hint(Player& player, std::string& word, std::string& scrambledWord);
void earnedPoints(Player& player);

#endif //GAMEDYNAMIC_H


