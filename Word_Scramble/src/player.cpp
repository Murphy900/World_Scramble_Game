// player.cpp
// This library contain the implementation of the player class 

#include "player.h"
#include <string>

using namespace std;

Player::Player(const string& playerName){
    name = playerName; // initialize player's name
    score = 0; // initialize player's score to 0
    life = 3; // initialize player's life count to 3
    counter = 3; // initialize player's counter to 3
}
// Constructor to initialize player's name, score, life and numbber of try
// Player class is used to represent a player in the Word Scramble game
// It contains the player's name and score, and a constructor to initialize these values.

string Player::getName() const {
    return name; // return player's name
}

int Player::getScore() const {
    return score; // return player's score
}   
int Player::getCounter() const {
    return counter; // return player's counter
} // Getter for player's counter

void Player::updateCounter() {
    counter -= 1; // set the player's counter to a new value
    
} // Setter for player's counter
// This function returns the current score of the player.

void Player::resetCounter() {
    counter = 3; // reset the player's counter to 3
} // Function to reset player's counter
// This function resets the player's counter to 3, which is used to track the number of
// tries left for the player in the game.

void Player::updateScore() {
    int numbersTry = getCounter(); // get the current life count

    switch (numbersTry) {
        case 3:
            score += 10;
            break;
        case 2:
            score += 5;
            break;
        case 1:
            score += 2;
            break;
        default:
            break;
    }

    if (score < 0) {
        score = 0; // ensure score does not go below 0
    }
} // Function to update player's score
// This function updates the player's score by adding the specified points to the current score.
// If the updated score goes below 0, it is set to 0 to prevent negative scores.

void Player::updateLife (){
    life -= 1; // update player's life count by subtracting lifeCount
    if (life < 0) {
        life = 0; // ensure life count does not go below 0  
    }
} 

int Player::getLife() const {
    return life; // return player's life count
} 
// Getter for player's life count
// This function returns the current life count of the player.
// It is used to check how many lives the player has left in the game.

void Player::setScore(int s) {
   score  = s;
}

void Player::setLife(int l) {
   life = l;
}