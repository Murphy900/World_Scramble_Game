#ifndef RAND_H
#define RAND_H

#include <vector>  // for using vectors
#include <string>


// Function that generates a random number between min and max, where the max is the length of the
// dictionary vector
int word_pick(const std::vector<std::string>& dictionary);

// Function to shuffle a word picked in the dictionary vector 
std::string shuffle_word(const std::vector<std::string>& dictionary, int index);


#endif