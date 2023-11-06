#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// Vertex struct represents a vertex in the graph
struct Vertex {
    // Represents the state of the vertex, which is a pair of integers representing the amounts in the jugs
    pair<int, int> state;
    
    // Distance from the initial state 
    int distance;

    // Pointer to the previous vertex in the path
    Vertex* prev;

    // Array representing the neighbors of the vertex where each neighbor is represented by a pair of integers
    int neighbor[6][2];
};

// Jug class to represent the jug problem and goals
class Jug {
public:
    // Constructor to help solve the jug problem
    Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA);

    // Add Big Three (Destructor, Copy constructor, Copy assignment operator) for Jug
    ~Jug();
    Jug(const Jug& sourceObject);
    Jug& operator=(const Jug& sourceObject);

    // Solves the jug problem and returns the number of steps required
    int solve(string& solution);

private:
    // Private member variables representing different actions and goals
    int capacityA;
    int capacityB;
    int goal;
    int costFillA;
    int costFillB;
    int costEmptyA;
    int costEmptyB;
    int costPourAB;
    int costPourBA;
    
    // Adjacency list representation of the graph
    vector<Vertex> adjList;

    // Helper function for deep copying the adjacency list
    void copyAdjList(const std::vector<Vertex>& sourceObject);

    // Private functions to help solve the jug problem 
    void createGraph(vector<Vertex>& vert);
    bool solutionExists(const Vertex& vert) const;
    bool checkInput(const string& solution) const;
    int locate(const Vertex& vert) const;

    // Private functions to represent the actions that can be taken
    void fillA(Vertex& vert);
    void fillB(Vertex& vert);
    void pourAB(Vertex& vert);
    void pourBA(Vertex& vert);
    void emptyA(Vertex& vert);
    void emptyB(Vertex& vert);

};

