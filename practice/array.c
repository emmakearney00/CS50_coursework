#include <cs50.h>
#include <stdio.h>

//global variable
const int SIZE = 10;

int main(void)
{
    int array[SIZE];
    array[0] = 1;

    for(int i = 0; i < SIZE; i++)
    {
        array[i] = 2 * array[i - 1];
        printf("%i\n", array[i]);
    }
}

