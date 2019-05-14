// ----------------- Dijkstra's Algorithm ----------------------
// Daria Sykuleva 
// Date created: February 3, 2019
// Date last modified: January 17, 2019
// -------------------------------------------------------------
// Purpose: This class implements the Dijkstra's Algorithm
// -------------------------------------------------------------

#include "nodedata.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>  // for the output formatting

#ifndef DIJKSTRA_GRAPHM_H
#define DIJKSTRA_GRAPHM_H

#endif //DIJKSTRA_GRAPHM_H

using namespace std;

#define INFINITY 9999999

struct TableType {
    bool visited;          // whether node has been visited
    int dist;              // shortest distance from source known so far
    int path;              // previous node in path of min dist
};

class GraphM {
public:
    GraphM();
    ~GraphM();
    void buildGraph(ifstream&);
    void insertEdge(int, int, int);
    void removeEdge(int, int);
    void findShortestPath();
    int findV(int);
    void displayAll();
    void display(int, int);

private:
    static const int MAXNODES = 101;
    NodeData data[MAXNODES];              // data for graph nodes
    int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix
    int size;                             // number of nodes in the graph
    TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path

    void printPath(int, int);
    void printNames(int, int);
};

