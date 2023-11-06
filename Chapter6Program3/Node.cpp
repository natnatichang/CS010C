#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

// Default constructor for node in 2-3 tree
Node::Node() 
    : small(""), large(""), left(nullptr), middle(nullptr), right(nullptr), parent(nullptr) {}

// Constructor for a node with string data only
Node::Node(const string &small)
    :  small(small), large(""), left(nullptr), middle(nullptr), right(nullptr), parent(nullptr) {}
