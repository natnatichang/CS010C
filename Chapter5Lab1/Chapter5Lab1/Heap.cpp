#include <iostream>
#include "Heap.h"

using namespace std;  

// Create an empty heap
Heap::Heap() 
    : numItems(0) {}

// Destructor for Heap
Heap::~Heap() {
    // Iterate through the array to delete the items
    for (int i = 0; i < numItems; i++) {
        delete arr[i];
    }
}

// Copy constructor for Heap
Heap::Heap(const Heap& sourceObject) {
    // Copy the number of items from the source object to the new object
    numItems = sourceObject.numItems;

    // Create a new PrintJob object with the same data by looping
    for (int i = 0; i < numItems; i++) {
        arr[i] = new PrintJob(*sourceObject.arr[i]);
    }
}

// Copy assignment operator for Heap
Heap& Heap::operator=(const Heap& sourceObject) {
    // Handle self-assignment
    if (this != &sourceObject) {
        // Free existing memory in the object being assigned to by deleting
        for (int i = 0; i < numItems; i++) {
            delete arr[i];
        }
        
        // Create deep copy of the source object
        numItems = sourceObject.numItems;
        
        // Create a new PrintJob object with the same data by looping
        for (int i = 0; i < numItems; i++) {
            arr[i] = new PrintJob(*sourceObject.arr[i]);
        }
    }
    // Return a reference to the object being assigned 
    return *this;
}

// // Enqueue function will inserts a PrintJob to the heap without violating max-heap properties
// void Heap::enqueue(PrintJob* loader) {
//     // The following test case may fail zyBooks code but are included to prevent silent failure
    
//     // If the heap is full, throw a runtime error indicating that a new print job can not be enqueued
//     if (numItems >= MAX_HEAP_SIZE) {
//         throw runtime_error("Heap is full. Can not enqueue.");
//     }

//     // Check if there is space available in the heap
//     if (numItems < MAX_HEAP_SIZE) { 
//         // If the heap is empty, insert it as the first element in the array
//         if (numItems == 0) { 
//             arr[numItems] = loader; 
//             ++numItems;
//         } else { 
//             // If the heap is not empty, insert the job at the bottom of the heap and move it up to the correct position

//             // Set the current index to the last position in the heap
//             int currentIndex = numItems;

//             // If the current index is not the root of the heap, and parent has lower priority, shift the parent downwards
//             while (currentIndex > 0 && (arr[(currentIndex - 1 ) / 2]->getPriority() < loader->getPriority())) { 
//                 // Shift the parent down to the current position
//                 arr[currentIndex] = arr[(currentIndex - 1) / 2]; 
//                 // Update the current index to the parent index
//                 currentIndex = (currentIndex - 1) / 2; 
//             } 

//             // Insert the job at the current position and increment the number of items
//             arr[currentIndex] = loader; 
//             ++numItems; 
//         }
//     }
// }

// UPDATED WITH THE PERCULATE FUCNTION

// Enqueue function inserts a PrintJob into the heap without violating max-heap properties
void Heap::enqueue(PrintJob* loader) {
    // The following test case may fail in zyBooks code but is included to prevent silent failure

    // If the heap is full, throw a runtime error indicating that a new print job cannot be enqueued
    if (numItems >= MAX_HEAP_SIZE) {
        throw runtime_error("Heap is full. Cannot enqueue.");
    }

    // Check if there is space available in the heap
    if (numItems < MAX_HEAP_SIZE) {
        // If the heap is empty, insert it as the first element in the array
        if (numItems == 0) {
            arr[numItems] = loader;
            ++numItems;
        } else {
            // If the heap is not empty, insert the job at the bottom of the heap
            // and percolate it up to the correct position

            // Set the current index to the last position in the heap
            int currentIndex = numItems;

            // Insert the job at the current position and increment the number of items
            arr[currentIndex] = loader;
            ++numItems;

            // Percolate up the newly inserted job to maintain the max-heap property
            percolateUp(currentIndex);
        }
    }
}

void Heap::percolateUp(int index) {
    int parentIndex = (index - 1) / 2;

    while (index > 0 && arr[parentIndex]->getPriority() < arr[index]->getPriority()) {
        // Swap the current item with its parent
        PrintJob* tempJob = arr[parentIndex];
        arr[parentIndex] = arr[index];
        arr[index] = tempJob;

        // Update the current index and parent index for further comparisons
        index = parentIndex;
        parentIndex = (index - 1) / 2;
    }
}


// Dequeue function removes the item with the highest priority from the heap
void Heap::dequeue() {
    // The following test case may fail zyBooks code but are included to prevent silent failure

    // If the heap is empty, throw a runtime error indicating that a new print job can not be dequeued
    if (numItems == 0) {
       throw runtime_error("Heap is empty. Can not dequeue.");
    }

    // If there is only one item in the heap, remove and return it
    if (numItems == 1) {
        numItems = 0;
        arr[0] = 0;
        return;
    }

    // If there are more items in the heap, move the last item to the root position
    if (numItems > 1) {
        // Replace the root with the last item in the heap
        arr[0] = arr[numItems - 1];

        // Set the last item in the heap to remove it from the heap
        arr[numItems - 1] = nullptr;

        // Decrement the count to show item has been dequeued
        numItems--;

        // Trickle down the new root to maintain heap properties by calling helper function
        trickleDown(0);
    }
}

// TrickleDown helper function helps to maintain heap property after removing the root item from heap
void Heap::trickleDown(int numbers) {
    // Loop through all the items in the heap
    for (int i = 0; i < numItems; i++) {
        // Check if priority of the current item is less than the priority of the child
        if (arr[numbers]->getPriority() < arr[i]->getPriority()) {
            // Swap the current item with the child item
            PrintJob* tempJob  = arr[numbers];
            arr[numbers] = arr[i];
            arr[i] = tempJob ;
        }
    }
}

// Highest function returns the item with highest priority
PrintJob* Heap::highest() const {
    // The following test case may fail zyBooks code but are included to prevent silent failure

    // If the heap is empty, throw a runtime error indicating that the highest does not exist
    if (numItems == 0) {
        throw runtime_error("Heap is empty. No highest priority could be found.");
    } 

    // Heap has max-heap property, so root item has highest priority
    return arr[0];
}

// Print function prints out the highest priority for priority, job number, and number of pages
void Heap::print() const {
    // The following test case may fail zyBooks code but are included to prevent silent failure

    // If the heap is empty, throw a runtime error indicating that there is nothing to be printed out
    if (numItems == 0) {
        throw runtime_error("Heap is empty. Nothing to print out.");
    }   

    // If not empty, print out the priority, job number, number of pages
    cout << "Priority: " << highest()->getPriority();
    cout << ", Job Number: " << highest()->getJobNumber();
    cout << ", Number of Pages: " << highest()->getPages() << endl;
    return;
}

