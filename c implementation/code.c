#include <stdio.h>
#include <string.h>
#include <limits.h>
#define d 256
void search(char pattern[], char text[], int q) 
{
    int M = strlen(pattern);
    int N = strlen(text);
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;
    for (i = 0; i < M - 1; i++) 
	{
        h = (h * d) % q;
    }
    for (i = 0; i < M; i++) 
	{
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }
    for (i = 0; i <= N - M; i++) 
	{
        if (p == t) 
		{
            for (j = 0; j < M; j++) 
			{
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == M) 
			{
                printf("Pattern found at index %d\n", i);
            }
        }
        if (i < N - M) 
		{
            t = (d * (t - text[i] * h) + text[i + M]) % q;
            if (t < 0)
            {
                t = (t + q);
            }
        }
    }
}
int main() 
{
    FILE *inputFile;
    char txt[1000], pat[1000];
    int q;
    int num_test_cases, i;
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) 
	{
        printf("Unable to open file.\n");
        return 1;
    }
    fscanf(inputFile, "%d", &num_test_cases);
    for (i = 0; i < num_test_cases; i++) 
	{
        fscanf(inputFile, "%s\n%s\n%d\n", txt, pat, &q);
        printf("Text: %s\n", txt);
        printf("Pattern: %s\n", pat);
        printf("Prime number q: %d\n", q);
        printf("\n");
        search(pat, txt, q);
        printf("\n");
    }
    fclose(inputFile);
    return 0;
}
