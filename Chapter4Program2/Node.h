#pragma once
#include <string>

using namespace std;

class Node {
private:
    string word;
    int count; 
    // Node* leftChild;
    // Node* rightChild;

public:
    Node* leftChild;
    Node* rightChild;

    Node();
    Node(const string& word, int count);

// DO I NEED THIS?
    const string& getString() const;
    int getCount() const;
    void setString(const string&);
    void setCount(int);
    void incrementCount();
    void decrementCount();
    Node* getLeftChild() const;
    Node* getRightChild() const;
    void setLeftChild(Node* left);
    void setRightChild(Node* right);
};
