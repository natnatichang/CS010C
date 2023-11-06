#pragma once 

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Vertex {
    int A;
    int B;
    string step;
    int cost;

    Vertex(int A, int B, string step, int cost)
        : A(A), B(B), step(step), cost(cost) {}
};

class Jug {
public:
    Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA);
    ~Jug();

        // need to implement 

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.

        // why no const 
    int solve(string& solution);

private:
    int Ca, Cb, N, cfA, cfB, ceA, ceB, cpAB, cpBA;

    bool isValidInput();
    
};