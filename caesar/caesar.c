#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//function prototypes
bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
    if (argc != 2 || only_digits(argv[1]) == false) //tests for incorrect number of arguments or the command includes non-digits
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        int key = atoi(argv[1]); //converts string digit into integer digit
        string ptext = get_string("plaintext: "); //prompts user for plaintext

        printf("ciphertext: ");

        int n = strlen(ptext);
        for (int i = 0; i < n; i++) //for each character in string from user
        {
            char new_c = rotate(ptext[i], key); //apply rotate function with plaintext character and key as arguments
            printf("%c", new_c);
        }
        printf("\n");
    }
}

bool only_digits(string s)
{
    int n = strlen(s);
    for (int i = 0; i < n; i++)
    {
        if (!isdigit(s[i])) //checks if given character in string provided is not digit
        {
            return false;
        }
    }
    return true;
}

char rotate(char c, int n)
{
    if islower(c) //if character is lower case, subtract 97 ('a') to standardize, then rotate according to key
    {
        char value = (((c - 'a') + n) % 26) + 'a';
        return value;
    }
    else if isupper(c) //if character is upper case, subtract 65 ('A') to standardize, then rotate according to key
    {
        char value = (((c - 'A') + n) % 26) + 'A';
        return value;
    }
    else
    {
        return c; //if character neither upper case or lower case, return character as is
    }
}

