#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

// WordEntry class to represent an entry for a word in the hash table
class WordEntry {
private:
	// Private member variables
	string word;
	int numAppearances;
	int totalScore;

public:
	// Constructor to initialize a WordEntry object with the given text and score
	WordEntry(const string& text, int score);

	// Public method to add a new appearance of the word with the given score
	void addNewAppearance(int score);

	// Public accessor methods for word and average
	const string& getWord() const;
	double getAverage() const;
};
