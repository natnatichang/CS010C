#include "HashTable.h"
#include "WordEntry.h"
#include <iostream>
#include <fstream>

using namespace std;

// Main function reads movie review data, calculates sentiment, and displays the result from hash table
int main() {
	// Declare variables for inputing the data
	string line;    
	int score;
	string message = " ";
	string filename;

    // Try-catch block will catch and handle any exceptions that may occur at runtime
	try {
		// Prompt user to input a file name
		cout << "Please input a file name: " << endl;
		cin >> filename;
		cin.ignore();

		// Open input file
		ifstream myfile(filename);

		// If the file could not be opened, then throw an exception
		if (myfile.fail()) {
			throw runtime_error("Could not open file");
		}

		// Create a hash table
		HashTable table(20071);

		// Read data from the input file and populate the hash table
		while (!myfile.eof()) {
			// Read the score from the input file
			myfile >> score;    

			// Get the blank space after the score
			myfile.get();     

			// Read the remaining line from the input file
			getline(myfile, line);

			// Get the length of the line
			int len = line.size();

			// Extract individual strings from the line
			while (len > 0) {    
				string sub;
				len = line.find(" ");

				// If the size is greater than 0, then there is a space character in the line to extract 
				if (len > 0) {
					// Extract the substring before the space
					sub = line.substr(0, len);

					// Update the line by removing the extracted substring and the space
					line = line.substr(len + 1, line.size());
				} else {
					// If is size is less than 0, then there are no more space characters to extract 
					
					// Extract the last substring before the newline character
					sub = line.substr(0, line.size() - 1);
				}

				// Insert the extracted string with the score into the hash table
				table.put(sub, score);
			}
		}

		// Prompt the user for a new movie review and calculate sentiment
		while (message.length() > 0) {
			cout << "Enter a review -- Press return to exit: " << endl;
			getline(cin, message);

			// Initialize variables for sentiment calculation
			double sum = 0;
			int count = 0;
			double sentiment = 0.0;

			// Obtain the size of the input message
			size_t len = message.size();

			// Extract individual words from the message
			while (len != string::npos) {
				string sub;
				len = message.find(" ");

				// Check if a space character is found in the message
				if (len != string::npos) {
					// Extract the word from the beginning of the message up to the position of the space character
					sub = message.substr(0, len);

					// Update the message by removing the extracted word and the following space character
					message = message.substr(len + 1, message.size());
				} else {
					// If no space character is found, assign the remaining part of the message as the word
					sub = message;
				}

				 // Calculate the average score for each word using the hash table
				sum += table.getAverage(sub);
				++count;
			}

			// If the message is not empty, calculate the sentiment and display the result
			if (message.size() > 0) {
				sentiment = sum / count;
				cout << "The review has an average value of " << sentiment << endl;

				// Determine the sentiment based on the average score
				if (sentiment >= 3.0) {
					cout << "Positive Sentiment" << endl;
				} else if (sentiment >= 2.0) {
					cout << "Somewhat Positive Sentiment" << endl;
				} else if (sentiment >= 1.0) {
					cout << "Somewhat Negative Sentiment" << endl;
				} else {
					cout << "Negative Sentiment" << endl;
				}
				cout << endl;
			}
		}
	} catch (const exception& e) {
		// If any errors occur, then display error message and terminate the program
		cout << e.what() << endl;
		exit(1);
	}
	return 0;
}

// Constructor to initialize hash table with the given size
HashTable::HashTable(int tableSize) {
	size = tableSize;
    hashTable = new list<WordEntry>[size];
}

// Destructor to deallocate the dynamically allocated memory for the hash table array
HashTable::~HashTable() {
	delete[] hashTable; 
}

// Copy constructor for hash table
HashTable::HashTable(const HashTable& sourceObject) {
    // Create a new hash table array with the same size as the source object
	size = sourceObject.size;
    hashTable = new list<WordEntry>[size];

	// Copy each list of WordEntry objects from the source object to the new hash table
    for (int i = 0; i < size; i++) {
        hashTable[i] = sourceObject.hashTable[i];
    }
}

// Copy assignment operator for hash table
HashTable& HashTable::operator=(const HashTable& sourceObject) {
	// Check for self assignment
    if (this == &sourceObject) {
        return *this;
    }
	// Deallocate the memory of the current hash table
    delete[] hashTable;

	// Create a new hash table array with the same size as the source object
    size = sourceObject.size;
    hashTable = new list<WordEntry>[size];

	// Copy each list of WordEntry objects from the source object to the new hash table
    for (int i = 0; i < size; i++) {
        hashTable[i] = sourceObject.hashTable[i];
    }

	// Return a reference to the current object after the copy operation
    return *this;
}

// ComputeHash function calculates the hash value for a given input string, which determinew the index in the hash table where the string will be stored
int HashTable::computeHash(const string& word) const {
	// Initialize an integer variable to accumulate the hash value
    int hash = 0;
	
	// Iterate through each character in the word
    for (char letter : word) {
		// Convert the character to its ASCII value and add it to the hash
        hash += static_cast<int>(letter); 
    }
	
	// Compute the hash value by taking the modulus of the hash with the size of the hash table
    // This ensures that the computed hash value falls within the bounds of the hash table array
    return hash % size;

}

// Put function adds a word and its corresponding score to the hash table, updating the appearance if the word already exists
void HashTable::put(const string& word, int score) {
    // Check if word is present in hash table
    if (contains(word) == true) {
		// Compute the hash value for the given word to determine the index in the hash table
        int index = computeHash(word);

		// Get the reference to the list of WordEntry objects at the computed index
        list<WordEntry>& wordList = hashTable[index];

		// Iterate over the WordEntry objects in the list
        for (auto i = wordList.begin(); i != wordList.end(); ++i) {
			// Check if the current WordEntry object's word matches the given word
            if (i->getWord() == word) {
				// If found, update the appearance with the provided score
                i->addNewAppearance(score);
                return;
            }
        } 

    } else {
		// If word is not present, create a new WordEntry and add it to the hash table

		// Compute the hash value for the given word to determine the index in the hash table
        int index = computeHash(word);

		// Create a new WordEntry object with the given word and score
        WordEntry newWord(word, score);

		// Add the newWord to the list at the computed index in the hash table
        hashTable[index].push_back(newWord);
    }
}   

// Contains function checks if a given word is present in the hash table
bool HashTable::contains(const string& word) const {
	// Compute the hash value for the given word to determine the index in the hash table
    int index = computeHash(word);

	// Get the reference to the list of WordEntry objects at the computed index
    list<WordEntry>& wordList = hashTable[index];

	// Iterate over the list to check if any WordEntry objects word matches the given word
    for (auto iter = wordList.begin(); iter != wordList.end(); ++iter) {
		// If a match is found, return true indicating that the word exists in the hash table
        if (iter->getWord() == word) {
            return true;
        }
    } 

	// If no match is found in the list, return false indicating that the word does not exist in the hash table
    return false;
}

// GetAverage function retrieves the average score of a given word from the hash table, or returns 2.0 if not found
double HashTable::getAverage(const string& word) const {
	// Check if the word is present in the hash table
    if (contains(word) == true) {
		// Compute the hash value for the given word to determine the index in the hash table
        int index = computeHash(word);

		// Get the reference to the list of WordEntry objects at the computed index
        list<WordEntry>& wordList = hashTable[index];

		// Iterate through the list of WordEntry objects to find the matching word
        for (auto iter = wordList.begin(); iter != wordList.end(); ++iter) {
			// If a match is found, return the average
            if (iter->getWord() == word) {
                return iter->getAverage();
            }
        } 
    } 
    
    // If the string is not found, then return 2.0 which represents neutral result
    return 2.0;
}


