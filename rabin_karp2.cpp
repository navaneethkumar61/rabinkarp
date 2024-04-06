#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

#define d 256  // d is the number of characters in the input alphabet

void search(const string& pattern, const string& text, int q) {
    int M = pattern.length();
    int N = text.length();
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for text
    int h = 1;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and the first window of text
    for (i = 0; i < M; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++) {
        // Check the hash values of current window of text and pattern.
        // If the hash values match then only check for characters one by one
        if (p == t) {
            // Check for characters one by one
            for (j = 0; j < M; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }

            // If pattern is present at the current index
            if (j == M)
                cout << "Pattern found at index " << i << endl;
        }

        // Calculate hash value for next window of text: Remove leading digit,
        // add trailing digit
        if (i < N - M) {
            t = (d * (t - text[i] * h) + text[i + M]) % q;

            // We might get negative value of t, converting it to positive
            if (t < 0)
                t = (t + q);
        }
    }
}

int main() {
    ifstream inputFile;
    string txt, pat;
    int q; // Initialize q to maximum integer value
    //string filename = "input.txt";

    inputFile.open("input.txt");
    if (inputFile.is_open()) {
        // Read the text and pattern from the file
        inputFile >> txt >> pat >> q; // Attempt to read values directly

        // Check if the reading operation is successful
        if (!inputFile.fail()) {
            cout << "Text: " << txt << endl;
            cout << "Pattern: " << pat << endl;
            cout << "Prime number q: " << q << endl;
            cout << endl;

            // Call the search function
            search(pat, txt, q);
        } else {
            cout << "Error reading input values from file." << endl;
        }
        
        inputFile.close();
    } else {
        cout << "Unable to open file." << endl;
    }

    return 0;
}

