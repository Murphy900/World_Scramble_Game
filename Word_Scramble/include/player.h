#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player{
    private:
        std::string name; // player's name  
        int score; // player's score
        int life; // player's life count
        int counter; // number of tries left

    public:
        // Constructor to initialize player's name and score
        Player(const std::string& playerName );
        // Getter for player's name
        std::string getName() const;
        // Getter for player's score
        int getScore() const;
        // Function to update player's score
        void updateScore();    
        void updateLife(); // Function to update player's life count
        int getLife() const; // Getter for player's life count
        int getCounter() const; // Getter for player's counter
        void updateCounter(); // Setter for player's counter
        void resetCounter(); // Function to reset player's counter
        void setScore(int score);
        void setLife(int life);
};

#endif // PLAYER_H