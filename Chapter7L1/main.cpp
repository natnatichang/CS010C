#include <iostream>
#include <limits>

#include "AVLTree.h"

using namespace std;

// Declare functions to be used for menu
const int menu();

// Main function provides functionality for AVL Tree
int main() {
    // Declare an AVLTree object, choice, and string to create menu functionality
    AVLTree tree;
    int choice = menu();
    string entry;

    while (choice != 3) {

        // Try-catch block will catch and handle any exceptions that may occur at runtime
        try {

            if (choice == 1) {
                // Take in user input for a node to be inserted to tree
                cout << "Enter string to insert: ";
                getline(cin, entry);
                cout << endl;
                
                // The following test case may fail zyBooks code but is included to indicate to the user
                
                // If the string is found, then can not insert the node since it is a duplicate
                if (tree.search(entry)) {
                    cout << "'" << entry << "' was found in tree. Duplicates can not be inserted." << endl;
                } else {
                    // If the string is not found, then there is no duplicates and can be inserted
                    tree.insert(entry);
                    cout << entry << " has been inserted into the tree." << endl;
                }
            
            } else if (choice == 2) {
                // Print the balance factor for each node
                tree.printBalanceFactors();
            } 
        } catch (const exception& e) {
            // If any errors occur, then print out statement 
            cout << "An exception occurred: " << e.what() << endl;
        }
        // If there are no errors and input isn't 3, then continue to prompt user 
        choice = menu();
    }
    return 0;
}

// Menu function prints out the menu for the user to make a choice
const int menu() {
    // Print out the menu options
    int choice = 0;
    cout << endl << "Enter menu choice: ";
    cout << endl;
    cout << "1. Insert" << endl;
    cout << "2. Print" << endl;
    cout << "3. Quit" << endl;
    
    // If the user input is not a choice between 1-3, then throw an error so it doesn't fail silently
    if (!(cin >> choice) || choice < 1 || choice > 3) {
        cin.clear();
        cin.ignore();
        throw runtime_error("Invalid input. Please enter a number between 1 and 3.");
    }

    // If the user input is valid, clear the error flags and buffer to return the user choice
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}
