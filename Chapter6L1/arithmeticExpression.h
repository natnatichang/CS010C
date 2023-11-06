#pragma once
#include <iostream>
#include <cstdlib>

using namespace std;

// Define a struct to represent a tree node with character data and keys
struct TreeNode {
   // Member variables of binary tree node
   char data;
   TreeNode* left;
   TreeNode* right;

   // Constructor to create a node
   TreeNode(char data)
      : data(data), left(0), right(0) {}
};

class arithmeticExpression {
private:
   // Private member variable to help create a binary expression tree 
   string infixExpression;
   TreeNode* root;

public:
   // Constructor to create a new object for the arithmeticExpression class
   arithmeticExpression(const string &infixExpression);

   // Add Big Three (Destructor, Copy constructor, Copy assignment operator) for tree
   ~arithmeticExpression();
   arithmeticExpression(const arithmeticExpression& sourceObject);
   arithmeticExpression& operator=(const arithmeticExpression& sourceObject);

   // Functions to build the tree and print the tree
   void buildTree();
   void infix() const;
   void prefix() const;
   void postfix() const;

 private:
   // Private helper functions for Big Three
   void deleteTree(TreeNode* currNode);
   void copyTree(TreeNode* currNode);

   // Private helper functions to get the operator priority
   int priority(char op);

   // Private helper function to convert infix expression to postfix notation
   string infix_to_postfix();

   // Private helper functions to help print out the tree
   void infixHelper(TreeNode* root) const;
   void prefixHelper(TreeNode* root) const;
   void postfixHelper(TreeNode* root) const;

};