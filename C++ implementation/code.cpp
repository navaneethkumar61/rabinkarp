#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;
#define d 256  
void search(const string& pattern, const string& text, int q) 
{
    int M = pattern.length();
    int N = text.length();
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
                cout << "Pattern found at index " << i << endl;
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
    ifstream inputFile;
    string txt, pat;
    int num_test_cases, i;
    int q; 
    inputFile.open("input.txt");
    inputFile >> num_test_cases;
    if (inputFile.is_open()) 
	{
		for(i=0;i<num_test_cases;i++)
		{
        	inputFile >> txt >> pat >> q;  
        	if (!inputFile.fail()) 
			{
            	cout << "Text: " << txt << endl;
            	cout << "Pattern: " << pat << endl;
            	cout << "Prime number q: " << q << endl;
            	cout << endl;
            	search(pat, txt, q);
            	cout << endl;
            }
			else 
			{
            	cout << "Error reading input values from file." << endl;
        	}
        }
    } 
	else 
	{
        cout << "Unable to open file." << endl;
    }
    return 0;
}
