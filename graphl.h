// ------------- Depth First Search Algorithm ------------------
// Daria Sykuleva 
// Date created: February 3, 2019
// Date last modified: January 17, 2019
// -------------------------------------------------------------
// Purpose: This class implements the Depth First Search
// Algorithm
// -------------------------------------------------------------

#include "nodedata.h"
#include <iomanip>
#include <sstream>
#include <iostream>

#ifndef DIJKSTRA_GRAPHL_H
#define DIJKSTRA_GRAPHL_H

#endif //DIJKSTRA_GRAPHL_H

using namespace std;

#define INFINITY 9999999

struct EdgeNode;      // forward reference for the compiler
struct GraphNode {
    EdgeNode* edgeHead; // head of the list of edges
    NodeData* data;     // data information about each node
    bool visited;
};

struct EdgeNode {
    int adjGraphNode;  // subscript of the adjacent graph node
    EdgeNode* nextEdge;
};

class GraphL {
public:
    GraphL();
    ~GraphL();
    void buildGraph(ifstream&);
    void displayGraph();
    void depthFirstSearch();
    void visitNode(GraphNode&);

private:
    static const int MAXNODES = 101;
    int size;
    GraphNode T[MAXNODES];
    //list<int> *adjList;
};
