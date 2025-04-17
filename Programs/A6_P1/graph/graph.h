#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <iomanip>
#include <string>
#include "sqll.h"  // for our traversal algorithms

using namespace std;

struct edge
{
    struct vertex* dest;
    edge* eNext;
    int weight;
};

struct vertex
{
    char data;
    vertex* vNext;
    edge* aHead;

    // for traversal
    short visited;
};

// implementing both adj list and adj matrix for an undirected weighed graph
class Graph 
{
    private:
        vertex* vertices; // list of vertices
        int** adjMatrix; 
        bool* visited;
        int maxVertices;
        int numVertices;

    public:
        Graph(int maxV);
        ~Graph();

        // core operations
        void addVertex(char data);
        void addEdge(char src, char dest, int weight);
        void removeVertex(char data);
        void removeEdge(char src, char dest);  // complete this

        // display
        void displayAdjList();
        void displayAdjMatrix();

        // traversal/search algorithms
        void bfsL(char start);
        void bfsM(char start); // complete this
        void dfsL(char start); // complete this
        void dfsM(char start); // complete this

        // ---------------- Extra Credits - Pick one of the two ----------------------------- 
        // Detect cycle with DFS - Option 1
        // bool detectCycleDFS();

        // Print Connected Components - Option 2
        void connectedComponents();
};

#endif