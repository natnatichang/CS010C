#include <iostream>
#include <limits>

#include "Tree.h"

using namespace std;

// Declare functions to be used for printing and menu
void printOrders(const Tree *tree);
const int menu();

// Main function provides functionality for 2-3 Tree
int main() {
    // Declare a Tree object, choice, and string to create menu functionality 
    Tree tree;
    int choice = menu();
    string entry;

    // If the user inputs 5, then the program ends
    while (choice != 5) {

        // Try-catch block will catch and handle any exceptions that may occur at runtime
        try {

            if (choice == 1) {
                // Take in user input for a node to be inserted to tree
                cout << "Enter movie title to insert: ";
                getline(cin, entry);
                cout << endl;

                // The following test case may fail zyBooks code but is included to demonstrate the insert edge case

                // If the string is found, then can not insert the node since it is a duplicate
                if (tree.search(entry)) {
                    cout << "'" << entry << "' was found in tree. Duplicates can not be inserted." << endl;
                } else {
                    // If the string is not found, then there is no duplicates and can be inserted
                    tree.insert(entry);
                    cout << entry << " has been inserted into the tree." << endl;
                }

            } else if (choice == 2) {
                // Take in user input for a node to be removed from tree
                cout << "Enter movie title to remove: ";
                getline(cin, entry);
                cout << endl;

                // The following test case may fail zyBooks code but is included to demonstrate the remove edge case

                // If the string is found, then remove the node
                if (tree.search(entry)) {
                    tree.remove(entry);
                    cout << entry << " has been removed from the tree." << endl;
                } else {
                    // If the string is not found, no node to remove
                    cout << "'" << entry << "' was not found in tree to be removed." << endl;
                }

            } else if (choice == 3) {
                // Prints out the tree in preorder, inorder, postorder
                printOrders(&tree);

            } else if (choice == 4) {
                // Take in user input for a string to be searched for
                cout << "Enter movie title to search for: ";
                getline(cin, entry);
                cout << endl;

                // Returns 'Found' if the string is there
                if (tree.search(entry)) {
                    cout << "Found" << endl;
                } else {
                    // If the string is not found, return 'Not Found'
                    cout << "Not Found" << endl;
                }
            }
        } catch (const exception& e) {
            // If any errors occur, then print out statement 
            cout << "An exception occurred: " << e.what() << endl;
        }
        // If there are no errors and input isn't 5, then continue to prompt user 
        choice = menu();
    }
    return 0;
}

// PrintOrders function passes in the tree to print out preorder, inorder, postorder
void printOrders(const Tree *tree) {
    // Print out the tree from root, left subtree, right subtree
    cout << "Preorder = ";
    tree->preOrder();
    cout << endl;

    // Print out the tree from left subtree, root, right subtree
    cout << "Inorder = ";
    tree->inOrder();
    cout << endl;

    // Print out the tree from left subtree, right subtree, root
    cout << "Postorder = ";
    tree->postOrder();
    cout << endl;
}

// Menu function prints out the menu for the user to make a choice
const int menu() {
    // Print out the menu options
    int choice = 0;
    cout << endl << "Enter menu choice: ";
    cout << endl;
    cout << "1. Insert" << endl;
    cout << "2. Remove" << endl;
    cout << "3. Print" << endl;
    cout << "4. Search" << endl;
    cout << "5. Quit" << endl;


    // If the user input is not a choice between 1-5, then throw an error so it doesn't fail silently
    if (!(cin >> choice) || choice < 1 || choice > 5) {
        cin.clear();
        cin.ignore();
        throw runtime_error("Invalid input. Please enter a number between 1 and 5.");
    }

    // If the user input is valid, clear the error flags and buffer to return the user choice
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}
