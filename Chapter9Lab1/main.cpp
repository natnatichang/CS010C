#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Declare a const size for the array
const int NUMBERS_SIZE = 50000;

// Declare functions to be used later
int genRandInt(int low, int high);
void fillArrays(int arr1[], int arr2[], int arr3[]);
void Quicksort_midpoint(int numbers[], int i, int k);
void Quicksort_medianOfThree(int numbers[], int i, int k);
void InsertionSort(int numbers[], int numbersSize);

// Main function tests out sorting algorithms
int main() {

    // Try-catch block will catch and handle any exceptions that may occur at runtime
    try {

        // Create a variable that helps to represent the number of clock ticks per millisecond 
        const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000; 
        
        // Create arrays and fill it up with numbers to test the sorting algorithms
        int arrOne[NUMBERS_SIZE], arrTwo[NUMBERS_SIZE], arrThree[NUMBERS_SIZE];
        fillArrays(arrOne, arrTwo, arrThree);

        // Measure the time taken by Quicksort using midpoint pivot selection
        clock_t Start1 = clock();
        Quicksort_midpoint(arrOne, 0, NUMBERS_SIZE - 1);
        clock_t End1 = clock();
        int elapsedTime1 = (End1 - Start1) / CLOCKS_PER_MS; 
        cout << "Time for quicksort midpoint: " << elapsedTime1 << endl;

        // Measure the time taken by Quicksort using median-of-three pivot selection
        clock_t Start2 = clock();
        Quicksort_medianOfThree(arrTwo, 0, NUMBERS_SIZE - 1);
        clock_t End2 = clock();
        int elapsedTime2 = (End2 - Start2) / CLOCKS_PER_MS; 
        cout << "Time for quicksort median of three: " << elapsedTime2 << endl;

        // Measure the time taken by Insertion Sort algorithm
        clock_t Start3 = clock();
        InsertionSort(arrThree, NUMBERS_SIZE);
        clock_t End3 = clock();
        int elapsedTime3 = (End3 - Start3) / CLOCKS_PER_MS; 
        cout << "Time for insertion sort: " << elapsedTime3 << endl;

    } catch (const exception& e) {
        // If any errors occur, then print out statement 
        cout << "An exception occurred: " << e.what() << endl;
    }
    
    return 0;
}

// Function to generate a random integer between low and high
int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

// Function to fill the three arrays with random numbers
void fillArrays(int arr1[], int arr2[], int arr3[]) {
    // Based on the size of the array, generate and assign the same numbers to each index
    for (int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0, NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

// Quicksort_midpoint function implements the quicksort algorithm with a midpoint pivot selection strategy
void Quicksort_midpoint(int numbers[], int i, int k) {
    // Initialize the left and right indices
    int left = i, right = k;

    // Select the pivot element as the middle element
    int pivot = numbers[(i + k) / 2];

    // Partition the array using the pivot
    while (left <= right) {
        // Find an element on the left side that is greater than the pivot
        while (numbers[left] < pivot) {
            ++left;
        } 

        // Find an element on the right side that is smaller than the pivot
        while (numbers[right] > pivot) {
            --right;
        } 

        // Swap the elements if they are out of order
        if (left <= right) {
            swap(numbers[left], numbers[right]);
            ++left;
            --right;
        }
    }

    // Recursively sort the left partition if it contains more than one element
    if (i < right) {
        Quicksort_midpoint(numbers, i, right);
    } 

    // Recursively sort the right partition if it contains more than one element
    if (left < k) {
        Quicksort_midpoint(numbers, left, k);
    }
}

// Quicksort_medianOfThree function implements the quicksort algorithm with a median-of-three pivot selection strategy
void Quicksort_medianOfThree(int numbers[], int i, int k) {
    // Create the base case so if the current subarray has only one or no elements, it is already sorted
    if (i >= k) {
        return;
    }

    // Handle the case when the subarray has two elements
    if (k - i == 1) {
        // Check if the elements are in the correct order, and swap them if necessary
        if (numbers[i] > numbers[k]) {
            swap(numbers[i], numbers[k]);
        }
        return;
    }

    // Find the index of the median element using median-of-three pivot selection
    int center = (i + k) / 2;

    // Ensure that the first element is smaller than or equal to the median element
    if (numbers[i] > numbers[center]) {
        swap(numbers[i], numbers[center]);
    }

    // Ensure that the first element is smaller than or equal to the last element
    if (numbers[i] > numbers[k]) {
        swap(numbers[i], numbers[k]);
    }

    // Ensure that the median element is greater than or equal to the last element
    if (numbers[center] > numbers[k]) {
        swap(numbers[center], numbers[k]);
    }

    // Move the median element to the second-to-last position
    swap(numbers[center], numbers[k - 1]);

    // Select the pivot as the element at the second-to-last position
    int pivot = numbers[k - 1];

    // Initialize the left and right indices for partitioning
    int left = i;
    int right = k - 2;

    // Partition the subarray using the pivot
    while (left <= right) {
        // Find an element on the left side that is greater than the pivot
        while (numbers[left] < pivot) {
            ++left;
        }

        // Find an element on the right side that is smaller than the pivot
        while (numbers[right] > pivot) {
            --right;
        }

        // Swap the elements if they are out of order
        if (left <= right) {
            swap(numbers[left], numbers[right]);
            ++left;
            --right;
        }
    }

    // Move the pivot element to its correct sorted position
    swap(numbers[left], numbers[k - 1]);

    // Recursively sort the left and right partitions
    Quicksort_medianOfThree(numbers, i, left - 1);
    Quicksort_medianOfThree(numbers, left + 1, k);
}

// InsertionSort function implements insertion sort algorithm to sort an array of integers in ascending order
void InsertionSort(int numbers[], int numbersSize) {
    int i, j, key;

    // Iterate through the array starting from the second element since the first element is already considered sorted
    for (i = 1; i < numbersSize; ++i) {

        // Store the current element that needs to be inserted into its correct position
        key = numbers[i];

        // Initialize 'j' to the index of the element before the current element
        j = i - 1;

        // Compare the key with each element in the sorted subarray
        while (j >= 0 && numbers[j] > key) {
            // Move the elements greater than the key one position to the right
            numbers[j + 1] = numbers[j];
            j = j - 1;
        }

        // Insert the key into its correct position in the sorted subarray
        numbers[j + 1] = key;
    }
}

