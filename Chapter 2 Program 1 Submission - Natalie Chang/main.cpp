#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

// Define a struct for node that contains the payload and pointer to next node
struct Node {
    string payload;
    Node* next;
};

// Function to help create a new node using the given payload
Node* newNode(const string& payload) {
    // Dynamically allocate memory for a new node
    Node* newNode = new Node;

    // Set the payload and the next pointer for the new node
    newNode->next = newNode;
    newNode->payload = payload;

    return newNode;
}

// Function to load a circular linked list with nodes containing the names for the game
Node* loadGame(int numNames, vector<string>& storeNames) {
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;

    // Loop through each name in the input vector
    for (int i = 0; i < numNames; ++i) {
        // Get the name at the current index for the new node
        name = storeNames.at(i);
        
        // If the head pointer is null, create a new Node for it to insert after head
        if (head == nullptr) {
            head = newNode(name); 
            prev = head;
        } else {
            // Otherwise, create a new node with the current name, set prev next pointer to it, and set prev to it
            Node* newNodePtr = newNode(name);
            prev->next = newNodePtr;
            prev = newNodePtr;
        }
    }

    // If prev is not null, set its next pointer to head to make the list circular  
    if (prev != nullptr) {
        prev->next = head;
    }

    // Return a pointer to the head node of the list
    return head;
}

// Function to print the names in the circular linked list 
void print(Node* start) { 
    // Start at the given node
    Node* curr = start;
    
    // Traverse through the list until the end is reached
    while (curr != nullptr) {
        // Print the name at the current node
        cout << curr->payload << endl;

        // Move to the next node
        curr = curr->next;

        // If the next node is the start node, then exit the circular list to prevent infinite looping
        if (curr == start) {
            break; 
        }
    }
}

// Function to run Josephus game with a given circular linked list starting from given node and number of skips
Node* runGame(Node* start, int numSkips) {
    Node* curr = start;
    Node* prev = curr;

    // Loop through the list until the end is reached (only one person left)
    while (curr->next != curr) {

        // Loop through k times to find the kth node
        for (int i = 0; i < numSkips; ++i) { 

            // Set the previous node pointer to the current node and move to the next
            prev = curr;
            curr = curr->next;
        }

        // Link the prev node to the next node and eliminate the current node that represents the person 
        prev->next = curr->next;
        delete curr;
      
        // Move the current node to the next person in the list
        curr = prev->next;
    }
    
    // Returns the last person standing after the game is played
    return curr;
}

// Driver program to test above functions
int main() {

    // Initializes variables hold the number of names and skips
    int numNames = 1, numSkips = 1;

    // Create a vector of strings to store the names
    string name;
    vector<string> storeNames;

    // User inputs the number of names and skips to be played in the game
    cout << "Input the number of names followed by the number of skips to be used in the game:" << endl;

    try {
        // Check for input failure
        if (!(cin >> numNames >> numSkips)) {
            throw runtime_error("Invalid input: Please enter integers only.");
        } 
    } catch (const exception& excpt) {
        // Catch any exception thrown by the input operation and print the error message
        cout << excpt.what() << endl;
        return 1;
    }

    // The while loop gets the inputs until end of file or "." is entered to indicate the end of input
    cout << "Please enter the names of people who will participate in the game. Enter '.' when finished:" << endl;

    try {
        while (cin >> name && name != ".") { 
            storeNames.push_back(name); 
        } 
    } catch (const exception& excpt) {
        // Catch any exception thrown by the input operation and print the error message
        cout << "Error: " << excpt.what() << endl;
    }

    // Load the game with the names, then start the game to execute the elimination game
    Node* startPerson = loadGame(numNames, storeNames);
    Node* lastPerson = runGame(startPerson, numSkips);

    // If there is only one person standing, then they win
    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl;
    } else {
        // Otherwise, an error message is printed
        cout << "error: null game" << endl;
    }

    // Delete the last person to prevent memory leak
    delete lastPerson;

    return 0;
}

