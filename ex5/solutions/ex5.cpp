/*
Exercise 5
Ben Malen
bm365

This program demonstrates hashing.
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node {
    int item;
    Node* next;
};

Node* hashTable[100];
int emptyCount = 0;
int longestChain = 0;
int chainCount = 0;
int nCollisions = 0;

// Insert a new node into the hash table
void insertNode(int key, int value) {
    Node* newNode = new Node();
    newNode->item = value;
    newNode->next = NULL;
    if (hashTable[key] == NULL)
        hashTable[key] = newNode;
    else {
        Node* currentNode = hashTable[key];
        while (currentNode->next != NULL)
            currentNode = currentNode->next;
        currentNode->next = newNode;
    }
}

// Generate a hash from the value to use as a key
int hashFunction(int value) {
    return value % 100;
}

// Recursively visit each node in the chain
void visit(Node* node) {
    ++chainCount;
    cout << "----" << chainCount << ": " << node->item << endl;
    if (node->next != NULL) {
        ++nCollisions;
        visit(node->next);
    }
    delete node; // we're done with the node
}

int main() {
    //string filename;
    //cout << "Enter file name: ";
    //cin >> filename;
    ifstream fin; // open the file
    //fin.open(filename.c_str());
    fin.open("ex5.txt");
    if (!fin) {
        cerr << "Could not open file." << endl;
        return -1;
    }
    // Initialize hash table
    for (int i = 0; i < 100; ++i)
        hashTable[i] = NULL;
    // Read values from file and insert them into the hash table
    int item;
    while (fin >> item)
        insertNode(hashFunction(item), item);
    // close the file
    fin.close();
    // Visit each node
    for (int i = 0; i < 100; ++i) {
        if (hashTable[i] == NULL) {
            ++emptyCount;
            continue;
        }
        chainCount = 0; // reset the chain count

        cout << i << ": " << endl;
        visit(hashTable[i]);
        if (chainCount > longestChain)
            longestChain = chainCount;
    }
    cout << "Empty entries: " << emptyCount
         << "\nCollisions: " << nCollisions
         << "\nLength of longest chain: " << longestChain << endl;
    return 0;
}
