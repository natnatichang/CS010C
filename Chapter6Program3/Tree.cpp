#include <iostream>
#include <string> 
#include "Tree.h"

using namespace std;

// Constructor for the Tree class to create the 2-3 Tree
Tree::Tree() 
    : root(nullptr) {}

// Destructor for the Tree class to destroy the 2-3 tree
Tree::~Tree() {
    // Call the deleteHelper function to delete all nodes recursively
    deleteHelper(root);
}

// DeleteHelper function to recursively delete all nodes
void Tree::deleteHelper(Node* currNode) {
    // If the current node is not null pointer, then recursively call the left, middle, right to delete the current node
    if (currNode != nullptr) {
        // The nodes in tree will be deleted, starting from the leaf nodes to the root
        deleteHelper(currNode->left);
        deleteHelper(currNode->middle);
        deleteHelper(currNode->right);
        delete currNode;

    }
}

// Copy constructor for 2-3 Tree
Tree::Tree(const Tree& sourceObject) {
    // Initailize the root of the new tree to nullptr to prevent undefined behavior
    root = nullptr;

    // Call the copyTree function to deep copy the nodes
    root = copyTree(sourceObject.root);
}

// Copy assignment operator for BSTree
Tree& Tree::operator=(const Tree& sourceObject) {
    // Handle self-assignment
    if (this != &sourceObject) {
        // Delete existing nodes of the tree by calling destructor
        deleteHelper(root);
        root = nullptr;

        // Deep copy all nodes from the original tree to the new tree
        root = copyTree(sourceObject.root);

    }
    return *this;
}

// CopyTree function to recursively copy nodes from one tree to another
Node* Tree::copyTree(const Node* currNode) const {
    // Base case so if the current node is null, then there is nothing else to copy
    if (currNode == nullptr) {
        return nullptr;
    } 

    // Create a new node and copy the data from the current node.
    Node* newNode = new Node();
    newNode->small = currNode->small; 
    newNode->large = currNode->large; 

    // Recursively copy the left, middle, and right subtrees.
    newNode->left = copyTree(currNode->left); 
    newNode->middle = copyTree(currNode->middle); 
    newNode->right = copyTree(currNode->right); 
    
    // Set the parent pointer of the child nodes to the new node based on whether they have left, middle, or right child
    if (newNode->left != nullptr) { 
        // If there is no left child, set the parent pointer of the left child to newNode
        newNode->left->parent = newNode; 

    } else if (newNode->middle != nullptr) { 
        // No left node child means to set the parent pointer of the middle child to newNode
        newNode->middle->parent = newNode; 

    } else if (newNode->right != nullptr) {
        // No left child or middle child means to set the parent pointer of the right child to newNode 
        newNode->right->parent = newNode;

    } 
 
    // Return the new node 
    return newNode;
}

// Insert a string into the 2-3 tree based on user input 
void Tree::insert(const string& insertString) {
    // If the tree is empty, create a new root node and assign the string to its small data
    if (root == nullptr) {
        root = new Node();
        root->small = insertString;

    } else {
        // If there is a root, then traverse the tree to find the appropriate for the string
        Node* targetNode = root;
        while (targetNode->left != nullptr) {

            // Check if targetNode has a large data, indicating whether it is a 2-node or a 3-node
            if (!targetNode->large.empty()) {

                // If it has a large data, determine the next child to traverse based on the comparison with insertString
                if (targetNode->small > insertString) {
                    // If the node being inserted is less than the small data, traverse left
                    targetNode = targetNode->left;

                } else if (targetNode->large < insertString) {
                    // If the node being inserted is greater than the large data, traverse right
                    targetNode = targetNode->right;

                } else {
                    // If the node being inserted is greater than small data, less than large data, traverse middle
                    targetNode = targetNode->middle;

                }

            } else {
                // If it's a 2-node, there is no large so determine the next child to traverse based on the comparison with insertString
                if (targetNode->small > insertString) {
                    // If the node being inserted is less than the small data, traverse left
                    targetNode = targetNode->left;

                } else {
                    // If the node being inserted is greater than the large data, traverse right
                    targetNode = targetNode->middle;

                }
            }
        }

        // Split the node if it is full, indicating it is a 3-node
        if (!targetNode->large.empty()) {
            splitNode(targetNode, insertString);

        } else {
            // If the node is a 2-node, assign the insertString to the appropriate position (small or large)
            if (targetNode->small > insertString) {
                // If the string is smaller than current small data, shift the current small to the large to insert
                targetNode->large = targetNode->small;
                targetNode->small = insertString;

            } else {
                // If the string is larger than current small data, just insert it to the new large
                targetNode->large = insertString;

            }
        }
    }
}

// Split a full 3-node into two 2-nodes and perform necessary updates
void Tree::splitNode(Node* node, const string& insertString) {
    string small;
    string middle;
    string large;

    //  Checks if inserted string being inserted is smaller than the current small value
    if (node->small > insertString) {
        // If smaller, shift the current small and large values to create space for the new insertion
        small = insertString;
        middle = node->small;
        large = node->large;

    } else {
        // Checks if string is either equal to or greater than the current small value
        small = node->small;

        // Check if string is greater than the current large value
        if (node->large < insertString) {
            // If greater, shift the current large value to create space for the new insertion
            middle = node->large;
            large = insertString;

        } else {
            // Check if string is between the small and large values
            // Then shift the current large value to create space for the new insertion
            middle = insertString;
            large = node->large;
        }
    }

    // Create new nodes to hold the split data
    Node* smallNode = new Node();
    smallNode->small = small;
    Node* largeNode = new Node();
    largeNode->small = large;

    // Reassign the data and child pointers of the target node
    node->small = middle;
    node->large = "";
    node->left = smallNode;
    node->middle = largeNode;
    node->right = nullptr;

    // Set the parent pointers for the newly created nodes
    smallNode->parent = node;
    largeNode->parent = node;

    // Recursively insert the insertString into the tree starting from the target node
    insertHelper(node, insertString);
}

// InsertHelper function to find where the new string needs to be inserted, perform splits if necessary
void Tree::insertHelper(Node* currNode, const string& insertString) {
    // Check if the current node has a parent node before traversing
    if (currNode->parent != nullptr) {
        Node* parent = currNode->parent;

        // Split the node if it is full, indicating it is a 3-node
        if (!parent->large.empty()) {

            // Split the node to accommodate the new string
            if (parent->small > currNode->small) {
                // Create a new large node to hold the links
                Node* newLarge = new Node();
                newLarge->left = parent->middle;
                newLarge->left->parent = newLarge;
                newLarge->middle = parent->right;
                newLarge->middle->parent = newLarge;
                newLarge->small = parent->large;

                // Update the old parent nodes
                parent->left = currNode;
                parent->middle = newLarge;
                parent->right = nullptr;
                parent->large = "";

                // Update the parent pointer of the new node
                newLarge->parent = parent;

            } else if (parent->large < currNode->small) {
                // Create a new small node to hold the links
                Node* newSmall = new Node();
                newSmall->left = parent->left;
                newSmall->left->parent = newSmall;
                newSmall->middle = parent->middle;
                newSmall->middle->parent = newSmall;
                newSmall->small = parent->small;

                // Update the old parent nodes
                parent->left = newSmall;
                parent->middle = currNode;
                parent->right = nullptr;
                parent->small = parent->large;
                parent->large = "";

                // Update the parent pointer of the new node
                newSmall->parent = parent;

            } else {
                // Create a new small node to hold the links
                Node* newSmall = new Node();
                newSmall->small = parent->small;
                newSmall->left = parent->left;
                newSmall->left->parent = newSmall;
                newSmall->middle = currNode->left;
                newSmall->middle->parent = newSmall;

                // Create a new large node to hold the links
                Node* newLarge = new Node();
                newLarge->small = parent->large;
                newLarge->left = currNode->middle;
                newLarge->left->parent = newLarge;
                newLarge->middle = parent->middle;
                newLarge->middle->parent = newLarge;

                // Update the old parent nodes for small and large
                parent->left = newSmall;
                parent->middle = newLarge;
                parent->right = nullptr;
                parent->small = currNode->small;
                parent->large = "";

                // Update the parent pointer for both new nodes
                newSmall->parent = parent;
                newLarge->parent = parent;

                // Free the memory that was merged into the parent node
                delete currNode;
            }
            // InsertHelper is called recursively so the insertion is applied to the parent nodes
            insertHelper(parent, insertString);

        } else {
            // Parent node has no large value, then check if insert string is smaller than parent's small value
            if (parent->small > currNode->small) {
                // Swap the small value of the parent with the insert string
                parent->large = parent->small;
                parent->small = currNode->small;

                // Rearrange the child nodes to maintain the links
                parent->left = currNode->left;
                parent->right = parent->middle;
                parent->middle = currNode->middle;
            } else {
                // Assign the insert string as the large value of the parent
                parent->large = currNode->small;

                // Rearrange the child nodes to maintain the links
                parent->middle = currNode->left;
                currNode->left->parent = parent;
                parent->right = currNode->middle;
                currNode->middle->parent = parent;
            }

            // Update parent pointers and delete the current node
            currNode->left->parent = parent;
            currNode->middle->parent = parent;
            delete currNode;
        }
    }
}

// Remove function to remove a specified string in the tree
void Tree::remove(const string& removeString) {
    Node* targetNode = root;

    // Traverse the tree to find the node containing the removeString
    while (targetNode != nullptr) {
        // Check if the removeString matches the small value of the current node
        // or if the node is a 2-3 node and the removeString matches the large value
        if (targetNode->small == removeString || ( (!targetNode->large.empty()) && targetNode->large == removeString)) {
            // If node containing the removeString was found, stop looping
            break;

        } else {
            // Determine the next node to traverse based on the removeString
            if (targetNode->small > removeString) {
                // If the node being looked for is less than small, go left
                targetNode = targetNode->left;

            } else {
                // Check if the node is a 2-3 node and the removeString is greater than the large value
                if ((!targetNode->large.empty()) && targetNode->large < removeString) {
                    // If it has a large, is full, and is greater than the current large, then go right
                    targetNode = targetNode->right;

                } else {
                    // Otherwise, there is only small and middle, so go middle
                    targetNode = targetNode->middle;
        
                }
            }
        }
    }
    
    // If the targetNode is not nullptr, means that the string was in the tree
    if (targetNode != nullptr) {

        // Checks if the node is already full or not
        if (!targetNode->large.empty()) {

            // Check if the removeString matches the small value of targetNode
            if (removeString == targetNode->small) {
                // Move the large value to the small value and reset the large value
                targetNode->small = targetNode->large;
                targetNode->large = "";
            } else {
                // If the string being removed is just the large, just clear the large value
                targetNode->large = "";
            }
        } else {
            Node* parent = targetNode->parent;
            
            // Check if node to be removed has a parent
            if (parent != nullptr) {

                // Check if string is less than parent's small value
                if (removeString < parent->small) {
                    // Update the parent nodes by removing the left child
                    parent->left = nullptr;

                    // Set the large value to small value of middle child
                    parent->large = parent->middle->small;

                    // Clear the middle child
                    parent->middle = nullptr;

                } else {
                    // Check if string is greater than or equal to the parent's small value, then remove middle child
                    parent->middle = nullptr;
                    
                    // Update parents large and small value with the small value of the left child so the links don't break
                    parent->large = parent->small;
                    parent->small = parent->left->small;

                    // Clear the left child 
                    parent->left = nullptr;

                }
            } else {
                // If the node to be removed is the root node
                Node* tempNode = new Node();

                // Check there are left and middle children for the root
                if (root->left != nullptr && root->middle != nullptr) {
                    // Create a temp node to take the small values of the left and middle children so the links don't break
                    tempNode->small = root->left->small;
                    tempNode->large = root->middle->small;

                    // The temp node will be the new root
                    root = tempNode;

                } else {
                    // If it is only the root, then just remove the node
                    root = nullptr;

                }
            }
        }
    }
}

// Search function to find given string in the tree
bool Tree::search(const string& searchString) const {
    Node* searchNode = root;

    // Traverse the tree until there is no more to search for
    while (searchNode != nullptr) {
        // Check if the search string matches the small value of the current node 
        // or if the node is a 2-3 node and the search string matches the large value
        if (searchNode->small == searchString || ((!searchNode->large.empty()) && searchNode->large == searchString)) {
            // If so, then string is found
            return true;

        } else {
            // Based on the value for the string being searched, determine the next node to traverse
            if (searchNode->small > searchString) {
                // If it the smaller than the current value, go left
                searchNode = searchNode->left;

            } else { 
                // Check if the node is a 2-3 node and if search string is greater than the large value 
                if ((!searchNode->large.empty()) && searchNode->large < searchString) {
                    // If it does have a large and it is full, then go right
                    searchNode = searchNode->right;

                } else {
                    // If there is no large, then traverse the middle
                    searchNode = searchNode->middle;

                }
            }
        }
    }
    // If string not found, return false
    return false;
}

// Calls helper to print preOrder
void Tree::preOrder() const {
    preOrderHelper(root);
}

// Helper function to print the tree in preOrder traversal
void Tree::preOrderHelper(const Node* currNode) const {
    if (currNode != nullptr) {
        // Current node is a 3-node 
        if (!currNode->large.empty()) {
            // Print the current small value, then traverse left subtree
            cout << currNode->small << ", ";
            preOrderHelper(currNode->left);

            // Print the large value, and traverse the middle and right subtrees.
            cout << currNode->large << ", ";
            preOrderHelper(currNode->middle);
            preOrderHelper(currNode->right);

        } else {
            // Current node is a 2 node, then print the current small value
            cout << currNode->small << ", ";

            // Traverse left and middle subtrees only to print
            preOrderHelper(currNode->left);
            preOrderHelper(currNode->middle);

        }
    }
}

// Calls helper to print inOrder
void Tree::inOrder() const {
    inOrderHelper(root);
}

// Helper function to print the tree in inOrder traversal
void Tree::inOrderHelper(const Node* currNode) const {
    if (currNode != nullptr) {
        // Traverse the left subtree, print the small value, then traverse middle
        inOrderHelper(currNode->left);
        cout << currNode->small << ", ";
        inOrderHelper(currNode->middle);

        // Current node is a 3-node, then print large and traverse right
        if (!currNode->large.empty()) {
            cout << currNode->large << ", ";
            inOrderHelper(currNode->right);

        }
    }
}

// Calls helper to print postOrder
void Tree::postOrder() const {
    postOrderHelper(root);
}

// Helper function to print the tree in postOrder traversal
void Tree::postOrderHelper(const Node* currNode) const {
    if (currNode != nullptr) {
        // Current node is a 3-node 
        if (!currNode->large.empty()) {
            // Traverse the left and middle subtrees, print the small value
            postOrderHelper(currNode->left);
            postOrderHelper(currNode->middle);
            cout << currNode->small << ", ";
            
            // Traverse the right subtree, and finally print the large value
            postOrderHelper(currNode->right);
            cout << currNode->large << ", ";

        } else {
            // Current node is a 2 node, traverse left and middle only, then print small value
            postOrderHelper(currNode->left);
            postOrderHelper(currNode->middle);
            cout << currNode->small << ", ";

        }
    }
}
