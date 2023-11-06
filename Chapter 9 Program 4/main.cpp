#include <iostream>
#include <string>

#include "Jug.h"

using namespace std;

int main() {
   // Try-catch block will catch and handle any exceptions that may occur at runtime
   try {
      // Initialize a string variable to store the solution and create an instance of Jug with specific parameters
      // The goal is to find a sequence of steps that leaves Jug A empty and exactly 4 gallons in Jug B
      string solution;
      Jug jug1(3, 5, 4, 1, 2, 3, 4, 5, 6);

      // If the solution for jug1 is not found, throw "No Solution"
      if (jug1.solve(solution) != 1) {
         throw runtime_error("No Solution");
      }

      // Print the solution
      cout << solution << endl << endl;

      // Create another instance of Jug with different parameters
      // The goal is to find a sequence of steps that leaves Jug A empty and exactly 4 gallons in Jug B
      Jug jug2( 3, 5, 4, 1, 1, 1, 1, 1, 2);

      // If the solution for jug2 is not found, throw "No Solution"
      if (jug2.solve(solution) != 1) {
         throw runtime_error("No Solution");
      }

      // Print the solution
      cout << solution << endl;

   } catch (const exception& e) {
        // If any errors occur, then print out statement 
        cout << "An exception occurred: " << e.what() << endl;
   }
   
   return 0;
}
