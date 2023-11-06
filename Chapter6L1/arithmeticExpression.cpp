#include <iostream>
#include <sstream>
#include <fstream>
#include <stack>
using namespace std;

#include "arithmeticExpression.h"

// Constructor that takes an infix expression and initializes the root to null
arithmeticExpression::arithmeticExpression(const string& infixExpression)
  : infixExpression(infixExpression), root(nullptr) {}

// Destructor to delete the arithmetic expression by calling the deleteTree function
arithmeticExpression::~arithmeticExpression() {
    deleteTree(root);
}

// Helper function to delete the tree by using recursion to traverse the tree
void arithmeticExpression::deleteTree(TreeNode* currNode) {
    // If there are no more nodes, then return
    if (currNode == nullptr) {
        return;
    }

    // Go left and right in the tree to recursively delete the tree
    deleteTree(currNode->left);
    deleteTree(currNode->right);
    delete currNode;
}

// Copy constructor that creates a new arithmetic expression with the same infix as the original
arithmeticExpression::arithmeticExpression(const arithmeticExpression& sourceObject)
    : infixExpression(sourceObject.infixExpression), root(nullptr) {
    // Call the copyTree function to copy the tree structure
    copyTree(sourceObject.root);
}

// Helper function to copy the tree by traversing through the tree recursively
void arithmeticExpression::copyTree(TreeNode* currNode) {
    // If there are no more nodes, then return
    if (currNode == nullptr) {
        return;
    }

    // Create a new root to copy the tree
    root = new TreeNode(currNode->data);
    copyTree(currNode->left);
    copyTree(currNode->right);
}

// Copy assignment operator to copy the infix expression from the original object
arithmeticExpression& arithmeticExpression::operator=(const arithmeticExpression &sourceObject) {
    // Check for self assignemnt
    if (this != &sourceObject) {
        infixExpression = sourceObject.infixExpression;

        // Delete the current tree to create a new one with the same structure as the original
        deleteTree(root);
        root = nullptr;
        buildTree();
    }
    // Return a reference to the object
    return *this;
}

void arithmeticExpression::buildTree() {
    // Convert infix to postfix
    string postFixString = infix_to_postfix();

    // Create a stack to hold nodes
    stack <TreeNode*> stackers; 
    char newChar;

    // Iterate through the postfix string
    for (unsigned i = 0; i < postFixString.size();++i){

        newChar = postFixString.at(i);

        // Checks if the character is an operator
        if (newChar =='+' || newChar == '-' || newChar == '*' || newChar == '/') { 

        // If the character is an operator, create a new node
        TreeNode* newNode = new TreeNode(newChar);

        // Check to make sure that the stack isn't empty before continuing 
        if (stackers.empty()) {
            throw runtime_error("Expected an operand to pop off, but stack is empty.");
        }

        // If the character is an operator, pop two elements off the stack so it can be children for new node
        TreeNode* node1 = stackers.top();
        stackers.pop();

        TreeNode* node2 = nullptr;

        // Before popping off the second element, check that there is at least one operand in the stack to pop off
        if (!stackers.empty()) {
            node2 = stackers.top();
            stackers.pop();
        } else {
            // If there is not, throw an error
            throw runtime_error("Expected one final operand but stack contains a different number of elements.");
        }

        // Connect the two operands popped off the stack as left and right child of new node
        newNode->left = node2;
        newNode->right = node1;

        // Push the new node onto the stack
        stackers.push(newNode);

        } else if (isalpha(newChar)) {
            // If the character is an operand, create a new node to push onto the stack
            TreeNode* node3 = new TreeNode(newChar);
            stackers.push(node3);
        } else {
            // If the character is invalid, then throw an error
            throw runtime_error("Invalid character in expression");
        }

    }

    // After the nodes are pushed onto the stack, there should only be one node left, else throw an error
    if (stackers.size() != 1) {
        throw runtime_error("Expected one final operand but stack contains a different number of elements.");
    }

    // Set the root node as the last node on the stack, then remove it from the stack
    root = stackers.top();
    stackers.pop();
}

// Function to print the tree in infix
void arithmeticExpression::infix() const {
    infixHelper(root);
}

// Helper function to print infix
void arithmeticExpression::infixHelper(TreeNode* root) const {
    // Print out the tree from left subtree, root, right subtree
    if (root != nullptr) {

        // If there is a left node from the root, print opening parenthesis
        if (root->left != nullptr) {
            cout  << "(";
        }

        // Recursively print the left and right subtree
        infixHelper(root->left);
        cout << root->data;
        infixHelper(root->right);

        // If there a right node from the root, print closing parenthesis 
        if (root->right != nullptr) {
            cout << ")";
        }
    }
}

// Function to print the tree in prefix
void arithmeticExpression::prefix() const {
    prefixHelper(root);
}

// Helper function to print prefix
void arithmeticExpression::prefixHelper(TreeNode* root) const {
    // Print out the tree from root, left subtree, right subtree
    if (root != nullptr) {
        cout << root->data;
        prefixHelper(root->left);
        prefixHelper(root->right);
    }
}

// Function to print the tree in postfix
void arithmeticExpression::postfix() const {
    postfixHelper(root);
}

// Helper function to print postfix
void arithmeticExpression::postfixHelper(TreeNode* root) const {
    // Print out the tree from left subtree, right subtree, root
    if (root != nullptr) {
        postfixHelper(root->left);
        postfixHelper(root->right);
        cout << root->data;
    }
}

// Function takes a character operand and returns its priority value
int arithmeticExpression::priority(char op) {
    // Create a variable to determine the order of operations
    int priority = 0;
    
    // Depending on which operator it is, it will assign that specific value for it
    if (op == '(') {
        priority =  3;
    } else if (op == '*' || op == '/') {
        priority = 2;
    } else if (op == '+' || op == '-') {
        priority = 1;
    }

    // Return the priority value after evaluating 
    return priority;
}

// Function converts an infix expression to postfix notation using a stack
string arithmeticExpression::infix_to_postfix() {
    // Create an empty stack of characters to store opeartors 
    stack<char> operatorStack;

    // Created empty output string stream to construct postfix
    ostringstream oss;

    // New char variable to hold the current char being processed
    char newChar;

    // Start a loop over each character in infix expression 
    for (unsigned i = 0; i < infixExpression.size(); ++i) { 
        newChar = infixExpression.at(i);

        // If the character is a whitespace, skip it
        if (newChar == ' '){
            continue;
        }

        // Checks if the character is a certain operand before proceeding  
        if (newChar == '+' || newChar == '-' || newChar == '*' || newChar == '/' || newChar == '(' || newChar == ')') {
            // Push left parenthesis on operator stack 
            if (newChar == '(') {
                operatorStack.push(newChar);
            } else if (newChar == ')') {
                // Otherwise, handle the right parentheses by popping operators off and appending to output string stream
                while (operatorStack.top() != '(') {
                    oss << operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.pop();
            }
            else {
                // Otherwise hand all other operators by popping off operators with higher or equal precendence 
                while (!operatorStack.empty() && priority(newChar) <= priority(operatorStack.top())) {
                    if (operatorStack.top() == '('){
                        break;
                    }
                    // Append to the output string stream
                    oss << operatorStack.top();
                    operatorStack.pop();
                }
                // Push the new operator onto the stack
                operatorStack.push(newChar);
            }
        } else { 
            // Handles operands by appending them to output string stream
            oss << newChar;
        }
    }

    // Empty the operator stack and append any remaining operator to output string stream
    while (!operatorStack.empty()) {
        oss << operatorStack.top();
        operatorStack.pop();
    }

    // Return the constructed postfix expression as a string
    return oss.str();
}

