d = 256  # d is the number of characters in the input alphabet

def search(pattern, text, q):
    M = len(pattern)
    N = len(text)
    h = pow(d, M-1, q)  # The value of h would be "pow(d, M-1)%q"
    p = 0  # hash value for pattern
    t = 0  # hash value for text

    # Calculate the hash value of pattern and the first window of text
    for i in range(M):
        p = (d * p + ord(pattern[i])) % q
        t = (d * t + ord(text[i])) % q

    # Slide the pattern over text one by one
    for i in range(N - M + 1):
        # Check the hash values of current window of text and pattern.
        # If the hash values match then only check for characters one by one
        if p == t:
            # Check for characters one by one
            for j in range(M):
                if text[i + j] != pattern[j]:
                    break
            else:
                # If pattern is present at the current index
                print("Pattern found at index", i)

        # Calculate hash value for next window of text: Remove leading digit,
        # add trailing digit
        if i < N - M:
            t = (d * (t - ord(text[i]) * h) + ord(text[i + M])) % q

# Main function
def main():
    filename = "input.txt"
    try:
        with open(filename, 'r') as inputFile:
            txt, pat, q = inputFile.read().splitlines()
            print("Text:", txt)
            print("Pattern:", pat)
            print("Prime number q:", q)
            print()

            # Call the search function
            search(pat, txt, int(q))
    except FileNotFoundError:
        print("Unable to open file.")

if __name__ == "__main__":
    main()
