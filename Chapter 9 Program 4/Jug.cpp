#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <climits>

#include "Jug.h"

using namespace std; 

// Jug constructor to help set up the problem and find the solution
Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA)
    : capacityA(Ca), capacityB(Cb), goal(N), costFillA(cfA), costFillB(cfB), costEmptyA(ceA), costEmptyB(ceB), costPourAB(cpAB), costPourBA(cpBA)
{   
    // Check if the input constraints are valid
    if (!(Ca > 0 && Ca <= Cb) || !(Cb > N && Cb <= 1000)) {
        // If the input is invalid, return without creating the Jug object
        return;
    }
    
    // Check if the cost values are non-negative
    if (cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0) {
        // If the input is invalid, return without creating the Jug object
        return;
    }

    // Create the graph representation of the problem
    createGraph(adjList);
}

// Destructor for Jug
Jug::~Jug() {
    // Declare an empty destructor since no dynamically allocated resources
}

// Copy constructor for Jug
Jug::Jug(const Jug& sourceObject)
    : capacityA(sourceObject.capacityA), capacityB(sourceObject.capacityB), goal(sourceObject.goal),
      costFillA(sourceObject.costFillA), costFillB(sourceObject.costFillB), costEmptyA(sourceObject.costEmptyA),
      costEmptyB(sourceObject.costEmptyB), costPourAB(sourceObject.costPourAB), costPourBA(sourceObject.costPourBA) 
{
    // Call helper function to make a deep copy
    copyAdjList(sourceObject.adjList);
}

// Copy assignment operator for Jug
Jug& Jug::operator=(const Jug& other) {
    // Check for self-assignment before copying the list
    if (this != &other) {
        capacityA = other.capacityA;
        capacityB = other.capacityB;
        goal = other.goal;
        costFillA = other.costFillA;
        costFillB = other.costFillB;
        costEmptyA = other.costEmptyA;
        costEmptyB = other.costEmptyB;
        costPourAB = other.costPourAB;
        costPourBA = other.costPourBA;
        copyAdjList(other.adjList);
    }

    // Return a reference to the current object
    return *this;
}

// CopyAdjList function for deep copying the adjacency list
void Jug::copyAdjList(const std::vector<Vertex>& sourceObject) {
    adjList.clear();
    for (const auto& vertex : sourceObject) {
        adjList.push_back(vertex);
    }
}

// CreateGraph function generates a graph of vertices and edges to represent the domain of the problem
void Jug::createGraph(vector<Vertex>& vert) {
    Vertex v;
    Vertex init;
    vert.push_back(v);

    // Iterate through each vertex in the graph
    for (unsigned i = 0; i < vert.size(); ++i) {
        // Create six temporary vertices for different operations
        init = vert[i];
        Vertex vert1 = init;
        Vertex vert2 = init;
        Vertex vert3 = init;
        Vertex vert4 = init;
        Vertex vert5 = init;
        Vertex vert6 = init;
        
        // Perform various operations on the temporary vertices to find different states and transitions 
        fillA(vert1);
        fillB(vert2);
        emptyA(vert3);
        emptyB(vert4);
        pourAB(vert5);
        pourBA(vert6);

        // Add the temporary vertices to the graph if they represent new states
        if (!solutionExists(vert1)) {
            vert.push_back(vert1);
        }

        if (!solutionExists(vert2)) {
            vert.push_back(vert2);
        }

        if (!solutionExists(vert3)) {
            vert.push_back(vert3);
        }

        if (!solutionExists(vert4)) {
            vert.push_back(vert4);
        }

        if (!solutionExists(vert5)) {
            vert.push_back(vert5);
        }

        if (!solutionExists(vert6)) {
            vert.push_back(vert6);
        }
        
        // Update the neighbor information of the current vertex
        init.neighbor[0][0] = locate(vert1);
        init.neighbor[0][1] = costFillA;
        init.neighbor[1][0] = locate(vert2);
        init.neighbor[1][1] = costFillB;
        init.neighbor[2][0] = locate(vert3);
        init.neighbor[2][1] = costEmptyA;
        init.neighbor[3][0] = locate(vert4);
        init.neighbor[3][1] = costEmptyB;
        init.neighbor[4][0] = locate(vert5);
        init.neighbor[4][1] = costPourAB;
        init.neighbor[5][0] = locate(vert6);
        init.neighbor[5][1] = costPourBA;

        // Update the current vertex in the graph with the updated neighbor information
        vert[i] = init;
    }
}

// SolutionExists function checks whether a given vertex state already exists in the adjacency list
bool Jug::solutionExists(const Vertex& vert) const {
    // Iterate through the vertices in the adjacency list
    for (unsigned i = 0; i < adjList.size(); ++i) {
        // Check if the state of the current vertex matches the state of the input vertex
        if (adjList[i].state.first == vert.state.first && adjList[i].state.second == vert.state.second) {
            // A matching state exists in the adjacency list which shows there is a solution
            return true;
        }
    }
    // If no matching state is found in the adjacency list, then a solution does not exist
    return false;
}

// CheckInput function helps validate the input parameters and the solution string provided to the Jug class 
bool Jug::checkInput(const string& solution) const {
    // Create a local variable to construct the solution string
    string tempSolution = solution; 
    
    // Check the validity of the cost value
    if (costFillA < 0 || costFillB < 0 || costEmptyA < 0 || costEmptyB < 0 || costPourAB < 0 || costPourBA < 0) {
        tempSolution = "";
        return false;
    }

    // Check the validity of the capacity values 
    if (capacityA <= 0 || capacityA > capacityB || capacityB <= 0) {
        tempSolution = "";
        return false;
    }

    // Check the validity of the goal value
    if (goal > capacityB || capacityB > 1000 || goal > 1000) {
        tempSolution = "";
        return false;
    }

    // If none of the above conditions are met, return true to indicate that input parameters are valid
    return true;
}

// Locate function helps find the index of a given vertex in the adjacency list
int Jug::locate(const Vertex& vert) const {
    // Iterate through the vertices
    for (unsigned i = 0; i < adjList.size(); ++i) {
        // Check if the state of the current vertex in adjList matches the state of the given vertex
        if (adjList[i].state.first == vert.state.first && adjList[i].state.second == vert.state.second) {
            // Return index of the location if matching vertex is found
            return i;
        }
    }

    // If no matching vertex was found, return -1  
    return -1;
}

// Solve function to find the solution for the jug problem
int Jug::solve(string& solution) {
    // Create a local string variable 'sol' to store solution
    string sol = "";

    // Check if the input values are valid using the checkInput function
    if (!checkInput(solution)) {
        return -1;
    }

    // Initialize variables for tracking the index of the goal vertex and whether it is assigned
    int index = 0;
    bool indexAssigned = false;

    // Iterate through the vertices
    for (unsigned i = 0; i < adjList.size(); ++i) {
        // Check if the state of the current vertex in adjList matches the goal state
        if (adjList[i].state.first == 0 && adjList[i].state.second == goal) {
            // Assign index of the goal vertex and mark it as assigned
            index = i;
            indexAssigned = true;
        }
    }

    // If the index of the goal vertex is not assigned, then goal is impossible to reach
    if (!indexAssigned) {
        solution = "";
        return 0;
    }

    // Create a queue to perform breadth-first search (BFS) on the graph
    queue<Vertex*> vertexQueue;

    for (unsigned i = 0; i < adjList.size(); ++i) {
        // Initialize the distance of all vertices except the source vertex to large number
        adjList[i].distance = INT_MAX;

        // Set the previous vertex for all vertices to nullptr
        adjList[i].prev = nullptr;

        // Push all vertices into the queue
        vertexQueue.push(&adjList[i]);
    }

    // Set the distance of the source vertex to 0
    adjList[0].distance = 0;

    // Perform Dijkstra's algorithm using the breadth-first search approach
    while (!vertexQueue.empty()) {
        // Get the front vertex from the queue
        Vertex* curr = vertexQueue.front();
        vertexQueue.pop();

        // Iterate through the neighbor vertices of the current vertex
        for (unsigned i = 0; i < 6; ++i) {
            int edgeW = curr->neighbor[i][1];
            int alt = curr->distance + edgeW;
            int A = curr->neighbor[i][0];
            
            // If the new distance is smaller than the current distance of the neighbor vertex,
            // update the distance and set the previous vertex to the current vertex
            if (alt < adjList[A].distance) {
                adjList[A].distance = alt;
                adjList[A].prev = curr;
            }
        }
    }
    
    // Create a stack to store the vertices in the shortest path from the source to the goal
    stack<Vertex*> vertexStack;
    Vertex* curr = &adjList[index];

    // Push the goal vertex and its previous vertices into the stack
    while (curr != nullptr) {
        vertexStack.push(curr);
        curr = curr->prev;
    }

    // Generate the solution string by processing the vertices in the stack
    while (vertexStack.size() > 1) {
        curr = vertexStack.top();
        vertexStack.pop();

        Vertex* prior = vertexStack.top();

        // Determine the action required to reach the next vertex and append it to the solution string
        if (curr->neighbor[0][0] == locate(*prior)) {
            sol += "fill A\n";
        }
        if (curr->neighbor[1][0] == locate(*prior)) {
            sol += "fill B\n";
        }
        if (curr->neighbor[2][0] == locate(*prior)) {
            sol += "empty A\n";
        }
        if (curr->neighbor[3][0] == locate(*prior)) {
            sol += "empty B\n";
        }
        if (curr->neighbor[4][0] == locate(*prior)) {
            sol += "pour A B\n";
        }
        if (curr->neighbor[5][0] == locate(*prior)) {
            sol += "pour B A\n";
        }
    }

    // Append the final success message and the distance of the goal vertex to the solution string
    sol += "success " + to_string(adjList[index].distance);
    solution = sol;

    // Return 1 to indicate a successful solution
    return 1;
}

// FillA function fills jug A to its maximum capacity
void Jug::fillA(Vertex& vert) {
    vert.state.first = capacityA;
}

// FillB function fills jug B to its maximum capacity
void Jug::fillB(Vertex& vert) {
    vert.state.second = capacityB;
}

// PourAB function pours water from jug A to jug B until either jug A becomes empty or jug B becomes full
void Jug::pourAB(Vertex& vert) {
    // Loop until first jug is empty or second jug is full 
    while (vert.state.first != 0 && vert.state.second != capacityB) {
        vert.state.first--;
        vert.state.second++;
    }
}

// PourBA function pours water from jug B to jug A until either jug B becomes empty or jug A becomes full
void Jug::pourBA(Vertex& vert) {
    // Loop until second jug is empty or first jug is full 
    while (vert.state.second != 0 && vert.state.first != capacityA) {
        vert.state.second--;
        vert.state.first++;
    }
}

// EmptyA function empties jug A
void Jug::emptyA(Vertex& vert) {
    vert.state.first = 0;
}

// EmptyB function empties jug B
void Jug::emptyB(Vertex& vert) {
    vert.state.second = 0;
}

