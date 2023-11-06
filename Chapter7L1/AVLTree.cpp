#include <iostream>
#include <string> 
#include <fstream>
#include "AVLTree.h"

using namespace std;

// Constructor for the AVLTree class to create the AVL Tree
AVLTree::AVLTree()
    : root(nullptr) {}

// Destructor for the AVL class to destroy the AVL tree
AVLTree::~AVLTree() {
    // Call the destroyTree function to delete all nodes recursively
    destroyTree(root);
}

// DestroyTree function to recursively delete all nodes
void AVLTree::destroyTree(Node* currNode) {
    // If the current node is not null pointer, then recursively call the left and right to delete the current node
    if (currNode != nullptr) {
        // The nodes in tree will be deleted, starting from the leaf nodes to the root
        destroyTree(currNode->left);
        destroyTree(currNode->right);
        delete currNode;
    }
}

// Copy constructor for AVL Tree
AVLTree::AVLTree(const AVLTree& sourceObject) {
    // Call copyTree function to copy all nodes from the other tree
    root = copyTree(sourceObject.root);
}

// Copy assignment operator for AVL Tree
AVLTree& AVLTree::operator=(const AVLTree& sourceObject) {
    // Handle self-assignment
    if (this == &sourceObject) {
        return *this;
    }

    // Call a recursive helper function to copy all nodes from the other tree
    destroyTree(root);
    root = copyTree(sourceObject.root);

    return *this;
}

// CopyTree function to recursively copy nodes from one tree to another
Node* AVLTree::copyTree(Node* currNode) const {
    // If there is no nodes to copy, return nullptr
    if (currNode == nullptr) {
        return nullptr;
    }

    // Create a new node with the same key and height
    Node* newNode = new Node(currNode->key);
    newNode->height = currNode->height;

    // Recursively copy the left subtree
    newNode->left = copyTree(currNode->left);

    // If the left is not nullptr, update its parent pointer
    if (newNode->left != nullptr) {
        newNode->left->parent = newNode;
    }

    // Recursively copy the right subtree
    newNode->right = copyTree(currNode->right);

    // If right is not nullptr, update its parent pointer
    if (newNode->right != nullptr) {
        newNode->right->parent = newNode;
    }

    // Return the root of the copied tree
    return newNode;
}

// Insert function inserts a new node with the given key into the AVL tree
void AVLTree::insert(const string& key) {
    // Create a new node with the given key
    Node* node = new Node(key);
    
    // If the tree is empty, make the new node the root and return
    if (root == nullptr) {
        root = node;
        node->parent = nullptr;
        return;
    }

    // Start the insertion from the root
    Node* currNode = root;

    // Traverse the tree to find the appropriate position for the new node
    while (currNode != nullptr) {

        // If the key is less than the key of the current node, move to the left subtree
        if (key < currNode->key) {
            // If the left child is nullptr, insert the new node as the left child
            if (currNode->left == nullptr) {
                currNode->left = node;
                node->parent = currNode;
                currNode = nullptr;
            } else {
                // Move to the left child
                currNode = currNode->left;
            }

        } else if (key > currNode->key) {
            // If the key is greater than the key of the current node, move to the right subtree
            if (currNode->right == nullptr) {
                // If the right child is nullptr, insert the new node as the right child
                currNode->right = node;
                node->parent = currNode;
                currNode = nullptr;
            } else {
                // Move to the right child
                currNode = currNode->right;
            }
        } else {
            // If the key is equal to the key of the current node, the node already exists in the tree, so return
            return;
        }
    }

    // Rebalance the tree starting from the parent of the newly inserted node
    Node* currentNode = node->parent;
    while (currentNode != nullptr) {
        rebalance(currentNode);
        currentNode = currentNode->parent;
    }
}

// Rebalance function rebalances the AVL tree starting from the specified node
void AVLTree::rebalance(Node *currNode) {
    // Update the height of the current node
    updateHeight(currNode);       

     // Check if the current node is imbalanced
    if (balanceFactor(currNode) == -2) {

        // Check if the right child of the current node is imbalanced
        if (balanceFactor(currNode->right) == 1) {
             // Perform a double rotation by first rotating the right child to the right
            rotateRight(currNode->right);

        }
        // Rotate the current node to the left to rebalance the tree
        rotateLeft(currNode);

    } else if (balanceFactor(currNode) == 2) {
        // Check if the current node is imbalanced
        // Then check if the left child of the current node is imbalanced
        if (balanceFactor(currNode->left) == -1) {
            // Perform a double rotation by first rotating the left child to the left
            rotateLeft(currNode->left);
        }
            // Rotate the current node to the right to rebalance the tree
            rotateRight(currNode);
    }        
}

// UpdateHeightfunction updates the height of a given node based on the heights of its left and right children
void AVLTree::updateHeight(Node* currNode) {
    // Initialize the heights of the left children to -1 (if they exist)
    int leftHeight = -1;
    if (currNode->left){
        leftHeight = currNode->left->height;
    }

    // Initialize the heights of the right children to -1 (if they exist)
    int rightHeight = -1;
    if (currNode->right) {
        rightHeight = currNode->right->height;
    }

    // Calculate the height of the current node as itself plus the maximum height of its children
    currNode->height = 1 + max(leftHeight, rightHeight);

}

// BalanceFactor function calculates the balance factor of a given node
int AVLTree::balanceFactor(Node* currNode) const {
    // Initialize the heights of the left children to -1 (if they exist)
    int leftHeight = -1;
    if (currNode->left) {
        leftHeight = currNode->left->height;
    }

    // Initialize the heights of the right children to -1 (if they exist)
    int rightHeight = -1;
    if (currNode->right) {
        rightHeight = currNode->right->height;
    }
    
    // The balance factor is calculated as the difference between the left height and right height
    return leftHeight - rightHeight;
}

// SetChild function sets a specific child node of a given parent node in the AVL tree
bool AVLTree::setChild(Node* parent, string specChild, Node* child) {
    // Check if the specified child is valid
    if (specChild != "left" && specChild != "right") {
        // If the specified child is not valid, return false to indicate failure
        return false;
    }

    // Set the child node as the specified child of the parent.
    if (specChild == "left") {
        parent->left = child;
    } else {
        parent->right = child;
    }

    // If the child is not nullptr, update its parent pointer to the parent node
    if (child != nullptr) {
        child->parent = parent;

    }

    // Update the height of the parent node after modifying its child
    updateHeight(parent);

    // Return true to show that setting of the child node was successful
    return true;
}

// ReplaceChild function replaces a child node of a given parent node with a new child node in the AVL tree
bool AVLTree::replaceChild(Node* parent, Node* currChild, Node* newChild) {
    // If the current child is the left child of the parent, replace it with the new child
    if (parent->left == currChild) {
        return setChild(parent, "left", newChild);

    } else if (parent->right == currChild) { 
        // If the current child is the right child of the parent, replace it with the new child
        return setChild(parent, "right", newChild);
    }

    // If the current child is not found as either the left or right child of the parent, return false
    return false;
}

// RotateLeft function performs a left rotation on the specified node in the AVL tree
void AVLTree::rotateLeft(Node* currNode) {
    // Store the left child of the right child of the current node
    Node* rightLeftChild = currNode->right->left;

    // If the current node has a parent, replace the current node with its right child
    if (currNode->parent != nullptr) {
        replaceChild(currNode->parent, currNode, currNode->right);

    } else {
        // If the current node is root, update the root to be the right child
        root = currNode->right;
        root->parent = nullptr;

    }

    // Set the left child of the right child of the current node as the new right child of the current node
    setChild(currNode->right, "left", currNode);
    // Set the current node as the new right child of the previously left child of the right child of the current node
    setChild(currNode, "right", rightLeftChild);

    // Update the heights of the current node and its parent after the rotation
    updateHeight(currNode);
    updateHeight(currNode->parent);
}

// RotateRight function performs a right rotation on the specified node in the AVL tree
void AVLTree::rotateRight(Node* currNode) {
    // Store the right child of the left child of the current node
    Node* leftRightChild = currNode->left->right;

    // If the current node has a parent, replace the current node with its left child
    if (currNode->parent != nullptr) {    
        replaceChild(currNode->parent, currNode, currNode->left);

    } else {
        // If the current node is root, update the root to be the left child
        root = currNode->left;
        root->parent = nullptr;

    }

    // Set the right child of the left child of the current node as the new left child of the current node
    setChild(currNode->left, "right", currNode);
    // Set the current node as the new left child of the previously right child of the left child of the current node
    setChild(currNode, "left", leftRightChild);

    // Update the heights of the current node and its parent after the rotation
    updateHeight(currNode);
    updateHeight(currNode->parent);
}

// Search function helps to check so that a duplicate node isn't inserted
bool AVLTree::search(const string& key) const {
    Node* currNode = root;

    // Traverse the tree
    while (currNode != nullptr) {
        // If the key is less than the key of the current node, move to the left subtree
        if (key < currNode->key) {
            currNode = currNode->left;

        } else if (key > currNode->key) {
            // If the key is greater than the key of the current node, move to the right subtree
            currNode = currNode->right;

        } else {
            // If the key is equal to the key of the current node, the key is found in the tree
            return true;

        }
    }

    // If false, then key not found
    return false;
}

// PrintBalanceFactors helps to print the balance factor of all nodes 
void AVLTree::printBalanceFactors() const {
    // Call the helper function
    printBalanceFactors(root);
    cout << endl;
}

// PrintBalanceFactors function recursively prints the balance factors of nodes 
void AVLTree::printBalanceFactors(Node* currNode) const {
    // Base case to exit recursion
    if (currNode != nullptr) {
        // Print the balance factors after looking at the left subtree and right subtree
        printBalanceFactors(currNode->left);
        int balance = balanceFactor(currNode);
        cout << currNode->key << "(" << balance << "), ";
        printBalanceFactors(currNode->right);
    }
}


