#include <iostream>
#include "IntList.h"

using namespace std;

int main() {
    // Create an IntList object to test each function
    IntList myList;

    cout << "---------------------------------------------------------------" << endl;

    cout << "Testing Push Front, Print Reverse, Pop Front, and an Empty List" << endl;
    myList.push_front(0);
    myList.push_front(10);
    myList.push_front(20);
    cout << "Push Front Function: " << myList << endl;

    cout << "Print Reverse Function: ";
    myList.printReverse();
    cout << endl;

    myList.pop_front();
    cout << "Pop Front Function 1st: " << myList << endl;
    myList.pop_front();
     cout << "Pop Front Function 2nd: " << myList << endl;
    myList.pop_front();
    cout << "Pop Front Function 3rd: " << myList << endl;

    cout << "Testing Empty Function: ";
    if (myList.empty()) {
        cout << "Empty" << endl;
    } else {
        cout << "Not Empty" << endl;
    }
    cout << "Checking the list: " << myList << endl;

    cout << "---------------------------------------------------------------" << endl;

    cout << "Testing Push Back, Pop Back, and a Non-Empty List" << endl;
    myList.push_back(1);
    myList.push_back(2);
    myList.push_back(3);
    myList.push_back(4);
    cout << "Push Back Function: " << myList << endl;
 
    myList.pop_back();
    cout << "Pop Back Function 1st: " << myList << endl;
    myList.pop_back();
    cout << "Pop Back Function 2nd: " << myList << endl;
    
    cout << "Testing Not Empty Function: ";
    if (myList.empty()) {
        cout << "Empty" << endl;
    } else {
        cout << "Not Empty" << endl;
    }
    cout << "Checking the list: " << myList << endl;

    cout << "---------------------------------------------------------------" << endl;

    cout << "Testing Copy Constructor, Copy Assignment, Destructor" << endl;

    IntList copyList(myList);
    cout << "Copy Constructor: " << copyList << endl;
    
    IntList copyAssignmentList;
    copyAssignmentList = myList;
    cout << "Copy Assignment: " << copyAssignmentList << endl;

    cout << "Destructor: " << endl;

    return 0;
}