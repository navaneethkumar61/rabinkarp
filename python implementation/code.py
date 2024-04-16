d = 256

def search(pattern, text, q):
    M = len(pattern)
    N = len(text)
    h = pow(d, M-1, q)
    p = 0
    t = 0
    for i in range(M):
        p = (d * p + ord(pattern[i])) % q
        t = (d * t + ord(text[i])) % q
    for i in range(N - M + 1):
        if p == t:
            for j in range(M):
                if text[i + j] != pattern[j]:
                    break
            else:
                print("Pattern found at index", i)
        if i < N - M:
            t = (d * (t - ord(text[i]) * h) + ord(text[i + M])) % q

def main():
    filename = "input.txt"
    try:
        with open(filename, 'r') as inputFile:
            num_test_cases = int(inputFile.readline().strip())
            print("Number of test cases:", num_test_cases)
            for _ in range(num_test_cases):
                line = inputFile.readline().split()
                if len(line) == 3:
                    txt, pat, q = line
                    print("Text:", txt)
                    print("Pattern:", pat)
                    print("Prime number q:", q)
                    print()
                    search(pat, txt, int(q))
                    print()
                else:
                    print("Invalid input format in file for test case.")
    except FileNotFoundError:
        print("Unable to open file.")

if __name__ == "__main__":
    main()
