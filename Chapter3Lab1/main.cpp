#include <iostream>
#include <vector>
#include <stdexcept>
#include <ctime>
#include <string>

using namespace std;

// Template and Function Declarations

template<typename T>
unsigned min_index(const vector<T>& vals, unsigned index);

template<typename T>
void selection_sort(vector<T>& vals);

template<typename T>
T getElement(const vector<T>& vals, int index);

template<typename T>
void printVector(const vector<T>& vals);

vector<char> createVector();

int main() {

    // Test harnesses for selection sort to sort vectors of doubles, integers, and strings 

    vector<double> vecDouble {67.3, 34.2, 45.25, 45.125, 0.0, 2.4, 1.3, -3.1, -4.5, -2};

    vector<int> vecInt {3, 78, 12, 67, 34, 67, 23, 12, 99, 56, -2, -34, -123};

    vector<string> vecString {"red", "blue", "green" , "purple", "orange", "black", "yellow"};

    cout << "------------------------------------------" << endl;
    
    // Test case for vector of doubles to show before and after selection_sort

    cout << "Before selection sort for double: " << endl;
    printVector(vecDouble);

    selection_sort(vecDouble);

    cout << endl << "After selection sort for double: " << endl;
    printVector(vecDouble);
    
    cout << "------------------------------------------" << endl;

    // Test case for vector of integers to show before and after selection_sort

    cout << "Before selection sort for integer: " << endl;
    printVector(vecInt);

    selection_sort(vecInt);

    cout << endl << "After selection sort for integer: " << endl;
    printVector(vecInt);

    cout << "------------------------------------------" << endl;

    // Test case for vector of strings to show before and after selection_sort

    cout << "Before selection sort for string: " << endl;
    printVector(vecString);

    selection_sort(vecString);

    cout << endl << "After selection sort for string: " << endl;
    printVector(vecString);

    cout << "------------------------------------------" << endl;

    // Create random vector of characters to find the character at a given index

    srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    int index;
    int numOfRuns = 10;
    
    // Test case for try and catch exception

    cout << "Test Case for Try and Catch Exception" << endl << endl;
    cout << "Vector that is created: " << endl;
    printVector(vals);

    cout << "------------------------------------------" << endl;

    // Program will take 10 inputs from the user and output the current character
    while (--numOfRuns >= 0) {

        // Check if the user input is a valid integer, otherwise throw a runtime error
        if (!(cin >> index)) {
            throw runtime_error("Invalid input as value is not an integer.");
        }

        // Try to retrieve the element located at the given index in the vector
        try {
            // Call the function getElement to return the element located at the index of the value
            curChar = getElement(vals, index);
            cout << "Element located at " << index << " is " << curChar << endl;

        } catch (const out_of_range& e) {
            // Handle errors that occur when trying to access an element of a datatype outside of the valid index range
            cout << "Error message: " << e.what()<< endl;

            // Clear the error state and discard any remaining characters in the input buffer
            cin.clear();
            cin.ignore(); 

        } catch (const exception& e) {  
            // Handle any other exceptions may occur while executing the code in the try block
            cout << "Error message: " << e.what() << endl;

            // Clear the error state and discard any remaining characters in the input buffer
            cin.clear();
            cin.ignore(); 

        }
    }
    return 0;
}

// Function that finds the minimum value of a vector for any datatype starting at given index
template<typename T>
unsigned min_index(const vector<T>& vals, unsigned index) {
    // Initialize minimum value as element at given index
    T minVal = vals[index];

    // Initialize index of the miniuum value to be the given index
    unsigned minIndex = index;

    // Loop through the remaining elements after the given index to find minimum index
    for (unsigned i = index + 1 ; i < vals.size(); ++i) {

       // If element is smaller than current minimum value, update the minimum value and index
        if (vals[i] < minVal) {
            minVal = vals[i];
            minIndex = i;
        }
    }
    // Return the index of the minimum value
    return minIndex;
}

//  Function sorts a vector in ascending order by repeatedly finding and moving the minimum value to its correct position
template<typename T>
void selection_sort(vector<T>& vals) {
    // Loop through the unsorted parts of the vector
    for (int i = 0; i < static_cast<int>(vals.size()) - 1; i++) {

        // Using the min_index function, find the index of the minimum value of the unsorted parts
        unsigned minIndex = min_index(vals, i);

       // Swap the ith value of the vector with the minimum value to sort the vector
        swap(vals[i], vals[minIndex]);
    }
}

// Function returns the element located at the given index in a vector
template<typename T>
T getElement(const vector<T>& vals, int index) {
    // If the user input is less than the vector size, then out of range error occurred
    if (index < 0) {
        throw out_of_range("Out of Range Exception Occured");
    } 
    
    // If the user input index is greater than the vector size, then out of range error occurred
    if (index >= static_cast<int>(vals.size())) {
        throw out_of_range("Out of Range Exception Occured");
    }

    // If the index is within the vector, then return the index
    return vals.at(index);
}

// Function helps print out the vectors for the test harnesses
template<typename T>
void printVector(const vector<T> &vals) {
    // Iterate through the vector to print all the values
    for (const auto& index : vals) {
        cout << index << " ";
    }
    cout << endl;
}

// Function creates a random vector of characters between a-z
vector<char> createVector() {
    // Give the vector a random size
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;

    // Loop through to add characters into the vectors starting from 'a'
    for (int i = 0; i < vecSize; i++) {       
        vals.push_back(c);
        c++;
    }

    // Return the random vector of characters
    return vals;
}