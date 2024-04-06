#include <stdio.h>
#include <string.h>
#include <limits.h>
#define d 256  // d is the number of characters in the input alphabet

void search(char pattern[], char text[], int q) {
    int M = strlen(pattern);
    int N = strlen(text);
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
                printf("Pattern found at index %d \n", i);
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
    FILE *inputFile;
    char txt[1000], pat[1000];
    int q; // Initialize q to maximum integer value
    char filename[] = "input.txt";

    inputFile = fopen(filename, "r");
    if (inputFile != NULL) {
        // Read the text and pattern from the file
        if (fscanf(inputFile, "%s\n%s\n%d", txt, pat,&q) == 3) {
            printf("Text: %s\n", txt);
            printf("Pattern: %s\n", pat);
            printf("Prime number q: %d\n", q);
            printf("\n");

            // Call the search function
            search(pat, txt, q);
        } else {
            printf("Error reading input values from file.\n");
        }
        
        fclose(inputFile);
    } else {
        printf("Unable to open file.\n");
    }

    return 0;
}
