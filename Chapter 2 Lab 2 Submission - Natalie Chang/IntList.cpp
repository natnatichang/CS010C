#include <iostream>
#include "IntList.h"

using namespace std; 

// Constructor for IntList that initializes the dummy head and tail nodes
IntList::IntList() : dummyHead(new IntNode(0)), dummyTail(new IntNode(0)) {
    // The dummy head and tail nodes are linked to each other to create efficient traversal in forward/backward direction
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
}

// Destructor for IntList to destroys the IntNode objects to ensure no memory leaks
IntList::~IntList() {
    // Create a new node to start traversing from the dummyHead to delete
    IntNode* currNode = dummyHead;

    // Loop through the list starting from dummyHead until it reaches dummyTail
    while (currNode != nullptr) {
        // Keep track of the next node before deleting the current node
        IntNode* nextNode = currNode->next;

        // Print a message to show that the current node is being deleted
        cout << "Deleting node with value: " << currNode->data << endl;

        // Delete the current node
        delete currNode;

        // Move onto the next node in the list to get to the end
        currNode = nextNode;
    }
    cout << endl;
}

// Copy constructor for IntList to perform deep copy by creating a new node with the same values as the original node
IntList::IntList(const IntList& sourceObject) {
    // Create a dummy head and a dummy tail for the new list
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);

    // Link the dummy head and dummy tail together
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;

    // Copy each node from the original list to the new list
    IntNode* curr = sourceObject.dummyHead->next;
    while (curr != sourceObject.dummyTail) {
        // Create a new node with the data as the current node to copy from the original list
        IntNode* newNode = new IntNode(curr->data);

        // Link the new node to dummy tail node
        newNode->prev = dummyTail->prev;
        newNode->next = dummyTail;

        // Link the new node to the list by updating prev nodes next pointer and dummy tails prev pointer to point to the new node
        dummyTail->prev->next = newNode;
        dummyTail->prev = newNode;

        // Update the curr pointer to point to next node in the original list to copy the rest of the list
        curr = curr->next;
    }
}

// Copy assignment operator for IntList to copy values of right hand side objects to left hand side objects
IntList& IntList::operator=(const IntList& sourceObject) {
    // Handle self-assignment
    if (this == &sourceObject) {
        return *this;
    }

    // Delete the existing list nodes so it can copy the nodes from other list without having the old nodes create memory leak
    IntNode* currNode = dummyHead->next;
    while (currNode != dummyTail) {
        IntNode* nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }

    // Set the head and tail pointers to an empty list and connect the two
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;

    // Traverse through the list to copy each node from the original list to the new list
    IntNode* curr = sourceObject.dummyHead->next;
    while (curr != sourceObject.dummyTail) {
        // Create a new node with the data as the current node to copy from the original list
        IntNode* newNode = new IntNode(curr->data);

        // Link the new node to dummy tail node
        newNode->prev = dummyTail->prev;
        newNode->next = dummyTail;

        // Update the nodes that come before and after the new node to connect it to the list as the new last node
        dummyTail->prev->next = newNode;
        dummyTail->prev = newNode;

        // Update the curr pointer to point to next node in the original list to copy the rest of the list
        curr = curr->next;
    }

    // Return a reference to the current object so the assignment operator can be linked 
    return *this;
}


// Push_front function adds a new IntNode with the given value to the front of the list after dummy head
void IntList::push_front(int value) { 
    // Create a new node with given values to insert at the beginning 
    IntNode* newNode = new IntNode(value);

    // Connect the new node to the node that is after the dummy head and the node that was previously connected to the head
    newNode->next = dummyHead->next;
    newNode->prev = dummyHead;

    // Connect the previous node to the new node and the head
    dummyHead->next = newNode;
    newNode->next->prev = newNode;
}

// Pop_front function to delete the front node of the list after dummy head
void IntList::pop_front() {
    // Make sure that there are nodes between the dummy heads and dummy tails to delete
    if (dummyHead->next != dummyTail) {
        // Create an IntNode for the node to be deleted after the dummy head 
        IntNode* frontNode = dummyHead->next;

        // Reconnect the list without the deleted node at the front
        dummyHead->next = frontNode->next;
        frontNode->next->prev = dummyHead;

        // Delete the node to ensure no memory leaks
        delete frontNode;
    }
}

// Push_back function adds a new IntNode with the given value to the back of the list before dummy tail 
void IntList::push_back(int value) {
    // Create a new node with given values to insert at the end 
    IntNode* newNode = new IntNode(value);

    // Connect the new node to the tail node and the node that was previously connected to the tail
    newNode->prev = dummyTail->prev;
    newNode->next = dummyTail;

    // Connect the previous node to the new node and the tail
    dummyTail->prev->next = newNode;
    dummyTail->prev = newNode;
}

// Pop_back function to delete the back node of the list before dummy tail
void IntList::pop_back() {
    // Make sure that there are nodes between the dummy heads and dummy tails to delete
    if (dummyTail->prev != dummyHead) {
        // Create an IntNode for the node to be deleted before the dummy tail 
        IntNode* lastNode = dummyTail->prev;

        // Reconnect the list without the deleted node at the back
        dummyTail->prev = lastNode->prev;
        lastNode->prev->next = dummyTail;

        // Delete the node to ensure no memory leaks
        delete lastNode;
    }
}

// Check if the IntList is empty to return true or false
bool IntList::empty() const {
    // If there is only the dummy head and dummy tail in the list then the list is considered empty
    if (dummyHead->next == dummyTail) {
        return true;
    } else {
        // If there are other nodes between dummy head and dummy tail, then the list is not empty
        return false;
    }
}

// Overload << operator to output IntList objects
ostream & operator<<(ostream &out, const IntList &rhs) {
   // Initialize pointer to first node in the list to traverse list
   IntNode* currNode = rhs.dummyHead->next;

    // Traverse list until the tail node is reached
    while (currNode != rhs.dummyTail) {
        // Output the data stored at the current node
        out << currNode->data;

        // Print a space after each value except for the last one
        if (currNode->next != rhs.dummyTail) {
            out << " ";
        }

        // Move to the next node in the list
        currNode = currNode->next;
    }
    // Return the output stream object
    return out;  
}

// Prints IntList in reverse order
void IntList::printReverse() const {
    // Check if list is empty to prevent accessing invalid memory 
    if (!empty()) {
        // Start from the node before the dummy tail to traverse backwards
        IntNode* currNode = dummyTail->prev;

        // Print out the nodes data and move to the previous node of the list
        while (currNode != dummyHead) {
            cout << currNode->data << " ";
            currNode = currNode->prev;
        }
    }
}

