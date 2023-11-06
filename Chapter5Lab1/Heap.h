#pragma once 
#include "PrintJob.h"

using namespace std;

// Maximum size of heap
const int MAX_HEAP_SIZE = 10;

// Heap class that represents max-heap data structure that stores PrintJob objects
class Heap {
private:
  // Private member variables to create an array of PrintJob pointers
  PrintJob* arr[MAX_HEAP_SIZE];    
  int numItems; 

private:
  // Private helper function for dequeue function to move the new root down the heap to appropriate location
  void trickleDown(int index);

public:
  // Constructor for an empty heap
  Heap();

  // Add Big Three (Destructor, Copy constructor, Copy assignment operator) for Heap
  ~Heap();
  Heap(const Heap& sourceObject);
  Heap& operator=(const Heap& sourceObject);
  
  // Public member functions to help with the printing job
  void enqueue(PrintJob* loader);
  void dequeue();
  PrintJob* highest() const;
  void print() const;
};

