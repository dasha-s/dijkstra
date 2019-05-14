// ----------------- Dijkstra's Algorithm ----------------------
// Daria Sykuleva
// Date created: February 3, 2019
// Date last modified: January 17, 2019
// -------------------------------------------------------------
// Purpose: This class implements the Dijkstra's Algorithm
// -------------------------------------------------------------
// NOTE: The function "stoi" that I used to read the first int
// from the file is not recognized when I compile with "g++ -o ..."
// It works with newer compilers, such as the command
// -std=c++11
// -------------------------------------------------------------

#include "graphm.h"

//default constructor
GraphM::GraphM() {
    //initialize everything to nulls
    size = 0;
    for (int i = 0; i < MAXNODES; i++) {
        for (int j = 0; j < MAXNODES; j++) {
            T[i][j].visited = false;
            T[i][j].path = 0;

            T[i][j].dist = INFINITY;
            C[i][j] = INFINITY;
        }
    }
}

GraphM::~GraphM() {}

// -------------------------------------------------------------
//builds up graph node information and adjacency matrix of edges
// between each node reading from a data file.
// -------------------------------------------------------------
void GraphM::buildGraph(ifstream &file) {
    string line;
    if (!getline(file, line)) {   //if cannot get the file
        return;
    }
    //read the first line
    size = stoi(line);       //initialize the first line to size
    for (int i = 1; i <= size; i++) {
        string s;
        getline(file, s);
        NodeData nd(s);      //to use operator=
        data[i] = nd;
    }
    for (;;) {               //read lines until reach 0
        int x, y, distance;  //store the numbers from the input file
        getline(file, line);
        istringstream iss(line);
        iss >> x;
        iss >> y;
        iss >> distance;
        if (x == 0) {
            break;
        }
        C[x][y] = distance;
    }
}

// -------------------------------------------------------------
//insert an edge into graph between two given nodes
// -------------------------------------------------------------
void GraphM::insertEdge(int x, int y, int distance) {
    C[x][y] = distance;
}

// -------------------------------------------------------------
// remove an edge between two given nodes
// -------------------------------------------------------------
void GraphM::removeEdge(int x, int y) {
    C[x][y] = INFINITY;
}

// -------------------------------------------------------------
// find the shortest path between every node to every other node
// in the graph, i.e., TableType T is updated with shortest path
// information
// -------------------------------------------------------------
void GraphM::findShortestPath() {
    for (int source = 1; source <= size; source++) {
        T[source][source].dist = 0;
        // finds the shortest distance from source to all other nodes
        for (int i = 1; i<= size; i++) {
            int v = findV(source);       //not visited, shortest distance at this point
            if (v == INFINITY) {   //if findV doesn't find anything
                break;
            }
            T[source][v].visited = true;      // mark v visited
            for (int j = 1; j <= size; j++) {
                if (C[v][j] < INFINITY && !T[source][j].visited) {
                    if (T[source][v].dist + C[v][j] < T[source][j].dist) {
                        T[source][j].dist = T[source][v].dist + C[v][j];
                        T[source][j].path = v;     //to record shortest path from node to node
                    }
                }
            }
        }
    }
}

// -------------------------------------------------------------
//finds the shortest distance between nodes
// -------------------------------------------------------------
int GraphM::findV(int src) {
    int v = INFINITY;
    for (int i = 1; i <= size; i++) {
        if (!T[src][i].visited && (v == INFINITY || T[src][i].dist < T[src][v].dist)) {
            v = i;
        }
    }
    return v;
}

// -------------------------------------------------------------
// uses couts to demonstrate that the algorithm works properly
// -------------------------------------------------------------
void GraphM::displayAll() {
    cout << "Description" << setw(15) <<  "From node" << setw(15) << "to node "
        << setw(15) << "Dijkstra's" << setw(15) << "Path " << endl;
    for (int i = 1; i <= size; i++) {
        cout << data[i];
        cout << endl;
        for (int j = 1; j <= size; j++) {
            if (i == j) {
                continue;    //skip an iteration
            }
            if (T[i][j].dist != INFINITY) {    //if it's not null
                cout << setw(26) << i << setw(15) << j
                     << setw(15) << T[i][j].dist << setw(15);
                printPath(i, j);
                cout << endl;
            } else {
                cout << setw(26) << i << setw(15) << j
                     << setw(15) << "---" << endl;
            }
        }
    }
}

// -------------------------------------------------------------
// prints the path to the node
// -------------------------------------------------------------
void GraphM::printPath(int x, int y) {
    if (T[x][y].path != 0) {
        printPath(x, T[x][y].path);   //recursion first to print from the back
    }
    cout << y << " ";
}

// -------------------------------------------------------------
// uses couts to display the shortest distance with path info
// between the fromNode to toNode.
// -------------------------------------------------------------
void GraphM::display(int i, int j) {
    if (T[i][j].dist != INFINITY) {    //if it's not null
        cout << i << setw(15) << j
             << setw(15) << T[i][j].dist << setw(15);
        printPath(i, j);
        cout << endl;
        printNames(i, j);
    } else {
        cout << i << setw(15) << j
             << setw(15) << "---" << endl;
    }
}

// -------------------------------------------------------------
// helper function to print the names for the numbers
// -------------------------------------------------------------
void GraphM::printNames(int x, int y) {
    if (T[x][y].path != 0) {
        printNames(x, T[x][y].path);
    }
    cout << data[y] << endl;
}
