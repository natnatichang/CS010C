#pragma once
#include <string>

using namespace std;

// Node class that represents a node in the 2-3 tree
class Node {
    // Declare AVLTree class as a friend to allow access to private members
    friend class AVLTree;
    
private: 
    // Private data members representing the height and key of the node
    int height;
    string key;

    // Pointer to child and parent nodes
    Node* left;
    Node* right;
    Node* parent;

public: 
    // Default constructor for a node
    Node();
    
    // Constructor with a string parameter
    Node(const string& inputString);
};