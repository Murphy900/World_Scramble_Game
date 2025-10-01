#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <parser.h> // include the parser header file

using namespace std;

vector<string> read(const string& text){
    vector<string> words; // vector to hold words from the dictionary
    ifstream inFile;  // open the file specified by text
    inFile.open(text); // open the file
    
    if (!inFile){
        cerr << "Error opening file: " << text <<endl;
        exit(1); // call system to exit the program if file cannot be opened
    }
    string word;

    while (inFile >> word){ // read words from the file until end of file
        words.push_back(word); // add each word to the vector
    }
    inFile.close(); // close the file after reading
    return words; // return the vector containing the words
} // vector to hold words from the dictionary

// testing the read function
// this function reads words from a file and returns them as a vector of strings


/*int main(int argc, char* argv[]) {

    // Check if the correct number of arguments is provided
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <dictionary_file>" << endl;
        return 1; // exit if no file is provided
    }
    string filename = argv[1]; // get the filename from command line arguments
    vector<string> words = read(filename); // read words from the file
    cout << "Words read from the file: " << words.size() << endl; // print the number of words read

    return 0;
}
w*/