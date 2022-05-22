#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    printf("Argc; %i\n", argc);
    for (int i = 0; i < argc; i++)
    {
        printf("i is %i: ", i);
        printf("%s\n", argv[i]);
    }
}