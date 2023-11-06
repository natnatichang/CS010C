#pragma once 

using namespace std;

// Definition of a doubly linked list node containing integer data and pointers to the prev and next nodes
struct IntNode {
    int data;
    IntNode *prev;
    IntNode *next;
    IntNode(int data) : data(data), prev(0), next(0) {}
};

// Intlist class that represents a doubly-linked list and its operations
class IntList {
public:
    // Default constructor that creates a dummy head and dummy tail and links them together
    IntList();

    // Add Big Three (Destructor, Copy constructor, Copy assignment operator) for IntList
    ~IntList();
    IntList(const IntList& sourceObject);
    IntList& operator=(const IntList& sourceObject);

    // Public member functions for IntList
    void push_front(int value);
    void pop_front(); 
    void push_back(int value);
    void pop_back();
    bool empty() const;
    friend ostream & operator<<(ostream &out, const IntList &rhs);
    void printReverse() const;

private:
    // Pointers to IntNode objects to provide easy access to beginning and end of list without traversal each time
    IntNode* dummyHead;
    IntNode* dummyTail;
};