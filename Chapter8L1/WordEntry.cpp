#include "WordEntry.h"

// WordEntry constructor initializes a new instance of the WordEntry class
WordEntry::WordEntry(const string& text, int score)
    : word(text), numAppearances(1), totalScore(score) {}

// AddNewApperance function increases the total score and number of appearances for a word
void WordEntry::addNewAppearance(int score) {
	totalScore += score;
	++numAppearances;
}

// GetWord function gets the word associated with the WordEntry
const string& WordEntry::getWord() const {
    return word;
}

// GetAverage function calculates and returns the average score of the word
double WordEntry::getAverage() const {
	return static_cast<double> (totalScore) / numAppearances;
}