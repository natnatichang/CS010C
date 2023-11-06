#pragma once

#include <string>
#include <list>
#include <iostream>
#include "WordEntry.h"

using namespace std;

// HashTable class represents a hash table data structure used for storing and managing WordEntry objects
class HashTable {
private:
 	// Private member functions for pointer to array of list and size of hash table
	list<WordEntry>* hashTable;
	int size;

public:
	// Constructor to initialize hash table 
	HashTable(int tableSize);

	// Add Big Three (Destructor, Copy constructor, Copy assignment operator) for hash table
	~HashTable();
	HashTable(const HashTable& sourceObject);
	HashTable& operator=(const HashTable& sourceObject);

	// Public functions to create functionality for the hash table
	int menu() const;
	void put(const string& word, int score);
	bool contains(const string& word) const;
	double getAverage(const string& word) const;
 
private:
	// Private functions to help compute the hash for the public functions
	int computeHash(const string& word) const;
};

