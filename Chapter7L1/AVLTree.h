#pragma once
#include "Node.h"

using namespace std;

// AVLTree class that organizes a collection of strings for AVL Trees
class AVLTree {
private: 
    // Private member variable to point to the root node of the tree
    Node* root;

public:
    // Default constructor for AVL Tree
    AVLTree();

    // Add Big Three (Destructor, Copy constructor, Copy assignment operator) for 2-3 Tree
    ~AVLTree();
    AVLTree(const AVLTree& sourceObject);
    AVLTree& operator=(const AVLTree& sourceObject);
    
    // Public functions to helper insert and search the tree
    void insert(const string& key);
    bool search(const string& key) const; 

    // Public function to print the balance factors
    void printBalanceFactors() const;

private:
    // Private helper functions for destructor and copying the tree 
    void destroyTree(Node* currNode);
    Node* copyTree(Node* currNode) const;

    // Private functions to help insert nodes into the AVL tree properly
    void rebalance(Node* currNode);
    void updateHeight(Node* currNode);
    int balanceFactor(Node* currNode) const;
    bool setChild(Node* parent, string specChild, Node* child);
    bool replaceChild(Node* parent, Node* currChild, Node* newChild);  
    void rotateLeft(Node* currNode);
    void rotateRight(Node* currNode);

    // Private function to help print the nodes
    void printBalanceFactors(Node* currNode) const;

};



