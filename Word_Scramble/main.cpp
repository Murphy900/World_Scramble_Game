//main.cpp 
// This is the main file for the Word Scramble game
// It initializes the game, loads the dictionary, and handles user input and game logic.

#include "rand.h"
#include "parser.h"
#include "player.h"
#include "gameDynamic.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

int main(){
    cout <<  R"(                                                           
            _ _ _              _    _____                        _    _      
            | | | | ___  ___  _| |  |   __| ___  ___  ___  _____ | |_ | | ___ 
            | | | || . ||  _|| . |  |__   ||  _||  _|| .'||     || . || || -_|
            |_____||___||_|  |___|  |_____||___||_|  |__,||_|_|_||___||_||___|
                                                                  
    )" << endl;
    cout << "Welcome to the Word Scramble Game!" << endl;

       
        
        char choice;
        while (true){
            cout << "Start the game ? y/n"<< endl;
            cin >> choice;
            if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N') {
                break; // exit the loop if the input is valid
            } else {
                cout << "Invalid input. Please enter 'y' to start or 'n' to exit." << endl;
            }
        }
        if (choice == 'n' || choice == 'N') {
            cout << "Thank you for your time! Goodbye!" << endl;
            return 0; // exit the game if the user chooses not to start
        }


        // Prompt the user for their name and create a Player object
        char playerName[50];
        cout << "Enter your name: ";
        cin >> playerName; // get player's name from input
        Player player(playerName); // create a Player object with the player's name
        cout << "Hello, " << player.getName() << "! Let's start the game." << endl;

        // Load the dictionary from a file        
        string path = "dictionary.txt"; 

        char customDict;
        while (true) {
            cout << "Do you want to load a custom dictionary? (y/n): ";
            cin >> customDict;
            if (customDict == 'y' || customDict == 'Y' || customDict == 'n' || customDict == 'N') {
                break;
            } else {
                cout << "Invalid input. Please enter 'y' or 'n'." << endl;
            }
        }

        if (customDict == 'y' || customDict == 'Y') {
            cout << "Enter the relative path to your dictionary file: ";
            cin >> path;

            ifstream testFile(path);
            if (!testFile) {
                cerr << "The file you provided doesn't exist. Falling back to default dictionary." << endl;
                path = "dictionary.txt";
            }
        }
        
        vector<string> dictionary = read(path); // read the dictionary from the specified file

        if (dictionary.empty()) {
            cerr << "Error: Dictionary is empty. Please provide a valid dictionary file." << endl;
            return 1; // exit if the dictionary is empty    
        } 
        cout << "Dictionary loaded successfully. It contains " << dictionary.size() << " words." << endl;

        // Game loop        
        while(true){
            int index = word_pick(dictionary); // pick a random word from the dictionary
            string scrambledWord = shuffle_word(dictionary ,index); // scramble the picked word
            cout << "Scrambled word: " << scrambledWord << endl; // display the scrambled word
            cout << "Guess the word: ";
            
            while(true){
                string guess;
                cin >> guess; // get the player's guess
                
                // Check if the guess is correct
                if (guess == dictionary[index]){
                    earnedPoints(player); // update score for correct guess
                    player.resetCounter(); // reset the player's counter
                    break; // exit the guessing loop if the guess is correct
                }else{
                    player.updateCounter(); // update life count for incorrect guess
                    player.updateLife(); // update player's life count

                    if(player.getLife() == 0){
                    cout << "Game Over! You have no lives left." << endl;
                    cout << "Your final score is: " << player.getScore() << endl;
                    return 0; // exit the game if the player has no lives left
                    }
                    
                    cout << "Your answer is incorrect, and you lost 1 life" << endl;
                    cout << "You have " << player.getLife() << " lives left." << endl;
                    cout << "You have " << player.getCounter() << " tries left." << endl; 
                    cout << "Do you want a hint? (y/n): " << endl;
                    char hintChoice;
                    while(true){
                        cin >> hintChoice;
                        if (hintChoice == 'y' || hintChoice == 'Y' || hintChoice == 'n' || hintChoice == 'N') {
                            break; // exit the loop if the input is valid
                        } else {
                            cout << "Invalid input. Please enter 'y' for yes or 'n' for no." << endl;
                        }
                    }
                    // Provide a hint if the player chooses to
                    if (hintChoice == 'y' || hintChoice == 'Y') {
                        cout << " Hint: The first letters are: " << hint(player, dictionary[index], scrambledWord) << endl;
                        cout << "Guess the word again: " << endl;                    
                    }else{
                        cout << "Guess the word again: " << endl; // prompt the player to guess again without a hint
                    }                  
                }
            }  

            // Ask the player if they want to continue playing 
            cout << "Your actual score is: " << player.getScore() << endl;
            cout << "You have " << player.getLife() << " lives left." << endl;

            char continueChoice;
            while (true) {
                cout << "Do you want to continue playing? (y/n): ";
                cin >> continueChoice;      
                if (continueChoice == 'y' || continueChoice == 'Y' || continueChoice == 'n' || continueChoice == 'N') {
                    break; // exit the loop if the input is valid
                } else {
                    cout << "Invalid input. Please enter 'y' to continue or 'n' to exit." << endl;
                }
                
            } 
            if (continueChoice != 'y' && continueChoice != 'Y') {
                cout << "Thank you for playing! Your final score is: " << player.getScore() << endl;
                return 0; // exit the game if the user does not want to continue  
                }        
        }
}
