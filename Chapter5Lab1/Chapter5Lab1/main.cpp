#include <iostream>
#include "Heap.h"

using namespace std;

// Declare functions to be used for printing menu
int menu();

int main() {
  // Create an object of the Heap class
  Heap max_heap;

  // Display the menu to the user to get choice
  int choice = menu();

  // If the user inputs 4, then the program ends
  while (choice != 4) {

    // Try-catch block will catch and handle any exceptions that may occur at runtime
    try {

      if (choice == 1) {
        // Prompt user to enter print job details
        int priority, jobNumber, numPages;
        cout << "Enter print job to enqueue (priority, job Number, number of pages): ";

        // Try to read the input values and throw an error if they are invalid
        if(!(cin >> priority >> jobNumber >> numPages)) {
          throw runtime_error("Error: Invalid Input");
        }
        cout << endl;

        // Create a new PrintJob object to enqueue into the heap
        max_heap.enqueue(new PrintJob(priority, jobNumber, numPages));

      } else if (choice == 2) {
        // Print the PrintJob with highest priority in the heap
        max_heap.print();

      } else if (choice == 3) {
        // Remove the PrintJob with highest priority from the heap
        max_heap.dequeue();

      }
    } catch(const exception& e) {
      // If any errors occur, then print out statement 
      cout << "An exception occurred: " << e.what() << endl;
    }
    // If there are no errors and input isn't 4, then continue to prompt user 
    choice = menu();
  }
  return 0;
}

// Menu function prints out the menu for the user to make a choice
int menu() {
  // Print out the menu options
  int choice = 0;
  cout << endl << "Enter menu choice: " << endl;
  cout << "1. Enqueue" << endl;
  cout << "2. Print" << endl;
  cout << "3. Dequeue" << endl;
  cout << "4. Quit" << endl;
  
  // If the user input is not a choice between 1-4, then throw an error so it doesn't fail silently
  if (!(cin >> choice) || choice < 1 || choice > 4) {
    cin.clear();
    cin.ignore();
    throw runtime_error("Invalid input. Please enter a number between 1 and 4.");
  }

  // If the user input is valid, clear the error flags and buffer to return the user choice
  cin.clear();
  cin.ignore(256, '\n');
  return choice;
}
