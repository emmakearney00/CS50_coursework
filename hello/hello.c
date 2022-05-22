#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //create string name and prompt user for name,
    string name = get_string("What is your name? ");
    printf("hello, %s\n", name);
}

