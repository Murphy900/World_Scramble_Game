//rand.cpp
// this library is used to generate random numbers for 
//shuffling words in the Word Scramble game

#include <cstdlib>   // for random number generation
#include <rand.h>    // include the rand header file
#include <vector>  // for using vectors
#include <string>
#include <ctime>   // for seeding the random number generator
#include <iostream> // for error messages
#include <random> // for random_shuffle 
#include <rand.h> // include the rand header file

using namespace std;

// Function that generates a random number between min and max, where the max is the lenght of the 
// dictionary vector

int word_pick (const vector<string>& dictionary){
    int length = dictionary.size(); // get the size of the dictionary vector
    
    if (dictionary.empty()) {
        cerr << "Error: Dictionary is empty." << endl;
        return -1; // return -1 if the dictionary is empty  
    }
    
    srand(time(0)); // seed the random number generator with current time
    int random_index = rand() % length; // generate a random index within the range of the dictionary size

    return random_index; // return the random index
}

// Function to shuffle the words in the dictionary vector

string shuffle_word(const vector<string>& dictionary, int index ){
    if (index < 0 || index >= dictionary.size()) {
        cerr << "Error: Index out of bounds." << endl;
        exit(1); // return if the index is out of bounds
    }
    string word = dictionary[index];
    random_device rd; // obtain a random number from hardware
    mt19937 g(rd()); // seed the generator
    shuffle(word.begin(), word.end(),g); // shuffle the characters in the word

    return word; // return the shuffled word
}








