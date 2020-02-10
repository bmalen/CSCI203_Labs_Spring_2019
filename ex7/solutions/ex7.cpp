/*
Exercise 7
Ben Malen
bm365

This program demonstrates a Breadth First Search.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // setw
using namespace std;

const unsigned int MAX = 100;

/*----------------------------------------------------------------------------*/

// FIFO queue
class VertexQueue {
    public:
        VertexQueue() {
            nVertices_ = 0;
            front_ = 0;
            rear_ = MAX - 1;
        }
        bool isFull() { return nVertices_ == MAX; }
        bool isEmpty() { return nVertices_ == 0; }
        void enqueue(unsigned int vertex);
        unsigned int dequeue();
    private:
        unsigned int vertices_[MAX];
        unsigned int nVertices_, front_, rear_;
};

// A new vertex is placed into the rear of the queue.
void VertexQueue::enqueue(unsigned int vertex) {
    if (isFull()) {
        cerr << "MAX exceeded." << endl;
        exit(1);
    }
    rear_ = (rear_ + 1) % MAX; // modular arithmetic so rear_ "wraps around" to zero when it reaches MAX
    vertices_[rear_] = vertex;
    ++nVertices_;
}

// The vertex in the front of the queue is removed.
unsigned int VertexQueue::dequeue() {
    if (isEmpty()) {
        cerr << "VertexQueue is empty." << endl;
        exit(1);
    }
    unsigned int vertex = vertices_[front_];
    front_ = (front_ + 1) % MAX; // modular arithmetic so front_ "wraps around" to zero when it reaches MAX
    --nVertices_;
    return vertex;
}

/*----------------------------------------------------------------------------*/
// Breadth First Search

void BFS(unsigned int startVertex, bool **matrix, unsigned int n) {
    bool visited[n]; // visited vertices
    for (unsigned int i = 0; i < n; ++i)
        visited[i] = false;
    VertexQueue vertexQueue;
    vertexQueue.enqueue(startVertex);
    visited[startVertex] = true;
    while (!vertexQueue.isEmpty()) {
        unsigned int current = vertexQueue.dequeue();
        // for each vertex adjacent to the current vertex
        for (unsigned int i = 0; i < n; ++i) {
            if (matrix[current][i] && !visited[i]) {
                vertexQueue.enqueue(i);
                visited[i] = true;
                cout << current << " " << i << endl;
            }
        }
    }
}

int main() {
    //string filename;
    //cout << "Enter file name: ";
    //cin >> filename;
    ifstream fin; // open the file
    //fin.open(filename.c_str());
    fin.open("ex7.txt");
    if (!fin) {
        cerr << "Could not open file." << endl;
        return -1;
    }
    unsigned int n; // number of vertices in the graph
    fin >> n;
    bool ** matrix = new bool *[n];
    for (unsigned int i = 0; i < n; ++i) {
        matrix[i] = new bool[n];
        for (unsigned int j = 0; j < n; ++j)
            matrix[i][j] = false;
    }
    unsigned int v1, v2;
    while (fin >> v1 >> v2) {
        // bidirectional
        matrix[v1][v2] = true;
        matrix[v2][v1] = true;
    }
//    for (unsigned int i = 0; i < n; ++i) {
//        for (unsigned int j = 0; j < n; ++j)
//            cout << setw(4) << matrix[i][j];
//        cout << endl;
//    }
    fin.close();
    BFS(0, matrix, n);
    // clean up
    for (unsigned int i = 0; i < n; ++i) {
        delete [] matrix[i];
    }
    delete [] matrix;
    return 0;
}
