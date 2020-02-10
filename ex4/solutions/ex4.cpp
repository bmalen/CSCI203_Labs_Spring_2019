/*
Exercise 4
Ben Malen
bm365

This program demonstrates a BST sort.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // setw
using namespace std;

int counter = 0;

struct Node {
    int item;
    Node* left;
    Node* right;
};

Node* find(int item, Node* node);
void insert(int item, Node* node);
Node* insertFirst(int item);
void visit(Node* node);

int main() {
    // string filename;
    // cout << "Enter file name: ";
    // cin >> filename;
    ifstream fin; // open the file
    // fin.open(filename.c_str());
    fin.open("ex4.txt");
    if (!fin) {
        cerr << "Could not open file." << endl;
        return -1;
    }
    Node* root = NULL;
    int item;
    while (fin >> item) {
        if (root == NULL)
            root = insertFirst(item);
        insert(item, root);
    }
    // close the file
    fin.close();
    // visit and print each item in order
    visit(root);
    cout << endl;
    return 0;
}

// Recursively find item in BST
Node* find(int item, Node* node) {
    if (node == NULL)
        return NULL;
    if (item < node->item)
        find(item, node->left);
    else if (item > node->item)
        find(item, node->right);
    return node;
}

// Insert into BST
void insert(int item, Node* node) {
    Node* next;
    bool isLeft;
    if (item == node->item) // already in the tree
        return;
    if (item < node->item) { // we need to go left
        next = node->left;
        isLeft = true;
    }
    else { // we need to go right
        next = node->right;
        isLeft = false;
    }
    if (next != NULL)
        insert (item, next); // keep trying
    else {
        Node* next = new Node; // make a new node
        // Initialise the contents
        next->item = item;
        next->left = NULL;
        next->right = NULL;
        if (isLeft) // update the parent
            node->left = next;
        else
            node->right = next;
    }
}

// Insert the first node into the BST
Node* insertFirst(int item) {
    Node* first = new Node;
    // Initialise the contents
    first->item = item;
    first->left = NULL;
    first->right = NULL;
    return first;
}

// Recursively visit each node
void visit(Node* node) {
    if (node->left != NULL)
        visit(node->left);
    // Print
    ++counter;
    cout << right << setw(5) << node->item;
    if (counter % 10 == 0)
        cout << endl;
    if (node->right != NULL)
        visit(node->right);
    delete node; // we're done with the node
}
