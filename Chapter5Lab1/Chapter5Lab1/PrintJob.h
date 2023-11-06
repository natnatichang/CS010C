#pragma once 

using namespace std;

// PrintJob class that represents a print job in a printer queue
class PrintJob {
private:
  // Private member variables that contains information about the print job
  int priority;
  int jobNumber;
  int numPages;

public:
  // Constructor for the PrintJob class
  PrintJob (int setP, int setJ, int numP);

  // Public functions to help access the priority, job number, and number of pages of a print job object
  int getPriority() const;
  int getJobNumber() const;
  int getPages() const;
};
