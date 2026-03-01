#ifndef RAND_H
#define RAND_H

#include <vector>  // for using vectors
#include <string>
using namespace std;

// Function that generates a random number between min and max, where the max is the length of the
// dictionary vector
int word_pick(const vector<string>& dictionary);

// Function to shuffle a word picked in the dictionary vector 
string shuffle_word(const vector<string>& dictionary, int index);


#endif