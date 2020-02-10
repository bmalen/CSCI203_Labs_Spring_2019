/*
Exercise 2
Ben Malen
bm365

This program demonstrates heaps.

Notes:
Heap - a balanced binary tree with the parents being bigger than its children (max-heap), or smaller (min-heap).
The children are not necessarily in order, unlike a BST (Binary Search Tree) which is ordered.

14, 31, 27, 38, 37
963, 955, 957, 911, 940

*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_ELEMENTS = 200;
int heap[MAX_ELEMENTS]; // the heap
int total = 0; // total number of elements in the heap

// prototypes
void insertElement(int ele); // insert
void makeHeap(int* arr, int n);
void print();
void siftUp(int* arr, int i);
void siftDown(int* arr, int n, int i);
void mySwap(int& x, int& y);

int main() {
    // display a prompt for the file name
    // string filename;
    // cout << "Enter file name: ";

    // read in the file name
    // cin >> filename;

    // try to open the file
    ifstream fin;
    // fin.open(filename.c_str());
    fin.open("ex2.txt");

    // if the file fails to open, print an error message on the screen and exit
    if (!fin) {
        cerr << "Could not open file." << endl;
        return -1;
    }

    // while we can read an int from the file
    int number;
    while (fin >> number) {
        // insert the int into the array (to make a min heap)
        insertElement(number);
    }

    // close the file
    fin.close();

    // print the first 5 elements of the heap
    print();

    // makeHeap() (to make a max heap)
    makeHeap(heap, total);

    // print the first 5 elements of the heap
    print();

    return 0;
}

// insert elements into the heap and perform siftUp on each element inserted
void insertElement(int ele) {
    if (total >= MAX_ELEMENTS) {
        cerr << "Heap is full." << endl;
        return;
    }

    heap[total++] = ele;
    siftUp(heap, total - 1);
}

// makeHeap starts at the level of the parents of the last children in the binary tree
void makeHeap(int* arr, int n) {
    for (int i = (n - 1) / 2; i >= 0; --i)
        siftDown(heap, n, i);
}

// print the first 5 elements of the heap
void print() {
    for (int i = 0; i < 5; ++i)
        cout << heap[i] << (i < 4 ? ", " : "");

    cout << endl;
}

void mySwap(int& x, int& y) {
    int temp;
    temp = x;
    x = y;
    y = temp;
}

// Moves the element up into the correct position.
// This example produce a min-heap (the element at the beginning will be the smallest).
// heap[0..n-1]
// 12, 7, 6, 10, 8, 20 = 6, 8, 7, 12, 10, 20
void siftUp(int* arr, int i) {
    int child = i; // child element we are sifting up

    if (child == 0)   // then the element is the top parent
        return;

    // integer division to find the parent
    int parent = (child - 1) / 2;

    if (heap[parent] < heap[child]) // min heap
        return;
    else {
        mySwap(heap[child], heap[parent]); // put smallest in parent
        siftUp(heap, parent); // and siftUp parent
    }
}

// Moves the element down into the correct position.
// This example produce a max-heap (the element at the beginning will be the biggest).
// heap[0..n-1]
// 6, 8, 7, 12, 10, 20 = 20, 12, 7, 8, 10, 6
void siftDown(int* arr, int n, int i) {
    int parent = i; // parent element we are sifting down
    int leftChild = i * 2 + 1; // index of the left child (but does it exist?)

    if (leftChild < n) { // then the left child exists
        int biggestChild = leftChild;
        int rightChild = leftChild + 1; // index of the right child (but does it exist?)

        if (rightChild < n && heap[biggestChild] < heap[rightChild]) // then the right child exists and it is the biggest child
            biggestChild = rightChild;

        // if the biggest child is bigger than the parent, then swap them and siftDown
        if (heap[parent] < heap[biggestChild]) {
            mySwap(heap[parent], heap[biggestChild]);
            siftDown(heap, n, biggestChild);
        }
    }
}
