/*
Exercise 3
Ben Malen
bm365
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    const int MAX_SIZE = 100;
    int data[MAX_SIZE];
    int fward[MAX_SIZE];
    int bward[MAX_SIZE];
    int validCount = 0;

    // Read in filename
    // string filename;
    // cout << "Enter file name: ";
    // cin >> filename;

    ifstream fin; // open the file
    // fin.open(filename.c_str());
    fin.open("ex3.txt");

    if (!fin) {
        cerr << "Could not open file." << endl;
        return -1;
    }

    // Read in what, where
    int what, where;
    while (true) {
        fin >> what >> where;

        if (what == -1)
            break;

        // Set what, where
        data[where] = what;
        fward[validCount] = where;
        bward[where] = validCount;

        ++validCount;
    }

    // Read in probe
    int probe;
    while (true) {
        fin >> probe;

        if (probe == -1)
            break;

        // Check if data[probe] has been initialised
        if (bward[probe] >= 0 && bward[probe] <= validCount && fward[bward[probe]] == probe)
            cout << "Position " << probe << " has been initialised to " << data[probe] << "." << endl;
        else
            cout << "Position " << probe << " has not been initialised." << endl;
    }

    // close the file
    fin.close();

    return 0;
}
