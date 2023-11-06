#include <iostream>
#include <string> 
#include "Node.h"

using namespace std;

// Default constructor for node in AVL tree
Node::Node() 
    : height(0), key(""), left(nullptr), right(nullptr), parent(nullptr) {}

// Constructor for a node with the string data
Node::Node(const string& inputString) 
    : height(0), key(inputString), left(nullptr), right(nullptr), parent(nullptr) {}