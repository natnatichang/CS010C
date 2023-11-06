#pragma once 
#include <string>
#include "Node.h"

using namespace std;

// Tree class that organizes a collection of strings for 2-3 Trees
class Tree {
private:
    // Private member variable to point to the root node of the tree
    Node* root;

public:
    // Default constructor for 2-3 Tree
    Tree();

    // Add Big Three (Destructor, Copy constructor, Copy assignment operator) for 2-3 Tree
    ~Tree();
    Tree(const Tree& sourceObject);
    Tree& operator=(const Tree& sourceObject);

    // Public member functions to create functionality for 2-3 Tree
    void insert(const string& insertString);
    void remove(const string& removeString); 
    bool search(const string& searchString) const;

    // Public member functions for printing the tree
    void preOrder() const;
    void inOrder() const;
    void postOrder() const;

private:
    // Private helper functions for destructor and copying the tree 
    void deleteHelper(Node* currNode);
    Node* copyTree(const Node* currNode) const;

    // Private helper functions for inserting and splitting the node
    void insertHelper(Node* currNode, const string& insertString);
    void splitNode(Node* currNode, const string& insertString);

    // Private helper functions printing
    void preOrderHelper(const Node* currNode) const; 
    void inOrderHelper(const Node* currNode) const;
    void postOrderHelper(const Node* currNode) const; 

};

