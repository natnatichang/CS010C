#include <iostream>
#include "PrintJob.h"

using namespace std; 

// Constructor that sets the member variables
PrintJob::PrintJob (int setP, int setJ, int numP)
    : priority(setP), jobNumber(setJ), numPages(numP) {}

// GetPriority function returns the priority of the print job
int PrintJob::getPriority() {
    return priority;
}

// GetJobNumber function returns the job number of the print job
int PrintJob::getJobNumber() {
    return jobNumber;
}

// GetPages function return the number of pages of the print job
int PrintJob::getPages() {
    return numPages;
}