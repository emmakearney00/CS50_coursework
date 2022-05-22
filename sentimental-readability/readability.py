from cs50 import get_string

def main():
    #get text input from user
    text = get_string("Input text: ")

    #calculate number of words, sentences, letters in input
    words = 0
    sentences = 0
    letters = 0
    for character in range(len(text)):
        if text[character] == ' ':
            words = words + 1
        if text[character] == '.' or text[character] == '!' or text[character] == '?':
            sentences = sentences + 1
        if (ord(text[character]) >= ord('a') and ord(text[character]) <= ord('z')) or (ord(text[character]) >= ord('A') and ord(text[character]) <= ord('Z')):
            letters = letters + 1

    #Coleman Laiu index
    L = letters / (words + 1) * 100
    S = sentences / (words + 1) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


main()

