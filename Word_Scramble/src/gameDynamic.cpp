//gameDynamic.cpp
#include "player.h"
#include "gameDynamic.h"
#include <string>
#include <iostream>

using namespace std;

// This function provides a suggestion for the player by combining the first three characters of the original word
// with the remaining characters of the scrambled word. It is used to help players who are struggling
string hint(Player& player, string& word, string& scrambledWord){
    int currentLife = player.getLife();
    
    switch (currentLife){
        case 2:
            return word.substr(0, 2) + scrambledWord.substr(3, word.length());
        case 1:
            return word.substr(0, 3) + scrambledWord.substr(3, word.length());
        default:
            return scrambledWord; // if no lives left, return the scrambled word as is
    }
}

void earnedPoints(Player& player){
    int numbersTry = player.getCounter();
    
    switch(numbersTry){
        case 3:
            cout << "Correct! You earned 10 points." << endl;
            player.updateScore(); // update score for correct guess
            break;
        case 2:
            cout << "Correct! You earned 5 points." << endl;
            player.updateScore(); // update score for correct guess
            break;
        case 1:
            cout << "Correct! You earned 2 points." << endl;
            player.updateScore(); // update score for correct guess
            break;
    }
    
}






