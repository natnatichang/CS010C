#pragma once
#include <string>

using namespace std;

// Node class that represents a node in the 2-3 tree
class Node {
    // Declare Tree class as a friend to allow access to private members
    friend class Tree;

private:
    // Private data members representing the keys in the node
    string small;
    string large;

    // Pointer to child nodes
    Node* left;
    Node* middle;
    Node* right;

    // Pointer to the parent node
    Node* parent;

public: 
    // Default constructor for a node
    Node();
    
    // Constructor with a small key parameter
    Node(const string& small);

};

