import sys

def main():
    # Check for correct number of args
    if len(sys.argv) != 2:
        print("Usage: red.py file.txt")
        sys.exit(1)

    filename = sys.argv[1]
    file = open(filename, "r")
    text = file.read()

    counter = 0
    for i in text:
        if i == "#":
            counter+=1
    print(counter)

main()