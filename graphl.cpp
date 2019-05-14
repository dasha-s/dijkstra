// ------------- Depth First Search Algorithm ------------------
// Daria Sykuleva 
// Date created: February 3, 2019
// Date last modified: January 19, 2019
// -------------------------------------------------------------
// Purpose: This class implements the Depth First Search
// Algorithm
// -------------------------------------------------------------

#include "graphl.h"

GraphL::GraphL() {
    size = 0;
    for (int i = 0; i < MAXNODES; i++) {  //initialize everything to 0, and make all not visited
        T[i].visited = false;
        T[i].data = 0;
        T[i].edgeHead = 0;
    }
}

GraphL::~GraphL() {  //delete all the pointers
    for (int i = 1; i <= size; i++) {
        NodeData* current = T[i].data;
        delete current;
        EdgeNode* en = T[i].edgeHead;
        while (en != NULL) {
            EdgeNode* curEn = en;
            en = en->nextEdge;
            delete curEn;
        }
    }
}

// -------------------------------------------------------------
// builds up graph node information and adjacency list of edges
// between each node reading from a data file.
// -------------------------------------------------------------
void GraphL::buildGraph(ifstream &file) {
    string line;
    if (!getline(file, line)) {
        return;
    }
    //read the first line
    size = stoi(line);       //initialize the first line to size
    for (int i = 1; i <= size; i++) {
        string s;
        getline(file, s);
        T[i].data = new NodeData(s);
    }
    for (;;) {               //read lines until reach 0
        int x, y;  //store the numbers from the input file
        getline(file, line);
        istringstream iss(line);
        iss >> x;
        iss >> y;
        if (x == 0) {
            break;
        }
        EdgeNode* head = T[x].edgeHead;
        EdgeNode* created = new EdgeNode();
        created->adjGraphNode = y;
        created->nextEdge = head;
        T[x].edgeHead = created;
    }
}

// -------------------------------------------------------------
// Displays each node information and edge in the graph
// -------------------------------------------------------------
void GraphL::displayGraph() {
    cout << "Graph:" << endl;
    for (int i = 1; i <= size; i++) {
        cout << "Node" << i << setw(51) <<  *(T[i].data) << endl;   //* - to print an actual value, not an address
        EdgeNode* curEdge = T[i].edgeHead;
        while (curEdge != NULL) {
            cout << setw(7) << "edge" << setw(5) << i << setw(5) << curEdge->adjGraphNode << endl;
            curEdge = curEdge->nextEdge;
        }
    }
}

// -------------------------------------------------------------
// Makes a depth-first search and displays each node in depth-first
// order
// -------------------------------------------------------------
void GraphL::depthFirstSearch() {
    cout << "Depth First Ordering: ";
    for (int i = 1; i <= size; i ++) {
        if (!T[i].visited) {
            cout << i << " ";
            visitNode(T[i]);
        }
    }
    cout << endl;
}

// -------------------------------------------------------------
// helper funtion for the DFS
// -------------------------------------------------------------
void GraphL::visitNode(GraphNode &gn) {
    gn.visited = true;
    EdgeNode* curEdge = gn.edgeHead;
    while (curEdge != NULL) {
        if (!T[curEdge->adjGraphNode].visited) {
            cout << curEdge->adjGraphNode << " ";
            visitNode(T[curEdge->adjGraphNode]);
        }
        curEdge = curEdge->nextEdge;
    }
}
