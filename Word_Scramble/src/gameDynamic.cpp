//gameDynamic.cpp
#include "player.h"
#include "gameDynamic.h"
#include <string>
#include <iostream>
#include <rand.h>
using namespace std;

// This function provides a suggestion for the player by combining the first three characters of the original word
// with the remaining characters of the scrambled word. It is used to help players who are struggling
string hint(Player& player, string& word, string& scrambledWord){
    int currentLife = player.getLife();
    int revealCount = (currentLife == 2) ? 2 : 3;

    // Revealed letters from the original word
    string revealed = word.substr(0, revealCount);

    // Copy of the scrambled word from which to remove the revealed letters
    string remaining = scrambledWord;
    for (int i = 0; i < revealCount; i++) {
        size_t pos = remaining.find(word[i]);
        if (pos != string::npos)
            remaining.erase(pos, 1);
    }

    return revealed + remaining;
    
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







