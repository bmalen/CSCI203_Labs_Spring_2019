/*
Exercise 1
Ben Malen
bm365
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAXWORDS = 20;
string arr[MAXWORDS]; // the stack
int position = -1; // top of the stack

// prototypes
void push(string& line);
string top();
void pop();
bool isEmpty();

int main() {
    // display a prompt for the file name
    // string filename;
    // cout << "Enter file name: ";

    // read in the file name
    // cin >> filename;

    // try to open the file
    ifstream fin;
    // fin.open(filename.c_str());
    fin.open("ex1.txt");

    // if the file fails to open, print an error message on the screen and exit
    if (!fin) {
        cerr << "Could not open file." << endl;
        return -1;
    }

    // read in a word from the file
    string line;
    while (fin >> line) {
        // Push the word onto the stack
        push(line);
    }

    // close the file
    fin.close();

    // while the stack is not empty
    while (!isEmpty()) {
        // display the top stack word on the screen followed by a space
        cout << top() << " ";

        // pop the top value from the stack
        pop();
    }

    cout << endl;
    return 0;
}

void push(string& line) {
    if (position >= (MAXWORDS - 1)) {
        cerr << "Stack is full." << endl;
        return;
    }

    ++position;
    arr[position] = line;
}

string top() {
    if (isEmpty()) {
        cerr << "Stack is empty." << endl;
        return "";
    }

    return arr[position];
}

void pop() {
    if (!isEmpty()) {
        --position;
    }
}

bool isEmpty() {
    return position < 0;
}
