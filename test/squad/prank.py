import sys

def main():
    if len(sys.argv) < 2 | len(sys.argv) > 7:
        print("Usage: prank.py file1.txt ... file7.txt")
        sys.exit(1)
    txt_files = len(sys.argv) - 1
    for i in range(0, txt_files):
        filename = sys.argv[i+1]
        file = open(filename, "r")
        text = file.read()
        print(text)
main()

