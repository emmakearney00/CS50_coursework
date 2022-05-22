#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What's your name? ");

    int i = 0;
    while (name[i] != '\0')
    {
        printf("%c", name[i]);
        i++;
    }
}