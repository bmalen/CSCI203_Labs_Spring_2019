/*
Exercise 6
Ben Malen
bm365

This program demonstrates the Karp-Rabin string search algorithm.
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//define the number of chars in the input alphabet d (e.g. 256)
int numChars = 256;
//define a suitable prime number q (e.g. 101)
int primeNumber = 101;

// Rolling hash function: Calculates hash value for next substring
int roll(int ht, int c1, int c2, int h) {
    // Remove leading char and add trailing char to hash value
    ht = (numChars * (ht - c1 * h) + c2) % primeNumber;
    if (ht < 0)
        ht += primeNumber;
    return ht;
}

// pow with mod so it doesn't overflow
int pow(int numChars, int e) {
    int p = 1;
    for (int i = 0; i < e; ++i)
        p = (p * numChars) % primeNumber;
    return p;
}

// returns rolling hash key of str
int rHash(string str, int len) {
    int h = 0;
    for (int i = 0; i < len; ++i)
        h = ((numChars * h) + str[i]) % primeNumber;
    return h;
}

int main() {
    // string filename;
    // cout << "Enter file name: ";
    // cin >> filename;
    ifstream fin; // open the file
    // fin.open(filename.c_str());
    fin.open("ex6.txt");
    if (!fin) {
        cerr << "Could not open file." << endl;
        return -1;
    }
    string text;
    string searchStr;
    fin >> text;
    fin >> searchStr;
    // close the file
    fin.close();
    int textLen = text.length();
    int searchStrLen = searchStr.length();
    int hashFactor = pow(numChars, searchStrLen - 1);
    int hash_s = rHash(searchStr, searchStrLen);
    int hash_t = rHash(text, searchStrLen);
    for (int i = 0; i < textLen - searchStrLen; ++i) {
        if (hash_s == hash_t) {
            if (text.substr(i, searchStrLen) == searchStr) // confirm in case of collision
                cout << "String found at location: " << i << endl;
        }
        // call next rolling hash key
        hash_t = roll(hash_t, text[i], text[i + searchStrLen], hashFactor);
    }
    return 0;
}
