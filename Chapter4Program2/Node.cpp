#include <iostream>
#include "Node.h"

using namespace std; 

// is this zero or one...
Node::Node() 
    : word(""), count(0), leftChild(nullptr), rightChild(nullptr) {}

Node::Node(const string& word, int count) 
    : word(word), count(count), leftChild(nullptr), rightChild(nullptr) {}

const string& Node::getString() const {
    return word;
}

int Node::getCount() const {
    return count;
}

void Node::setString(const string& item) {

word = item;
}


void Node::setCount(int x) {
  count = x;
}


void Node::incrementCount() {
    count++;
}

void Node::decrementCount() {
    count--;
}

Node* Node::getLeftChild() const {
    return leftChild;
}

Node* Node::getRightChild() const {
    return rightChild;
}

void Node::setLeftChild(Node* left) {
    leftChild = left;
}

void Node::setRightChild(Node* right) {
    rightChild = right;
}  


