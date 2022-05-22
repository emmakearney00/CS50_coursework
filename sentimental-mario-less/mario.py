from cs50 import get_int


def main():
    while True:
        height = get_int("Height: ")
        if (height > 0) and (height < 9):
            break
    for i in range(height):
        for space in range(height - i - 1):
            print(" ", end="")
        for hash in range(i + 1):
            print("#", end="")
        print()


main()
