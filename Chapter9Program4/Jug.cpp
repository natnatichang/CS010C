#include <iostream> 
#include <string>
#include <queue>

#include "Jug.h" 

using namespace std;

// check the consts 

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA)
    : Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA) {}


Jug::~Jug() {

}

int Jug::solve(string& solution) {
    if (!isValidInput()) {
        solution = "";
        return -1;
    }

    queue<Vertex> q;
    Vertex initial(0, 0, "", 0);
    q.push(initial);

    while (!q.empty()) {
        Vertex current = q.front();
        q.pop();

        if (current.B == N) {
            solution = current.step + "success " + to_string(current.cost);
            return 1;
        }

        // Fill jug A
        if (current.A < Ca) {
            int cost = current.cost + cfA;
            Vertex next(Ca, current.B, current.step + "fill A\n", cost);
            q.push(next);
        }

        // Fill jug B
        if (current.B < Cb) {
            int cost = current.cost + cfB;
            Vertex next(current.A, Cb, current.step + "fill B\n", cost);
            q.push(next);
        }

        // Empty jug A
        if (current.A > 0) {
            int cost = current.cost + ceA;
            Vertex next(0, current.B, current.step + "empty A\n", cost);
            q.push(next);
        }

        // Empty jug B
        if (current.B > 0) {
            int cost = current.cost + ceB;
            Vertex next(current.A, 0, current.step + "empty B\n", cost);
            q.push(next);
        }

        // Pour from A to B
        if (current.A > 0 && current.B < Cb) {
            int transfer = min(current.A, Cb - current.B);
            int cost = current.cost + cpAB;
            Vertex next(current.A - transfer, current.B + transfer, current.step + "pour A B\n", cost);
            q.push(next);
        }

        // Pour from B to A
        if (current.B > 0 && current.A < Ca) {
            int transfer = min(current.B, Ca - current.A);
            int cost = current.cost + cpBA;
            Vertex next(current.A + transfer, current.B - transfer, current.step + "pour B A\n", cost);
            q.push(next);
        }
    }

    solution = "";
    return 0;
}

bool Jug::isValidInput() {
    if (Ca <= 0 || Cb <= 0 || N < 0 || cfA < 0 || cfB < 0 || ceA < 0 || ceB < 0 || cpAB < 0 || cpBA < 0) {
        return false;
    }
    if (Ca > Cb || N > Cb || Cb > 1000) {
        return false;
    }
    return true;
}