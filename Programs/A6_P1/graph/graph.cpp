#include "graph.h"

Graph::Graph(int maxV)
{
    maxVertices = maxV;
    numVertices = 0;
    vertices = nullptr;

    adjMatrix = new int*[maxVertices]; // pointer of rows
    // each int* stores a row
    for(int i = 0; i < maxVertices; i++)
    {
        adjMatrix[i] = new int[maxVertices]; // create a new row (array of ints)
        for(int j = 0; j < maxVertices; j++)
            adjMatrix[i][j] = 0;
    }

    visited = new bool[maxVertices] {false};    
}

Graph::~Graph()
{
    delete[] visited;

    for(int i = 0; i < maxVertices; i++)
    {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;

    vertex* tempVertex;
    while (vertices) 
    {
        edge* tempEdge;
        // free the memory of the neighbor list of that vertex
        while(vertices->aHead)
        {
            tempEdge = vertices->aHead;
            vertices->aHead = vertices->aHead->eNext;
            delete tempEdge;
        }
        // free that vertex itself
        tempVertex = vertices;
        vertices = vertices->vNext;
        delete tempVertex;

    }
}

void Graph::addVertex(char data)
{
    if(numVertices >= maxVertices)
    {
        cout << "Max number of vertices reached!" << endl;
        return;
    }

    vertex* newVertex = new vertex;
    newVertex->data = data;
    newVertex->vNext = vertices;
    newVertex->aHead = nullptr;
    newVertex->visited = 0;
    vertices = newVertex;

    numVertices++;
}

void Graph::addEdge(char src, char dest, int weight)
{
    vertex* srcVertex = vertices;
    vertex* destVertex = vertices;

    // find src and dest vertices
    while(srcVertex && srcVertex->data != src)
    {
        srcVertex = srcVertex->vNext;
    }
    while(destVertex && destVertex->data != dest)
    {
        destVertex = destVertex->vNext;
    }

    if(!srcVertex || !destVertex)
    {
        cout << "Vertices not found - can't add an edge" << endl;
        return;
    }

    // Adj list - undirected graph
    edge* newEdge = new edge;
    newEdge->dest = destVertex;
    newEdge->weight = weight;
    newEdge->eNext = srcVertex->aHead;
    srcVertex->aHead = newEdge;

    // Since undirected, add the reverse edge as well
    newEdge = new edge;
    newEdge->dest = srcVertex;
    newEdge->weight = weight;
    newEdge->eNext = destVertex->aHead;
    destVertex->aHead = newEdge;

    // Adj Matrix
    int srcIndex = srcVertex->data - 'A';
    int destIndex = destVertex->data - 'A';
    adjMatrix[srcIndex][destIndex] = weight;
    adjMatrix[destIndex][srcIndex] = weight;
}

void Graph::removeVertex(char data)
{
    // find the vertex
    vertex* temp = vertices;
    vertex* prev = nullptr;

    while(temp && temp->data != data)
    {
        prev = temp;
        temp = temp->vNext;
    }
    
    if(!temp)
    {
        cout << "Vertex not found - can't remove" << endl;
        return;
    }

    // remove that vertex from the adj list of all other vertices
    for(vertex* v = vertices; v != nullptr; v = v->vNext)
    {
        edge* e = v->aHead;
        edge* prevEdge = nullptr;
        while(e)
        {
            if(e->dest->data == data)
            {
                if(prevEdge)
                    prevEdge->eNext = e->eNext;
                else
                    v->aHead = e->eNext;
                delete e;
                break;
            }
            prevEdge = e;
            e = e->eNext;
        }
    }

    // remove the vertex
    if(prev)
        prev->vNext = temp->vNext;
    else
        vertices = temp->vNext;

    delete temp;

    // Adj matrix
    int index = temp->data - 'A';
    for(int i = 0; i < maxVertices; i++)
    {
        adjMatrix[i][index] = 0;
        adjMatrix[index][i] = 0;
    }

    numVertices--;
}

void Graph::displayAdjList()
{
    for(vertex* v = vertices; v != nullptr; v = v->vNext)
    {
        cout << v->data << " -> ";
        for(edge* e = v->aHead; e != nullptr; e = e->eNext)
        {
            cout << e->dest->data << " (" << e->weight << ") -> ";
        }
        cout << "null" << endl;
    }
    cout << endl;
}

void Graph::displayAdjMatrix()
{
    cout << "     ";
    for(int i = 0; i < maxVertices; i++)
    {
        cout << setw(3) << char('A' + i) << " "; // column headers
    }
    cout << endl;
    cout << "   ";
    
    for(int i = 0; i < maxVertices; i++)
    {
        cout << "-----";
    }
    cout << endl;

    for(int i = 0; i < maxVertices; i++)
    {
        cout << setw(3) << char('A' + i) << " |"; // row header
        for(int j = 0; j < maxVertices; j++)
        {
            cout << setw(3) << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::bfsL(char start)
{
    for(int i = 0; i < maxVertices; i++)
        visited[i] = false;

    // find the start vertex
    vertex* startVertex = vertices;
    while(startVertex && startVertex->data != start)
        startVertex = startVertex->vNext;

    if(!startVertex)
    {
        cout << "Start vertex not found - can't traverse" << endl;
        return;
    }

    // initialize queue for bfs
    node* queue = nullptr;
    enqueue(queue, start); 
    visited[startVertex->data - 'A'] = true;

    cout << "BFS traversal Adjacency List : ";
    while (queue)
    {
        // dequeue the front
        char currentData = queue->data;
        dequeue(queue);
        cout << currentData << " ";

        // find the vertex corresponding to the dequeued element
        vertex* currentVertex = vertices;
        while(currentVertex && currentVertex->data != currentData)
            currentVertex = currentVertex->vNext;

        // add all its neighbors to the queue
        for(edge* e = currentVertex->aHead; e != nullptr; e = e->eNext)
        {
            if(!visited[e->dest->data - 'A'])
            {
                enqueue(queue, e->dest->data);
                visited[e->dest->data - 'A'] = true;
            }
        }
    }
    cout << endl; 
}

// Klink Task 1 Start
// Removes an undirected edge between two vertices in both adjacency list and matrix
void Graph::removeEdge(char src, char dest)
{
    vertex* srcVertex = vertices;
    vertex* destVertex = vertices;

    // Find pointers to source and destination vertices in the vertex list
    while(srcVertex && srcVertex->data != src)
        srcVertex = srcVertex->vNext;

    while(destVertex && destVertex->data != dest)
        destVertex = destVertex->vNext;

    // If either vertex is not found, report and exit
    if(!srcVertex || !destVertex)
    {
        cout << "One or both vertices not found: " << src << ", " << dest << endl;
        return;
    }

    // Remove the edge from src's adjacency list
    bool removed = false;
    edge* prevEdge = nullptr;
    edge* e = srcVertex->aHead;
    while(e)
    {
        if(e->dest == destVertex)
        {
            if(prevEdge)
                prevEdge->eNext = e->eNext; // Remove middle or end edge
            else
                srcVertex->aHead = e->eNext; // Remove first edge
            delete e;
            removed = true;
            break;
        }
        prevEdge = e;
        e = e->eNext;
    }

    // Remove the edge from dest's adjacency list (since undirected)
    prevEdge = nullptr;
    e = destVertex->aHead;
    while(e)
    {
        if(e->dest == srcVertex)
        {
            if(prevEdge)
                prevEdge->eNext = e->eNext;
            else
                destVertex->aHead = e->eNext;
            delete e;
            break;
        }
        prevEdge = e;
        e = e->eNext;
    }

    // Update the adjacency matrix by zeroing both directions
    int srcIndex = src - 'A';
    int destIndex = dest - 'A';
    adjMatrix[srcIndex][destIndex] = 0;
    adjMatrix[destIndex][srcIndex] = 0;

    // Report success or failure
    if (removed)
        cout << "Edge removed between " << src << " and " << dest << endl;
    else
        cout << "Edge NOT found between " << src << " and " << dest << endl;
}
// Klink Task 1 End

// Klink Task 2 Start
// Performs BFS traversal using the adjacency matrix
void Graph::bfsM(char start)
{
    // Reset visited array
    for(int i = 0; i < maxVertices; i++)
        visited[i] = false;

    int startIndex = start - 'A';
    // Check for valid start vertex
    if(startIndex < 0 || startIndex >= maxVertices)
    {
        cout << "Start vertex out of range - can't traverse" << endl;
        return;
    }

    // Queue setup for BFS
    node* queue = nullptr;
    enqueue(queue, start);
    visited[startIndex] = true;

    cout << "BFS traversal Adjacency Matrix : ";
    while(queue)
    {
        char current = queue->data;
        dequeue(queue);
        cout << current << " ";

        int currentIndex = current - 'A';
        // Visit all unvisited adjacent vertices
        for(int i = 0; i < maxVertices; i++)
        {
            if(adjMatrix[currentIndex][i] != 0 && !visited[i])
            {
                enqueue(queue, char('A' + i));
                visited[i] = true;
            }
        }
    }
    cout << endl;
}
//  Klink Task 2 End

//  Klink Task 3 Start
// Recursive DFS helper for adjacency list traversal
void dfsLHelper(vertex* v)
{
    if(!v) return;

    cout << v->data << " ";
    v->visited = 1;

    // Recursively visit all unvisited adjacent vertices
    for(edge* e = v->aHead; e != nullptr; e = e->eNext)
    {
        if(e->dest->visited == 0)
        {
            dfsLHelper(e->dest);
        }
    }
}

// DFS traversal starting from a given vertex using adjacency list
void Graph::dfsL(char start)
{
    // Reset visited flags
    for(vertex* v = vertices; v != nullptr; v = v->vNext)
        v->visited = 0;

    // Find starting vertex
    vertex* startVertex = vertices;
    while(startVertex && startVertex->data != start)
        startVertex = startVertex->vNext;

    if(!startVertex)
    {
        cout << "Start vertex not found - can't traverse" << endl;
        return;
    }

    cout << "DFS traversal Adjacency List : ";
    dfsLHelper(startVertex);
    cout << endl;
}
//  Klink Task 3 End

//  Klink Task 4 Start
// Recursive DFS helper for adjacency matrix traversal
void dfsMHelper(int index, int maxVertices, int** adjMatrix, bool* visited)
{
    cout << char('A' + index) << " ";
    visited[index] = true;

    // Visit all connected and unvisited neighbors
    for(int i = 0; i < maxVertices; i++)
    {
        if(adjMatrix[index][i] != 0 && !visited[i])
        {
            dfsMHelper(i, maxVertices, adjMatrix, visited);
        }
    }
}

// DFS traversal starting from a given vertex using adjacency matrix
void Graph::dfsM(char start)
{
    // Reset visited flags
    for(int i = 0; i < maxVertices; i++)
        visited[i] = false;

    int startIndex = start - 'A';
    if(startIndex < 0 || startIndex >= maxVertices)
    {
        cout << "Start vertex out of range - can't traverse" << endl;
        return;
    }

    cout << "DFS traversal Adjacency Matrix : ";
    dfsMHelper(startIndex, maxVertices, adjMatrix, visited);
    cout << endl;
}
//  Klink Task 4 End

//  Klink Task Extra Start
// Finds and prints all connected components using DFS (Adjacency List)
void Graph::connectedComponents()
{
    // Reset all vertices to unvisited
    for (vertex* v = vertices; v != nullptr; v = v->vNext)
        v->visited = 0;

    cout << "Connected Components:\n";

    // For each unvisited vertex, start a DFS to collect the component
    for (vertex* v = vertices; v != nullptr; v = v->vNext)
    {
        if (v->visited == 0)
        {
            cout << "Component: ";
            dfsLHelper(v); // Use existing DFS to print all reachable vertices
            cout << endl;
        }
    }
}
//  Klink Task Extra End