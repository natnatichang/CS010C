#pragma once
#include <iostream>
#include <stdexcept>

// Define constant for MAX_SIZE with value of 20 using a preprocessor directive
#define MAX_SIZE 20

using namespace std;

// Define template class that can be used with any data type, specified as the generic type parameter T
template<typename T>

class stack {
private:
    // Private variables to store the elements of the array
    T data[MAX_SIZE];
    int size;

public:
    // Creates an empty stack
    stack() : size(0) {} 
    
    // Function pushes an new element into the data, otherwise throw errors
    void push(T val) {
        // Can't insert a new element if the array is full, so throw error
        if (size >= MAX_SIZE) {
            throw overflow_error("Called push on full stack.");
        } 

        // If there is room in the array, then push the new value into the data
        data[size++] = val;
    }    
    
    // Function gets rid of the last element from the data, and throws errors if empty
    void pop() {
        // If the array is empty, then throw error
        if (size <= 0) {
            throw out_of_range("Called pop on empty stack.");
        } 

        // Get rid of the last element in the data
        size--; 
    }
    
    // Function gets rid of the two last elements in the stack and throws out of range errors based on the case
    void pop_two() {
        // If the size is 0 or less, then throw an error since theres nothing to pop
        if (size <= 0) {
            throw out_of_range("Called pop_two on empty stack.");
        } 
        
        // If the size is 1, then throw an error since not enough to pop
        if (size == 1) {
            throw out_of_range("Called pop_two on a stack of size 1.");
        } 
            
        // If there are enough elements in the array, get rid of the last two elements 
        size -= 2;
    } 
    
    // Function returns top of the stack which was the last inserted element and throws errors if empty
    T top() {
        //If the array is empty, there's nothing on top so throw error
        if (size <= 0) {
            throw underflow_error("Called top on empty stack.");
        } 

        // Get the top element of the stack if not empty
        return data[size - 1];
    } 
    
    // Function returns true if stack is empty, else false
    bool empty() const {
        return (size == 0);
    } 

};


